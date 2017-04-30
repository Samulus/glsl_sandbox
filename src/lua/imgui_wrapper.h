/*
 * imgui_wrapper.h
 * Author: Samuel Vargas
 */

#pragma once
#include "video.h"
#include "sol.h"

class ImGuiWrapper {
   private:
      static const Video* video;
   public:
      ImGuiWrapper(const Video&);
      void bind(sol::state&);
   public:
      static void Begin(std::string);
      static void End();
};

