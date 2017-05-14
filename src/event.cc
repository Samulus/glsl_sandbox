/*
 * event.cc
 * Author: Samuel Vargas
 * 05/03/2017
 *
 * Event detection / retrevial for application
 */

#include <SDL.h>
#include "event.h"
#include "error.h"

Event::Event() {
   if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0) {
      throw SDL_Exception("Cannot init SDL2: " + std::string(SDL_GetError()));
   }
}

bool Event::hasEvent() {
   SDL_PumpEvents();
   SDL_Event sdlEvent;
   int results = SDL_PeepEvents(&sdlEvent, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
   return results > 0;
}

SDL_Event Event::getEvent() {
   SDL_Event sdlEvent;
   SDL_PeepEvents(&sdlEvent, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
   return sdlEvent;
}
