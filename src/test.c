#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "avxfish.h"

static int avxfish_test(const char* output, const char* input, const char *key, const char *tweak) {
  __attribute__((aligned(64))) uint64_t input_bytes[16];
  __attribute__((aligned(64))) uint64_t subkeys[336];

  threefish1024_key_schedule(key, tweak, subkeys);
  memcpy(input_bytes, input, sizeof(input_bytes));
  avxfish(input_bytes, subkeys);

  return (memcmp(input_bytes, output, sizeof(input_bytes)) == 0);
}

#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION __FILE__ ":" S2(__LINE__)
#define TEST(FUNC, WHERE, INFO, OUTPUT, INPUT, KEY, TWEAK) \
  do {                                                     \
    if (!FUNC(OUTPUT, INPUT, KEY, TWEAK)) {                \
      printf("FAIL "#FUNC" ["WHERE"] - "INFO"\n");         \
      return EXIT_FAILURE;                                 \
    } else {                                               \
      printf("PASS "#FUNC" ["WHERE"] - "INFO"\n");         \
    }                                                      \
  } while (0)

int main(void) {
  TEST(avxfish_test, LOCATION, "SHA3 KAT test 1 (all zeroes)",
    "\xf0\x5c\x3d\x0a\x3d\x05\xb3\x04\xf7\x85\xdd\xc7\xd1\xe0\x36\x01"
    "\x5c\x8a\xa7\x6e\x2f\x21\x7b\x06\xc6\xe1\x54\x4c\x0b\xc1\xa9\x0d"
    "\xf0\xac\xcb\x94\x73\xc2\x4e\x0f\xd5\x4f\xea\x68\x05\x7f\x43\x32"
    "\x9c\xb4\x54\x76\x1d\x6d\xf5\xcf\x7b\x2e\x9b\x36\x14\xfb\xd5\xa2"
    "\x0b\x2e\x47\x60\xb4\x06\x03\x54\x0d\x82\xea\xbc\x54\x82\xc1\x71"
    "\xc8\x32\xaf\xbe\x68\x40\x6b\xc3\x95\x00\x36\x7a\x59\x29\x43\xfa"
    "\x9a\x5b\x4a\x43\x28\x6c\xa3\xc4\xcf\x46\x10\x4b\x44\x31\x43\xd5"
    "\x60\xa4\xb2\x30\x48\x83\x11\xdf\x4f\xee\xf7\xe1\xdf\xe8\x39\x1e",
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");

  TEST(avxfish_test, LOCATION, "SHA3 KAT test 2 (sequential bytes)",
    "\xa6\x65\x4d\xdb\xd7\x3c\xc3\xb0\x5d\xd7\x77\x10\x5a\xa8\x49\xbc"
    "\xe4\x93\x72\xea\xaf\xfc\x55\x68\xd2\x54\x77\x1b\xab\x85\x53\x1c"
    "\x94\xf7\x80\xe7\xff\xaa\xe4\x30\xd5\xd8\xaf\x8c\x70\xee\xbb\xe1"
    "\x76\x0f\x3b\x42\xb7\x37\xa8\x9c\xb3\x63\x49\x0d\x67\x03\x14\xbd"
    "\x8a\xa4\x1e\xe6\x3c\x2e\x1f\x45\xfb\xd4\x77\x92\x2f\x83\x60\xb3"
    "\x88\xd6\x12\x5e\xa6\xc7\xaf\x0a\xd7\x05\x6d\x01\x79\x6e\x90\xc8"
    "\x33\x13\xf4\x15\x0a\x57\x16\xb3\x0e\xd5\xf5\x69\x28\x8a\xe9\x74"
    "\xce\x2b\x43\x47\x92\x6f\xce\x57\xde\x44\x51\x21\x77\xdd\x7c\xde",
    "\xff\xfe\xfd\xfc\xfb\xfa\xf9\xf8\xf7\xf6\xf5\xf4\xf3\xf2\xf1\xf0"
    "\xef\xee\xed\xec\xeb\xea\xe9\xe8\xe7\xe6\xe5\xe4\xe3\xe2\xe1\xe0"
    "\xdf\xde\xdd\xdc\xdb\xda\xd9\xd8\xd7\xd6\xd5\xd4\xd3\xd2\xd1\xd0"
    "\xcf\xce\xcd\xcc\xcb\xca\xc9\xc8\xc7\xc6\xc5\xc4\xc3\xc2\xc1\xc0"
    "\xbf\xbe\xbd\xbc\xbb\xba\xb9\xb8\xb7\xb6\xb5\xb4\xb3\xb2\xb1\xb0"
    "\xaf\xae\xad\xac\xab\xaa\xa9\xa8\xa7\xa6\xa5\xa4\xa3\xa2\xa1\xa0"
    "\x9f\x9e\x9d\x9c\x9b\x9a\x99\x98\x97\x96\x95\x94\x93\x92\x91\x90"
    "\x8f\x8e\x8d\x8c\x8b\x8a\x89\x88\x87\x86\x85\x84\x83\x82\x81\x80",
    "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f"
    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f"
    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f"
    "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f"
    "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f"
    "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f"
    "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f"
    "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f",
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\x2f\x93\x8b\x4c\x66\x9c\x73\x9d\x6b\x4e\x0f\x82\x4a\x03\x5b\xb8"
    "\x74\x32\xe0\x4a\xe7\x89\xda\x53\xf3\xd1\x37\x72\x90\xed\x44\x28"
    "\x5d\xce\x77\x4f\xe0\xb4\x56\x01\xd7\x8d\x71\xb3\x85\x62\x59\x60"
    "\xab\xee\xaa\xeb\xf8\x0a\x32\x11\x5d\x24\xd6\xec\xd8\x36\x0a\xca"
    "\xe1\xf0\x97\xfd\x78\x43\xf8\xda\xdd\x98\xa2\xc0\x4e\x6d\x47\x5a"
    "\xea\x8b\x8c\xa8\x09\x6f\x52\x5d\x5f\xa4\x16\xb4\x35\xca\xa9\xfc"
    "\xea\x96\x63\x9e\xbe\xef\xab\x4b\xc9\xbc\xe4\x4f\x32\x4f\x6b\x1d"
    "\x6c\x0f\xa2\xa5\x94\x9a\xb3\x9b\x9c\x60\x1e\x3a\x1e\x65\x1d\x21",
    "\x52\x07\x12\x53\x7c\xa7\xf2\x0e\x7c\x04\x48\xbc\xd7\x64\x40\x3f"
    "\x5f\x58\x05\xda\x36\x86\xea\xcd\x8a\x7a\xd7\xc6\x30\x15\x45\xd0"
    "\x10\x5d\x5b\x97\xfa\xea\xeb\x91\x00\xd8\x10\x8f\xa4\x23\xbe\x8f"
    "\x1c\xe4\x24\x09\x98\x03\xaa\xfa\x9f\x81\x70\xf0\xb5\xfe\x08\x42"
    "\x7a\x9c\xa2\xbd\x99\xbf\x55\xee\x8b\xa5\x80\x0f\xa9\xa9\x9b\xd6"
    "\x12\xb4\x18\xf0\x32\xf6\x68\x7d\x54\xee\xb7\x0a\x0b\x12\x9f\xbc"
    "\x5b\x66\xe2\x25\x05\x9c\x00\x60\x3b\x29\x4c\x54\xe7\xfe\x4f\x38"
    "\x2b\x1d\xf5\x22\x5e\x68\xd8\xb3\x17\x06\x10\xba\xc1\x7e\x74\xba",
    "\x9b\x0b\xbe\x9f\x88\x3a\x6a\xdb\x03\x22\x74\x7c\x8e\xe1\x5d\x04"
    "\xf6\xb8\x33\x81\xc2\x58\xce\xac\x49\x62\x05\xb8\x06\xe3\x1a\xa5"
    "\x28\x15\x38\x91\x1d\xe4\xb7\x76\x0b\xd7\x9e\x40\xa4\xea\xf4\xcf"
    "\xec\x78\x7b\x1f\xf3\x84\x94\xaa\xd2\xb0\x10\x14\x14\x73\x8d\x24"
    "\x27\x9e\xa6\x3b\xc1\x44\xb9\xf5\x70\xfb\x95\x35\x0e\xb1\xeb\x15"
    "\x72\xb5\x71\xb2\xaf\x88\xe4\xf3\x22\xd5\xfd\x61\xb3\xa7\xe8\xb1"
    "\x70\x73\x56\x14\x1b\x6d\x19\x54\x4e\xf3\x34\x57\x66\x86\xbb\xaa"
    "\x9e\x0d\x43\xfa\xbe\x5e\xc8\x13\xdc\x63\x5a\xf8\xb9\x10\xb6\x9f",
    "\x73\x1b\x8c\xdc\xfe\x20\x59\x22\xe8\x27\xc2\xcd\x8b\x2a\xb3\xed"
    "\x2f\x93\x8b\x4c\x66\x9c\x73\x9d\x6b\x4e\x0f\x82\x4a\x03\x5b\xb8");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\xd1\xa9\xc1\x6b\x89\xf5\xde\xc5\xf7\x4a\x19\xed\x3b\x38\x42\x55"
    "\x96\x4d\xc3\x00\x46\xe3\x4f\x4d\x34\xd2\xc1\x9f\x2d\x8d\x26\xfd"
    "\x98\xbb\x6c\x19\x40\xb8\xa3\x30\x3c\x4e\xc1\x15\xc5\x0f\x6e\x87"
    "\x4a\xd1\xb7\x42\x3d\x25\xb0\x60\xb2\xdd\x2b\x51\x78\xd0\x41\x64"
    "\x76\x32\x9e\x94\x18\xff\x3a\xa5\x9a\xb3\xc8\xc2\x79\xfe\x5a\x76"
    "\x38\x24\xfe\x07\xa7\xe9\xfc\xf4\x02\xb8\x90\x0a\x5e\xde\xcf\x2a"
    "\x2a\xcc\x43\x31\x45\xb2\xb2\x87\x85\xa2\xa2\x42\xeb\x2d\xb7\x22"
    "\x11\xad\xd0\x53\x58\x20\x4f\x4a\x74\xa8\x0a\xd0\xb3\xbb\x74\x5c",
    "\x55\x4a\x44\xac\x75\x8c\xef\xa9\x62\xd6\x76\x23\xf2\x7f\xe5\x5e"
    "\xdd\x10\xce\x52\x6e\x07\x62\x0c\xa0\xf6\xd7\x11\x6d\xb5\x54\x38"
    "\x0f\xe9\xc9\x0e\x39\x49\x92\x3b\xa5\xc4\xf7\x88\xcc\x04\x29\x52"
    "\x85\x16\x78\x85\x39\x4d\x24\xfd\xb9\x46\x96\x15\x0c\x83\x55\x6e"
    "\x11\x29\xa8\x3b\x7e\xac\x11\x6c\x6a\x7b\x80\x63\xa9\xc2\xbb\xd9"
    "\xb4\x56\xb2\x3d\x1a\xd2\x92\xf5\xf0\xfd\x00\xfe\x46\xa8\xf1\xce"
    "\x84\x02\xb6\x66\x29\xfb\x77\xb8\x61\xd9\x15\x0b\x97\x5c\x35\x2e"
    "\x50\xf0\x6f\xd7\x8f\x54\xc3\x6f\xc1\x87\x1f\x31\x46\x3f\xb8\x34",
    "\xd7\x1a\x79\xd7\x8a\x67\x77\x6f\xee\xa4\xf9\x43\x88\x34\xa9\x35"
    "\x24\xb7\x80\x30\xfd\x12\x7d\x9f\x4f\x92\xc6\x0c\xf6\x9f\xeb\x32"
    "\x49\xdd\x3c\x37\x15\x9c\x55\x32\x31\x7c\xd5\x64\x3e\x20\x3c\x38"
    "\x3c\x4e\x24\xb1\xcf\xcb\x88\xc9\xc1\xb0\xce\x62\x19\x35\xd5\xdb"
    "\x84\x89\xaf\xe1\x88\xa2\xa9\xca\xb2\x00\x90\x8d\xe6\xfe\x30\xcd"
    "\x03\x5c\x91\x30\xe9\x2b\x3e\xfc\x70\x71\x60\xa9\xc0\x01\x81\xa5"
    "\x25\x36\x3f\xd0\x39\xbb\xf1\x68\xb5\x62\xd7\x5b\xb3\x88\x2b\xb9"
    "\x30\x06\x56\x98\xd2\x07\x0c\x25\x48\xd6\x92\xb6\x8d\x7b\x6d\x08",
    "\xad\xcf\x8d\x65\x79\x7f\xda\x9b\xab\x65\x3c\x57\xd0\xa7\x32\x99"
    "\xd1\xa9\xc1\x6b\x89\xf5\xde\xc5\xf7\x4a\x19\xed\x3b\x38\x42\x55");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\x73\xf7\x7a\xfc\x64\xca\x8f\xbd\xea\xa6\xa5\xef\x0e\xab\xcc\xef"
    "\xc3\xae\x84\x08\x97\xee\xfa\xcc\x11\x01\x3f\x70\x29\xce\x06\xda"
    "\xfb\x88\x11\x0f\x4a\x58\xdf\x37\x8f\x01\xe5\xf2\x3b\x20\xe5\xcb"
    "\xfe\x77\xe2\x59\xb5\xa2\x8c\x5d\xa4\xe4\x23\xff\x39\x5c\x53\x8d"
    "\x8a\x78\x14\x99\xcf\xa7\x12\x3c\x0c\x0c\xa5\x0d\xd7\x1a\x0a\x68"
    "\xa1\x41\x32\x27\xda\x55\xfe\x94\x54\x6c\x62\x29\xa3\x68\xef\x20"
    "\xc7\xc7\x94\x30\xf1\x3a\x24\x46\xf5\xc0\x1d\xa1\x8e\xe5\x3d\x20"
    "\xde\x1d\xa0\x8c\x10\x43\xc1\x5d\xbf\x6e\xa8\x0d\x2d\x52\x8a\x5b",
    "\x9d\x0c\xa5\xf9\x05\xc6\x9c\xcd\x5a\x13\x1b\x2a\x10\xc9\x45\xe6"
    "\x0e\x9c\xc5\xc9\x17\x33\xf4\x48\x79\x18\xd4\x52\xde\xfc\x7d\x7e"
    "\x51\x54\x54\x36\x61\xcc\xb8\x1f\x50\xba\xaa\x89\xa4\x52\xde\xad"
    "\xeb\x45\x1e\xab\xe5\xd6\x8c\xce\x2c\x00\x96\x5e\x0f\x5c\x81\x1c"
    "\x0b\xab\xdd\xaa\xce\x60\x75\x36\xb8\x78\xbf\x88\x87\xbb\xef\x74"
    "\x39\x24\x76\xd9\x4e\x9e\x69\x65\x0a\x6f\xb3\x98\xdc\x42\x2b\xc6"
    "\xd6\x7a\xb9\x90\x8e\xcb\x02\x18\x0d\xd5\x7e\xfb\xc1\x26\xf4\x50"
    "\xd7\x16\x1e\x97\xd4\xa3\x92\xe2\x42\x60\x25\x1c\x98\xd2\x2f\x56",
    "\x24\x7b\x0a\x11\x80\xc8\xe7\x9e\xdd\x4a\xe7\xf3\x98\x91\x96\x5c"
    "\xf8\xc8\x3a\x20\x44\x61\x4e\xc9\x3b\x89\x72\x65\x97\xca\x58\x8b"
    "\x1a\x16\x1d\x6b\x69\x56\x14\x31\x37\x24\x0d\x88\x85\x22\xd0\x2f"
    "\x01\x3f\x7c\x80\x77\x9d\xf5\xdc\x89\xd6\x89\x3a\xb0\xed\x0a\x6c"
    "\x61\x2a\x56\xc3\x80\x5a\x2f\xa1\x36\x4e\xd6\xce\xe5\x08\xd7\xfa"
    "\x1f\x16\xce\x44\x3a\xc3\xd4\x21\xdd\xc9\xf7\x3a\x53\xcb\xb6\x64"
    "\xea\x4c\x54\x07\x2e\xf7\x30\x0c\x87\xc0\x6d\x5b\x3d\xec\xec\xca"
    "\xca\x90\xa6\xac\x62\xd6\xbb\x9f\xb7\xc1\x5b\xe6\x42\x8c\x22\x06",
    "\x0f\xe6\xb8\x7c\xa1\x28\xba\x00\x7b\xb0\xd4\x4f\x5a\x6b\xec\xb4"
    "\x73\xf7\x7a\xfc\x64\xca\x8f\xbd\xea\xa6\xa5\xef\x0e\xab\xcc\xef");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\x7f\x46\xc4\xa5\x8e\x89\xa7\x1e\x75\x42\x39\xe1\x89\x95\x44\xdd"
    "\x9b\xe4\x2c\x85\xcf\xb8\xce\x64\x5f\xe8\x6f\xb1\xeb\x15\x6b\xee"
    "\x69\x0b\x1f\x4e\x69\x25\x65\x51\xd2\x8d\xe2\x43\xb3\xd9\x9d\xfb"
    "\x8b\x1f\x4b\x82\xf6\x37\x98\xf3\x88\x6a\xfc\x5d\x37\x02\xf3\x87"
    "\x7b\x99\x0c\x28\x45\x06\x81\xc7\x91\xe1\xc7\x2e\x80\x3f\xd4\x5f"
    "\x28\x7f\xac\xe8\x82\x79\x2d\xbb\x18\xd5\x1b\xb7\xa1\x88\xd1\xb9"
    "\x0d\x47\xce\xf5\xc6\xb2\x0a\xa2\x5c\x28\xf1\xb6\xb2\xfb\xce\xf9"
    "\xe1\x46\x1e\x9e\xbb\xa0\x9a\x9a\xb5\xab\xb5\xe0\xf6\x40\x07\x6f",
    "\xec\x0b\xb7\x5b\x16\x59\x1a\x36\x78\xa7\xad\x43\x71\x01\x23\xe5"
    "\x07\x8a\x1e\x9a\x1e\x3e\x34\xb4\x2f\x11\x05\xa1\x89\xd9\xaa\x51"
    "\x90\x36\xc6\x46\x0c\x57\x70\xda\x0d\x40\x5a\x76\xa7\x26\xf7\x03"
    "\x53\x37\x0a\xfe\x01\x58\x62\x12\x1e\x81\x34\x5c\x46\x2d\xfb\xc6"
    "\x6a\x68\x7a\x8c\xbd\xed\x16\x8e\x52\xad\x06\x62\x8c\x8a\xbf\xd6"
    "\x4d\x9f\xa5\x43\x0f\x81\x30\x5a\x1e\x08\x10\x71\xf9\x24\x4c\xe3"
    "\x39\x61\xad\x41\xd4\xe1\xd2\x86\x42\x15\xf9\xf0\x81\xac\x0f\x67"
    "\x11\x26\x6c\x7a\x2a\x45\x97\xec\x5a\x2c\x87\x47\x31\xd6\x82\x88",
    "\x6c\x12\xe6\xbc\x9e\x56\x7b\x61\x33\x55\x41\x4c\x04\x5f\x75\xce"
    "\xe8\x84\xeb\x97\x3c\x73\xec\x99\x01\xa0\x6f\x64\xc5\x42\xa8\xb2"
    "\xdb\xaf\xd0\xe4\x84\x41\x0c\xa0\xeb\x12\xe2\xe4\x4f\x51\x78\x88"
    "\x3a\x1a\x7d\x17\x56\x72\x32\x6f\x52\x78\xf7\xdb\x83\x3e\x30\x4e"
    "\xfd\x75\x67\x7b\xe4\x1f\xff\x34\x0f\x86\x09\x4c\x8f\x87\x50\x2a"
    "\x3e\xc7\x2b\x62\x30\x25\x0f\x82\x07\x24\x6a\x9d\xfb\xb9\xfa\x99"
    "\x82\xde\xa4\xbc\xc2\x04\x3b\xf0\x8f\x53\x86\xf3\x14\xcd\x8f\x48"
    "\xc8\xbe\x67\x40\x5b\xfc\xcb\xd9\x01\x54\x1c\x09\xf3\x40\x3d\x93",
    "\x96\x2d\x90\x22\xc2\x22\x7d\x15\xa2\xf8\x65\x77\x5e\x1a\xb9\x0f"
    "\x7f\x46\xc4\xa5\x8e\x89\xa7\x1e\x75\x42\x39\xe1\x89\x95\x44\xdd");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\x55\x24\x6b\x01\x66\x47\xd8\xd2\x9b\xb2\xdb\x13\x3a\x11\xa4\x51"
    "\x05\xf5\xf5\xba\x23\x0c\x66\x19\x79\xca\x27\x5a\x99\xd8\x0b\xff"
    "\xbe\xfd\x87\x86\xa4\xeb\xa5\xbe\xba\x9f\x1d\x39\xb9\xdb\xb4\x58"
    "\xdf\x08\xb0\x5d\xdc\xc3\x63\x2e\xf1\xaf\x98\xc2\xa6\x9e\x74\x03"
    "\xd8\xd3\xb9\x27\x5c\x79\xf0\xed\xca\x88\xa7\x5a\x21\x61\x54\x7f"
    "\xa7\xf2\x58\x46\x8b\x4a\xea\x3d\xce\xba\x63\xb3\xce\xbf\x16\x16"
    "\xb6\xc9\x0a\x80\x66\x7e\x71\x10\x5c\x58\xb5\xc0\xfa\xc6\x6a\xb5"
    "\x0a\x89\x29\x6c\x23\x32\x13\xe6\xdf\xef\x5f\xcd\x83\xb3\xef\x4f",
    "\x05\x71\xb2\xf7\xc2\x1d\x71\xb8\xab\x2d\xc0\x11\xdc\x02\xc0\x57"
    "\x1a\x1d\xf7\x0b\x69\xcf\x35\x0b\xa0\x5a\x48\x7e\x51\xe8\x95\xff"
    "\xf5\xaa\xf5\x8e\x12\x95\xec\x05\xf2\x08\x97\x71\xc5\x7c\x0f\x0a"
    "\x99\xf0\x6b\xec\xdb\xc5\x22\x53\x2a\x4f\xe2\xaa\x1a\x01\xa3\x2e"
    "\xc1\xca\x9d\xa9\x37\x40\x39\x6e\xef\x25\x7e\x78\xf6\xc1\x85\xd5"
    "\x0e\x72\x55\x23\x8b\xe7\xf7\x28\x13\xb7\x1c\x29\xa8\xac\xda\x74"
    "\x21\x93\x03\x04\x1a\x52\x40\xf7\xc7\xe4\xdd\xf7\xf8\xb3\x25\xba"
    "\x0f\xbe\x03\xa0\xad\x2e\x6d\x41\xd3\x18\x33\x36\xb3\xfd\x11\x1f",
    "\xae\x16\x40\x3c\x28\x2a\xb1\xba\x91\xce\xd4\x45\xf7\xee\xb1\xce"
    "\x3f\xfa\xd8\xa2\x5c\x37\x8f\xbd\x51\x7c\x38\x37\x3e\x93\xb6\xb0"
    "\x1d\xec\xb6\x5e\x5d\x48\xa1\x8c\x5f\x3a\x86\xe9\x59\x5a\x7c\x04"
    "\xb5\x8e\x7e\x7d\x81\xc7\xca\x14\x5b\xc1\xc0\xa7\x27\x29\x0c\x3c"
    "\x1e\x2c\xb6\x78\x6f\x5a\x93\x63\xbd\xd1\xcf\x98\x79\x99\xef\x46"
    "\x9f\xab\x1c\x8d\x63\xc4\x55\xe6\x4d\x91\x2f\x13\xea\x2e\x82\xe8"
    "\xe7\x77\xb6\x8e\xeb\x11\x7a\x53\xae\xe4\x0d\x85\xa3\xd2\x28\x47"
    "\x4d\x12\xc2\x1d\xf2\xed\x25\x34\x25\xb0\x0f\x2b\xe9\xd8\xb7\x20",
    "\x51\xcb\x26\xbd\x97\xc3\xe0\x11\x51\xd9\x87\x9d\xdd\x19\x42\x6c"
    "\x55\x24\x6b\x01\x66\x47\xd8\xd2\x9b\xb2\xdb\x13\x3a\x11\xa4\x51");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\xe5\xc2\xa7\x08\x90\xbf\xf0\xfc\xf8\x72\x61\x4c\x2d\xea\x77\x95"
    "\xa0\x5b\xc0\x06\x58\xdb\xc9\x86\xe4\x1d\x43\x75\xaf\x5c\x09\xf2"
    "\xde\x5d\x15\x07\x63\x6a\x69\xf1\x79\xdc\xdd\x79\xc9\xba\xb1\x0f"
    "\x47\xe0\x82\x2e\x6c\xe7\x63\xb3\xc2\x59\x14\x80\x83\x8a\x67\xc5"
    "\x22\xe1\x8e\xae\x8f\xcf\x38\xdf\x76\x69\x8c\x31\x98\x85\x1f\x37"
    "\x43\x1e\x0d\x33\xb7\x78\x9f\x52\x7b\x83\xb4\x59\x2d\xdb\x90\xe9"
    "\xc9\x53\xa4\xdc\xe4\x8d\xef\xd1\xde\x09\x9e\x25\xfb\xef\xae\x5a"
    "\x96\xcb\x55\x64\x0f\xba\x7c\x1d\xd2\x5c\x33\xa2\x4c\x3f\x79\x61",
    "\x04\x07\x25\x53\x79\x4c\xfd\x33\x1c\x2e\x4e\x81\x53\x18\x4a\xb1"
    "\x30\x2c\x2c\x00\x26\x76\x53\x8f\x46\x21\x30\xb2\x61\x16\xad\x71"
    "\x0b\x9c\xc8\x7f\xb6\xc6\xbb\x74\xa2\x9a\xb9\x39\x49\x33\x61\xd4"
    "\x42\xa3\x0c\xf8\x18\xcb\x14\xd4\xd4\x89\xbb\xa7\x11\xfb\x7f\xde"
    "\x3f\xcb\xa3\x0d\x81\x8f\x18\x4c\xd3\x7a\x97\x93\xfc\x1a\x5d\x3c"
    "\x79\xe7\xca\xd8\xcc\xe1\xcc\xd1\x02\x2d\x6c\x41\x4e\xe3\x53\x47"
    "\x26\xe8\x22\x3c\x29\xd3\x4a\x94\xef\xe5\x82\xc4\x81\x7c\xc7\xa0"
    "\xf2\xde\x49\x03\x37\x67\x7b\xcd\xbd\xc7\xd8\x0f\x33\x2d\x4f\xe9",
    "\xdd\x9f\x4c\x3a\x7b\xa0\xd3\xfe\xfb\xb2\xb6\xbe\xe3\x36\xaf\xfc"
    "\xf9\xbe\x2a\x48\x1a\xd8\xc5\x6a\x4d\x99\x24\x66\xfc\x19\x12\xdd"
    "\x9d\x37\x9c\xee\xf6\x09\x55\x01\x95\xd2\x4c\x1a\x4f\xf6\xa4\x6c"
    "\x70\x0a\x22\xc2\xbe\xd3\x3f\xb6\x6f\x8d\xc2\x04\xda\x72\xcf\xc1"
    "\x81\x4b\xc3\xbc\xd8\x95\x64\xec\xd5\x8e\x21\xa8\x8e\x7b\xf8\x9c"
    "\x07\x1c\xf4\x4b\x68\xe4\x2d\x9f\x4b\x99\xc0\x68\x5b\xab\x1f\xcc"
    "\x2e\xf0\xc1\xef\x1d\xf5\xa4\x4c\xc1\x5c\x26\xd0\xa8\xd4\xc3\xee"
    "\x88\x14\x1a\x72\xd7\x81\xfb\x6b\xb2\x3f\x8b\x59\x8b\xfb\xcd\x41",
    "\x32\xd2\xc5\x32\x66\x7f\x8e\x41\x1a\x39\x17\xb6\x03\x3d\xb8\x58"
    "\xe5\xc2\xa7\x08\x90\xbf\xf0\xfc\xf8\x72\x61\x4c\x2d\xea\x77\x95");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\x69\xe0\xa6\x45\xca\x9c\xad\xd4\x1a\x40\x9b\x56\x24\x66\xd3\x51"
    "\x92\xd6\x0c\x25\xc8\xa8\x91\x3e\xb6\xf3\xbc\x33\xe8\x20\xca\x4a"
    "\x6d\xed\xca\x93\xe8\x3c\xf8\x5e\xcd\xc6\x4a\xca\x4a\x33\xda\x58"
    "\xa6\xdf\xde\x37\x7f\x3b\xfc\x43\x6d\x8b\x2e\x79\x7a\xbc\x39\x0f"
    "\x25\x37\x3f\xbb\xf0\x6f\x61\xcc\xc4\xc4\x52\xe6\x9a\xf0\x93\x3e"
    "\xf7\x75\x62\x40\x52\x64\x87\x63\x2b\x54\x9e\xc2\x92\xf0\x22\x46"
    "\x46\xf2\x9c\x28\x8f\xd7\x0b\x10\xf3\xab\xc8\xa6\x15\x79\xf3\x0f"
    "\x5f\x7b\x66\x61\x5e\x26\x58\xd5\x8e\xa5\x5c\x37\xe1\xc2\x82\xa3",
    "\x56\x9f\x12\x79\x75\x32\x71\x80\x0c\x5b\x9c\xf1\x4a\x7a\x26\x3c"
    "\x1a\x55\x61\x1f\x1d\xc8\x37\x03\x56\xa9\x90\x1b\xcb\x97\x7d\x74"
    "\xe8\x1a\x6c\xb7\xf1\xee\xe4\xa8\x32\xda\x3e\x1b\x36\x1c\xb9\x4b"
    "\x5b\xea\xa0\x51\x21\xb9\x31\x3f\xb3\x25\x0f\xfb\xf2\xf9\xa9\x4c"
    "\xab\xcb\xd8\xdc\x5c\xfe\xf7\xf0\x56\x9b\x55\xab\xaf\xf2\xe9\x5c"
    "\x74\xdf\x44\x45\x51\x2d\x80\xf2\x32\x3c\x24\xce\x8c\x2b\xfe\x0a"
    "\xaf\xbf\xa5\x93\x48\x3e\xdd\x9f\xbd\x96\xc3\xb5\x24\xc5\x68\x94"
    "\xb8\x0a\x58\x53\x5d\x68\xc1\x49\xe4\x61\x43\xf7\xf7\x89\x8b\x77",
    "\xc7\xe2\x19\x9b\x68\x1b\xf3\x4d\x7a\x48\x9e\x3d\x4f\xc9\x3e\x70"
    "\xe1\x83\xa2\x6d\xb7\x65\x64\x7f\x40\xa0\xed\x59\x41\x12\x07\x97"
    "\xca\x49\x3a\x89\x7f\x28\xf1\x3a\x51\xc2\xf5\x0a\xb2\xb4\x91\xa1"
    "\x66\xc7\xa1\x91\x3f\x05\x61\x63\x19\xf1\x40\x45\x18\xab\x45\x04"
    "\x36\x4b\x1c\xf9\x95\x8d\x3d\xaa\x15\x65\x97\x47\xa4\x58\x3e\x94"
    "\x27\x4c\xbb\xa0\x43\x48\x1d\xd7\x8d\x87\xe7\xd3\xc0\x75\x87\x72"
    "\xe9\xf3\x04\xf6\xc0\xc8\x30\x0f\xdc\xe2\x64\x4f\xe1\x22\xcf\x17"
    "\x53\x5d\x9d\xa0\x91\x3a\x08\x7f\xdf\xa7\x16\x67\xbc\x60\x1e\x43",
    "\x55\x59\x30\xab\x16\xdd\x69\x9c\x97\x80\x48\x2a\x43\xde\x47\x62"
    "\x69\xe0\xa6\x45\xca\x9c\xad\xd4\x1a\x40\x9b\x56\x24\x66\xd3\x51");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\x97\xf6\xb6\xb2\x1e\x28\x51\x8b\x85\xc6\x3b\x92\x83\xa8\xa9\x27"
    "\xda\x17\x4f\xa8\x46\x58\xe1\x06\x0f\xc7\x7c\x82\x5a\xf4\xa5\xd0"
    "\xb6\xc7\x6d\x9f\x47\x54\xa4\x6d\x22\xf8\x88\xd0\x04\x54\xb7\xa6"
    "\xfe\x4d\xec\xf0\xfb\x46\xd2\x40\xe0\xf4\x1d\xd1\x73\xf6\x1a\x8a"
    "\xba\xf0\x90\x96\x9d\xe8\xa3\xda\x3b\x0e\xc9\xfe\x09\x58\xe7\xfb"
    "\x84\xa2\xf8\xf9\x2a\x54\x50\xaa\x85\x5d\x88\x35\xae\x3e\x66\xc8"
    "\xd1\xf1\xca\x03\xce\x94\x41\xee\x66\x93\x4d\xbc\x33\xfb\xb2\x84"
    "\x8f\x9e\x3d\xb4\x0c\x70\x06\x19\xf1\x5e\x6a\x5c\x20\x2d\x3f\xae",
    "\x71\xc9\x69\xd2\xda\xbe\x65\x5c\x18\xa3\xe7\x88\x7c\x02\x4a\x10"
    "\x38\xe8\x03\xab\x89\xbf\x4e\x60\x2e\x8b\xa6\xad\x9a\xd3\x08\x42"
    "\xbb\xb6\x9f\xdb\xa2\xe4\x41\xcd\x13\x1a\x10\x08\xbf\x28\xf0\x07"
    "\x95\x6a\x1f\x5c\xe0\xb2\x85\x90\xd8\x51\x73\x92\x35\xfa\x25\xd0"
    "\xbf\xef\x80\x9f\x8c\x81\xd1\xa9\xbd\x92\x53\x62\xdf\xad\x5e\xbe"
    "\xb9\xfb\xf9\x9a\xec\x96\x2d\x66\x39\x1a\x1d\x15\xd9\x00\x40\x54"
    "\x6c\x33\xea\xea\xe8\x93\xbf\x00\xf2\x84\x98\x0b\x5c\xa9\xc9\x96"
    "\x4d\x9a\x96\x0d\x04\x94\x99\xbb\xb0\x9a\xd9\xb9\xb0\xd2\x60\xaf",
    "\x82\x1f\x7d\xb7\x01\xe0\x24\x8b\x15\x33\xa4\x6e\xd7\xa9\x83\x41"
    "\xa7\x76\x74\x1c\x41\xbc\xa6\xdd\xce\xab\xb7\x4f\xf7\x7e\x14\x40"
    "\x2b\xbf\x61\x28\x9a\xf0\x44\x6f\x59\xb9\xc8\xaa\xdb\xc7\x6a\xab"
    "\xbd\x34\x45\xc1\x40\x21\x7f\x98\xab\xe8\x59\x32\xba\x25\x01\xba"
    "\x3b\xde\x4b\x60\x51\x11\x12\xa9\xfa\x30\x24\x88\x5c\x04\x7e\x1d"
    "\xad\x39\x9a\x85\x1b\xbd\x3f\xea\xf8\x8c\x7d\xfc\xc2\x37\xbe\xf9"
    "\x4f\x65\xcd\xd6\x80\x16\xf9\xf8\x1b\x0f\x99\x71\x0b\x9c\xfd\x35"
    "\xc9\x37\x84\x7e\xa0\xc3\x95\x8b\x40\x48\xa5\x35\x62\x7a\x68\xad",
    "\xa1\xf4\x86\x47\xc6\x27\x3e\x35\x95\x0d\x8f\xae\x2b\xe3\xe4\xc4"
    "\x97\xf6\xb6\xb2\x1e\x28\x51\x8b\x85\xc6\x3b\x92\x83\xa8\xa9\x27");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\xb3\x5e\x1f\x57\x39\x83\x5f\xd4\x84\xce\x50\xc2\x91\x39\x07\x6c"
    "\xdc\x80\x48\xab\xb3\x00\x31\x21\xb3\x4e\x1f\xfc\x09\x10\xda\x50"
    "\xdd\x3b\x6e\x08\x3a\xd5\x83\x1e\xf5\xff\xff\xc0\xe5\x97\xcb\x55"
    "\x88\x14\x7f\x9f\x9c\x62\x41\x42\xb4\x59\x6c\x31\x64\x5f\x64\xb2"
    "\x31\x0c\x38\x4f\x5c\xd8\x6a\xc3\x6a\xf3\x24\x9f\x47\xee\xc9\x76"
    "\xba\x82\x73\x51\xbe\xc7\xc2\x12\x24\xc5\xde\xd1\x06\x7d\x8d\xb7"
    "\xc7\x59\x14\x7a\x02\x73\x0b\xbb\x32\x63\x9d\xa8\xaf\x8f\x61\x2b"
    "\x57\xec\xcc\x7f\xc7\x30\xf0\xc3\x17\xd1\x48\x1f\x3d\x3e\x5a\x52",
    "\x31\xc7\x45\xda\x6f\x1f\x67\x20\x83\xe3\x90\x74\x65\xf6\x20\xd6"
    "\x27\xa1\x08\xc3\xb5\x6e\xb4\x9c\x72\xb6\x88\xcd\xc4\xdc\xc4\x9e"
    "\x44\x08\x82\xd7\xaf\xc8\x43\x31\xd4\x8c\x5a\xd6\x46\x86\x0f\xf5"
    "\x63\x9f\xc9\x1d\xbb\xdc\x49\xb3\xf5\x79\x98\x6d\x02\xe9\x17\x64"
    "\xdc\x60\x79\x1d\x62\x32\x07\xc9\x24\x4c\x93\x9b\xad\xa7\x62\x3f"
    "\x0f\xe3\x1d\xbd\xfa\x2c\xd5\xfe\x38\xb6\x03\x61\xd5\x75\x13\x76"
    "\x54\xab\x5a\xf2\x57\x56\x13\x26\x9e\x17\x2d\x52\x80\x39\x7c\xb6"
    "\x09\x42\xc9\xb8\x52\x4d\x63\xb2\x4f\xa4\x42\x7e\xbe\x56\x67\x0a",
    "\x4a\xce\xd3\x96\x52\x92\x6b\xa1\x73\xdb\x0c\xd3\x18\xf2\x61\x80"
    "\xe7\x1d\x42\x8b\xe4\x90\xfe\xce\x6f\xd7\x72\x7a\xed\x68\x5c\xeb"
    "\x3f\x4c\xcb\x37\x45\x63\x64\xb5\xe8\x5c\x59\x1e\xb2\x0a\x24\x53"
    "\xfd\xe5\x76\x78\xe5\xfe\x0d\x1d\x3f\x4f\x50\xde\xf3\x11\xde\x7b"
    "\x03\xa5\x7d\x34\xf9\xac\xe5\xfc\x43\xbc\xb9\x95\x84\xc4\x0b\x3e"
    "\xa0\x88\x01\x80\xef\x01\xf5\xf9\x4a\xcb\x51\xb0\x08\x37\xb4\x22"
    "\x59\x72\x68\x55\x1e\x2c\x54\x4c\xdc\xa2\x78\x02\xc7\x94\xaf\xd0"
    "\x61\x63\x34\x21\x0f\x66\x73\x02\xc9\x7c\xf6\xc2\xb8\x3a\x0d\x70",
    "\xe4\xf1\x91\x2a\xb6\x50\xf6\xa6\x20\xd0\x1a\xe8\xbb\x52\xa4\x36"
    "\xb3\x5e\x1f\x57\x39\x83\x5f\xd4\x84\xce\x50\xc2\x91\x39\x07\x6c");

  TEST(avxfish_test, LOCATION, "Randomly generated test vector",
    "\x00\x9f\xc5\xca\xf2\xe5\x76\x53\x7b\x29\x1a\x33\x50\x7f\xa8\xbe"
    "\xe7\x31\x72\xbb\x03\xf3\x3f\xc1\x6b\xd7\x02\xd6\xbd\xea\xd1\x3b"
    "\x0a\xe7\xd9\x00\xd2\x47\x24\x7a\x76\xaa\x2d\x2a\xde\xb7\x7e\x80"
    "\x52\xf0\x31\x21\x31\xeb\x56\x26\x95\x2b\xf0\x84\x0a\xdc\x07\x60"
    "\x94\x63\x59\x1a\x62\x00\x7e\x56\x25\x35\xc7\x23\xe8\xb6\x4c\x33"
    "\xe1\xbd\xa4\xe5\xd0\x33\x1d\x39\xa7\x8d\x0e\x69\x55\x78\xc0\x17"
    "\x15\xf4\xc5\x98\xb7\xc4\xa5\xd5\xcb\x4d\x78\x94\x32\x60\xa4\x09"
    "\xd3\x05\xb5\xc7\x03\x3f\xb1\x48\x1c\x96\xb8\xa0\x54\x9a\xf3\x5d",
    "\x6e\x38\x59\xa6\x1a\x69\xe6\x64\x1c\x84\xf4\xc8\x55\xf0\xef\xf0"
    "\x95\x13\x91\x8a\xde\x32\xbc\x87\xef\x13\x68\x34\xce\x09\x14\x51"
    "\x7d\xdb\x32\xbd\x83\x0b\x15\xe6\xde\x48\x4e\x73\xa1\x51\xcd\x5f"
    "\x07\x59\xa0\x49\x05\x63\xe7\x1f\x43\x0d\xe5\xae\xfc\x3b\xa2\x14"
    "\xd5\xe2\x84\x99\x7f\xa4\x45\x2d\x2c\x1a\xba\x97\xc8\x80\x6d\x13"
    "\x01\xb8\x20\x0f\x4d\x06\x77\x1c\x6d\xb4\xff\xde\x1e\x31\xf2\xce"
    "\x39\x79\xd8\xf8\x3b\xb9\x32\x56\x0b\xc7\x56\xd1\x03\x00\x46\xe9"
    "\x55\xd8\xea\x54\xd0\xd8\xe2\xa2\x3a\xf8\x0f\x05\xcc\x08\xd3\x92",
    "\x4d\x81\xd4\x3a\xec\xb5\xf7\xba\x10\x1d\x8c\xc4\x1d\xc3\xdd\x47"
    "\x2d\x31\xcd\xae\x1e\xfb\x26\xa7\x4b\x44\x54\x2c\x24\x35\x50\xaa"
    "\x64\x0f\x65\x10\xef\x3f\x93\x04\xfa\x47\x7d\x1c\x7c\xb5\xa2\x4a"
    "\x3a\x39\x16\x23\x54\x1b\x49\xc6\x68\x91\x80\x86\xff\xc9\x9b\xa9"
    "\x6d\x75\x2b\x89\xfc\x67\xc4\x89\x3a\x11\xc8\xb6\xd2\x6a\x94\x43"
    "\xf5\x85\x51\x9f\xb3\x93\x33\xa3\x36\x27\x4b\xc7\x5e\x8b\x44\xf3"
    "\x87\x59\x88\x26\xff\xb3\xd5\xa0\x0b\x0a\xa5\x74\x02\xf5\xce\x7f"
    "\x62\x2e\xd1\x25\x0d\x02\x2f\xed\x6a\x90\xc9\x13\x05\x12\xf1\x29",
    "\xd4\x8c\x9b\xff\x01\xa5\x9b\x59\x93\x9e\xeb\x6c\x40\x7a\x66\x1c"
    "\x00\x9f\xc5\xca\xf2\xe5\x76\x53\x7b\x29\x1a\x33\x50\x7f\xa8\xbe");

  return EXIT_SUCCESS;
}
