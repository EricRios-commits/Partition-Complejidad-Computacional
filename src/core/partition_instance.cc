#include "core/partition_instance.h"

namespace partition {
  
  auto PartitionInstance::AddElement(const PartitionElement& element) -> void {
    elements_.push_back(element);
    RecalculateTotalSum();
  }
  
  auto PartitionInstance::SetElements(const std::vector<PartitionElement>& elements) -> void {
    elements_ = elements;
    RecalculateTotalSum();
  }

  auto PartitionInstance::IsValid() const -> bool {
    return !elements_.empty();
  }

  auto PartitionInstance::ToString() const -> std::string {
    std::ostringstream oss;
    oss << "Partition Instance:\n";
    oss << elements_.size() << " elements.\n";
    oss << "Total sum: " << total_sum_ << '\n';
    oss << "Elements:\n";
    for (const auto& elem : elements_) {
      oss << "  " << elem.ToString() << '\n';
    }
    return oss.str();
  }

  auto PartitionInstance::RecalculateTotalSum() -> void {
    total_sum_ = 0;
    for (const auto& element : elements_) {
      total_sum_ += element.size();
    }
  }
}