#include "s21_string.h"
#include "s21_utils.h";

char *s21_strncpy(char *dest, const char *src, s21_size_t n){
    s21_size_t len = min(s21_strlen(src), n);

    s21_memcpy(dest, src, len);
    if (len < n) s21_memset(dest + len, '\0', n - len);
    return dest;
}