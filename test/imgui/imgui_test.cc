/*
 * imgui_test.cc
 * Author: Samuel Vargas
 */

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "video.h"
#include "event.h"
#include "imgui.h"
#include "ui.h"
#include "imgui_impl_sdl_gl3.h"
#include <iostream>

TEST_CASE("Basic IMGUI Window", "[imgui test]") {

   auto video = Video();
   auto event = Event();
   auto window = Window(std::string("Example Window"), video);
   bool running = true;

   float x = 42;

   while (running) {
      while (event.hasEvent()) {
         SDL_Event sdlEvent = event.getEvent();
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
      video.clear(0, 0, 0);
      window.begin();
      window.text(std::string("Ayy Lmao!"));
      window.slider(x);
      window.end();
      window.render();
      video.present();
   }
}
