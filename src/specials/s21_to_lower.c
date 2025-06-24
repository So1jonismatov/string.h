#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  if (!str) return S21_NULL;

  int len = s21_strlen(str);
  char *result = (char *)malloc(len + 1);
  if (!result) return S21_NULL;

  for (int i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }
  result[len] = '\0';

  return (void *)result;
}
