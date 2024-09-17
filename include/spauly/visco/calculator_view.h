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
#ifndef SPAULY_VISCO_CALCULATOR_VIEW_H
#define SPAULY_VISCO_CALCULATOR_VIEW_H

#include <imgui.h>

#include "spauly/visco/utils/layer.h"
#include "spauly/vccore/calculator.h"
#include "spauly/vccore/data.h"

namespace spauly {
namespace visco {

class CalculatorView : public utils::Layer {
 public:
  CalculatorView() = default;
  virtual ~CalculatorView() = default;

  virtual void OnUIRender(const ImGuiWindowFlags& flags) override;

 protected:
  /// @brief Displays the disclaimer regarding the use of the software.
  void Disclaimer();

 private:
  vccore::Calculator calculator_;
  vccore::Parameters params_;
  vccore::Units units_;
  vccore::CorrectionFactors result_;
};

}  // namespace visco

}  // namespace spauly

#endif  // SPAULY_VISCO_CALCULATOR_VIEW_H