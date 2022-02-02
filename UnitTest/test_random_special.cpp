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

TEST(random_pointOnCircleShell, HandlesZeroInput) {
  randxor randgen(1256);

  const VectorD<3> normal({1, 0, 0});
  VectorD<3> result = randomPoint_onCircleShell(normal, 1.0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0);
  ASSERT_DOUBLE_EQ(result[1], 0.4609034347941241);
  ASSERT_DOUBLE_EQ(result[2], 0.19382472441610382);

  result = randomPoint_onCircleShell(normal, 1.0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0);
  ASSERT_DOUBLE_EQ(result[1], -0.49950959380379301);
  ASSERT_DOUBLE_EQ(result[2], 0.022139686040451481);
}