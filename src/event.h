/*
 * event.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#pragma once
class Event {
   public:
      Event();
      bool hasEvent();
      SDL_Event getEvent();
};
