/*
 * gmlodel.cc
 * Author: Samuel Vargas
 * Date: 05/03/2017
 *
 * Models are wrappers around tinyobj + friends
 * and represent a single object that can be rendered
 * onscreen
 */

#define TINYOBJLOADER_IMPLEMENTATION
#include <SDL.h>
#include "util_lua.h"
#include "tiny_obj_loader.h"
#include "gpubuffer.h"
#include "gml.hpp"
#include "glmodel.h"

GLModel::GLModel(GPUBuffer gpuBuffer) :
   trans(gml::mat4(1)),
   position(gml::vec3(0,0,0)),
   rotation(gml::vec3(0,0,0)),
      scale(gml::vec3(1,1,1)),
   gpuBuffer(gpuBuffer) {
}


GLModel GLModel::loadFromRawArray(sol::table args) {
   auto vertices = tableToVector<GLfloat>(args["vertices"]);
   //auto normals  = tableToVector<GLfloat>(args["normals"]);

   auto gpuBuffer = GPUBuffer(vertices.size() / 3,
         std::vector<GLVec>{GLVec::Vec3});

   gpuBuffer.insert(0, vertices);

   return GLModel(gpuBuffer);
}

/*
 * Load a Wavefront .obj file into the application
 * Right now we operate under the assumption that:
 *    - Each obj has an indices list (no triangulation is performed)
 *    - Each obj has a position list (vec3: xyz)
 *    - Each obj has normals list (vec3: xyz)
 *    - Each obj has a color list
 */

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

   /// Forward warning about missing ".mtl" file to users
   if (!ok && error.find("WARN: Material File")) {
      std::cerr << error << std::endl;
   }

   else if (!ok) {
      throw std::runtime_error(error);
   }

   /// Snatch indices from tinyobjloader
   /// and store them in the internal GPUBuffer
   /// for indexed rendering later on
   std::vector<GLuint> indices;
   for (const auto& i : shapes[0].mesh.indices) {
      indices.push_back(i.vertex_index);
   }

   /// Load required vertex attributes into internal gpubuffer
   /// (position, color, normal)
   auto gpuBuffer = GPUBuffer(
         attribs.vertices.size() / 3,
         std::vector<GLVec> { GLVec::Vec3, GLVec::Vec3 }
   );

   gpuBuffer.insert(0, attribs.vertices);   /// Position
   gpuBuffer.insert(1, attribs.normals);    /// Normals
   gpuBuffer.setEBO(indices);

   return GLModel(gpuBuffer);
}

void GLModel::render() {
   this->gpuBuffer.render();
}

gml::vec3 GLModel::getPosition() const {
   return this->position;
}

gml::vec3 GLModel::getRotation() const {
   return this->rotation;
}

gml::vec3 GLModel::getScale() const {
   return this->scale;
}

void GLModel::setScale(gml::vec3 factor) {
   this->trans *= gml::scale(factor);
}

gml::mat4 GLModel::getTransformationMatrix() const {
   return this->trans;
}
