#include "../../include/core/partition_element.h"

namespace partition {

PartitionElement::PartitionElement(const std::string& id, uint64_t size)
    : id_(id), size_(size) {}

auto PartitionElement::ToString() const -> std::string {
  return id_ + " " + std::to_string(size_);
}

}  // namespace partition