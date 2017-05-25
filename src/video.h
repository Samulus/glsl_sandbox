/*
 * video.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#pragma once

#include <SDL.h>

class Video {
   private:
      SDL_Window* window;
      SDL_GLContext glContext;
      static Video* instance;
      Video();
   public:
      static Video& getInstance();
      void clear(float r, float g, float b) const;
      void setViewport() const;
      void present() const;
      int width() const;
      int height() const;
      SDL_Window* getWindowPtr() const;
};
