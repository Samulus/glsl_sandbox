/*
 * glshader.cc
 * Author: Samuel Vargas
 * Date: 05/07/2017
 */

#include <string>
#include <fstream>
#include <sstream>
#include <glew.h>
#include <SDL.h>
#include "glshader.h"
#include "util_lua.h"
#include "util.h"
#include "gml.hpp"
#include "gml_lua.h"

GLShader::GLShader(sol::table table) {
   Lua::throwIfMissingArgument<std::string>(table, "vertex");
   Lua::throwIfMissingArgument<std::string>(table, "fragment");

   std::string fragmentSrc, vertexSrc;
   std::stringstream buffer;
   std::ifstream tmp;

   /// load vertex shader source code
   std::string vertexPath = table["vertex"].get<std::string>();

   /// load vertex shader source code
   tmp.open(vertexPath);
   buffer << tmp.rdbuf();
   vertexSrc = buffer.str();
   buffer.clear();
   buffer.str(std::string());
   tmp.close();

   if (vertexSrc.length() == 0) {
      throw std::runtime_error(strFormat("Couldn't open file: %s\n",vertexPath.c_str()));
   }

   /// load fragment shader source code
   std::string fragmentPath = table["fragment"].get<std::string>();
   if (fragmentPath.length() == 0) {
      throw std::runtime_error(strFormat("Couldn't open file: %s\n",vertexPath.c_str()));
   }

   tmp.open(fragmentPath);
   buffer << tmp.rdbuf();
   fragmentSrc = buffer.str();
   tmp.close();

   // compile && link glsl program
   GLuint vertexShaderID   = GLShader::compile(GL_VERTEX_SHADER, vertexSrc);
   GLuint fragmentShaderID = GLShader::compile(GL_FRAGMENT_SHADER, fragmentSrc);
   this->programID         = GLShader::link(vertexShaderID, fragmentShaderID);

   /// cleanup
   glDeleteShader(vertexShaderID);
   glDeleteShader(fragmentShaderID);
}

GLuint GLShader::compile(GLint shaderType, const std::string& shaderSource) {
   assert(shaderType == GL_VERTEX_SHADER || GL_FRAGMENT_SHADER);
   GLuint shaderID = glCreateShader(shaderType);
   GLint len = 0;
   const char* ptr  = shaderSource.c_str();
   len = shaderSource.length();
   glShaderSource(shaderID, 1, &ptr, &len);
   glCompileShader(shaderID);
   glGetShaderiv(shaderID, GL_COMPILE_STATUS, &len);

   if (len == 0) {
      GLchar errLog[8192] = {0};
      glGetShaderInfoLog(shaderID, 8192, nullptr, errLog);
      throw std::runtime_error(
         strFormat("Malformed Shader Type: %s\n"
                   "GLSL Error: %s",
                   (shaderType == GL_VERTEX_SHADER) ? "Vertex" : "Fragment",
                   errLog)

         );
   }
   return shaderID;
}

GLuint GLShader::link(const GLuint& vertexShaderID, const GLuint& fragmentShaderID) {
   GLint vertexLen = 0, fragmentLen = 0;
   glGetShaderiv(vertexShaderID, GL_SHADER_SOURCE_LENGTH, &vertexLen);
   glGetShaderiv(vertexShaderID, GL_SHADER_SOURCE_LENGTH, &fragmentLen);
   assert(vertexLen > 0 && fragmentLen > 0);

   GLuint programID;
   programID = glCreateProgram();
   glAttachShader(programID, vertexShaderID);
   glAttachShader(programID, fragmentShaderID);
   glLinkProgram(programID);

   GLint programOK;
   glGetProgramiv(programID, GL_LINK_STATUS, &programOK);
   if (!programOK) {
      GLchar error[8192];
      glGetProgramInfoLog(programID, 8192, NULL, error);
      throw std::runtime_error(
            strFormat("GLSL Linking Error: %s\n", error)
      );
   }

   return programID;
}

void GLShader::upload(sol::table dataArray) {

   /*
    * Expected Input:
    * { name = 'position', vec3 = model:getPosition()},
    * { name = 'scale',    vec3 = model:getScale()},
    * { name = 'rotation', vec3 = model:getRotation()},
    */

   glUseProgram(this->programID);

   /// Argument sanity check
   dataArray.for_each([&] (sol::object key, sol::object value) {
      /// Keys should be integers because its an array
      if (key.get_type() != sol::type::number) {
         throw std::runtime_error(
               "This function expects an array of tables."
               "You passed in a non integer as a key"
         );
      }

      /// Values should be tables
      if (value.get_type() != sol::type::table) {
         throw std::runtime_error(
               "This function expects an array of tables."
               "You passed in a non table as a value"
         );
      }

      const auto subTable = dataArray[key];

      Lua::throwIfMissingArgument<std::string>(subTable, "name");
      Lua::throwIfMissingArgument<std::string>(subTable, "data");

      const auto name  = subTable["name"].get<std::string>();

      // TODO: This won't always be a mat4, it can be any type
      // and we need to switch and dynaical
      const gml::mat4 neo  = subTable["data"].get<gml::mat4>();

      // TODO: Do not assume every single uploaded matrix is a '4fv'
      const auto uniLocation = glGetUniformLocation(this->programID, name.c_str());
      glUniformMatrix4fv(uniLocation, 1, GL_FALSE, neo.data());

      /// Expect a name, size, and data in each table
   });
}
