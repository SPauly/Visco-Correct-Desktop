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
      if (ImGui::MenuItem("Toggle Dark/Light mode [not impl]", "",
                          &use_dark_mode))
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

}  // namespace visco
}  // namespace spauly