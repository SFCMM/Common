#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(MathApprox, HandlesZeroInput) {
  const double eps = std::numeric_limits<double>::epsilon();
  ASSERT_TRUE(approx(1.0, 1.0, eps));
  ASSERT_TRUE(approx(1.0, 1.0));
  ASSERT_FALSE(approx(1.0, 1.0 + eps, eps));
  ASSERT_TRUE(approx(1.0, 1.0 + eps, 2*eps));

  const float one  = 1.0;
  const float epsf = std::numeric_limits<float>::epsilon();
  ASSERT_TRUE(approx(one, one, epsf));
  ASSERT_FALSE(approx(one, one + epsf, epsf));

  ASSERT_TRUE(isEven(2));
  ASSERT_FALSE(isEven(1));
}

TEST(MathRadians, HandlesZeroInput){
  ASSERT_EQ(toRadians(0), 0);
  ASSERT_EQ(toRadians(180), M_PI);
}