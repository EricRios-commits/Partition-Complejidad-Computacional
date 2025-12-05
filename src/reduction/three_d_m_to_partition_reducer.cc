namespace partition {
#include "three_d_m_to_partition_reducer.h"
#include "three_d_m_instance.cc"

auto ThreeDMToPartitionReducer::Reduce(const ThreeDMInstance& three_dm) const
    -> PartitionInstance {
  PartitionInstance partition_instance;
  element_to_triple_map_.clear();
  q_ = three_dm.q();
  auto k = three_dm.triples().size();
  auto elements = std::vector<PartitionElement>{};
  p_ = std::ceil(std::log2(k + 1));
  for (auto i{0}; i < k; ++i) {
    elements.push_back(PartitionElement("a_" + i, CalculateWeight(three_dm.triples()[i])));
  }
  auto total_weight = uint64_t{0};
  for (const auto& element : partition_instance.elements()) {
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

auto ThreeDMToPartitionReducer::CalculateWeight(const Triple& triple) const -> uint64_t {
  auto w_part = Pow2(3 * p_ * (q_ - triple.w_index));
  auto x_part = Pow2(2 * p_ * (q_ - triple.x_index));
  auto y_part = Pow2(p_ * (q_ - triple.y_index));
  return w_part + x_part + y_part;
}

auto ThreeDMToPartitionReducer::CalculateB() const -> uint64_t {
  auto upper = 3 * q_ - 1
  auto B = uint64_t{0};
  for (auto i{0}; i < upper; ++i) {
    B += Pow2( p_ * i);
  }
  return B;
}
} // namespace partition