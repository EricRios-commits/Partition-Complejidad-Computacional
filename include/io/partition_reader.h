#ifndef PARTITION_INCLUDE_PARTITION_READER_H_
#define PARTITION_INCLUDE_PARTITION_READER_H_

/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Header file for the PartitionReader.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "interfaces/instance_reader.h"
#include "core/partition_instance.h"

#include <string>

namespace partition {

/**
 * @brief Reads Partition instances from files.
 * Expected format:
 *   - Line 1: n (number of elements)
 *   - Line 2+: Element ID and size, one per line as "id size"
 */
class PartitionReader : public InstanceReader<PartitionInstance> {
 public:
  auto ReadFromFile(const std::string& filename) const
      -> PartitionInstance override;
  auto ReadFromStream(std::istream& input) const -> PartitionInstance override;
  auto GetFormatDescription() const -> std::string override;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_PARTITION_READER_H_
