#ifndef COMMON_BASE64_H
#define COMMON_BASE64_H

#include "binary.h"
namespace base64 {
static constexpr GChar                         maxValue = 64;
static constexpr GChar                         base64_zero{'A'};
static constexpr std::array<unsigned char, 65> encodeTable{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

// 000001
static constexpr GInt mask_firstBit = 0x01;
// 000011
static constexpr GInt mask_twoBit = 0x03;
// 000111
static constexpr GInt mask_threeBit = 0x07;
// 001111
static constexpr GInt mask_fourBit = 0x0F;
// 011111
static constexpr GInt mask_fiveBit = 0x1F;
// 111111
static constexpr GInt mask_sixBit = 0x3F;

static constexpr std::array<GInt, 7> masks = {0, mask_firstBit, mask_twoBit, mask_threeBit, mask_fourBit, mask_fiveBit, mask_sixBit};

constexpr inline static unsigned char encodeChar(const unsigned char c) { return encodeTable[c]; }
constexpr inline static unsigned char encodeCharMask(const unsigned char c) { return encodeTable[c & mask_sixBit]; }
constexpr inline static unsigned char encodeCharMS(const unsigned char c, const GInt shift, const GInt mask) {
  return encodeTable[(c >> shift) & masks[mask]];
}

inline static auto encode(const GUchar c) -> GString {
  // 128 64 32 16 8 4 2 1
  // example char ex:= 1 = 0000 0001 result should be: 0000 0000 0001
  std::array<GUchar, 2> tmp{base64_zero, base64_zero};
  // ex >> 6 -> 0000 0000
  tmp[0] = encodeCharMS(c, 6, 2);
  // 0x3F = 0011 1111
  tmp[1] = encodeCharMask(c);
  return {std::begin(tmp), std::end(tmp)};
}

inline static auto encode(const GChar c) -> GString {
  std::array<GUchar, 2> tmp{base64_zero, base64_zero};
  tmp[0] = encodeCharMS(c, 6, 2);
  tmp[1] = encodeCharMask(c);
  return {std::begin(tmp), std::end(tmp)};
}

inline static auto encode(const GShort c) -> GString {
  std::array<GUchar, 3> tmp{base64_zero, base64_zero, base64_zero};
  tmp[0] = encodeCharMS(c, 12, 4);
  tmp[1] = encodeCharMS(c, 6, 6);
  tmp[2] = encodeCharMask(c);
  return {std::begin(tmp), std::end(tmp)};
}

inline static auto encode(const GInt32 c) -> GString {
  static constexpr GInt num_chars = 6;
  static constexpr GInt shift     = (num_chars - 1) * 6;

  std::array<GUchar, num_chars> tmp;
  tmp.fill(base64_zero);
    tmp[0]                      = encodeChar((c >> shift) & mask_twoBit);
//  tmp[0] = encodeCharMS(c, shift, 2);
  for(int i = 1; i < num_chars; ++i) {
//    std::cerr << "before " << tmp[i] << std::endl;
//    std::cerr << "before " << encodeTable[(c >> (shift - i * 6)) & masks[6]] << std::endl;
//    tmp[i] = encodeCharMS(c, (shift - i * 6), 6);
    tmp[i] = encodeTable[(c >> (shift - i * 6)) & masks[6]];
//    std::cerr << tmp[i] << std::endl;
  }
  return {std::begin(tmp), std::end(tmp)};
}

inline static auto encode(const GFloat c) -> GString {
  static constexpr GInt num_chars = 6;
  static constexpr GInt shift     = (num_chars - 1) * 6;

  std::array<GUchar, num_chars> tmp;
  GFloat                        tmp_double = c;
  uint64_t                      tmp_int    = *(static_cast<uint64_t*>(static_cast<void*>(&tmp_double)));
//  tmp[0]                                   = encodeCharMS(tmp_int, shift, 2);
  tmp[0] = encodeTable[(tmp_int >>shift ) & masks[2]];

  for(int i = 1; i < num_chars; ++i) {
//    tmp[i] = encodeCharMS(tmp_int, shift - i * 6, 6);
    tmp[i] = encodeTable[(tmp_int >> (shift - i * 6)) & masks[6]];
  }
  return {std::begin(tmp), std::end(tmp)};
}

inline static auto encode(const GInt c) -> GString {
  static constexpr GInt num_chars = 11;
  static constexpr GInt shift     = (num_chars - 1) * 6;

  std::array<GUchar, num_chars> tmp;
//  tmp[0] = encodeCharMS(c, shift, 4);
  tmp[0] = encodeTable[(c >>shift ) & masks[4]];
  for(int i = 1; i < num_chars; ++i) {
//    tmp[i] = encodeCharMS(c, shift - i * 6, 6);
    tmp[i] = encodeTable[(c >> (shift - i * 6)) & masks[6]];
  }
  return {std::begin(tmp), std::end(tmp)};
}

inline static auto encode(const GDouble c) -> GString {
  static constexpr GInt num_chars = 11;
  static constexpr GInt shift     = (num_chars - 1) * 6;

  std::array<GUchar, num_chars> tmp;
  GDouble                       tmp_double = c;
  uint64_t                      tmp_int    = *(static_cast<uint64_t*>(static_cast<void*>(&tmp_double)));
//  tmp[0]                                   = encodeCharMS(tmp_int, shift, 4);
  tmp[0] = encodeTable[(tmp_int >>shift ) & masks[4]];
  for(int i = 1; i < num_chars; ++i) {
//    tmp[i] = encodeCharMS(tmp_int, shift - i * 6, 6);
    tmp[i] = encodeTable[(tmp_int >> (shift - i * 6)) & masks[6]];
  }
  return {std::begin(tmp), std::end(tmp)};
}


} // namespace base64

#endif // COMMON_BASE64_H
