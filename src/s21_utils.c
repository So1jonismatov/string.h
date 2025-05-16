#include "s21_string.h"
#include "s21_utils.h"

s21_size_t min(s21_size_t a, s21_size_t b){
    return a > b ? b : a;
}

char * find_null(char * c){
    return (c + s21_strlen(c));
}