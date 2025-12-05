#ifndef PARTITION_INCLUDE_THREE_DM_INSTANCE_H_
#define PARTITION_INCLUDE_THREE_DM_INSTANCE_H_

#include "triple.h"

#include <set>
#include <string>
#include <vector>

namespace partition {

/**
 * @brief Represents a 3-Dimensional Matching problem instance.
 */
class ThreeDMInstance {
 public:
  auto SetW(const std::set<std::string>& w) -> void;
  auto SetX(const std::set<std::string>& x) -> void;
  auto SetY(const std::set<std::string>& y) -> void;
  auto SetQ(size_t q) -> void;
  auto AddTriple(const Triple& triple) -> void;
  auto SetTriples(const std::vector<Triple>& triples) -> void;

  auto w() const -> const std::set<std::string>& { return w_; }
  auto x() const -> const std::set<std::string>& { return x_; }
  auto y() const -> const std::set<std::string>& { return y_; }
  auto triples() const -> const std::vector<Triple>& { return m_; }
  auto q() const -> size_t { return q_; }

  /**
   * @brief Returns true if the instance is valid (all sets have size q).
   * @return true if valid, false otherwise.
   */
  auto IsValid() const -> bool;

  // /**
  //  * @brief Returns true if a set of triples forms a valid matching.
  //  * @param matching The proposed matching to validate.
  //  * @return true if valid matching, false otherwise.
  //  */
  // auto IsValidMatching(const std::vector<Triple>& matching) const -> bool;

  auto ToString() const -> std::string;

 private:
  std::set<std::string> w_;
  std::set<std::string> x_;
  std::set<std::string> y_;
  std::vector<Triple> m_;
  size_t q_;  // Number of elements in each set. 
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_THREE_DM_INSTANCE_H_
