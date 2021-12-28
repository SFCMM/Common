// SPDX-License-Identifier: BSD-3-Clause

#ifndef SFCMM_INTEGRATION_H
#define SFCMM_INTEGRATION_H

#include "common/sfcmm_types.h"

namespace integration {

struct range {
  GDouble a;
  GDouble b;
};

inline auto midpoint(const range range, const std::function<GDouble(GDouble)>& f) -> GDouble {
  assert(range.a < range.b);
  const GDouble h        = range.b - range.a;
  const GDouble midpoint = range.a + 0.5 * h;
  return h * f(midpoint);
}

inline auto trapezoidal(const range range, const std::function<GDouble(GDouble)>& f) -> GDouble {
  assert(range.a < range.b);
  const GDouble h  = range.b - range.a;
  const GDouble x1 = range.a;
  const GDouble x2 = range.b;
  return 0.5 * h * (f(x1) + f(x2));
}

inline auto simpson(const range range, const std::function<GDouble(GDouble)>& f) -> GDouble {
  assert(range.a < range.b);
  const GDouble h  = 0.5 * (range.b - range.a);
  const GDouble x1 = range.a;
  const GDouble x2 = range.a + h;
  const GDouble x3 = range.b;
  return 1.0/3.0 * h * (f(x1) + 4 * f(x2) + f(x3));
}

} // namespace integration

#endif // SFCMM_INTEGRATION_H