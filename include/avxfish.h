#pragma once

#include <stddef.h>
#include <stdint.h>

// the block and subkeys pointers must be 64-byte aligned
extern void avxfish(void *block, const void *subkeys);

#define subkey(n, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, sa, sb, sc, sd, se, sf, t0, t1) \
  subkeys[n * 16 + 0x0] = key_w[s0];                                                      \
  subkeys[n * 16 + 0x1] = key_w[s1];                                                      \
  subkeys[n * 16 + 0x2] = key_w[s2];                                                      \
  subkeys[n * 16 + 0x3] = key_w[s3];                                                      \
  subkeys[n * 16 + 0x4] = key_w[s4];                                                      \
  subkeys[n * 16 + 0x5] = key_w[s5];                                                      \
  subkeys[n * 16 + 0x6] = key_w[s6];                                                      \
  subkeys[n * 16 + 0x7] = key_w[s7];                                                      \
  subkeys[n * 16 + 0x8] = key_w[s8];                                                      \
  subkeys[n * 16 + 0x9] = key_w[s9];                                                      \
  subkeys[n * 16 + 0xA] = key_w[sa];                                                      \
  subkeys[n * 16 + 0xB] = key_w[sb];                                                      \
  subkeys[n * 16 + 0xC] = key_w[sc];                                                      \
  subkeys[n * 16 + 0xD] = key_w[sd] + tweak_w[t0];                                        \
  subkeys[n * 16 + 0xE] = key_w[se] + tweak_w[t1];                                        \
  subkeys[n * 16 + 0xF] = key_w[sf] + n;

#define K_S (UINT64_C(0x1BD11BDAA9FC1A22))

void threefish1024_key_schedule(const void *key, const void *tweak, uint64_t * subkeys) {
  uint64_t tweak_w[3];
  uint64_t key_w[17];

  memcpy(key_w, key, 16 * sizeof(uint64_t));
  memcpy(tweak_w, tweak, 2 * sizeof(uint64_t));

  key_w[16] = key_w[0] ^ key_w[1] ^ key_w[2] ^ key_w[3] ^ key_w[4] ^ key_w[5]
            ^ key_w[6] ^ key_w[7] ^ key_w[8] ^ key_w[9] ^ key_w[10] ^ key_w[11]
            ^ key_w[12] ^ key_w[13] ^ key_w[14] ^ key_w[15] ^ K_S;
  tweak_w[2] = tweak_w[0] ^ tweak_w[1];

  subkey( 0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 0, 1);
  subkey( 1,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 1, 2);
  subkey( 2,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0, 2, 0);
  subkey( 3,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1, 0, 1);
  subkey( 4,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1,  2, 1, 2);
  subkey( 5,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1,  2,  3, 2, 0);
  subkey( 6,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1,  2,  3,  4, 0, 1);
  subkey( 7,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1,  2,  3,  4,  5, 1, 2);
  subkey( 8,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1,  2,  3,  4,  5,  6, 2, 0);
  subkey( 9,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1,  2,  3,  4,  5,  6,  7, 0, 1);
  subkey(10, 10, 11, 12, 13, 14, 15, 16,  0,  1,  2,  3,  4,  5,  6,  7,  8, 1, 2);
  subkey(11, 11, 12, 13, 14, 15, 16,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 2, 0);
  subkey(12, 12, 13, 14, 15, 16,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 0, 1);
  subkey(13, 13, 14, 15, 16,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 1, 2);
  subkey(14, 14, 15, 16,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 2, 0);
  subkey(15, 15, 16,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 0, 1);
  subkey(16, 16,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 1, 2);
  subkey(17,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 2, 0);
  subkey(18,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 0, 1);
  subkey(19,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0, 1, 2);
  subkey(20,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,  0,  1, 2, 0);

  // Vectorize all subkeys except the last one, by applying:
  // (0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15)

  for (int i = 0; i < 20; ++i) {
    uint64_t tmp[16];

    tmp[0] = subkeys[16 * i + 0];
    tmp[1] = subkeys[16 * i + 2];
    tmp[2] = subkeys[16 * i + 4];
    tmp[3] = subkeys[16 * i + 6];
    tmp[4] = subkeys[16 * i + 8];
    tmp[5] = subkeys[16 * i + 10];
    tmp[6] = subkeys[16 * i + 12];
    tmp[7] = subkeys[16 * i + 14];
    tmp[8] = subkeys[16 * i + 1];
    tmp[9] = subkeys[16 * i + 3];
    tmp[10] = subkeys[16 * i + 5];
    tmp[11] = subkeys[16 * i + 7];
    tmp[12] = subkeys[16 * i + 9];
    tmp[13] = subkeys[16 * i + 11];
    tmp[14] = subkeys[16 * i + 13];
    tmp[15] = subkeys[16 * i + 15];

    memcpy(&subkeys[16 * i], tmp, sizeof(tmp));
  }
}
