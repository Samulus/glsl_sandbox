/*
 * glmodel.cc
 * Author: Samuel Vargas
 * Date: 05/03/2017
 *
 * Models are wrappers around tinyobj + friends
 * and represent a single object that can be rendered
 * onscreen
 */

#include "glmodel.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "util_lua.h"
#include "tiny_obj_loader.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLModel::GLModel() :
   position(glm::vec3(0,0,0)),
   rotation(glm::vec3(0,0,0)),
      scale(glm::vec3(1,1,1)) {
}

GLModel GLModel::loadFromWavefront(sol::table args) {

   Lua::throwIfMissingArgument<std::string>(args, "filename");
   Lua::throwIfMissingArgument<std::string>(args, "baseDir");

   auto baseDir  = args["baseDir"].get<std::string>();
   auto filename = args["filename"].get<std::string>();


   std::vector<tinyobj::shape_t> shapes;
   std::vector<tinyobj::material_t> mtls;

   tinyobj::attrib_t attribs;
   std::string error;
   bool ok = tinyobj::LoadObj(
         &attribs, &shapes, &mtls, &error,
         (baseDir + "/" + filename).c_str(),
         (baseDir + "/").c_str()
   );

   if (!ok && error.find("WARN: Material File")) {
      std::cerr << error << std::endl;
   }

   else if (!ok) {
      throw std::runtime_error(error);
   }

   return GLModel();
}

void render() {
}

glm::vec3 GLModel::getPosition() {
   return this->position;
}

glm::vec3 GLModel::getRotation() {
   return this->rotation;
}

glm::vec3 GLModel::getScale() {
   return this->scale;
}
