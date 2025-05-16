#include "s21_string.h"
#include "s21_utils.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n){
    char * destination =  find_null(dest);
    s21_size_t len = min(s21_strlen(src), n);
    
    s21_memcpy(destination, src, len);
    *(destination + n) = '\0';
    return dest;
}