/*
 * video.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#pragma once

#include <SDL2/SDL.h>

class Video {
   private:
      SDL_Window* window;
      SDL_GLContext glContext;
      static Video* instance;
      Video();
   public:
      static Video& getInstance();
      void clear(float r, float g, float b);
      void setViewport();
      void present();
      int width() const;
      int height() const;
      SDL_Window* getWindowPtr() const;
};
