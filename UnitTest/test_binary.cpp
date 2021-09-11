#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Binary, HandlesZeroInput) {
  //        1 2 3 4 5  6  7  8   9   10  11   12   13   14   15    16
  // binary 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768

  // Big endian order    16 15 14 13 12 11 10 9 8  7  6  5  4  3  2  1
  // Little endian order 8  7  6  5  4  3  2  1 16 15 14 13 12 11 10 9

  // short (2 byte)
  ASSERT_EQ(binary::convert(static_cast<GShort>(1)).to_string(), "0000000000000001");
  ASSERT_EQ(binary::convert(static_cast<GShort>(-1)).to_string(), "1111111111111111");
  ASSERT_EQ(binary::convert(static_cast<GShort>(384)).to_string(), "0000000110000000");
  ASSERT_EQ(binary::convert(static_cast<GShort>(32767)).to_string(), "0111111111111111");

  // int32 (4 byte)
  ASSERT_EQ(binary::convert(static_cast<GInt32>(1)).to_string(), "00000000000000000000000000000001");
  ASSERT_EQ(binary::convert(static_cast<GInt32>(-1)).to_string(), "11111111111111111111111111111111");
  ASSERT_EQ(binary::convert(static_cast<GInt32>(384)).to_string(), "00000000000000000000000110000000");
  ASSERT_EQ(binary::convert(static_cast<GInt32>(32767)).to_string(), "00000000000000000111111111111111");

  // long (8 byte)
  ASSERT_EQ(binary::convert(static_cast<GInt>(1)).to_string(), "0000000000000000000000000000000000000000000000000000000000000001");
  ASSERT_EQ(binary::convert(static_cast<GInt>(-1)).to_string(), "1111111111111111111111111111111111111111111111111111111111111111");
  ASSERT_EQ(binary::convert(static_cast<GInt>(384)).to_string(), "0000000000000000000000000000000000000000000000000000000110000000");
  ASSERT_EQ(binary::convert(static_cast<GInt>(32767)).to_string(), "0000000000000000000000000000000000000000000000000111111111111111");

  // double
  ASSERT_EQ(binary::convert(static_cast<GDouble>(1)).to_string(), "0011111111110000000000000000000000000000000000000000000000000000");
  ASSERT_EQ(binary::convert(static_cast<GFloat>(-0.12499062716960907)).to_string(), "10111101111111111111101100010110");

  // todo: this is not correct... Should this throw an error?
  ASSERT_EQ(binary::convert(static_cast<GShort>(32768)).to_string(), "1000000000000000");

  GShort test = 1;
  binary::swapEndian(test);
  ASSERT_EQ(binary::convert(test).to_string(), "0000000100000000");
  ASSERT_EQ(binary::convertSwap(static_cast<GShort>(1)).to_string(), "0000000100000000");
  ASSERT_EQ(binary::convertSwap(static_cast<GFloat>(-0.12499062716960907)).to_string(), "00010110111110111111111110111101");
}