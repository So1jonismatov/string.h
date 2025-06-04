#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n){
    if(n == 0) return str;
    if (str == S21_NULL) return S21_NULL;

    unsigned char * buf = (unsigned char *) str;

    for (s21_size_t i = 0; i < n; i++) *(buf+i) = (unsigned char) c;

    return str;    
}