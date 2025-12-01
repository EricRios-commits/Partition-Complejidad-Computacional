#ifndef PARTITION_INCLUDE_INSTANCE_WRITER_H_
#define PARTITION_INCLUDE_INSTANCE_WRITER_H_

#include <ostream>
#include <string>

namespace partition {

/**
 * @brief Interface for writing problem instances to files or streams.
 * @tparam Instance The type of instance to write.
 */
template <typename Instance>
class InstanceWriter {
 public:
  virtual ~InstanceWriter() = default;

  /**
   * Writes an instance to a file.
   *
   * @param instance The instance to write.
   * @param filename Path to the output file.
   */
  virtual auto WriteToFile(const Instance& instance,
                           const std::string& filename) const -> void = 0;

  /**
   * Writes an instance to a stream.
   *
   * @param instance The instance to write.
   * @param output The output stream.
   */
  virtual auto WriteToStream(const Instance& instance,
                             std::ostream& output) const -> void = 0;

  /**
   * @brief Returns the output file format description.
   * @return Format description string.
   */
  virtual auto GetFormatDescription() const -> std::string = 0;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_INSTANCE_WRITER_H_
