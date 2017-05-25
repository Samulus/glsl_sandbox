/*
 * gpubuffer.cc
 * Author: Samuel Vargas
 * Date: 04/18/2017
 *
 * A wrapper around interleaving vectors of
 * vertex / normal / color / texture data into
 * single GLfloat[] for uploading to GPU.
 */

#include <iostream>
#include <cmath>

#include "gpubuffer.h"
#include "gltype.h"
#include "../error.h"
#include "util_lua.h"
#include "glm.hpp"

#include "SDL.h"

GPUBuffer::GPUBuffer(size_t numPoints, std::vector<GLVec> vectorLen) :
   vao(0), vbo(0), ebo(0),
   vaoSet(false), vboSet(false), eboSet(false),
   vectorLen(vectorLen), numPoints(numPoints) {

   unsigned long vertexSum = 0;
   for (unsigned int i=0; i < vectorLen.size(); ++i) {
      vertexSum += vectorLen[i];
   }

   if (vertexSum <= 0 || vertexSum > vectorLen.size() * 4) {
      throw OpenGL::BadVectorSize(vertexSum);
   }

   this->numElements = numPoints * vertexSum;
   buffer = new GLfloat[this->numElements];
}

void GPUBuffer::bind() {
   /// Init and bind the VAO

   if (!this->vaoSet) {
      this->vaoSet = true;
      glGenVertexArrays(1, &this->vao);
   }

   glBindVertexArray(this->vao);

   /// For each vertex attribute enabled
   /// in this gpuBuffer instance:
   /// - Bind the VBO
   /// - Enable each vertex  position
   /// - Upload it to the GPU

   if (!this->vboSet) {
      this->vboSet = true;
      glGenBuffers(1, &this->vbo);
   }

   glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

   size_t stride =0;
   for (const auto& e : this->vectorLen) {
      stride += (GLuint)e;
   }

   for (size_t i=0; i < this->vectorLen.size(); ++i) {

      size_t start = 0;
      for (size_t j=0; j < i; ++j) {
         start += (GLuint)vectorLen[j];
      }

      glEnableVertexAttribArray(i);

      glVertexAttribPointer(
         i,                                   /// Attribute Position
         (GLint)vectorLen[i],                 /// Size of the element
         GL_FLOAT, GL_FALSE,                  /// Always insert floats, no normalization
         (GLuint)(stride * sizeof(GLfloat)),  /// Set the stride
         (GLvoid*)(start * sizeof(GLfloat))   /// Set start position
      );
   }

   glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->numElements, buffer, GL_STATIC_DRAW);

   if (this->eboSet) {
      glGenBuffers(1, &this->ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

      /// Copy data from vector to array so OpenGL will
      /// be happy. TODO: Avoid using the vector in
      /// the first place.
      this->indices_ptr = new GLuint[this->indices.size()];
      for (size_t i=0; i < this->indices.size(); ++i) {
         this->indices_ptr[i] = this->indices[i];
      }

      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   sizeof(this->indices_ptr[0]) * this->indices.size(),
                   this->indices_ptr, GL_STATIC_DRAW);
      this->eboSet = true;
   }
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}

void GPUBuffer::unbind() {
   glBindVertexArray(0);
}

void GPUBuffer::insert(unsigned char position, std::vector<GLfloat> newVertexData) {
   // can't insert data into a non-existent position in the interleaved buffer
   if (position < 0 || position >= this->vectorLen.size()) {
      throw OpenGL::InvalidAttributePosition(position, newVertexData);
   }

   // not enough vertices passed into function
   // e.g they're trying to insert data for position=1 which is a vector3
   // but their data is missing an element or is formatted as a vector 2
   if (newVertexData.size() != numPoints * (int)this->vectorLen[position]) {
      throw OpenGL::MismatchVertexCount(position, vectorLen, numPoints, newVertexData);
   }

   size_t start = 0;
   for (size_t i=0; i < position; ++i) {
      start += (int)vectorLen[i];
   }

   size_t newVectorSize = (int)this->vectorLen[position];
   size_t stride = 0;

   for (size_t i=0; i < this->vectorLen.size(); ++i) {
      stride += (int)this->vectorLen[i];
   }
   size_t stop = (size_t)(newVertexData.size() / newVectorSize);

   /// interleave the GPUBuffer!
   size_t i=start, k=0, b=0;
   for (; k < stop; ++k) {
      for (size_t o=i, n=b; o < i+newVectorSize; ++o, ++n) {
         this->buffer[o] = newVertexData[n];
      }
      i += stride;
      b += newVectorSize;
   }
}

void GPUBuffer::setEBO(std::vector<GLuint> indices) {
   this->indices = indices;
}

void GPUBuffer::renderEBO() {
   glDrawArrays(GL_TRIANGLES, 0, this->numPoints);
   //glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, NULL);
}

const GLfloat* GPUBuffer::getInterleavedBuffer() const {
   return this->buffer;
}

/// sol2 / lua
GPUBuffer::GPUBuffer(size_t numPoints, sol::table vectorLen) :
   GPUBuffer::GPUBuffer(numPoints, tableToVector<GLVec>(vectorLen)) {
}

void GPUBuffer::insert(unsigned char position, sol::table newVertexData) {
     this->insert(position, tableToVector<GLfloat>(newVertexData));
}

void GPUBuffer::setEBO(sol::table indices) {
   this->setEBO(tableToVector<GLuint>(indices));
}
