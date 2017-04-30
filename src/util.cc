/*
 * util.cc
 * Author: Samuel Vargas
 * Date: 04/30/2017
 */

#include "util.h"

/// Return absolute path of binary
std::string thisExePath() {
   char* path = nullptr;
   int dirname_len;

   // get length of exe path
   int len = wai_getExecutablePath(NULL, 0, &dirname_len);
   assert(len > 0);
   path = (char*)calloc(len+1, sizeof(char));

   // store exe path into path pointer
   wai_getExecutablePath(path, len, &dirname_len);
   std::string output = std::string(path);
   free(path);

   return output;
}
