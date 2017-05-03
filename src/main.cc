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
#include "imgui_lua.h"
#include "imgui_impl_sdl_gl3.h"
#include "util.h"

#include "sol.h"

int main() {
   auto video = Video();
   auto event = Event();

   /* 
    * Register Standard IO
    */
   sol::state lua;
   lua.open_libraries(sol::lib::base, sol::lib::package);
   ImGuiWrapper::bind(lua, video);

   std::string main_path = thisExePath() + "scripts/main.lua";

   try {
      lua.script_file(main_path);
   } catch (const std::exception& e) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
            "Missing scripts/main.lua",
            ("Please create the file :" + main_path).c_str(),
            video.getWindowPtr());
      return -1;
   }

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

      video.setViewport();
      video.clear(0.0,0.0,0.0);
      lua["render"]();
      video.present();

   }
   return 0; 
}
