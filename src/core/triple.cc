namespace partition {
  #include "triple.h"

  Triple::Triple(const std::string& w, const std::string& x, const std::string& y)
      : w_(w), x_(x), y_(y) {}

  auto Triple::SharesCoordinateWith(const Triple& other) const -> bool {
    return w_ == other.w_ || x_ == other.x_ || y_ == other.y_;
  }

  auto Triple::operator==(const Triple& other) const -> bool {
    return w_ == other.w_ && x_ == other.x_ && y_ == other.y_;
  }

  auto Triple::operator!=(const Triple& other) const -> bool {
    return !(*this == other);
  }

  auto Triple::ToString() const -> std::string {
    return "(" + w_ + ", " + x_ + ", " + y_ + ")";
  }
}