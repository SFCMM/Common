// SPDX-License-Identifier: BSD-3-Clause

#ifndef COMMON_RANDOM_SPECIAL_H
#define COMMON_RANDOM_SPECIAL_H

#include "gcem.hpp"
#include "randxor.h"
#include "sfcmm_types.h"

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
