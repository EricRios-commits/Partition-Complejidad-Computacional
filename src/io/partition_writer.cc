#include "io/partition_writer.h"
#include <fstream>

namespace partition {

  auto PartitionWriter::WriteToFile(const PartitionInstance& instance,
                                    const std::string& filename) const
      -> void {
    std::ofstream file_stream(filename);
    if (!file_stream.is_open()) {
      throw std::runtime_error("Could not open file: " + filename);
    }
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