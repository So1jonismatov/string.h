#include "s21_string.h"


int s21_memcmp(const void *str1, const void *str2, s21_size_t n){
    if(n == 0) return 0;
    // if(str1 == S21_NULL || str2 == S21_NULL) return 0;  // POSIX ga tug'ri kelmas ekan 
    if (str1 == str2) return 0;
    

    const unsigned char * first_string = (const unsigned char *)str1;
    const unsigned char * second_string = (const unsigned char *) str2;

    for(s21_size_t i = 0; i < n ; i++) if(*(first_string+i) != *(second_string + i)) return (*(first_string + i) - *(second_string + i));

    return 0;
}