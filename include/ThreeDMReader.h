#ifndef PARTITION_INCLUDE_THREE_DM_READER_H_
#define PARTITION_INCLUDE_THREE_DM_READER_H_

#include "InstanceReader.h"
#include "ThreeDMInstance.h"

#include <string>

namespace partition {

/**
 * @brief Reads 3DM instances from files.
 *
 * Expected format:
 *   - Line 1: q (size of each set)
 *   - Line 2: W elements (space-separated)
 *   - Line 3: X elements (space-separated)
 *   - Line 4: Y elements (space-separated)
 *   - Line 5+: Triples, one per line as "w x y"
 */
class ThreeDMReader : public InstanceReader<ThreeDMInstance> {
 public:
  auto ReadFromFile(const std::string& filename) const
      -> ThreeDMInstance override;
  auto ReadFromStream(std::istream& input) const -> ThreeDMInstance override;
  auto GetFormatDescription() const -> std::string override;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_READER_H_
