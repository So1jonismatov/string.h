#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (n == 0) return dest;
  if (dest == S21_NULL || src == S21_NULL) return dest;

  unsigned char *destination = (unsigned char *)dest;
  const unsigned char *source = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    *(destination + i) = *(source + i);
  }

  return dest;
}