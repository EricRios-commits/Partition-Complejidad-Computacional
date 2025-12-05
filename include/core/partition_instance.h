#ifndef PARTITION_INCLUDE_PARTITION_INSTANCE_H_
#define PARTITION_INCLUDE_PARTITION_INSTANCE_H_

#include "partition_element.h"

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
  
  std::vector<PartitionElement> elements_;
  int64_t total_sum_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_PARTITION_INSTANCE_H_
