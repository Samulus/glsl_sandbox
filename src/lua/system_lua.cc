/*
 * system_lua.cc
 * Author: Samuel Vargas
 * Date: 09/12/2017
 */

#include "system_lua.h"
#include "util.h"

void SystemWrapper::bind(sol::state& lua) {
   lua.create_named_table("system");
   auto system = lua["system"];
   system["prependAbsolutePath"] = [](std::string path) {
	   return SystemWrapper::prependAbsolutePath(path);
   };
}

std::string SystemWrapper::prependAbsolutePath(std::string path) {
	return thisExePath() + "Scripts\\" + path;
}