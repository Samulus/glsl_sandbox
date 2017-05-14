/*
 * video.cc
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "video.h"
#include "error.h"

Video* Video::instance = nullptr;

Video& Video::getInstance() {
   if (instance == nullptr) {
      instance = new Video();
   }
   return *instance;
}

Video::Video() {
   SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");

   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
      throw SDL_Exception("Cannot init SDL2: " + std::string(SDL_GetError()));
   }

   SDL_bool yes = SDL_bool(true);
   SDL_CaptureMouse(yes);

   // setup window
   window = SDL_CreateWindow("glsl_sandbox",
       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
       1280, 720,
       SDL_WINDOW_RESIZABLE |
       SDL_WINDOW_SHOWN |
       SDL_WINDOW_ALLOW_HIGHDPI  |
       SDL_RENDERER_ACCELERATED  |
       SDL_RENDERER_PRESENTVSYNC |
       SDL_WINDOW_OPENGL);

   // setup sdl2 + opengl
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   glContext = SDL_GL_CreateContext(window);
   SDL_GL_MakeCurrent(window, &glContext);

   // setup viewport
   this->setViewport();

   // setup GLEW
   glewExperimental = 1;
   if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to setup GLEW\n");
      throw SDL_Exception("Failed to setup GLEW");
   }

   if (window == nullptr) {
      SDL_Log("Cannot create SDL2 Window: %s\n", SDL_GetError());
      throw SDL_Exception("Cannot init SDL2: " + std::string(SDL_GetError()));
   }
}

void Video::clear(float r, float g, float b) {
   glClearColor(r,g,b,1.0);
   glClear(GL_COLOR_BUFFER_BIT);
}

void Video::setViewport() {
   int width  = SDL_GetWindowSurface(window)->w;
   int height = SDL_GetWindowSurface(window)->h;
   glViewport(0, 0, width, height);
}

void Video::present() {
   SDL_GL_SwapWindow(window);
}

int Video::height() const {
   return SDL_GetWindowSurface(window)->h;
}

int Video::width() const {
   return SDL_GetWindowSurface(window)->w;
}

SDL_Window* Video::getWindowPtr() const {
   return this->window;
}
