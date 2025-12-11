#ifndef PARTITION_INCLUDE_REDUCTION_STRATEGY_H_
#define PARTITION_INCLUDE_REDUCTION_STRATEGY_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the ReductionStrategy interface.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "core/partition_instance.h"
#include "core/three_d_m_instance.h"
#include "core/triple.h"

#include <memory>
#include <set>
#include <string>
#include <vector>

namespace partition {

/**
 * @brief Interface for reduction strategies from one problem to another.
 */
class ReductionStrategy {
 public:
  virtual ~ReductionStrategy() = default;

  /**
   * Reduces a 3DM instance to a Partition instance.
   *
   * @param three_dm The 3DM instance to reduce.
   * @return A Partition instance equivalent to the 3DM instance.
   */
  virtual auto Reduce(const ThreeDMInstance& three_dm) const
      -> PartitionInstance = 0;

  /**
   * Maps a Partition solution back to a 3DM solution.
   *
   * @param partition_solution Set of element IDs in the partition solution.
   * @param original_instance The original 3DM instance.
   * @return Vector of triples forming a matching in 3DM.
   */
  virtual auto MapSolutionBack(const std::set<std::string>& partition_solution,
                               const ThreeDMInstance& original_instance) const
      -> std::vector<Triple> = 0;

  /**
   * @brief Returns a description of the reduction strategy.
   * @return Description string.
   */
  virtual auto GetDescription() const -> std::string = 0;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_REDUCTION_STRATEGY_H_
