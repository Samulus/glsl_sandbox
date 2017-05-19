/*
 * script.cc
 * Author: Samuel Vargas
 * Date: 05/04/2017
 */

#include "script.h"
#include "imgui_lua.h"
#include "opengl_lua.h"
#include "sdl2_lua.h"

Script::Script(const std::string& path, const Video& video) {
   this->lua.open_libraries(
         sol::lib::io,
         sol::lib::base,
         sol::lib::package,
         sol::lib::string,
         sol::lib::math,
         sol::lib::table
   );

   ImGuiWrapper::bind(this->lua, video);
   OpenGLWrapper::bind(this->lua);
   SDL2Wrapper::bind(this->lua, video);

   this->lua.script_file(path);
}
