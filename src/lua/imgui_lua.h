/*
 * imgui_lua.h
 * Author: Samuel Vargas
 */

#pragma once
#include "video.h"
#include "sol.h"

namespace ImGuiWrapper {
   void bind(sol::state&, const Video&);
   /// Core
   static void newFrame();
   static bool begin(std::string, bool, int);
   static void end();
   static void render();
   /// Widgets
   static void text(std::string);
   static bool button(std::string, size_t, size_t);
   /// Settings
   static void setFontSize(size_t fontSize);
   static void enableSoftwareMouse();
   /// Misc
   static bool showTestWindow(bool);
};
