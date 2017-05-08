/*
 * glshader.h
 * Author: Samuel Vargas
 * Date: 05/07/2017
 */

#pragma once
#include <GL/glew.h>
#include "sol.h"

class GLShader {
   private:
      GLuint programID;
      static GLuint compile(GLint, const std::string&);
      static GLuint link(const GLuint& vertexShaderID, const GLuint& fragmentShaderID);
   public:
      GLShader(sol::table);
      void use();
};