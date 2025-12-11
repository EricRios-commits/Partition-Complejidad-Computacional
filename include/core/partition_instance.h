#ifndef PARTITION_INCLUDE_PARTITION_INSTANCE_H_
#define PARTITION_INCLUDE_PARTITION_INSTANCE_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the PartitionInstance class.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "core/partition_element.h"

#include <set>
#include <string>
#include <vector>
#include <sstream>

namespace partition {

/**
 * @brief Represents a Partition problem instance.
 *
 * Single Responsibility: Manages the Partition instance data (set A with
 * sizes).
 */
class PartitionInstance {
 public:
  /**
   * @name Builders
   * Methods for building the instance.
   */
  auto AddElement(const PartitionElement& element) -> void;

  auto SetElements(const std::vector<PartitionElement>& elements) -> void;

  auto SetBinaryDisplayWidth(size_t width) -> void { binary_display_width_ = width; }

  /**
   * @name Getters
   * Methods for accessing instance data.
   */
  auto elements() const -> const std::vector<PartitionElement>& {
    return elements_;
  }

  auto total_sum() const -> int64_t { return total_sum_; }

  auto size() const -> size_t { return elements_.size(); }

  /**
   * @brief Returns true if the instance is valid.
   * @return true if valid, false otherwise.
   */
  auto IsValid() const -> bool;

  // /**
  //  * @brief Returns true if a subset forms a valid partition.
  //  * @param subset_ids Set of element IDs forming the proposed partition.
  //  * @return true if valid partition, false otherwise.
  //  */
  // auto IsValidPartition(const std::set<std::string>& subset_ids) const -> bool;

  auto ToString() const -> std::string;

 private:
  auto RecalculateTotalSum() -> void;
  auto ToBinaryString(uint64_t value, size_t min_width = 0) const -> std::string;
  
  std::vector<PartitionElement> elements_;
  int64_t total_sum_;
  size_t binary_display_width_ = 0;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_PARTITION_INSTANCE_H_
