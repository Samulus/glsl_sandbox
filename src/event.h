/*
 * event.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 *
 * Event detection / retrevial for application
 */

#pragma once
#include <SDL2/SDL.h>
class Event {
   public:
      Event();
      bool hasEvent();
      SDL_Event getEvent();
};
