#ifndef PARTITION_INCLUDE_INSTANCE_SOLVER_H_
#define PARTITION_INCLUDE_INSTANCE_SOLVER_H_

#include <memory>
#include <optional>
#include <string>

namespace partition {

/**
 * @brief Generic interface for problem instance solvers.
 * @tparam Instance The problem instance type.
 * @tparam Solution The solution type.
 */
template <typename Instance, typename Solution>
class InstanceSolver {
 public:
  virtual ~InstanceSolver() = default;

  /**
   * Attempts to solve the given problem instance.
   *
   * @param instance The problem instance to solve.
   * @return A solution if one exists, std::nullopt otherwise.
   */
  virtual auto Solve(const Instance& instance) -> std::optional<Solution> = 0;

  /**
   * @brief Returns the name/description of the solver algorithm.
   * @return Algorithm name string.
   */
  virtual auto GetAlgorithmName() const -> std::string = 0;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_INSTANCE_SOLVER_H_
