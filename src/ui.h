/*
 * ui.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#pragma once

#include <SDL2/SDL_video.h>
#include <iostream>
#include "video.h"

class Window {
   private:
      static bool ImGui_ImplSdlGL3_Init_called;
      static Window* activeWindow;
      std::string title;
      const Video& video;
      bool began;
      bool visible;
   public:
      Window(std::string title, const Video& video);
      /// core
      void begin();
      void end();
      void render();
      /// widgets
      void text(std::string text);
      void slider(float& value);
};

/*
namespace Ui {
   class ForgotToCallBegin : public std::logic_error {
      std::logic_error(
         strFormat("Window @ %p is active but 
                        "but GPUBuffer::insert was called with %d elements"
                        "instead (expected %d elements instead)",
                        numPoints, position, vectorLen[position], newVertexData.size(),
                        vectorLen[position] * numPoints)) {}
   };
   class ForgotToCallEnd : public std::logic_error {
   }
*/
