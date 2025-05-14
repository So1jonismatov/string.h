#ifndef _S21_STRING
#define _S21_STRING

typedef unsigned long int s21_size_t;
#define S21_NULL ((void*)0);


void *s21_memchr(const void *str, int c, s21_size_t n);

#endif