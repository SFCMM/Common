#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(circle_pointOnCircle, HandlesZeroInput) {
  const GDouble    diameter = 1.0;
  const VectorD<3> normal({1, 0, 0});
  const VectorD<3> normal2({1, 1, 1});
  const VectorD<3> normal3({0, 1, 0});
  const VectorD<3> normal4({0, 0, 1});

  //  std::cerr << pointOnCircleShell(normal, diameter, 0) << std::endl;

  //  ASSERT_EQ(pointOnCircleShell(normal, diameter, 0), VectorD<3>({0.0, -0.00249968, -0.499994}));
  const VectorD<3> result1 = pointOnCircleShell(normal, diameter, 0);
  ASSERT_DOUBLE_EQ(result1[0], 0);
  ASSERT_DOUBLE_EQ(result1[1], 0);
  ASSERT_DOUBLE_EQ(result1[2], -0.5);
  ASSERT_EQ(pointOnCircleShell(normal, diameter, toRadians(180)), VectorD<3>({0.0, 0.0, 0.5}));

  const VectorD<3> result2 = pointOnCircleShell(normal2, diameter, 0);
  ASSERT_DOUBLE_EQ(result2[0], 0);
  ASSERT_DOUBLE_EQ(result2[1], -0.35355339059327373);
  ASSERT_DOUBLE_EQ(result2[2], 0.35355339059327373);

  const VectorD<3> result3 = pointOnCircleShell(normal2, diameter, toRadians(180));
  ASSERT_DOUBLE_EQ(result3[0], 0);
  ASSERT_DOUBLE_EQ(result3[1], 0.35355339059327373);
  ASSERT_DOUBLE_EQ(result3[2], -0.35355339059327373);
  ASSERT_DOUBLE_EQ(result3.norm(), 0.5);

  const VectorD<3> result4 = pointOnCircleShell(normal3, diameter, toRadians(180));
  ASSERT_DOUBLE_EQ(result4[0], 0.0);
  ASSERT_DOUBLE_EQ(result4[1], 0);
  ASSERT_DOUBLE_EQ(result4[2], -0.5);

  const VectorD<3> result5 = pointOnCircleShell(normal4, diameter, toRadians(180));
  ASSERT_DOUBLE_EQ(result5[0], 0);
  ASSERT_DOUBLE_EQ(result5[1], 0.5);
  ASSERT_DOUBLE_EQ(result5[2], 0);

}