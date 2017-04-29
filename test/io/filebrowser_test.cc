/*
 * filebrowser_test.cc
 * Author: Samuel Vargas
 */

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "filebrowser.h"
#include <iostream>

TEST_CASE("FileBrowser::ls()", "[io]") {
   GIVEN ("Alphabet path") {
      auto fb = FileBrowser("/home/sam/music");
      auto results = fb.ls();
      for (unsigned int i=0; i < results.size(); ++i) {
         std::cout << results[i] << std::endl;
      }
   }
}
