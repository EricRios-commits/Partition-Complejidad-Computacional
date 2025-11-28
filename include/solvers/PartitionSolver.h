#ifndef PARTITION_INCLUDE_PARTITION_SOLVER_H_
#define PARTITION_INCLUDE_PARTITION_SOLVER_H_

#include "InstanceSolver.h"
#include "PartitionInstance.h"

#include <set>
#include <string>

namespace partition {

/**
 * @brief Solves Partition problem instances.
 */
class PartitionSolver
    : public InstanceSolver<PartitionInstance, std::set<std::string>> {
 public:
  enum class Algorithm {
    kDynamicProgramming,
    kBacktracking,
    kGreedyHeuristic
  };

  explicit PartitionSolver(Algorithm algo = Algorithm::kDynamicProgramming);

  auto Solve(const PartitionInstance& instance)
      -> std::optional<std::set<std::string>> override;

  auto GetAlgorithmName() const -> std::string override;

 private:
  auto SolveDynamicProgramming(const PartitionInstance& instance)
      -> std::optional<std::set<std::string>>;
  auto SolveBacktracking(const PartitionInstance& instance)
      -> std::optional<std::set<std::string>>;
  auto SolveGreedy(const PartitionInstance& instance)
      -> std::optional<std::set<std::string>>;

  /**
   * @brief Helper for backtracking.
   * @param instance The partition instance.
   * @param index Current element index.
   * @param current_sum Current subset sum.
   * @param target_sum Target sum to achieve.
   * @param current_subset Current subset being built.
   * @return true if solution found, false otherwise.
   */
  auto BacktrackHelper(const PartitionInstance& instance, size_t index,
                       int64_t current_sum, int64_t target_sum,
                       std::set<std::string>& current_subset) -> bool;

  Algorithm algorithm_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_PARTITION_SOLVER_H_
