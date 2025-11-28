#ifndef PARTITION_INCLUDE_PARTITION_ELEMENT_H_
#define PARTITION_INCLUDE_PARTITION_ELEMENT_H_

#include <cstdint>
#include <string>

namespace partition {

/**
 * @brief Represents a single element in a Partition problem instance.
 */
class PartitionElement {
 public:
  PartitionElement(const std::string& id, int64_t size);

  auto id() const -> const std::string& { return id_; }
  auto size() const -> int64_t { return size_; }

  auto operator==(const PartitionElement& other) const -> bool;
  auto operator!=(const PartitionElement& other) const -> bool;

  auto ToString() const -> std::string;

 private:
  std::string id_;
  int64_t size_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_PARTITION_ELEMENT_H_
