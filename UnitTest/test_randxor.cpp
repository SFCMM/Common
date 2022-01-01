#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(randxor, HandlesZeroInput) {
  randxor randgen(1256);

  ASSERT_LT(std::abs(randgen.double_value() - 0.686644), 1E-6);
  ASSERT_LT(std::abs(randgen.double_value() - 0.25705), 1E-6);
  ASSERT_LT(std::abs(randgen.double_value() - 0.457203), 1E-6);
  ASSERT_EQ(randgen.uinteger_value(), 17796889931525078062U);
  ASSERT_EQ(randgen.uinteger_value(), 5437181467800694949);
  ASSERT_EQ(randgen.uinteger_value(), 10107773513175681509U);
  ASSERT_EQ(randgen.uinteger_value(), 12675789557651290906U);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 3);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 8);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 2);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 5);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 5);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 4);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 6);
  ASSERT_EQ(randgen.uinteger_value(0, 10), 9);
  ASSERT_LT(std::abs(randgen.double_value(0, 10)-3.147143), 1E-6);
  ASSERT_LT(std::abs(randgen.double_value(0, 10)-8.392814), 1E-6);
  ASSERT_LT(std::abs(randgen.double_value(0, 10)- 3.240196), 1E-6);
}
