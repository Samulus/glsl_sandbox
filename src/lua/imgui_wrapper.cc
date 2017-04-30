/*
 * imgui_wrapper.cc
 * Author: Samuel Vargas
 * Date: 04/30/2017
 */

#include "imgui.h"
#include "imgui_wrapper.h"
#include "imgui_impl_sdl_gl3.h"

const Video* ImGuiWrapper::video = nullptr;

void ImGuiWrapper::Begin(std::string title) {
   bool yes = true;
   ImGui_ImplSdlGL3_NewFrame(ImGuiWrapper::video->getWindowPtr());
   ImGui::Begin(title.c_str(), &yes, 0);
}

void ImGuiWrapper::End() {
   ImGui::End();
}

ImGuiWrapper::ImGuiWrapper(const Video& v) {
   ImGuiWrapper::video = &v;
}

void ImGuiWrapper::bind(sol::state& lua) {
   assert(video != nullptr);
   ImGui_ImplSdlGL3_Init(ImGuiWrapper::video->getWindowPtr());
   lua.create_named_table("imgui");
   lua["imgui"]["Begin"]          = ImGuiWrapper::Begin;
   lua["imgui"]["Text"]           = ImGui::Text;
   lua["imgui"]["SliderInt"]      = ImGui::SliderInt;
   lua["imgui"]["End"]            = ImGuiWrapper::End;
   lua["imgui"]["Render"]         = ImGui::Render;
}
