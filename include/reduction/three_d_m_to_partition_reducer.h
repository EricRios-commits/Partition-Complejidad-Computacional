#ifndef PARTITION_INCLUDE_THREE_D_M_TO_PARTITION_REDUCER_H_
#define PARTITION_INCLUDE_THREE_D_M_TO_PARTITION_REDUCER_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the ThreeDMToPartitionReducer.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "interfaces/reduction_strategy.h"

#include <string>
#include <unordered_map>

namespace partition {

/**
 * @brief Concrete implementation of the 3DM to Partition reduction.
 * The reduction works by:
 * 1. Assigning unique weights to each element in W, X, Y
 * 2. Creating a partition element for each triple with size = sum of its
 *    coordinate weights
 * 3. Adding "filler" elements to ensure the target sum works correctly
 */
class ThreeDMToPartitionReducer : public ReductionStrategy {
 public:
  auto Reduce(const ThreeDMInstance& three_dm) const
      -> PartitionInstance override;

  auto MapSolutionBack(const std::set<std::string>& partition_solution,
                       const ThreeDMInstance& original_instance) const
      -> std::vector<Triple> override;

  auto GetDescription() const -> std::string override;

 private:
  auto CalculateWeight(const Triple& triple) const -> uint64_t;
  auto CreateIndexMaps(const ThreeDMInstance& three_dm) const -> void;

  auto CalculateB() const -> uint64_t;

  inline auto Pow2(uint64_t exp) const -> uint64_t {
    return static_cast<uint64_t>(1) << exp;
  }
  mutable size_t q_;
  mutable uint64_t p_;
  // Index maps for W, X, Y elements
  mutable std::unordered_map<std::string, size_t> w_indices_;
  mutable std::unordered_map<std::string, size_t> x_indices_;
  mutable std::unordered_map<std::string, size_t> y_indices_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_TO_PARTITION_REDUCER_H_
