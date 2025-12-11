#ifndef PARTITION_INCLUDE_PARTITION_ELEMENT_H_
#define PARTITION_INCLUDE_PARTITION_ELEMENT_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the PartitionElement class.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include <cstdint>
#include <string>

namespace partition {

/**
 * @brief Represents a single element in a Partition problem instance.
 */
class PartitionElement {
 public:
  PartitionElement(const std::string& id, uint64_t size);

  auto id() const -> const std::string& { return id_; }
  auto size() const -> uint64_t { return size_; }

  // auto operator==(const PartitionElement& other) const -> bool;
  // auto operator!=(const PartitionElement& other) const -> bool;

  auto ToString() const -> std::string;

 private:
  std::string id_;
  uint64_t size_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_PARTITION_ELEMENT_H_
