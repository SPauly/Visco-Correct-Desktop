// Visco Correct Desktop - Correction factors for centrifugal pumps
// Copyright (C) 2023  Simon Pauly
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// Contact via <https://github.com/SPauly/Visco-Correct-Desktop>
#include "spauly/visco/application.h"

namespace spauly {
namespace visco {

Application::~Application() { Shutdown(); }

bool Application::Init() {
  // Get the ImGui context
  io_ = &ImGui::GetIO();
  (void)io_;
  io_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io_->ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
  io_->ConfigFlags |=
      ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport / Platform
                                         // Windows

  // Set the style
  ConfigWindow();
  SetStyle();

  viewport_ = ImGui::GetMainViewport();

  // Register the layers

  return true;
}

void Application::Shutdown() {
  // Shutdown all layers
}

bool Application::Render() {
  // Render all layers

  MenuBar();
  CalculatorView();
  return true;
}

void Application::MenuBar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("Menu")) {
      ImGui::MenuItem("Add Project", "STRG + P");
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View")) {
      if (ImGui::MenuItem("Toggle Dark/Light mode", "", &use_dark_mode))
        SetStyle();
      if (ImGui::MenuItem("Show Graph [beta]", "STRG + G", &show_graph_)) {
        if (show_graph_) {
          // Resize window and show graph
        } else {
          // Remove graph window and resize
        }
      }

      if (ImGui::MenuItem("Enable open workspace [beta]", "STRG+O",
                          &use_open_workspace)) {
        if (use_open_workspace)
          ;  // Forward the flags to the graph
        else
          ;  // Forward the flags to the graph
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("Contact")) {
        // Open the contact window
      }

      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

void Application::HelpMarker(const char *description,
                             const char *marker) const {
  ImGui::TextDisabled((marker) ? marker : "(?)");
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(description);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void Application::HyperLink(const char *link, const char *marker) const {
  ImGui::TextDisabled((marker) ? marker : link);
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(link);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
  if (ImGui::IsItemClicked()) {
    // Open the browser
  }
}

void Application::ConfigWindow() {
  style_ = &ImGui::GetStyle();
  colors_ = style_->Colors;

  style_->WindowTitleAlign = ImVec2(0.5f, 0.5f);
  style_->WindowMenuButtonPosition = ImGuiDir_None;
  style_->TabRounding = rounding_;
  style_->FrameRounding = rounding_;
  style_->WindowRounding = rounding_;
}

void Application::SetStyle() {
  return (use_dark_mode) ? DarkMode() : LightMode();
}

void Application::Disclaimer() {
  ImGui::Text("");
  ImGui::Text("                    !!! DISCLAIMER !!!");
  ImGui::Text("This software currently is purely experimental and all ");
  ImGui::Text("calculated values should be verified manually. ViscoCorrect");
  ImGui::Text("uses a graphical approach based on ");
  ImGui::SameLine();
  HyperLink(
      "https:\\\\www.researchgate.net\\figure\\The-graph-obtained-by-the-"
      "American-Institute-of-hydraulics_fig1_335209726",
      "this graph");
  ImGui::SameLine();
  ImGui::Text(" obtained by");
  ImGui::Text("the American Institute of Hydraulics.");
  ImGui::Text(
      "Note that the used standard is deprecated! The HI advises only ");
  ImGui::Text("using the latest ");
  ImGui::SameLine();
  HyperLink(
      "https:\\\\www.pumps.org\\what-we-do\\standards\\?pumps-search-product=9."
      "6.7",
      "ANSI/HI 9.6.7 Standard");
  ImGui::SameLine();
  ImGui::Text("!");
  ImGui::Text("Use at your own risk.");
  ImGui::Text("");
  ImGui::Text("Please ");
  ImGui::SameLine();
  if (ImGui::SmallButton("provide feedback")) submitting_feedback_ = true;
  ImGui::SameLine();
  ImGui::Text(" in case the calculated values are");
  ImGui::Text("incorrect. Thank you :)");
}

void Application::LightMode() {
  colors_[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors_[ImGuiCol_TextDisabled] = ImVec4(0.72f, 0.58f, 0.47f, 1.00f);
  colors_[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
  colors_[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors_[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
  colors_[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
  colors_[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors_[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors_[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.69f, 0.26f, 0.95f);
  colors_[ImGuiCol_FrameBgActive] = ImVec4(0.99f, 0.59f, 0.16f, 0.67f);
  colors_[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
  colors_[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
  colors_[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
  colors_[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
  colors_[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
  colors_[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
  colors_[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.95f, 0.50f, 0.19f, 0.76f);
  colors_[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.97f, 0.39f, 0.00f, 1.00f);
  colors_[ImGuiCol_CheckMark] = ImVec4(0.97f, 0.59f, 0.14f, 1.00f);
  colors_[ImGuiCol_SliderGrab] = ImVec4(0.98f, 0.67f, 0.26f, 0.78f);
  colors_[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
  colors_[ImGuiCol_Button] = ImVec4(1.00f, 0.60f, 0.07f, 0.86f);
  colors_[ImGuiCol_ButtonHovered] = ImVec4(0.84f, 0.79f, 0.73f, 1.00f);
  colors_[ImGuiCol_ButtonActive] = ImVec4(0.73f, 0.61f, 0.44f, 1.00f);
  colors_[ImGuiCol_Header] = ImVec4(0.98f, 0.67f, 0.26f, 0.31f);
  colors_[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.73f, 0.26f, 0.80f);
  colors_[ImGuiCol_HeaderActive] = ImVec4(0.99f, 0.57f, 0.08f, 0.95f);
  colors_[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
  colors_[ImGuiCol_SeparatorHovered] = ImVec4(0.95f, 0.71f, 0.16f, 0.78f);
  colors_[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
  colors_[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
  colors_[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors_[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors_[ImGuiCol_Tab] = ImVec4(0.88f, 0.63f, 0.23f, 0.93f);
  colors_[ImGuiCol_TabHovered] = ImVec4(0.95f, 0.53f, 0.03f, 0.85f);
  colors_[ImGuiCol_TabActive] = ImVec4(1.00f, 0.67f, 0.18f, 1.00f);
  colors_[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
  colors_[ImGuiCol_TabUnfocusedActive] = ImVec4(0.99f, 0.72f, 0.31f, 1.00f);
  colors_[ImGuiCol_DockingPreview] = ImVec4(0.98f, 0.57f, 0.26f, 0.22f);
  colors_[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors_[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  colors_[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors_[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors_[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
  colors_[ImGuiCol_TableHeaderBg] = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
  colors_[ImGuiCol_TableBorderStrong] = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
  colors_[ImGuiCol_TableBorderLight] = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
  colors_[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors_[ImGuiCol_TableRowBgAlt] = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
  colors_[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors_[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors_[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors_[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
  colors_[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
  colors_[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void Application::DarkMode() {
  colors_[ImGuiCol_Text] = ImVec4(0.95f, 0.89f, 0.89f, 1.00f);
  colors_[ImGuiCol_TextDisabled] = ImVec4(0.72f, 0.58f, 0.47f, 1.00f);
  colors_[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
  colors_[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors_[ImGuiCol_PopupBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.98f);
  colors_[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
  colors_[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors_[ImGuiCol_FrameBg] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
  colors_[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.69f, 0.26f, 0.95f);
  colors_[ImGuiCol_FrameBgActive] = ImVec4(0.99f, 0.59f, 0.16f, 0.67f);
  colors_[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors_[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
  colors_[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.07f, 0.07f, 0.51f);
  colors_[ImGuiCol_MenuBarBg] = ImVec4(0.26f, 0.24f, 0.24f, 1.00f);
  colors_[ImGuiCol_ScrollbarBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.53f);
  colors_[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
  colors_[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.95f, 0.50f, 0.19f, 0.76f);
  colors_[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.97f, 0.39f, 0.00f, 1.00f);
  colors_[ImGuiCol_CheckMark] = ImVec4(0.97f, 0.59f, 0.14f, 1.00f);
  colors_[ImGuiCol_SliderGrab] = ImVec4(0.98f, 0.67f, 0.26f, 0.78f);
  colors_[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
  colors_[ImGuiCol_Button] = ImVec4(1.00f, 0.60f, 0.07f, 0.86f);
  colors_[ImGuiCol_ButtonHovered] = ImVec4(0.84f, 0.79f, 0.73f, 1.00f);
  colors_[ImGuiCol_ButtonActive] = ImVec4(0.73f, 0.61f, 0.44f, 1.00f);
  colors_[ImGuiCol_Header] = ImVec4(0.98f, 0.67f, 0.26f, 0.31f);
  colors_[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.73f, 0.26f, 0.80f);
  colors_[ImGuiCol_HeaderActive] = ImVec4(0.99f, 0.57f, 0.08f, 0.95f);
  colors_[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
  colors_[ImGuiCol_SeparatorHovered] = ImVec4(0.95f, 0.71f, 0.16f, 0.78f);
  colors_[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
  colors_[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
  colors_[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors_[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors_[ImGuiCol_Tab] = ImVec4(0.88f, 0.63f, 0.23f, 0.93f);
  colors_[ImGuiCol_TabHovered] = ImVec4(0.95f, 0.53f, 0.03f, 0.85f);
  colors_[ImGuiCol_TabActive] = ImVec4(1.00f, 0.67f, 0.18f, 1.00f);
  colors_[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
  colors_[ImGuiCol_TabUnfocusedActive] = ImVec4(0.61f, 0.38f, 0.05f, 1.00f);
  colors_[ImGuiCol_DockingPreview] = ImVec4(0.98f, 0.57f, 0.26f, 0.22f);
  colors_[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors_[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  colors_[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors_[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors_[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
  colors_[ImGuiCol_TableHeaderBg] = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
  colors_[ImGuiCol_TableBorderStrong] = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
  colors_[ImGuiCol_TableBorderLight] = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
  colors_[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors_[ImGuiCol_TableRowBgAlt] = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
  colors_[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors_[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors_[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors_[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
  colors_[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
  colors_[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

}  // namespace visco
}  // namespace spauly