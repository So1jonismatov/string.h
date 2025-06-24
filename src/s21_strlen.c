#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  if (str == S21_NULL) return 0;
  if (*str == '\0') return 0;

  s21_size_t length = 0;

  do {
    length++;
  } while (*(str + length) != '\0');

  return length;
}
