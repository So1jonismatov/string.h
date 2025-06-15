#include "s21_string.h"
#include "s21_utils.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t minlen = min(n, s21_strlen(str1));
  minlen = min(minlen, s21_strlen(str2));
  
  return s21_memcmp(str1, str2, minlen);
}
