#include "../s21_string.h"
#include <stdlib.h>

// Helper function to check if a character is in trim_chars
int is_char_in_set(char c, const char *trim_chars, s21_size_t trim_len) {
    for (s21_size_t i = 0; i < trim_len; i++) {
        if (c == trim_chars[i]) return 1;
    }
    return 0;
}

void *s21_trim(const char *src, const char *trim_chars) {
    if (!src) return S21_NULL;

    s21_size_t src_len = s21_strlen(src);
    
    const char *default_trim = " \t\n\r\v\f";
    if (!trim_chars || s21_strlen(trim_chars) == 0) {
        trim_chars = default_trim;
    }
    s21_size_t trim_len = s21_strlen(trim_chars);

    s21_size_t start = 0;
    while (start < src_len && is_char_in_set(src[start], trim_chars, trim_len)) {
        start++;
    }

    // If all characters are trimmed, return empty string
    if (start == src_len) {
        char *res = (char *)malloc(1);
        if (!res) return S21_NULL;
        res[0] = '\0';
        return (void *)res;
    }

    s21_size_t end = src_len - 1;
    while (end > start && is_char_in_set(src[end], trim_chars, trim_len)) {
        end--;
    }

   s21_size_t new_len = end - start + 1;
    char *res = (char *)malloc(new_len + 1);
    if (!res) return S21_NULL;

    for (s21_size_t i = 0; i < new_len; i++) {
        res[i] = src[start + i];
    }
    res[new_len] = '\0';

    return (void *)res;
}