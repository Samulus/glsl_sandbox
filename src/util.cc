/*
 * util.cc
 * Author: Samuel Vargas
 * Date: 04/30/2017
 */

#include "util.h"
#include <SDL.h>

// Guaranteed to return a '/' or '\'
// at end of path
std::string thisExePath() {
   char* p = SDL_GetBasePath();
   std::string output = std::string(p);
   free(p);
   return output;
}
