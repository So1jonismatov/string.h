#include "s21_string.h"

char * find_null(char * c){
    return (c + s21_strlen(c));
}

char *s21_strncat(char *dest, const char *src, s21_size_t n){
    char * destination =  find_null(dest);
    s21_memcpy(destination, src, n);
    *(destination + n) = '\0';
    return dest;
}