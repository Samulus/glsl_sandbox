/*
 * glsl_sandbox
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#include <SDL2/SDL.h>
#include <iostream>
#include "video.h"
#include "event.h"
#include "ui.h"
#include "error.h"

int main() {
   auto video = Video();
   auto event = Event();

   bool running = true;
   while (running) {
      while (event.hasEvent()) {
         auto sdlEvent = event.getEvent();
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
      video.present();
   }
   return 0; 
}
