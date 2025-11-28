#ifndef PARTITION_INCLUDE_PARTITION_READER_H_
#define PARTITION_INCLUDE_PARTITION_READER_H_

#include "InstanceReader.h"
#include "PartitionInstance.h"

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
