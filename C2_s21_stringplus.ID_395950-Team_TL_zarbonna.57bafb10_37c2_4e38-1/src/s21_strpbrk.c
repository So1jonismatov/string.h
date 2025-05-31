#include "s21_string.h"


char *s21_strpbrk(const char *str1, const char *str2){
    if (*str2 == '\0') return S21_NULL;
    
    s21_size_t n = s21_strcspn(str1, str2);
    if (n == s21_strlen(str1)) return S21_NULL;
    
    return (char *) (str1 + n);
}