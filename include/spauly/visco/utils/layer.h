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
#ifndef SPAULY_VISCO_UTILS_LAYER_H
#define SPAULY_VISCO_UTILS_LAYER_H

#include <imgui.h>

namespace spauly {
namespace visco {
namespace utils {

/// @brief The base class for all layers.
class Layer {
 public:
  Layer() = default;
  virtual ~Layer() = default;

  virtual void OnAttach() {};
  virtual void OnDetach() {};

  virtual void OnUIRender(const ImGuiWindowFlags& flags) {};
};

}  // namespace utils

}  // namespace visco

}  // namespace spauly

#endif  // SPAULY_VISCO_UTILS_LAYER_H