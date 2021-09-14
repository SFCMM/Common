#include <sfcmm_common.h>
#include "gtest/gtest.h"

TEST(Base64, HandlesZeroInput) {
  //        1 2 3 4 5  6  7  8   9   10  11   12   13   14   15    16
  // binary 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768

  // Big endian order    16 15 14 13 12 11 10 9 8  7  6  5  4  3  2  1
  // Little endian order 8  7  6  5  4  3  2  1 16 15 14 13 12 11 10 9


  // char (1 byte)
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
  // A
  // 0000000000000000000000000000000000000000000000000000 000110 000000
  ASSERT_EQ(base64::encode(static_cast<GInt32>(384)), "AAAAGA");

  // int64 (4 byte)
  ASSERT_EQ(base64::encode(static_cast<GInt>(1)), "AAAAAAAAAAB");
  ASSERT_EQ(base64::encode(static_cast<GInt>(63)), "AAAAAAAAAA/");
  // A                                                    G      A
  // 0000000000000000000000000000000000000000000000000000 000110 000000
  ASSERT_EQ(base64::encode(static_cast<GInt>(384)), "AAAAAAAAAGA");
  // I      A      B      A
  // 001000 000000 000001 0000000000000000000000000000000000000000000000
  ASSERT_EQ(base64::encode(binary::getSwappedEndian(static_cast<GInt>(384))), "IABAAAAAAAA"); // this is incorrect for LE!
  // g      A      E      A  (Note: little endian is filled with 0 from right!!!!)
  // 100000 000000 000100 0000000000000000000000000000000000000000000000
  ASSERT_EQ(base64::encodeLE(static_cast<GInt>(384)), "gAEAAAAAAAA");

  // float
  // A     /      g      A      A      A
  // 000000 111111 100000 000000 000000 000000 = 1.0
  ASSERT_EQ(base64::encode(static_cast<GFloat>(1)), "A/gAAA");
  // C      9      /      /      s      W
  // 000010 111101 111111 111111 101100 010110
  ASSERT_EQ(base64::encode(static_cast<GFloat>(-0.12499062716960907)), "C9//sW");
  // A      W      +      /      +      9
  // 000000 010110 111110 111111 111110 111101
  ASSERT_EQ(base64::encode(binary::getSwappedEndian(static_cast<GFloat>(-0.12499062716960907))), "AW+/+9"); // this is incorrect for LE!
  // F      v      v      /      v      Q
  // 000101 101111 101111 111111 101111 010000
  ASSERT_EQ(base64::encodeLE(static_cast<GFloat>(-0.12499062716960907)), "Fvv/vQ");

  // double
  ASSERT_EQ(base64::encode(static_cast<GDouble>(1)), "D/wAAAAAAAA");
  // L      +      /      /      2      L      A      A      A      A      A
  // 001011 111110 111111 111111 110110 001011 000000 000000 000000 000000 000000
  ASSERT_EQ(base64::encode(static_cast<GDouble>(-0.12499062716960907)), "L+//2LAAAAA");

  // A      B
  // 000000 000001
  std::array<GChar, 1> test0 = {1};
  ASSERT_EQ((base64::encode<GChar, 1>(&test0[0])), "AB");

  // A      Q      I      D
  // 000000 010000 001000 000011
  std::array<GChar, 3> test = {1, 2, 3};
  ASSERT_EQ((base64::encode<GChar, 3>(&test[0])), "AQID");
  // A      Q      I      D
  // 000000 010000 001000 000011
//  ASSERT_EQ(base64::encodeLE(&test[0]), "AQID");
  // A      Q      I      D     =   = (padding to next 4 byte boundary)
  // 000000 010000 001000 000011
  //  ASSERT_EQ(base64::encode<4>(&test[0]), "AQID==");


  // A      B      A      g      M      E
  // 000000 000001 000000 100000 001100 000100
  std::array<GChar, 4> testB = {1, 2, 3, 4};
  ASSERT_EQ((base64::encode<GChar, 4>(&testB[0])), "ABAgME");

  // 00000001 00000010 00000011 00000100 00000101 00000110 00000111 00001000
  // A      E      C      A      w      Q      F      B       g      c      I
  // 000000 000100 000010 000000 110000 010000 000101 000001 100000 011100 001000
  std::array<GChar, 8> testC = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ((base64::encode<GChar, 8>(&testC[0])), "AECAwQFBgcI");

  // 00000001 00000010 00000011 00000100 00000101 00000110 00000111 00001000 00001001
  // A      Q      I      D      B      A      U      G      B      w      g      J
  // 000000 010000 001000 000011 000001 000000 010100 000110 000001 110000 100000 001001
  std::array<GChar, 9> testD = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_EQ((base64::encode<GChar, 9>(&testD[0])), "AQIDBAUGBwgJ");

  // A      Q      I      D      B      A
  // 000000 010000 001000 000011 000001 000000
//  ASSERT_EQ(base64::encodeLE(&test[0]), "AQIDBA");
  // A      B      A      g      M      E     =(42) =(48) =(54) =(60) =(64)
  // 000000 000001 000000 100000 001100 000100
//  ASSERT_EQ(base64::encode<4>(&test[0]), "ABAgME=====");
}