/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Implementation file for PartitionElement.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "core/partition_element.h"

namespace partition {

PartitionElement::PartitionElement(const std::string& id, uint64_t size)
    : id_(id), size_(size) {}

auto PartitionElement::ToString() const -> std::string {
  return id_ + " " + std::to_string(size_);
}

}  // namespace partition