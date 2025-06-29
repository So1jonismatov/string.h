#include <stdbool.h>

#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  if (str1 == S21_NULL || str2 == S21_NULL) return 0;
  if (*str2 == '\0') return 0;

  bool accept[256] = {0};
  while (*str2 != '\0') {
    accept[(unsigned char)*str2] = 1;
    str2++;
  }

  s21_size_t len = 0;
  while (*str1 != '\0') {
    if (!accept[(unsigned char)*str1]) return len;
    len++;
    str1++;
  }
  return len;
}
