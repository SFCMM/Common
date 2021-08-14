#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Sys, HandlesZeroInput) {
  ASSERT_TRUE(!dateString().empty());
  ASSERT_TRUE(!hostString().empty());
  ASSERT_TRUE(!userString().empty());
  ASSERT_TRUE(!getCWD().empty());
}
