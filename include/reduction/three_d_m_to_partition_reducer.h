#ifndef PARTITION_INCLUDE_THREE_DM_TO_PARTITION_REDUCER_H_
#define PARTITION_INCLUDE_THREE_DM_TO_PARTITION_REDUCER_H_

#include "reduction_strategy.h"

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

  auto CalculateB() const -> uint64_t;

  inline auto Pow2(uint64_t exp) const -> uint64_t {
    return static_cast<uint64_t>(1) << exp;
  }
  size_t q_;
  uint64_t p_;
  // Mapping from triples to their corresponding partition elements.
  mutable std::unordered_map<std::string, Triple> element_to_triple_map_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_TO_PARTITION_REDUCER_H_
