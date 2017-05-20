/*
 * gpubuffer.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 *
 * A wrapper around interleaving vectors of
 * vertex / normal / color / texture data into
 * single GLfloat[] for uploading to GPU.
 */

#pragma once

#include <glew.h>
#include <SDL_opengl.h>
#include <vector>
#include <iostream>

#include "sol.h"
#include "gltype.h"
#include "util.h"

class GPUBuffer {
   private:
      GLuint vao, vbo, ebo;
      bool vaoSet, vboSet, eboSet;
      std::vector<GLuint> indices;
      std::vector<GLVec> vectorLen;
      GLfloat* buffer;
      size_t numPoints;
   public:
      GPUBuffer(size_t vertexCount, std::vector<GLVec> vectorLen);
      void bind();
      void unbind();
      void insert(unsigned char position, std::vector<GLfloat> data);
      void setEBO(std::vector<GLuint> indices);
      const GLfloat* getInterleavedBuffer() const;
      void renderTri();
      void renderEBO();
      void renderLines();
   public: // sol2 / lua
      GPUBuffer(size_t numPoints, sol::table vectorLen);
      void insert(unsigned char, sol::table);
      void setEBO(sol::table);
};

namespace OpenGL {
   class BadVectorSize : public std::logic_error {
      public:
         BadVectorSize(int size) : std::logic_error(
               strFormat("Size: '%d' is an invalid size", size)) {}
   };

   class InvalidAttributePosition : public std::range_error {
      public:
         InvalidAttributePosition(unsigned char position, std::vector<GLfloat> data) :
            std::range_error(
                  strFormat("Position (%d) is out of bounds, expected [0 .. %d]",
                     position, data.size() - 1)){}
   };

   class MismatchVertexCount : public std::runtime_error {
      public:
         MismatchVertexCount(unsigned char position,
                             std::vector<GLVec> vectorLen,
                             size_t numPoints,
                             std::vector<GLfloat> newVertexData) :
            std::runtime_error(
                  strFormat("GPUBuffer has numPoints=%d and vectorLen[%d] = %d but "
                               "GPUBuffer::insert was called with %d elements"
                               "instead (expected %d elements instead)",
                               numPoints, position, vectorLen[position], newVertexData.size(),
                               vectorLen[position] * numPoints)) {}
      };
}
