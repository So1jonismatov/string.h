#include "s21_string.h"

char* s21_strstr(const char* haystack, const char* needle) {
  s21_size_t needle_len = s21_strlen(needle);
  if (needle_len == 0) {
    return (char*)haystack;
  }
  char* position = s21_strpbrk(haystack, needle);

  while (position != S21_NULL) {
    if (s21_strncmp(position, needle, needle_len) == 0) return position;
    position = s21_strpbrk(position + 1, needle);
  }

  return position;
}