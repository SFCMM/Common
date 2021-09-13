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


template <typename T>
inline static auto encode(const T c) -> GString {
  static constexpr GInt num_chars  = gcem::ceil(sizeof(T) * 8 / 6.0);
  static constexpr GInt shift      = (num_chars - 1) * 6;
  static constexpr GInt init_shift = sizeof(T) * 8 - shift;


  std::array<GUchar, num_chars> tmp{};
  T                             tmp_val = c;
  uint64_t                      tmp_int = *(static_cast<uint64_t*>(static_cast<void*>(&tmp_val)));
  tmp[0]                                = encodeTable[(tmp_int >> shift) & masks[init_shift]];
  for(int i = 1; i < num_chars; ++i) {
    tmp[i] = encodeTable[(tmp_int >> (shift - i * 6)) & masks[6]];
  }
  return {std::begin(tmp), std::end(tmp)};
}


} // namespace base64

#endif // COMMON_BASE64_H
