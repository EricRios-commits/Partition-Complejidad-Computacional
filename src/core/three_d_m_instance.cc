/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Implementation file for ThreeDMInstance.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "core/three_d_m_instance.h"
#include <iostream>

namespace partition {

  auto ThreeDMInstance::SetQ(size_t q) -> void {
    q_ = q;
  }
  
  auto ThreeDMInstance::SetW(const std::set<std::string>& w) -> void {
    w_ = w;
  }

  auto ThreeDMInstance::SetX(const std::set<std::string>& x) -> void {
    x_ = x;
  }

  auto ThreeDMInstance::SetY(const std::set<std::string>& y) -> void {
    y_ = y;
  }

  auto ThreeDMInstance::AddTriple(const Triple& triple) -> void {
    m_.push_back(triple);
  }

  auto ThreeDMInstance::SetTriples(const std::vector<Triple>& triples) -> void {
    m_ = triples;
  }

  auto ThreeDMInstance::IsValid() const -> bool {
    return w_.size() == q_ && x_.size() == q_ && y_.size() == q_;
  }

  auto ThreeDMInstance::ToString() const -> std::string {
    std::string instance_info{""};
    for (const auto& w_i: w_) {
      instance_info += w_i + " ";
    }
    instance_info += "\n";
    for (const auto& x_i: x_) {
      instance_info += x_i + " ";
    }
    instance_info += "\n";
    for (const auto& y_i: y_) {
      instance_info += y_i + " ";
    }
    instance_info += "\n";
    std::cout << "M size: " << m_.size() << "\n";
    for (std::size_t i{0}; i < m_.size(); ++i) {
      instance_info += m_[i].ToString() + "\n";
    }
    return instance_info;
  }
}