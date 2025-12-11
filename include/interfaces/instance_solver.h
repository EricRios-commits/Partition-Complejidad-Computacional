#ifndef PARTITION_INCLUDE_INSTANCE_SOLVER_H_
#define PARTITION_INCLUDE_INSTANCE_SOLVER_H_
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the InstanceSolver interface.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

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
