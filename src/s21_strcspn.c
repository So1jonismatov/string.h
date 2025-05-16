#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2){
    // buni ichma ich for bilan O(n*m) usilda qilish mumkin edi lekin sal optimizatsiya qilganman, hayron qomayla

    bool reject[256] = {0};
    while (*str2 != '\0'){
        reject[(unsigned char) *str2] = 1;
        str2++;
    }

    int len = 0;
    while (*str1 != '\0'){
        if (reject[(unsigned char) *str1]) return len;

        len++;
        str1++;
    }
    return len;
}