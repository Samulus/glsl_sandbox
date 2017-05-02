/*
 * glsl_sandbox
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#include <cstdlib>
#include <cstdio>

#include <SDL2/SDL.h>
#include <iostream>
#include "video.h"
#include "event.h"
#include "ui.h"
#include "error.h"
#include "imgui_wrapper.h"
#include "util.h"

#include "sol.h"

int main() {
   auto video = Video();
   auto event = Event();
   auto imguiWrapper = ImGuiWrapper(video);

   sol::state lua;
   lua.open_libraries(sol::lib::base, sol::lib::package);
   imguiWrapper.bind(lua);
   lua.script_file("./scripts/main.lua");

   bool running = true;
   while (running) {
      while (event.hasEvent()) {
         SDL_Event sdlEvent = event.getEvent();
         ImGui_ImplSdlGL3_ProcessEvent(&sdlEvent);
         switch (sdlEvent.type) {
            case SDL_QUIT:
               running = false;
               break;
            case SDL_KEYDOWN:
               break;
            case SDL_WINDOWEVENT:
               video.setViewport();
               break;
         }
      }

      video.clear(0.0,0.0,0.0);
      lua["render"]();
      video.present();

   }
   return 0; 
}
