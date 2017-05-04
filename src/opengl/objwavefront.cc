/*
 * objwavefront.cc
 * Author: Samuel Vargas
 * Date: 05/02/2017
 */

#define TINYOBJLOADER_IMPLEMENTATION

#include "objwavefront.h"
#include <iostream>

ObjWavefront::ObjWavefront(const std::string& path, const std::string& folder) {
   std::string error;
   bool ok = tinyobj::LoadObj(
         &(this->attribs), &(this->shapes), &(this->mtls), 
         &(error), 
         (folder + "/" + path).c_str(), 
         (folder + "/").c_str()
   );

   if (!ok || !error.empty()) {
      throw std::runtime_error(error);
   }
}

std::vector<tinyobj::index_t> ObjWavefront::indices() {
   return this->shapes[0].mesh.indices;
}
