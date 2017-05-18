/*
 * sdl2_lua.h
 * Author: Samuel Vargas
 * Date: 05/16/2017
 */

#pragma once
#include "sol.h"
#include "video.h"

namespace SDL2Wrapper {
   void bind(sol::state&, const Video&);
   void setWindowSize(size_t, size_t, size_t, size_t);
}
