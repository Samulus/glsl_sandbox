/*
 * glsl_sandbox
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#include <cstdlib>
#include <cstdio>

#include <SDL.h>
#include <iostream>
#include "video.h"
#include "event.h"
#include "error.h"
#include "script.h"
#include "imgui_lua.h"
#include "imgui_impl_sdl_gl3.h"
#include "util.h"

#include "sol.h"

int main() {
   auto video  = Video::getInstance();
   auto event  = Event();
   auto script = Script(
         thisExePath() + "scripts/main.lua", video
   );

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
      script.fn("render");
   }

   return 0;
}
