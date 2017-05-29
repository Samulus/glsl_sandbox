/*
 * imgui_lua.h
 * Author: Samuel Vargas
 */

#pragma once
#include "video.h"
#include "sol.h"

namespace ImGuiWrapper {
   void bind(sol::state&, const Video&);
};
