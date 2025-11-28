#ifndef PARTITION_INCLUDE_REDUCTION_VALIDATOR_H_
#define PARTITION_INCLUDE_REDUCTION_VALIDATOR_H_

#include "PartitionInstance.h"
#include "ReductionStrategy.h"
#include "ThreeDMInstance.h"
#include "Triple.h"

#include <set>
#include <string>
#include <vector>

namespace partition {

/**
 * @brief Validates the correctness of a reduction.
 */
class ReductionValidator {
 public:
  /**
   * @brief Validates that the reduction is correct.
   *
   * @param strategy The reduction strategy to validate.
   * @param three_dm The original 3DM instance.
   * @param partition The reduced Partition instance.
   * @return true if the reduction appears valid, false otherwise.
   */
  static auto ValidateReduction(const ReductionStrategy& strategy,
                                const ThreeDMInstance& three_dm,
                                const PartitionInstance& partition) -> bool;

  /**
   * @brief Validates that a solution mapping is correct.
   *
   * @param strategy The reduction strategy used.
   * @param partition_solution The solution to the partition instance.
   * @param three_dm_solution The mapped 3DM solution.
   * @param original_instance The original 3DM instance.
   * @return true if the mapping is valid, false otherwise.
   */
  static auto ValidateSolutionMapping(
      const ReductionStrategy& strategy,
      const std::set<std::string>& partition_solution,
      const std::vector<Triple>& three_dm_solution,
      const ThreeDMInstance& original_instance) -> bool;

  /**
   * @brief Generates a detailed validation report.
   *
   * @param strategy The reduction strategy used.
   * @param three_dm The original 3DM instance.
   * @param partition The reduced Partition instance.
   * @return A string report detailing the validation results.
   */
  static auto GetValidationReport(
      const ReductionStrategy& strategy, const ThreeDMInstance& three_dm,
      const PartitionInstance& partition) -> std::string;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_REDUCTION_VALIDATOR_H_
