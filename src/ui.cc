/*
 * ui.cc
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#include "ui.h"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <SDL2/SDL.h>

Window::Window(std::string title, const Video& video) : title(title), video(video) {
   //if (!Window::ImGui_ImplSdlGL3_Init_called) {
      ImGui_ImplSdlGL3_Init(video.getWindowPtr());
   //}
}

void Window::begin() {
   ImGui_ImplSdlGL3_NewFrame(video.getWindowPtr());
   ImGui::Begin(this->title.c_str(), &(this->visible), 0);
   /*
   if (this->activeWindow != nullptr) {
   }
   this->began = true;
   */
}

void Window::end() {
   ImGui::End();
}

void Window::text(std::string text) {
   ImGui::Text("%s", text.c_str());
}

void Window::slider(float& value) {
    ImGui::SliderFloat("Wrap width", &value, -20, 600, "%.0f");
}

void Window::render() {
   ImGui::Render();
}
