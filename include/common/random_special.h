// SPDX-License-Identifier: BSD-3-Clause

#ifndef COMMON_RANDOM_SPECIAL_H
#define COMMON_RANDOM_SPECIAL_H

#include "gcem.hpp"
#include "geometry/circle.h"
#include "randxor.h"
#include "sfcmm_types.h"

/// Obtain a random point in a circle on the given plane by the normal around the center (0.0, 0.0, 0.0).
/// \param[in] normal The plane's normal vector.
/// \param[in] diameter Diameter of the circle.
/// \param[in] prng Random number generator reference
/// \return Point on the defined circle.
inline auto randomPoint_inCircle(const VectorD<3>& normal, const GDouble diameter, randxor& prng) -> VectorD<3> {
  const GDouble random_angle    = prng.double_value(0, 2 * M_PI + GDoubleEps);
  const GDouble random_diameter = prng.double_value() * diameter;
  return pointOnCircleShell(normal, random_diameter, random_angle);
}

/// Obtain a random point on a circular shell with the given plane by the normal  around the center (0.0, 0.0, 0.0).
/// \param[in] normal The plane's normal vector.
/// \param[in] diameter Diameter of the circle.
/// \param[in] prng Random number generator reference
/// \return Point on the defined circle.
inline auto randomPoint_onCircleShell(const VectorD<3>& normal, const GDouble diameter, randxor& prng) -> VectorD<3> {
  const GDouble random_angle = prng.double_value(0, 2 * M_PI + GDoubleEps);
  return pointOnCircleShell(normal, diameter, random_angle);
}

/// Generate a random value using the Rosin-Rammler distribution. This often used for the size distribution of droplets during injection.
/// \tparam RR_SPREAD Constant spread factor
/// \param mean Mean value of the distribution
/// \param prng Random number generator reference to be used.
/// \return Random value distributed by the Rosin-Rammler distribution within [0.3 * mean, 3.0 * mean]
template <GInt RR_SPREAD = 3>
inline constexpr auto randomDist_rosinRammler(const GDouble mean, randxor& prng) -> GDouble {
  GDouble rr_max = 3.0 * mean;
  GDouble rr_min = 0.3 * mean;

  const GDouble K = 1.0 - gcem::exp(-gcem::pow((rr_max - rr_min) / mean, RR_SPREAD));
  const GDouble x = prng.double_value();

  return rr_min + mean * gcem::pow(-gcem::log(1.0 - x * K), 1.0 / RR_SPREAD);
}

#endif // COMMON_RANDOM_SPECIAL_H
