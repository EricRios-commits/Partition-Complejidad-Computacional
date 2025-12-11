#ifndef PARTITION_INCLUDE_REDUCTION_PIPELINE_H_
#define PARTITION_INCLUDE_REDUCTION_PIPELINE_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the ReductionPipeline.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "instance_reader.h"
#include "instance_solver.h"
#include "instance_writer.h"
#include "partition_instance.h"
#include "reduction_strategy.h"
#include "three_d_m_instance.h"
#include "triple.h"

#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace partition {

/**
 * @brief Orchestrates the complete reduction pipeline.
 */
class ReductionPipeline {
 public:
  ReductionPipeline(
      std::shared_ptr<ReductionStrategy> reduction_strategy,
      std::shared_ptr<InstanceReader<ThreeDMInstance>> three_dm_reader,
      std::shared_ptr<InstanceWriter<PartitionInstance>> partition_writer,
      std::shared_ptr<InstanceSolver<PartitionInstance, std::set<std::string>>>
          partition_solver);

  /**
   * Executes the complete reduction and solution pipeline.
   *
   * @param three_dm_file Path to the 3DM instance file.
   * @param partition_output_file Path to write the reduced Partition instance.
   * @return A report of the entire process.
   */
  auto Execute(const std::string& three_dm_file,
               const std::string& partition_output_file) -> std::string;

  /**
   * @brief Performs just the reduction step.
   * @param three_dm The 3DM instance to reduce.
   * @return The reduced Partition instance.
   */
  auto PerformReduction(const ThreeDMInstance& three_dm) -> PartitionInstance;

  /**
   * @brief Solves a partition instance and maps back to 3DM.
   * @param partition The partition instance to solve.
   * @param original_three_dm The original 3DM instance.
   * @return Optional vector of triples if solution found.
   */
  auto SolveAndMapBack(const PartitionInstance& partition,
                       const ThreeDMInstance& original_three_dm)
      -> std::optional<std::vector<Triple>>;

 private:
  auto GenerateReport(
      const ThreeDMInstance& three_dm, const PartitionInstance& partition,
      const std::optional<std::set<std::string>>& partition_solution,
      const std::optional<std::vector<Triple>>& three_dm_solution)
      -> std::string;

  std::shared_ptr<ReductionStrategy> reduction_strategy_;
  std::shared_ptr<InstanceReader<ThreeDMInstance>> three_dm_reader_;
  std::shared_ptr<InstanceWriter<PartitionInstance>> partition_writer_;
  std::shared_ptr<InstanceSolver<PartitionInstance, std::set<std::string>>>
      partition_solver_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_REDUCTION_PIPELINE_H_
