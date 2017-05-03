/*
 * objwavefront_test.cc
 * Author: Samuel Vargas
 * Date: 04/29/2017
 */

#include "sol.h"

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "objwavefront.h"
#include <vector>
#include <iostream>

TEST_CASE("Load cube using ::ObjWavefront wrapper", "[3d]") {

   ObjWavefront cube("cube.obj", "models/suzanne");
   std::vector<tinyobj::index_t> indices = cube.indices();
   for (size_t i=0; i < indices.size(); ++i) {
      std::cout << indices[i].vertex_index << std::endl;
   }

}
