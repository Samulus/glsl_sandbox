/*
 * gmlodel.h
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
#include "sol.h"
#include "gpubuffer.h"
#include "gml.hpp"

class GLModel {
   private:
      std::vector<GLuint> indices;
      std::vector<GLuint> vertices;
      gml::mat4 trans;
      gml::vec3 position, rotation, scale;
      GPUBuffer gpuBuffer;
      GLModel(GPUBuffer gpuBuffer);
   public:
      static GLModel loadFromWavefront(sol::table);
      static GLModel loadFromRawArray(sol::table);
      void bind();
      void unbind();
      void render();
      gml::vec3 getPosition() const;
      gml::vec3 getRotation() const;
      gml::vec3 getScale() const;
      void setScale(gml::vec3);
      gml::mat4  getTransformationMatrix() const;
};
