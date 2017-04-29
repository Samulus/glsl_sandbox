/*
 * gpubuffer_test.cc
 * Author: Samuel Vargas
 * Date: 04/18/2017
 */

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "../catch.hpp"
#include "gltype.h"
#include "gpubuffer.h"
#include <vector>

TEST_CASE("GPUBuffer", "[opengl]") {

   GIVEN ("GPUBuffer is simple quad") {
      size_t numPoints = 4;
      std::vector<GLVectorLen> vectorSizes = {GLVectorLen::TwoD};
      auto gpuBuffer = GPUBuffer(numPoints, vectorSizes);

      WHEN("(Too Many Verts) 9 elements are inserted 4 pairs of 2D vectors (8)") {
         std::vector<GLfloat> data = {1,2,3,4,5,6,7,8,9}; // '9' -> oops
         REQUIRE_THROWS_AS(gpuBuffer.insert(0, data), OpenGL::MismatchVertexCount);
      };

      WHEN("Too Few Verts) 7 elements are inserted instead of 4 pairs of 2D vectors(7)") {
         std::vector<GLfloat> data = {1,2,3,4,5,6,7}; // '7' -> oops
         REQUIRE_THROWS_AS(gpuBuffer.insert(0, data), OpenGL::MismatchVertexCount);
      };
   };

   GIVEN("GPUBuffer is quad with 3 attributes") {
      size_t numPoints = 4;
      std::vector<GLVectorLen> vectorSizes = {
         GLVectorLen::ThreeD, GLVectorLen::TwoD, GLVectorLen::ThreeD,
      };
      auto gpuBuffer = GPUBuffer(numPoints, vectorSizes);

      WHEN("Two attributes are correctly interleaved") {
         std::vector<GLfloat> position = {-1,-3,-5, -7,-9,-11, -13,-15,-17, -19,-21,-23};
         std::vector<GLfloat> normals  = {2,4,6, 8,10,12, 14,16,18, 20,22,24};
         gpuBuffer.insert(0, position);
         gpuBuffer.insert(2, normals);

         const GLfloat* interleaved = gpuBuffer.getInterleavedBuffer();
         REQUIRE(interleaved[0] == position[0]); 
         REQUIRE(interleaved[1] == position[1]);
         REQUIRE(interleaved[2] == position[2]);
         REQUIRE(interleaved[3] == 0);
         REQUIRE(interleaved[4] == 0);
         REQUIRE(interleaved[5] == normals[0]);
         REQUIRE(interleaved[6] == normals[1]);
         REQUIRE(interleaved[7] == normals[2]);

         REQUIRE(interleaved[8]  == position[3]); 
         REQUIRE(interleaved[9]  == position[4]);
         REQUIRE(interleaved[10] == position[5]);
         REQUIRE(interleaved[11] == 0);
         REQUIRE(interleaved[12] == 0);
         REQUIRE(interleaved[13] == normals[3]);
         REQUIRE(interleaved[14] == normals[4]);
         REQUIRE(interleaved[15] == normals[4]);
      };
   };
}
