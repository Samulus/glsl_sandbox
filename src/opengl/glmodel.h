/*
 * glmodel.h
 * Author: Samuel Vargas
 * Date: 05/03/2017
 *
 * Models are wrappers around tinyobj + friends
 * and represent a single object that can be rendered
 * onscreen
 */

#pragma once
#include <iostream>
#include <vector>
#include <glew.h>
#include "vec3.hpp"
#include "sol.h"
#include "gpubuffer.h"
#include "glm.hpp"

class GLModel {
   private:
      std::vector<GLuint> indices;
      std::vector<GLuint> vertices;
      glm::mat4 trans;
      glm::vec3 position, rotation, scale;
      GPUBuffer gpuBuffer;
      GLModel(GPUBuffer gpuBuffer);
   public:
      static GLModel loadFromWavefront(sol::table);
      void bind();
      void unbind();
      void render();
      glm::vec3 getPosition() const;
      glm::vec3 getRotation() const;
      glm::vec3 getScale() const;
      glm::mat4 getTransformationMatrix() const;
};
