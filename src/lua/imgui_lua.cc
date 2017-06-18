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
#include <cassert>

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

   imgui["begin"]                 = sol::overload(
                                       [] (std::string msg, bool collapse, int flags=0) {
                                          auto result = ImGui::Begin(msg.c_str(), &collapse, flags);
                                          return std::make_tuple(result, collapse);
                                       },

                                       [] (std::string msg) {
                                          bool collapse = true;
                                          auto result = ImGui::Begin(msg.c_str(), &collapse, 0);
                                          return std::make_tuple(result, collapse);
                                       }
                                    );

   imgui["_end"]                  = &ImGui::End;
   imgui["render"]                = &ImGui::Render;

   /// Main Menus
   imgui["beginMainMenuBar"]      = &ImGui::BeginMainMenuBar;
   imgui["beginMenu"]             = [] (std::string label) {
                                       return ImGui::BeginMenu(label.c_str(), true);
                                    };

   imgui["endMenu"]               = &ImGui::EndMenu;
   imgui["endMainMenuBar"]        = &ImGui::EndMainMenuBar;

   /// Menu Items
   imgui["menuItem"]              = sol::overload(
                                    [] (std::string label) {
                                       return ImGui::MenuItem(label.c_str(), NULL, true, true);
                                    },

                                    [] (std::string label, bool selected, bool enabled) {
                                       return ImGui::MenuItem(label.c_str(), NULL, selected, enabled);
                                    });

   /// Widgets
   imgui["text"]                  = [] (std::string text) {
                                       ImGui::Text("%s", text.c_str());
                                    };

   imgui["button"]                = sol::overload(
                                       [] (std::string text, size_t w, size_t h) {
                                          return ImGui::Button(text.c_str(), ImVec2(w, h));
                                       },
                                       [] (std::string text) {
                                          return ImGui::SmallButton(text.c_str());
                                       }
                                    );

   /// Grouping
   imgui["beginGroup"]            = &ImGui::BeginGroup;
   imgui["endGroup"]              = &ImGui::EndGroup;

   /// Layout
   imgui["newLine"]               = [] {
                                       ImGui::NewLine();
                                    };
   imgui["columns"]               = [] (size_t n, std::string title, bool border = false) {
                                       ImGui::Columns(n, title.c_str(), border);
                                    };

   imgui["pushItemWidth"]         = [] (float width) {
                                       ImGui::PushItemWidth(width);
                                    };

   imgui["popItemWidth"]          = &ImGui::PopItemWidth;


   imgui["separator"]             = &ImGui::Separator;
   imgui["sameLine"]              = sol::overload(
                                       [] () {
                                          ImGui::SameLine(0,0);
                                       },

                                       [] (float pos_x, float spacing_w) {
                                          ImGui::SameLine(pos_x,spacing_w);
                                       }
                                    );

   imgui["treeNode"]              = [] (std::string text) {
                                       ImGui::TreeNode(text.c_str());
                                    };

   imgui["treePop"]               = &ImGui::TreePop;

   /// ID Management
   imgui["pushID"]                = [] (size_t id) {
                                       ImGui::PushID(id);
                                    };

   imgui["popID"]                 =  &ImGui::PopID;

   /// Input
   imgui["inputFloat"]            = sol::overload(
                                       [] (std::string text, float* f)  {
                                          auto result = ImGui::InputFloat(text.c_str(), f, 0, 3, 4, 4);
                                          return std::make_tuple(result, *f);
                                       },
                                       [] (std::string text, float f)  {
                                          auto result = ImGui::InputFloat(text.c_str(), &f, 0, 3, 4, 4);
                                          return std::make_tuple(result, f);
                                       }
                                    );

   imgui["sliderFloat"]           = sol::overload(
                                       [] (std::string txt, float* v, float min, float max, std::string fmt, float p) {
                                          assert(v != nullptr && "Nil was passed to this function");
                                          auto result = ImGui::SliderFloat(txt.c_str(), v, min, max, fmt.c_str(), p);
                                          return std::make_tuple(result, *v);
                                       }
                                    );

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
   imgui["showTestWindow"]        = [] () {
                                       bool yes = true;
                                       ImGui::ShowTestWindow(&yes);
                                       return yes;
                                    };
}
