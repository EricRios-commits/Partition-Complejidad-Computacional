/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Implementation file for PartitionWriter.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

#include "io/partition_writer.h"
#include <fstream>

namespace partition {

  auto PartitionWriter::WriteToFile(const PartitionInstance& instance,
                                    const std::string& filename) const
      -> void {
    std::ofstream file_stream(filename);
    WriteToStream(instance, file_stream);
    return;
  }
  
  auto PartitionWriter::WriteToStream(const PartitionInstance& instance,
                                      std::ostream& output) const
      -> void {
    output << instance.size() << '\n';
    for (const auto& element : instance.elements()) {
      output << element.id() << ' ' << element.size() << '\n';
    }
    return;
  }
    
  auto PartitionWriter::GetFormatDescription() const -> std::string {
    return "Partition instance format:\n"
          "- Line 1: n (number of elements)\n"
          "- Line 2+: Element ID and size, one per line as 'id size'";
  }

}  // namespace partition