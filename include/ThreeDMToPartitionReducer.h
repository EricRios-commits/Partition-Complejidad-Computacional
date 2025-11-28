#ifndef PARTITION_INCLUDE_THREE_DM_TO_PARTITION_REDUCER_H_
#define PARTITION_INCLUDE_THREE_DM_TO_PARTITION_REDUCER_H_

#include "ReductionStrategy.h"

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
  explicit ThreeDMToPartitionReducer(int64_t base_weight = 1000000);

  auto Reduce(const ThreeDMInstance& three_dm) const
      -> PartitionInstance override;

  auto MapSolutionBack(const std::set<std::string>& partition_solution,
                       const ThreeDMInstance& original_instance) const
      -> std::vector<Triple> override;

  auto GetDescription() const -> std::string override;

 private:
  auto CalculateWeight(size_t index, size_t dimension) const -> int64_t;
  auto CalculateTripleSize(
      const Triple& triple,
      const std::unordered_map<std::string, size_t>& w_indices,
      const std::unordered_map<std::string, size_t>& x_indices,
      const std::unordered_map<std::string, size_t>& y_indices) const
      -> int64_t;
  auto CreateIndexMaps(const ThreeDMInstance& three_dm,
                       std::unordered_map<std::string, size_t>& w_indices,
                       std::unordered_map<std::string, size_t>& x_indices,
                       std::unordered_map<std::string, size_t>& y_indices) const
      -> void;

  int64_t base_weight_;  // Weight assignment parameters.
  // Mapping from triples to their corresponding partition elements.
  mutable std::unordered_map<std::string, Triple> element_to_triple_map_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_TO_PARTITION_REDUCER_H_
