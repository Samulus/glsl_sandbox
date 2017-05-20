/*
 * tinyobjloader_test.cc
 * Author: Samuel Vargas
 * Date: 04/29/2017
 */

#include "tiny_obj_loader.h"

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "util.h"
#include "SDL.h"

TEST_CASE("", "[tinyobjloader]") {

   std::string path(thisExePath() + "models/suzanne/suzanne.obj");

   std::vector<tinyobj::shape_t> shapes;
   std::vector<tinyobj::material_t> mtls;

   tinyobj::attrib_t attribs;
   std::string error;
   bool ok = tinyobj::LoadObj(
         &attribs, &shapes, &mtls, &error,
         path.c_str(),
         nullptr
   );

   SDL_Log("shapes.size() == %lu\n", shapes.size());
   SDL_Log("shapes.size() == %lu\n", attribs.vertices.size());

};
