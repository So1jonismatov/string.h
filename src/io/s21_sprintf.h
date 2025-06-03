
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef SPRINTF
#define SPRINTF


struct Format_Spec {
    bool optional;      // For sscanf (*)
    bool minus;         // Flag: -
    bool plus;          // Flag: +
    bool space;         // Flag: (space)
    int width;
    int precision;      // .number
    short length;       // h: -1, l: 1
    char specifier;
    bool isPercent;
};


char *s21_stoi(char *str, int *number, int base);
char *s21_itoa(long num, char *buf, int base);
char *s21_ftoa(double num, char *buf, int precision);
char *parse_format(Format_Spec *fs, char *format);
int s21_sprintf(char *str, const char *format, ...);


#endif