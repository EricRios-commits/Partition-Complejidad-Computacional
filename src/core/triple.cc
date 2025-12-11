/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Implementation file for Triple.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "core/triple.h"

namespace partition {
  auto Triple::SharesCoordinateWith(const Triple& other) const -> bool {
    return w_ == other.w_ || x_ == other.x_ || y_ == other.y_;
  }

  auto Triple::operator==(const Triple& other) const -> bool {
    return w_ == other.w_ && x_ == other.x_ && y_ == other.y_;
  }

  auto Triple::operator!=(const Triple& other) const -> bool {
    return !(*this == other);
  }

  auto Triple::ToString() const -> std::string {
    return "(" + w_ + ", " + x_ + ", " + y_ + ")";
  }
}