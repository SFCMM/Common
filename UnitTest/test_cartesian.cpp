#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Cartesian, HandlesZeroInput) {
  /* 0 -X
   * 1 +X
   * 2 -Y
   * 3 +Y
   * 4 -Z
   * 5 +Z
   * 6 -W
   * 7 +W
   */

  // 0 (-x) -> +x (1)
  ASSERT_EQ(cartesian::oppositeDir(0), 1);
  ASSERT_EQ(cartesian::oppositeDir(1), 0);
  ASSERT_EQ(cartesian::oppositeDir(2), 3);
  ASSERT_EQ(cartesian::oppositeDir(3), 2);
  ASSERT_EQ(cartesian::oppositeDir(4), 5);
  ASSERT_EQ(cartesian::oppositeDir(5), 4);
  ASSERT_EQ(cartesian::oppositeDir(6), 7);
  ASSERT_EQ(cartesian::oppositeDir(7), 6);

  ASSERT_EQ(cartesian::maxNoChildren<1>(), 2);
  ASSERT_EQ(cartesian::maxNoChildren<2>(), 4);
  ASSERT_EQ(cartesian::maxNoChildren<3>(), 8);
  ASSERT_EQ(cartesian::maxNoChildren<4>(), 16);
  ASSERT_EQ(cartesian::maxNoChildren<5>(), 32);

  ASSERT_EQ(cartesian::maxNoNghbrs<1>(), 2);
  ASSERT_EQ(cartesian::maxNoNghbrs<2>(), 4);
  ASSERT_EQ(cartesian::maxNoNghbrs<3>(), 6);
  ASSERT_EQ(cartesian::maxNoNghbrs<4>(), 8);
  ASSERT_EQ(cartesian::maxNoNghbrs<5>(), 10);
}
