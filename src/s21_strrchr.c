#include "s21_string.h"

char *s21_strrchr(const char *str, int c){

    int len = s21_strlen(str);

    while (len >= 0){
        if ((unsigned char)c == *(str + len)) return (char *)(str + len);

        len--;
    }

    return S21_NULL;
}