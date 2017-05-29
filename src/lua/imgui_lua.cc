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
   imgui["newFrame"]              = [] {
                                       assert(video != nullptr &&
                                             "Call ImGuiWrapper::bind() first");
                                       ImGui_ImplSdlGL3_NewFrame(video->getWindowPtr());
                                    };

   imgui["begin"]                 = [] (std::string msg, bool collapse, int flags=0) {
                                       auto result = ImGui::Begin(msg.c_str(), &collapse, flags);
                                       return std::make_tuple(result, collapse);
                                    };

   imgui["end"]                   = &ImGui::End;
   imgui["render"]                = &ImGui::Render;

   /// Main Menus
   imgui["beginMainMenuBar"]      = &ImGui::BeginMainMenuBar;
   imgui["beginMenu"]             = [] (std::string label) {
                                       return ImGui::BeginMenu(label.c_str(), true);
                                    };

   imgui["endMenu"]               = &ImGui::EndMenu;
   imgui["endMainMenuBar"]        = &ImGui::EndMainMenuBar;

   /// Menu Items
   imgui["menuItem"]              = [] (std::string label, bool selected, bool enabled) {
                                       return ImGui::MenuItem(label.c_str(), NULL, selected, enabled);
                                    };

   /// Widgets
   imgui["text"]                  = [] (std::string text) {
                                       ImGui::Text("%s", text.c_str());
                                    };

   imgui["button"]                = [] (std::string text, size_t w, size_t h) {
                                       return ImGui::Button(text.c_str(), ImVec2(w, h));
                                    };
   /// Settings
   imgui["setFontSize"]           = [] (size_t fontSize) {
                                       ImGuiIO& io = ImGui::GetIO();
                                       io.Fonts->AddFontFromFileTTF((thisExePath() + "assets/roboto.ttf").c_str(),
                                             fontSize);
                                    };

   imgui["enableSoftwareMouse"]   = [] {
                                       ImGui::GetIO().MouseDrawCursor = true;
                                    };

   /// Misc
   imgui["showTestWindow"]        = [] (bool open) {
                                       ImGui::ShowTestWindow(&open);
                                       return open;
                                    };
}
