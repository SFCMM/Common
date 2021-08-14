#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Constant, HandlesZeroInput) {
  ASSERT_EQ(resolveGeomType("sphere"), GeomType::sphere);
  ASSERT_EQ(resolveGeomType("cube"), GeomType::cube);
  ASSERT_EQ(resolveGeomType("box"), GeomType::box);
  ASSERT_EQ(resolveGeomType("stl"), GeomType::stl);
  ASSERT_EQ(resolveGeomType("STL"), GeomType::unknown);
}
