#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "avxfish.h"

#include <sys/time.h>
#include <sys/resource.h>

static double timestamp(void) {
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}

static void *aligned_memory_alloc(size_t size, size_t alignment) {
  void *ptr;

  if (posix_memalign(&ptr, alignment, size)) {
    printf("error: failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  return ptr;
}

static void scribble_memory(void *ptr, size_t length) {
  uint32_t value = 1;

  for (size_t i = 0; i < length / 4; ++i) {
    value = (value * 8198291 + 3921);
    ((uint32_t *)ptr)[i] = value;
  }
}

static void aligned_free(void *ptr) {
  free(ptr);
}

static void encryption_speed(void) {
  const size_t bufsize = 1024 * 1024 * 1024;
  const size_t trials = 25;
  double times = 0.0;

  __attribute__((aligned(64))) uint64_t subkeys[336];
  void *memory = aligned_memory_alloc(bufsize, 64);

  for (size_t i = 0; i < trials; ++i) {
    scribble_memory(subkeys, sizeof(subkeys));
    scribble_memory(memory, bufsize);

    double t0 = timestamp();

    for (size_t j = 0; j < bufsize / 128; ++j) {
      // 1024 bits = 128 bytes processed by iteration
      avxfish(((uint8_t *)memory) + 128 * j, subkeys);
    }

    double t1 = timestamp();
    times += t1 - t0;
  }

  aligned_free(memory);

  printf(": %.3f MB/s\n", trials * (bufsize / 1024.0 / 1024.0) / times);
}

int main(void) {
  encryption_speed();
  return EXIT_SUCCESS;
}
