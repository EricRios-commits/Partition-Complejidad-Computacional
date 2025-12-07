#include "reduction/three_d_m_to_partition_reducer.h"

#include <cmath>

namespace partition {

auto ThreeDMToPartitionReducer::Reduce(const ThreeDMInstance& three_dm) const
    -> PartitionInstance {
  PartitionInstance partition_instance;
  q_ = three_dm.q();
  auto k = three_dm.triples().size();
  auto elements = std::vector<PartitionElement>{};
  p_ = std::ceil(std::log2(k + 1));
  // create index maps
  CreateIndexMaps(three_dm);
  for (size_t i{0}; i < k; ++i) {
    elements.push_back(
        PartitionElement("a_" + std::to_string(i), CalculateWeight(three_dm.triples()[i])));
  }
  auto total_weight = uint64_t{0};
  for (const auto& element : elements) {
    total_weight += element.size();
  }
  auto B = CalculateB();
  auto b1 = 2 * total_weight - B;
  auto b2 = total_weight + B;
  elements.push_back(PartitionElement("b1", b1));
  elements.push_back(PartitionElement("b2", b2));
  partition_instance.SetElements(elements);
  return partition_instance;
}

auto ThreeDMToPartitionReducer::CreateIndexMaps(
    const ThreeDMInstance& three_dm) const -> void {
  w_indices_.clear();
  x_indices_.clear();
  y_indices_.clear();
  
  size_t index = 1;
  for (const auto& w_elem : three_dm.w()) {
    w_indices_[w_elem] = index++;
  }
  
  index = 1;
  for (const auto& x_elem : three_dm.x()) {
    x_indices_[x_elem] = index++;
  }
  
  index = 1;
  for (const auto& y_elem : three_dm.y()) {
    y_indices_[y_elem] = index++;
  }
}

auto ThreeDMToPartitionReducer::CalculateWeight(const Triple& triple) const
    -> uint64_t {
  auto w_index = w_indices_.at(triple.w());
  auto x_index = x_indices_.at(triple.x());
  auto y_index = y_indices_.at(triple.y());
  auto w_part = Pow2(3 * p_ * (q_ - w_index));
  auto x_part = Pow2(2 * p_ * (q_ - x_index));
  auto y_part = Pow2(p_ * (q_ - y_index));
  return w_part + x_part + y_part;
}

auto ThreeDMToPartitionReducer::CalculateB() const -> uint64_t {
  size_t upper = 3 * q_ - 1;
  auto B = uint64_t{0};
  for (size_t i{0}; i < upper; ++i) {
    B += Pow2(p_ * i);
  }
  return B;
}

auto ThreeDMToPartitionReducer::MapSolutionBack(
    const std::set<std::string>& partition_solution,
    const ThreeDMInstance& original_instance) const -> std::vector<Triple> {
  std::vector<Triple> matching;
  // TODO: Implement reverse mapping from partition solution to 3DM matching
  (void)partition_solution;
  (void)original_instance;
  return matching;
}

auto ThreeDMToPartitionReducer::GetDescription() const -> std::string {
  return "3D-Matching to Partition reduction strategy";
}

}  // namespace partition