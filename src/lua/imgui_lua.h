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
   static void NewFrame();
   static bool Begin(std::string, bool, int);
   static void End();
   static void Render();
   /// Widgets
   static void Text(std::string);
   static bool Button(std::string, size_t, size_t);
   /// Settings
   static void SetFontSize(size_t fontSize);
   static void EnableSoftwareMouse();
   /// Misc
   static bool ShowTestWindow(bool);
};
