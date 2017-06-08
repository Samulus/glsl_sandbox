/*
 * gpubuffer.cc
 * Author: Samuel Vargas
 * Date: 04/18/2017
 *
 * A wrapper around interleaving vectors of
 * vertex / normal / color / texture data into
 * single GLfloat[] for uploading to GPU.
 *
 */

#include <iostream>
#include <cmath>

#include "gpubuffer.h"
#include "gltype.h"
#include "../error.h"
#include "util_lua.h"
#include "gml.hpp"

#include "SDL.h"

GPUBuffer::GPUBuffer(size_t numPoints, std::vector<GLVec> attribLen) :
   vao(0), vbo(0), ebo(0), buffer(std::vector<GLfloat>()),
   attribLen(attribLen), numPoints(numPoints) {

   unsigned long vertexSum = 0;
   for (unsigned int i=0; i < attribLen.size(); ++i) {
      vertexSum += attribLen[i];
   }

   if (vertexSum <= 0 || vertexSum > attribLen.size() * 4) {
      throw OpenGL::BadVectorSize(vertexSum);
   }

   this->numElements = numPoints * vertexSum;
   buffer.resize(this->numElements);

   glGenVertexArrays(1, &this->vao);
   glBindVertexArray(this->vao);
   glGenBuffers(1, &this->vbo);
   glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void GPUBuffer::insert(unsigned char position, std::vector<GLfloat> newVertexData) {
   glBindVertexArray(this->vao);
   glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

   // can't insert data into a non-existent position in the interleaved buffer
   if (position < 0 || position >= this->attribLen.size()) {
      throw OpenGL::InvalidAttributePosition(position, this->attribLen.size());
   }

   /// Where to start inserting this verex data
   /// in the interleaved buffer
   size_t start = 0;
   for (size_t i=0; i < position; ++i) {
      start += (int)attribLen[i];
   }

   size_t newVectorSize = (int)this->attribLen[position];
   size_t stride = 0;

   for (size_t i=0; i < this->attribLen.size(); ++i) {
      stride += (int)this->attribLen[i];
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

   this->finalize();
}

void GPUBuffer::finalize() {
   glBindVertexArray(this->vao);
   glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

   size_t stride =0;
   for (const auto& e : this->attribLen) {
      stride += (GLuint)e;
   }

   /// Upload vertex data to GPU
   glBufferData(GL_ARRAY_BUFFER, sizeof(this->buffer[0]) * buffer.size(), &this->buffer[0], GL_DYNAMIC_DRAW);

   /// Enable all the uploaded vertex attributes
   for (size_t i=0; i < this->attribLen.size(); ++i) {
      size_t start = 0;
      for (size_t j=0; j < i; ++j) {
         start += (GLuint)attribLen[j];
      }

      glEnableVertexAttribArray(i);
      glVertexAttribPointer(
         i,                                   /// Attribute Position
         (GLint)attribLen[i],                 /// Size of the element
         GL_FLOAT, GL_FALSE,                  /// Always insert floats, no normalization
         (GLint)(stride * sizeof(GLfloat)),   /// Set the stride
         (GLvoid*)(start * sizeof(GLfloat))   /// Set start position
      );
   }
}

void GPUBuffer::setEBO(std::vector<GLuint> indices) {
   this->indices = indices;
   glBindVertexArray(this->vao);
   glGenBuffers(1, &this->ebo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices[0]) * this->indices.size(),
                                          &this->indices[0], GL_DYNAMIC_DRAW);
}

void GPUBuffer::render() {
   glBindVertexArray(this->vao);
   if (ebo) {
      glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices[0]) * this->indices.size(),
                                             &this->indices[0], GL_DYNAMIC_DRAW);
      glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
   }
   else {
      glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
      glDrawArrays(GL_TRIANGLES, 0, this->numPoints);
   }
}

/// sol2 / lua
GPUBuffer::GPUBuffer(size_t numPoints, sol::table attribLen) :
   GPUBuffer::GPUBuffer(numPoints, tableToVector<GLVec>(attribLen)) {
}

void GPUBuffer::insert(unsigned char position, sol::table newVertexData) {
     this->insert(position, tableToVector<GLfloat>(newVertexData));
}

void GPUBuffer::setEBO(sol::table indices) {
   this->setEBO(tableToVector<GLuint>(indices));
}
