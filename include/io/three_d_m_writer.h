#ifndef PARTITION_INCLUDE_THREE_DM_WRITER_H_
#define PARTITION_INCLUDE_THREE_DM_WRITER_H_

#include "../interfaces/instance_writer.h"
#include "../core/three_d_m_instance.h"

#include <string>

namespace partition {

/**
 * @brief Writes 3DM instances to files.
 *
 * Single Responsibility: Handles serialization of 3DM instances.
 */
class ThreeDMWriter : public InstanceWriter<ThreeDMInstance> {
 public:
  auto WriteToFile(const ThreeDMInstance& instance,
                   const std::string& filename) const -> void override;
  auto WriteToStream(const ThreeDMInstance& instance,
                     std::ostream& output) const -> void override;
  auto GetFormatDescription() const -> std::string override;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_WRITER_H_
