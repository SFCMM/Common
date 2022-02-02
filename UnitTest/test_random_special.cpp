#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(random_rosinrammler, HandlesZeroInput) {
  randxor randgen(1256);

  // the mean value is higher than 1 since the lower value is limited to 0.3 of the mean value
  GDouble mean = 0;
  for(GInt i = 0; i < 10000; ++i) {
    mean += randomDist_rosinRammler(1.0, randgen);
  }
  mean /= 10000;

  ASSERT_LT(std::abs(mean - 1.196572), 1E-6);
}

TEST(random_pointOnCircleShell, HandlesZeroInput) {
  randxor randgen(1256);

  const VectorD<3> normal({1, 0, 0});
  VectorD<3>       result = randomPoint_onCircleShell(normal, 1.0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0);
  ASSERT_DOUBLE_EQ(result[1], 0.4609034347941241);
  ASSERT_DOUBLE_EQ(result[2], 0.19382472441610382);

  result = randomPoint_onCircleShell(normal, 1.0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0);
  ASSERT_DOUBLE_EQ(result[1], -0.49950959380379301);
  ASSERT_DOUBLE_EQ(result[2], 0.022139686040451481);
}

TEST(random_pointInCircle, HandlesZeroInput) {
  randxor randgen(1256);

  const VectorD<3> normal({1, 0, 0});
  VectorD<3>       result = randomPoint_inCircle(normal, 1.0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0);
  ASSERT_DOUBLE_EQ(result[1], 0.11847503703903588);
  ASSERT_DOUBLE_EQ(result[2], 0.049822565142167118);

  result = randomPoint_inCircle(normal, 1.0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0);
  ASSERT_DOUBLE_EQ(result[1], -0.12815556057578284);
  ASSERT_DOUBLE_EQ(result[2], 0.46505062644840572);

  result = randomPoint_inCircle(normal, 1.0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0);
  ASSERT_DOUBLE_EQ(result[1], -0.2632129873189582);
  ASSERT_DOUBLE_EQ(result[2], 0.076022648807890558);
}

TEST(random_cone, HandlesZeroInput) {
  randxor randgen(1256);

  const VectorD<3> coneAxis({1, 0, 0});
  VectorD<3>       result = randomNormalizedDirection_inCone(coneAxis, 20, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0.95519460763768405);
  ASSERT_DOUBLE_EQ(result[1], 0.27283499754191665);
  ASSERT_DOUBLE_EQ(result[2], 0.1147358952385584);

  result = randomNormalizedDirection_inCone(coneAxis, 45, randgen);
  ASSERT_DOUBLE_EQ(result[0], 0.98968176331264135);
  ASSERT_DOUBLE_EQ(result[1], -0.038066032226745206);
  ASSERT_DOUBLE_EQ(result[2], 0.13813393702089793);

  result = randomNormalizedDirection_inCone(coneAxis, 0, randgen);
  ASSERT_DOUBLE_EQ(result[0], 1);
  ASSERT_DOUBLE_EQ(result[1], 0);
  ASSERT_DOUBLE_EQ(result[2], 0);
}