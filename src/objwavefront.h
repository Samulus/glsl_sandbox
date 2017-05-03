/*
 * objwavefront.h
 * Author: Samuel Vargas
 * Date: 05/02/2017
 */
#pragma once

#include "tiny_obj_loader.h"

class ObjWavefront {
   public:
      std::vector<tinyobj::shape_t> shapes;
      std::vector<tinyobj::material_t> mtls;
      tinyobj::attrib_t attribs;
   public:
      ObjWavefront(const std::string&, const std::string&);
      std::vector<tinyobj::index_t> indices();
};
