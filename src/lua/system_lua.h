/*
* system_lua.h
* Author: Samuel Vargas
* Date: 09/12/2017
*/

#pragma once
#include "sol.h"

namespace SystemWrapper {
   void bind(sol::state&);
   std::string prependAbsolutePath(std::string);
}
