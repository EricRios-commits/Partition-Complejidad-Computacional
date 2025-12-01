#include "partition_reader.h"

namespace partition {
  auto PartitionReader::ReadFromFile(const std::string& filename) const
      -> PartitionInstance {}

  auto PartitionReader::ReadFromStream(std::istream& input) const
      -> PartitionInstance {
    PartitionInstance instance;
    
      }

  auto PartitionReader::GetFormatDescription() const -> std::string {
    return "Partition instance format:\n"
          "- Line 1: n (number of elements)\n"
          "- Line 2+: Element ID and size, one per line as 'id size'";
  }
}  // namespace partition