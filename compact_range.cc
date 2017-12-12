#include <stdio.h>
#include <stdint.h>

uint64_t compact(uint16_t r0, uint16_t r1) {
  return (r0 << 16) ^ r1;
}

bool in_compact_range(uint64_t cr, uint16_t i) {
  uint64_t cmp_cap = (i << 16) ^ i;
  uint64_t cmp_min = (i << 16);
  return (cr > 65535 && cr <= cmp_min && cmp_cap <= cr) || (i <= cr);
}

bool in_range(uint16_t r0, uint16_t r1, uint16_t i) {
  return r0 <= i && i <= r1;
}

bool brute() {
  for (uint32_t i = 0; i <= 65535; i++) {
    if (i % 50 == 0) {
      printf("i: %hu\n", (uint16_t)i);
    }
    for (uint32_t j = i; j <= 65535; j++) {
      uint64_t cr = compact((uint16_t)i, (uint16_t)j);
      for (uint32_t q = i; q <= j; q++) {
        if (in_range((uint16_t)i, (uint16_t)j, (uint16_t)q) != in_compact_range(cr, (uint16_t)q)) {
          puts("nope:");
          printf("  i: %hu, j: %hu\n"
                 "  cr: %08llx, q: %hu\n",
                 (uint16_t)i, (uint16_t)j, cr, (uint16_t)q);
          return false;
        }
      }
    }
  }
  return true;
}


int main() {
  if (brute()) {
    puts("works");
  } else {
    puts("nope");
  }
}

