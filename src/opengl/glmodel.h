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

class GLModel {
   private:
      std::vector<GLuint> indices;
      std::vector<GLuint> vertices;
      glm::vec3 position, rotation, scale;
      GLModel();
   public:
      static GLModel loadFromWavefront(sol::table);
      void bind();
      void render();
      glm::vec3 getPosition();
      glm::vec3 getRotation();
      glm::vec3 getScale();
};
