#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Base64, HandlesZeroInput) {
  //        1 2 3 4 5  6  7  8   9   10  11   12   13   14   15    16
  // binary 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768

  // Big endian order    16 15 14 13 12 11 10 9 8  7  6  5  4  3  2  1
  // Little endian order 8  7  6  5  4  3  2  1 16 15 14 13 12 11 10 9


  //char (1 byte)
  ASSERT_EQ(base64::encodeChar(static_cast<GChar>(1)), 'B');
  ASSERT_EQ(base64::encodeChar(static_cast<GChar>(63)), '/');
  ASSERT_EQ(base64::encode(static_cast<GUchar>(1)), "AB");
  ASSERT_EQ(base64::encode(static_cast<GUchar>(128)), "CA");
  ASSERT_EQ(base64::encode(static_cast<GUchar>(255)), "D/");
  ASSERT_EQ(base64::encode(static_cast<GChar>(1)), "AB");
  ASSERT_EQ(base64::encode(static_cast<GChar>(63)), "A/");
  ASSERT_EQ(base64::encode(static_cast<GChar>(127)), "B/");


  // short (2 byte)
  ASSERT_EQ(base64::encode(static_cast<GShort>(1)), "AAB");
  ASSERT_EQ(base64::encode(static_cast<GShort>(63)), "AA/");

  // int32 (4 byte)
  ASSERT_EQ(base64::encode(static_cast<GInt32>(1)), "AAAAAB");
  ASSERT_EQ(base64::encode(static_cast<GInt32>(63)), "AAAAA/");
  //A
  //0000000000000000000000000000000000000000000000000000 000110 000000
  ASSERT_EQ(base64::encode(static_cast<GInt32>(384)), "AAAAGA");

  // int64 (4 byte)
  ASSERT_EQ(base64::encode(static_cast<GInt>(1)), "AAAAAAAAAAB");
  ASSERT_EQ(base64::encode(static_cast<GInt>(63)), "AAAAAAAAAA/");
  //A                                                    G      A
  //0000000000000000000000000000000000000000000000000000 000110 000000
  ASSERT_EQ(base64::encode(static_cast<GInt>(384)), "AAAAAAAAAGA");
  //I      A      B      A
  //001000 000000 000001 0000000000000000000000000000000000000000000000
  ASSERT_EQ(base64::encode(binary::getSwappedEndian(static_cast<GInt>(384))), "IABAAAAAAAA"); // this is incorrect!
  //g      A      E      A  (Note: little endian is filled with 0 from right!!!!)
  //100000 000000 000100 0000000000000000000000000000000000000000000000
  //  ASSERT_EQ(base64::encodeLE(static_cast<GInt>(384)), "gAEAAAAAAAA");

  // float
  // A     /      g      A      A      A
  //000000 111111 100000 000000 000000 000000 = 1.0
  ASSERT_EQ(base64::encode(static_cast<GFloat>(1)), "A/gAAA");
  //C      9      /      /      s      W
  //000010 111101 111111 111111 101100 010110
  ASSERT_EQ(base64::encode(static_cast<GFloat>(-0.12499062716960907)), "C9//sW");
  //A      W      +      /      +      9
  //000000 010110 111110 111111 111110 111101
  ASSERT_EQ(base64::encode(binary::getSwappedEndian(static_cast<GFloat>(-0.12499062716960907))), "AW+/+9");//this is incorrect

  // double
  ASSERT_EQ(base64::encode(static_cast<GDouble>(1)), "D/wAAAAAAAA");
  //L      +      /      /      2      L      A      A      A      A      A
  //001011 111110 111111 111111 110110 001011 000000 000000 000000 000000 000000
  ASSERT_EQ(base64::encode(static_cast<GDouble>(-0.12499062716960907)), "L+//2LAAAAA");

}