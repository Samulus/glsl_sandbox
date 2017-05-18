/*
 * sdl2_lua.cc
 * Author: Samuel Vargas
 * Date: 05/16/2017
 */

#include "sdl2_lua.h"
static const Video* video = nullptr;

void SDL2Wrapper::bind(sol::state& lua, const Video& v) {
   video = &v;
   lua.create_named_table("sdl2");
   auto sdl2 = lua["sdl2"];

   sdl2["setWindowSize"] = SDL2Wrapper::setWindowSize;
}

void SDL2Wrapper::setWindowSize(size_t x, size_t y, size_t width, size_t height) {
   SDL_SetWindowPosition(video->getWindowPtr(), x, y);
   SDL_SetWindowSize(video->getWindowPtr(), width, height);
}
