#ifndef PARTITION_INCLUDE_TRIPLE_H_
#define PARTITION_INCLUDE_TRIPLE_H_

#include <functional>
#include <string>

namespace partition {

/**
 * @brief Represents a single triple (w, x, y) in a 3DM instance.
 */
class Triple {
 public:
  Triple(const std::string& w, const std::string& x, const std::string& y) : w_(w), x_(x), y_(y) {}
  
  auto w() const -> const std::string& { return w_; }
  auto x() const -> const std::string& { return x_; }
  auto y() const -> const std::string& { return y_; }

  /**
   * @brief Returns true if this triple shares any coordinate with another.
   * @param other The other triple to compare with.
   * @return true if any coordinate matches, false otherwise.
   */
  auto SharesCoordinateWith(const Triple& other) const -> bool;

  auto operator==(const Triple& other) const -> bool {
    return w_ == other.w_ && x_ == other.x_ && y_ == other.y_;
  }
  auto operator!=(const Triple& other) const -> bool {
    return !(*this == other);
  }

  /**
   * @brief Returns a string representation of the triple.
   * @return String in the format "(w, x, y)".
   */
  auto ToString() const -> std::string {
    return "(" + w_ + ", " + x_ + ", " + y_ + ")";
  }

 private:
  std::string w_;
  std::string x_;
  std::string y_;
};

}  // namespace partition

#endif  // PARTITION_INCLUDE_TRIPLE_H_
