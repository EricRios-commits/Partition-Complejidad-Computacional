#ifndef PARTITION_INCLUDE_PARTITION_WRITER_H_
#define PARTITION_INCLUDE_PARTITION_WRITER_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the PartitionWriter.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "interfaces/instance_writer.h"
#include "core/partition_instance.h"

#include <string>

namespace partition {

/**
 * @brief Writes Partition instances to files.
 */
class PartitionWriter : public InstanceWriter<PartitionInstance> {
 public:
  auto WriteToFile(const PartitionInstance& instance,
                   const std::string& filename) const -> void override;
  auto WriteToStream(const PartitionInstance& instance,
                     std::ostream& output) const -> void override;
  auto GetFormatDescription() const -> std::string override;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_PARTITION_WRITER_H_
