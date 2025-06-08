#include "s21_string.h"


char *s21_strchr(const char *str, int c){
    if (str == S21_NULL) return S21_NULL;

    if ((unsigned char)c == '\0') return (char *)str + s21_strlen(str);
    
    while (*str != '\0') {
        if (*str == (unsigned char)c) return (char *)str;
        str++;
    }
    return S21_NULL;
}
