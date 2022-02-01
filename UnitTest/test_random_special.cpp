#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(random_rosinrammler, HandlesZeroInput) {
  randxor randgen(1256);

  // the mean value is higher than 1 since the lower value is limited to 0.3 of the mean value
  GDouble mean = 0;
  for(GInt i = 0; i < 10000; ++i){
    mean += randomDist_rosinRammler(1.0, randgen);
  }
  mean /=10000;

  ASSERT_LT(std::abs(mean - 1.196572), 1E-6);
}
