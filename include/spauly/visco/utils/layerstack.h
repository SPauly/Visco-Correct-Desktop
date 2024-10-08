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
#ifndef SPAULY_VISCO_UTILS_LAYERSTACK_H
#define SPAULY_VISCO_UTILS_LAYERSTACK_H

#include <memory>
#include <vector>

#include "spauly/visco/utils/layer.h"

namespace spauly {
namespace visco {
namespace utils {

class LayerStack {
 public:
  LayerStack() = default;
  ~LayerStack() { clear(); };

  void PushLayer(const std::shared_ptr<Layer> &layer) {
    layers_.emplace(layers_.begin() + layer_insert_index_, layer);
    layer_insert_index_++;
    layer->OnAttach();
  }

  void PushOverlay(const std::shared_ptr<Layer> &overlay) {
    layers_.emplace_back(overlay);
    overlay->OnAttach();
  }

  void PopLayer(std::shared_ptr<Layer> layer) {
    auto it = std::find(layers_.begin(), layers_.begin() + layer_insert_index_,
                        layer);
    if (it != layers_.begin() + layer_insert_index_) {
      layer->OnDetach();
      layers_.erase(it);
      layer_insert_index_--;
    }
  }

  void PopOverlay(std::shared_ptr<Layer> overlay) {
    auto it = std::find(layers_.begin() + layer_insert_index_, layers_.end(),
                        overlay);
    if (it != layers_.end()) {
      overlay->OnDetach();
      layers_.erase(it);
    }
  }

  void HideLayer(std::shared_ptr<Layer> layer) {
    auto it = std::find(layers_.begin(), layers_.begin() + layer_insert_index_,
                        layer);
    if (it != layers_.begin() + layer_insert_index_) {
      hidden_layers_.push_back(layer);
      layers_.erase(it);
      layer_insert_index_--;
    }
  }

  void ShowLayer(std::shared_ptr<Layer> layer) {
    auto it = std::find(hidden_layers_.begin(), hidden_layers_.end(), layer);
    if (it != hidden_layers_.end()) {
      layers_.emplace(layers_.begin() + layer_insert_index_, layer);
      layer_insert_index_++;
      hidden_layers_.erase(it);
    }
  }

  void clear() {
    for (std::shared_ptr<Layer> layer : layers_) {
      layer->OnDetach();
      layer.reset();
    }
    for (std::shared_ptr<Layer> layer : hidden_layers_) {
      layer->OnDetach();
      layer.reset();
    }
  }

  std::vector<std::shared_ptr<Layer>>::iterator begin() {
    return layers_.begin();
  }
  std::vector<std::shared_ptr<Layer>>::iterator end() { return layers_.end(); }
  std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() {
    return layers_.rbegin();
  }
  std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() {
    return layers_.rend();
  }

  std::vector<std::shared_ptr<Layer>>::const_iterator begin() const {
    return layers_.begin();
  }
  std::vector<std::shared_ptr<Layer>>::const_iterator end() const {
    return layers_.end();
  }
  std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const {
    return layers_.rbegin();
  }
  std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const {
    return layers_.rend();
  }

 private:
  std::vector<std::shared_ptr<Layer>> layers_;
  std::vector<std::shared_ptr<Layer>> hidden_layers_;
  unsigned int layer_insert_index_ = 0;
};

}  // namespace utils

}  // namespace visco

}  // namespace spauly

#endif  // SPAULY_VISCO_UTILS_LAYERSTACK_H