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
#include "tiny_obj_loader.h"


GLModel::GLModel() {}

GLModel GLModel::loadFromWavefront(std::string obj_path, std::string folder) {

   std::vector<tinyobj::shape_t> shapes;
   std::vector<tinyobj::material_t> mtls;
   tinyobj::attrib_t attribs;
   std::string error;
   bool ok = tinyobj::LoadObj(
         &attribs, &shapes, &mtls, &error,
         (folder + "/" + obj_path).c_str(),
         (folder + "/").c_str()
   );

   if (!ok || !error.empty()) {
      throw std::runtime_error(error);
   }

   return GLModel();
}
