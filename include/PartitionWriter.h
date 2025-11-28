#ifndef PARTITION_INCLUDE_PARTITION_WRITER_H_
#define PARTITION_INCLUDE_PARTITION_WRITER_H_

#include "InstanceWriter.h"
#include "PartitionInstance.h"

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
