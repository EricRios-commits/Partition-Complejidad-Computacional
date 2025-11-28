#ifndef PARTITION_INCLUDE_SOLUTION_VERIFIER_H_
#define PARTITION_INCLUDE_SOLUTION_VERIFIER_H_

#include "PartitionInstance.h"
#include "ThreeDMInstance.h"
#include "Triple.h"

#include <set>
#include <string>
#include <vector>

namespace partition {

/**
 * @brief Verifies solutions for problem instances.
 */
class SolutionVerifier {
 public:
  /**
   * @brief Verifies a 3DM matching solution.
   *
   * @param instance The 3DM instance.
   * @param matching The proposed matching.
   * @return true if the matching is valid, false otherwise.
   */
  static auto Verify3DMSolution(const ThreeDMInstance& instance,
                                const std::vector<Triple>& matching) -> bool;

  /**
   * @brief Verifies a Partition solution.
   *
   * @param instance The Partition instance.
   * @param subset The proposed subset A'.
   * @return true if the partition is valid, false otherwise.
   */
  static auto VerifyPartitionSolution(const PartitionInstance& instance,
                                      const std::set<std::string>& subset)
      -> bool;

  /**
   * @brief Gets a detailed verification report for a 3DM solution.
   *
   * @param instance The 3DM instance.
   * @param matching The proposed matching.
   * @return A string report detailing the verification results.
   */
  static auto Get3DMVerificationReport(const ThreeDMInstance& instance,
                                       const std::vector<Triple>& matching)
      -> std::string;

  /**
   * @brief Gets a detailed verification report for a Partition solution.
   *
   * @param instance The Partition instance.
   * @param subset The proposed subset A'.
   * @return A string report detailing the verification results.
   */
  static auto GetPartitionVerificationReport(
      const PartitionInstance& instance, const std::set<std::string>& subset)
      -> std::string;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_SOLUTION_VERIFIER_H_
