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
   imgui["newFrame"]              = ImGuiWrapper::newFrame;
   imgui["begin"]                 = ImGuiWrapper::begin;
   imgui["end"]                   = ImGuiWrapper::end;
   imgui["render"]                = ImGuiWrapper::render;
   /// Widgets
   imgui["text"]                  = ImGuiWrapper::text;
   imgui["button"]                = ImGuiWrapper::button;
   /// Settings
   imgui["setFontSize"]           = ImGuiWrapper::setFontSize;
   imgui["enableSoftwareMouse"]   = ImGuiWrapper::enableSoftwareMouse;
   /// Misc
   imgui["showTestWindow"]        = ImGuiWrapper::showTestWindow;
}

/// Core
void ImGuiWrapper::newFrame() {
   assert(video != nullptr && "Create an instance of ImGuiWrapper before calling this method");
   ImGui_ImplSdlGL3_NewFrame(video->getWindowPtr());
}

bool ImGuiWrapper::begin(std::string msg, bool collapse, int flags=0) {
   ImGui::Begin(msg.c_str(), &collapse, flags);
   return collapse;
}

void ImGuiWrapper::end() {
   ImGui::End();
}

void ImGuiWrapper::render() {
   ImGui::Render();
}


/// Widgets
void ImGuiWrapper::text(std::string msg) {
   ImGui::Text("%s", msg.c_str());
}

bool ImGuiWrapper::button(std::string msg, size_t width, size_t height) {
   return ImGui::Button(msg.c_str(), ImVec2(width, height));
}

/// Settings
void ImGuiWrapper::enableSoftwareMouse() {
   ImGui::GetIO().MouseDrawCursor = true;
}

void ImGuiWrapper::setFontSize(size_t fontSize) {
   ImGuiIO& io = ImGui::GetIO();
   io.Fonts->AddFontFromFileTTF((thisExePath() + "assets/roboto.ttf").c_str(), fontSize);
}

/// Misc
bool ImGuiWrapper::showTestWindow(bool open) {
   ImGui::ShowTestWindow(&open);
   return open;
}
