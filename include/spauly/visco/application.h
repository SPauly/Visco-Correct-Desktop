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
#ifndef SPAULY_VISCO_APPLICATION_H
#define SPAULY_VISCO_APPLICATION_H

#include <imgui.h>

namespace spauly {
namespace visco {

/// @brief The main application class. This class is responsible for rendering
/// the application specific data but must be integrated into a rendering
/// system.
class Application {
 public:
  Application() = default;
  ~Application();

  /// @brief Initializes the style as well as first layout of the application.
  /// This should be called before the main loop and after the Imgui context has
  /// been created.
  /// @return Returns true if the initialization was successful. False incase of
  /// an error.
  bool Init();

  /// @brief Shuts down the application.
  void Shutdown();

  /// @brief Renders one frame of the application. This should be called from
  /// within the main loop.
  /// @return Returns false if the application should be closed.
  bool Render();

 private:
  /// @brief Displays the menu bar.
  void MenuBar();

  void CalculatorView() {};

  /// @brief Configures the window layout.
  void ConfigWindow() {};

  /// @brief Configures the style of the application.
  void SetStyle() {};

  /// @brief Enables dark mode.
  void DarkMode() {};

  /// @brief Enables light mode.
  void LightMode() {};

  /// @brief Displays a help marker.
  void HelpMarker(const char *description, const char *marker = nullptr) {};

 private:
  // config
  bool use_open_workspace = false;
  bool show_graph_ = false;
  bool use_dark_mode = false;

  // internal use
  bool submitting_feedback_ = false;
  ImGuiIO *io_ = nullptr;
  ImGuiViewport *viewport_;

  // Appearence
  const int display_w_ = 445;
  const int display_h_ = 650;
  const int display_w_offset_graph_ = 445;
  int temp_display_w_, temp_display_h_;  // for temporary use
  const ImGuiWindowFlags closed_workspace_flags_ = ImGuiWindowFlags_NoCollapse |
                                                   ImGuiWindowFlags_NoMove |
                                                   ImGuiWindowFlags_NoResize;
  const ImGuiWindowFlags open_workspace_flags_ =
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
  const float rounding_ = 2.0;

  // Style
  ImVec4 clear_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  ImVec4 *colors_ = nullptr;
  ImGuiStyle *style_ = nullptr;
};

}  // namespace visco

}  // namespace spauly

#endif  // SPAULY_VISCO_APPLICATION_H