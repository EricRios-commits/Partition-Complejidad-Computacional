/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad computacional
 *
 * @brief Implementation file for PartitionInstance.
 * @authors Fabián González Lence, Diego Hernández Chico, Enmanuel Vegas Acosta, Luis David Romero Romero, Eric Ríos Hamilton
 * @date 11-12-2025
 */

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
    oss << "Total sum: " << total_sum_ << " (binary: " << ToBinaryString(total_sum_, binary_display_width_) << ")\n";
    oss << "Elements:\n";
    for (const auto& elem : elements_) {
      oss << "  " << elem.ToString() << " (binary: " << ToBinaryString(elem.size(), binary_display_width_) << ")\n";
    }
    return oss.str();
  }

  auto PartitionInstance::ToBinaryString(uint64_t value, size_t min_width) const -> std::string {
    if (value == 0) {
      std::string result = "0";
      if (min_width > 1) {
        result = std::string(min_width - 1, '0') + result;
      }
      return result;
    }
    std::string binary;
    uint64_t temp = value;
    while (temp > 0) {
      binary = (temp % 2 == 0 ? '0' : '1') + binary;
      temp /= 2;
    }
    // Pad with leading zeros if needed
    if (binary.length() < min_width) {
      binary = std::string(min_width - binary.length(), '0') + binary;
    }
    return binary;
  }

  auto PartitionInstance::RecalculateTotalSum() -> void {
    total_sum_ = 0;
    for (const auto& element : elements_) {
      total_sum_ += element.size();
    }
  }
}