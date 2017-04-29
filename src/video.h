/*
 * video.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#pragma once

#include <SDL2/SDL.h>

class Video {
   private:
      SDL_Window* window = nullptr;
      SDL_GLContext glContext = nullptr;
   public:
      Video();
      void init(bool& hasError);
      void clear(float r, float g, float b);
      void setViewport();
      void present();
      int width() const;
      int height() const;
      SDL_Window* getWindowPtr() const;
};
