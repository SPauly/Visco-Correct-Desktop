// ViscoCorrectCore - Correction factors for centrifugal pumps
// Copyright (C) 2024  Simon Pauly
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
// Contact via <https://github.com/SPauly/ViscoCorrectCore>
#ifndef SPAULY_VCCORE_UTILS_UI_HELPERS_H
#define SPAULY_VCCORE_UTILS_UI_HELPERS_H

#include <imgui.h>

namespace spauly {
namespace visco {
namespace utils {

void HelpMarker(const char *description, const char *marker) {
  ImGui::TextDisabled((marker) ? marker : "(?)");
  if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(description);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void HyperLink(const char *link, const char *marker) {
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

}  // namespace utils

}  // namespace visco

}  // namespace spauly

#endif  // SPAULY_VCCORE_UTILS_UI_HELPERS_H