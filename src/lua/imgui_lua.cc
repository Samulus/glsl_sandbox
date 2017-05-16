/*
 * imgui_lua.cc
 * Author: Samuel Vargas
 * Date: 04/30/2017
 */

#include "imgui.h"
#include "imgui_lua.h"
#include "imgui_impl_sdl_gl3.h"
#include "sol.h"
#include "util.h"
#include <functional>
#include <iostream>

static const Video* video = nullptr;

void ImGuiWrapper::bind(sol::state& lua, const Video& v) {
   video = &v;
   ImGui_ImplSdlGL3_Init(video->getWindowPtr());
   lua.create_named_table("imgui");
   auto imgui = lua["imgui"];


   /// Core
   imgui["NewFrame"]              = ImGuiWrapper::NewFrame;
   imgui["Begin"]                 = ImGuiWrapper::Begin;
   imgui["End"]                   = ImGuiWrapper::End;
   imgui["Render"]                = ImGuiWrapper::Render;
   /// Widgets
   imgui["Text"]                  = ImGuiWrapper::Text;
   imgui["Button"]                = ImGuiWrapper::Button;
   /// Settings
   imgui["SetFontSize"]           = ImGuiWrapper::SetFontSize;
   imgui["EnableSoftwareMouse"]   = ImGuiWrapper::EnableSoftwareMouse;
   /// Misc
   imgui["ShowTestWindow"]        = ImGuiWrapper::ShowTestWindow;
}

/// Core
void ImGuiWrapper::NewFrame() {
   assert(video != nullptr && "Create an instance of ImGuiWrapper before calling this method");
   ImGui_ImplSdlGL3_NewFrame(video->getWindowPtr());
}

bool ImGuiWrapper::Begin(std::string msg, bool collapse, int flags=0) {
   ImGui::Begin(msg.c_str(), &collapse, flags);
   return collapse;
}

void ImGuiWrapper::End() {
   ImGui::End();
}

void ImGuiWrapper::Render() {
   ImGui::Render();
}


/// Widgets
void ImGuiWrapper::Text(std::string msg) {
   ImGui::Text("%s", msg.c_str());
}

bool ImGuiWrapper::Button(std::string msg, size_t width, size_t height) {
   return ImGui::Button(msg.c_str(), ImVec2(width, height));
}

/// Settings
void ImGuiWrapper::EnableSoftwareMouse() {
   ImGui::GetIO().MouseDrawCursor = true;
}

void ImGuiWrapper::SetFontSize(size_t fontSize) {
   ImGuiIO& io = ImGui::GetIO();
   io.Fonts->AddFontFromFileTTF((thisExePath() + "assets/roboto.ttf").c_str(), fontSize);
}

/// Misc
bool ImGuiWrapper::ShowTestWindow(bool open) {
   ImGui::ShowTestWindow(&open);
   return open;
}
