#include <stdlib.h>

#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL || start_index > s21_strlen(src)) {
    return S21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  char *value = malloc(src_len + str_len + 1);
  if (value == S21_NULL) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < start_index; i++) {
    value[i] = src[i];
  }

  for (s21_size_t i = 0; i < str_len; i++) {
    value[start_index + i] = str[i];
  }

  for (s21_size_t i = 0; i <= src_len - start_index; i++) {
    value[start_index + str_len + i] = src[start_index + i];
  }

  value[src_len + str_len] = '\0';

  return (void *)value;
}
