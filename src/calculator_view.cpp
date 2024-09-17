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
#include "spauly/visco/calculator_view.h"

#include <imgui.h>

#include "spauly/visco/utils/ui_helpers.h"

namespace spauly {
namespace visco {

void CalculatorView::OnUIRender(const ImGuiWindowFlags &flags) {
  ImGui::Begin("Calculator", nullptr, flags);

  ImGui::PushItemWidth(100);
  ImGui::InputDouble("Q - Flowrate in", &static_cast<double>(params_.flowrate),
                     0.0, 0.0, "%.3f");
  ImGui::SameLine();
  ImGui::Combo("##flowunit", reinterpret_cast<int *>(&units_.flowrate),
               "m^3/h\0l/min\0GPM\0\0");
  ImGui::InputDouble("H - Total differential head in",
                     &static_cast<double>(params_.total_head), 0.0, 0.0,
                     "%.3f");
  ImGui::SameLine();
  ImGui::Combo("##totalhunit", reinterpret_cast<int *>(&units_.total_head),
               "m\0ft\0\0");
  ImGui::InputDouble("v - Viscosity in",
                     &static_cast<double>(params_.viscosity), 0.0, 0.0, "%.3f");
  ImGui::SameLine();
  ImGui::Combo("##viscounit", reinterpret_cast<int *>(&units_.viscosity),
               "mm^2/h\0cSt\0cP\0mPas\0\0");
  if (units_.viscosity == vccore::ViscosityUnit::kcP ||
      units_.viscosity == vccore::ViscosityUnit::kmPas) {  // Dynamic viscosity
    ImGui::InputDouble("Density", &static_cast<double>(params_.density), 0.0,
                       0.0, "%.3f");
    ImGui::SameLine();
    ImGui::Combo("##Densityunit", reinterpret_cast<int *>(&units_.density),
                 "g/l\0kg/m^3\0\0");
  }

  ImGui::PopItemWidth();

  if (ImGui::Button("Calculate", ImVec2(100, 0))) {
    calculator_.Calculate(params_, units_);
  }

  ImGui::Separator();

  if (result_.error_flag) [[unlikely]] {
    if (result_.error_flag & vccore::ErrorFlag::kFlowrateError) {
      ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                         "Flowrate must be in the range of 6 - 2000 m³/h");
    }
    if (result_.error_flag & vccore::ErrorFlag::kTotalHeadError) {
      ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                         "Total head must be in the range of 5 - 200 m");
    }
    if (result_.error_flag & vccore::ErrorFlag::kViscosityError) {
      ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                         "Viscosity must be in the range of 10 - 4000 mm²/s");
    }
  }

  ImGui::Text("Correction eta: %.3f", result_.eta);
  ImGui::Text("Correction Q: %.3f", result_.q);
  ImGui::Text("Correction H:");
  ImGui::Indent();
  ImGui::Text("0.6 x Q_opt: %.3f", result_.h.at(0));
  ImGui::Text("0.8 x Q_opt: %.3f", result_.h.at(1));
  ImGui::Text("1.0 x Q_opt: %.3f", result_.h.at(2));
  ImGui::Text("1.2 x Q_opt: %.3f", result_.h.at(3));
  ImGui::Unindent();

  Disclaimer();

  ImGui::End();
}

void CalculatorView::Disclaimer() {
  ImGui::Text("");
  ImGui::Text("                    !!! DISCLAIMER !!!");
  ImGui::Text("This software currently is purely experimental and all ");
  ImGui::Text("calculated values should be verified manually. ViscoCorrect");
  ImGui::Text("uses a graphical approach based on ");
  ImGui::SameLine();
  utils::HyperLink(
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
  utils::HyperLink(
      "https:\\\\www.pumps.org\\what-we-do\\standards\\?pumps-search-product="
      "9."
      "6.7",
      "ANSI/HI 9.6.7 Standard");
  ImGui::SameLine();
  ImGui::Text("!");
  ImGui::Text("Use at your own risk.");
  ImGui::Text("");
  ImGui::Text("Please ");
  ImGui::SameLine();
  if (ImGui::SmallButton("provide feedback"))
    ;  /// TODO: Implement helper function for feedback
  ImGui::SameLine();
  ImGui::Text(" in case the calculated values are");
  ImGui::Text("incorrect. Thank you :)");
}

}  // namespace visco

}  // namespace spauly