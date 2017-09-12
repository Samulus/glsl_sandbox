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
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
      throw SDL_Exception("Cannot init SDL2: " + std::string(SDL_GetError()));
   }

   SDL_bool yes = SDL_bool(true);
   SDL_CaptureMouse(yes);
   glewExperimental = GL_TRUE;
   // setup window
   window = SDL_CreateWindow("glsl_sandbox",
       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
       1920, 1080,
       SDL_WINDOW_RESIZABLE |
       SDL_WINDOW_SHOWN |
       SDL_WINDOW_ALLOW_HIGHDPI  |
       SDL_RENDERER_ACCELERATED  |
       SDL_RENDERER_PRESENTVSYNC |
       SDL_WINDOW_OPENGL);

   SDL_assert(window != false);

   if (!window) {
      throw std::runtime_error(std::string(SDL_GetError()));
   }

   // setup sdl2 + opengl
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   glContext = SDL_GL_CreateContext(window);
   


   // setup GLEW
   glewExperimental = 1;
   const auto glewOK = glewInit();
   if (glewOK != GLEW_OK) {
      fprintf(stderr, "Failed to setup GLEW: %s\n", glewGetErrorString(glewOK));
      throw SDL_Exception("Failed to setup GLEW");
   }

   if (window == nullptr) {
      SDL_Log("Cannot create SDL2 Window: %s\n", SDL_GetError());
      throw SDL_Exception("Cannot init SDL2: " + std::string(SDL_GetError()));
   }
   /*
   const auto okMakeCurrent = SDL_GL_MakeCurrent(window, &glContext);
   if (okMakeCurrent < 0) {
	   SDL_Log("Cannot create make SDL2 Window the OpenGL context: %s\n", SDL_GetError());  
   }
   */
   // setup viewport
   this->setViewport();
}

void Video::clear(float r, float g, float b) const {
   glClearColor(r,g,b,1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Video::setViewport() const {
   glViewport(0, 0, width(), height());
}

void Video::present() const {
   SDL_GL_SwapWindow(window);
}

int Video::height() const {
   int height, dontcare;
   SDL_GL_GetDrawableSize(this->window, &dontcare, &height);
   return height;
}

int Video::width() const {
   int width, dontcare;
   SDL_GL_GetDrawableSize(this->window, &width, &dontcare);
   return width;
}

SDL_Window* Video::getWindowPtr() const {
   return this->window;
}
