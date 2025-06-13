#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last_str = S21_NULL;
  if (str == S21_NULL && last_str != S21_NULL) str = last_str;
  if (str == S21_NULL) return S21_NULL;

  str += s21_strspn(str, delim);
  if (*str == '\0') {
    last_str = S21_NULL;
    return S21_NULL;
  }

  s21_size_t len = s21_strcspn(str, delim);
  if (str[len] == '\0') {
    last_str = S21_NULL;
  } else {
    str[len] = '\0';
    last_str = str + len + 1;
  }

  return str;
}