/*
 * opengl_lua.h
 * Author: Samuel Vargas
 */

#pragma once
#include "sol.h"
#include "gpubuffer.h"

namespace OpenGL_Lua {
   void bind(sol::state&);
   void bindGL3Enums(sol::table&);
   void bindCoreEnums(sol::table&);
   void bindFboEnums(sol::table&);
}
