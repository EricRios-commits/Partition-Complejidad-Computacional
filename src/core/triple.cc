#include "core/triple.h"

namespace partition {
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