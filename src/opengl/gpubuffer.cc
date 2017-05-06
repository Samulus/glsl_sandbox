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

GPUBuffer::GPUBuffer(size_t numPoints, std::vector<GLVectorLen> vectorLen) {
   this->numPoints = numPoints;
   this->vectorLen = vectorLen;
   this->vaoSet = false;
   this->vboSet = false;
   this->eboSet = false;

   unsigned long vertexSum = 0;
   for (unsigned int i=0; i < vectorLen.size(); ++i) {
      vertexSum += vectorLen[i];
   }

   if (vertexSum <= 0 || vertexSum > vectorLen.size() * 4) {
      throw OpenGL::BadVectorSize(vertexSum);
   }

   buffer = new GLfloat[numPoints * vertexSum]();
}

void GPUBuffer::bind() {
   if (!this->vaoSet) {
      this->vaoSet = true;
      glGenVertexArrays(1, &this->vao);
   }
   glBindVertexArray(this->vao);
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

const GLfloat* GPUBuffer::getInterleavedBuffer() const {
   return this->buffer;
}

/// sol2 / lua
GPUBuffer::GPUBuffer(size_t numPoints, sol::table vectorLen) :
   GPUBuffer::GPUBuffer(numPoints, tableToVector<GLVectorLen>(vectorLen)) {
}

void GPUBuffer::insert(unsigned char position, sol::table newVertexData) {
     this->insert(position, tableToVector<GLfloat>(newVertexData));
}

void GPUBuffer::setEBO(sol::table indices) {
   this->setEBO(tableToVector<GLuint>(indices));
}
