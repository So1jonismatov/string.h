
#ifndef S21_SPRINTF
#define S21_SPRINTF

#include <stdarg.h>
#include <stdbool.h>


typedef struct {
    bool minus;     // '-' flag
    bool plus;      // '+' flag
    bool space;     // ' ' flag
    bool hash;      // '#' flag
    bool zero_pad;  // '0' flag
    int width;      // Field width (number or -1 for '*')
    int precision;  // Precision (number or -1 for default, -2 for '*')
    int length;     // -1: h, 0: default, 1: l, 2: L
    char specifier; // c, d, i, e, E, f, g, G, o, s, u, x, X, p, n, %
    bool isPercent; // True if '%%'
} Sprintf_format_spec;


void reverse(char* str, int len);
char *s21_sprintf_parse_int(char *str, int *number);
char *s21_sprintf_itoa(unsigned long long num, char *buf, int base, bool is_signed, bool upper_case);
char *s21_sprintf_ftoa_ext(long double num, char *buf, int precision, char specifier, bool hash_flag);
char *sprintf_parse_format_spec(Sprintf_format_spec *fs, char *format, va_list args_copy);

int s21_sprintf(char *str, const char *format_const, ...);

#endif
