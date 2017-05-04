/*
 * script.cc
 * Author: Samuel Vargas
 * Date: 05/04/2017
 */

#include "script.h"
#include "imgui_lua.h"

Script::Script(const std::string& path, const Video& video) {
   this->lua.script_file(path);
   this->lua.open_libraries(sol::lib::base, sol::lib::package);
   ImGuiWrapper::bind(this->lua, video);
}
