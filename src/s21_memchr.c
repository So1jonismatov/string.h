#include "./s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == S21_NULL) return S21_NULL;
  if (n == 0) return S21_NULL;

  const unsigned char *myString = (const unsigned char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    if (*(myString + i) == (unsigned char)c) {
      return (void *)(myString + i);
    }
  }
  return S21_NULL;
}
