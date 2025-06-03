#include "../s21_string.h"
#include "s21_sprintf.h"


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

char *s21_stoi(char *str, int *number, int base) {
    *number = 0;
    int sign = 1;
    if (*str == '-') { sign = -1; str++; }
    while (*str && *str >= '0' && *str <= '9') {
        *number = *number * 10 + (*str - '0');
        str++;
    }
    *number *= sign;
    return str;
}

char *s21_itoa(long num, char *buf, int base) {
    char *p = buf;
    if (num == 0) { *p++ = '0'; *p = '\0'; return buf; }
    bool is_neg = num < 0;
    if (is_neg) num = -num;
    while (num) {
        int digit = num % base;
        *p++ = (digit < 10) ? digit + '0' : digit - 10 + 'a';
        num /= base;
    }
    if (is_neg) *p++ = '-';
    *p = '\0';
    // Reverse string
    char *start = buf, *end = p - 1;
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    return buf;
}

char *s21_ftoa(double num, char *buf, int precision) {
    if (precision < 0) precision = 6; // Default precision
    long int_part = (long)num;
    double frac_part = num - int_part;
    if (frac_part < 0) frac_part = -frac_part;
    char *p = buf;
    s21_itoa(int_part, p, 10);
    p += s21_strlen(p);
    if (precision > 0) {
        *p++ = '.';
        for (int i = 0; i < precision; i++) {
            frac_part *= 10;
            int digit = (int)frac_part;
            *p++ = digit + '0';
            frac_part -= digit;
        }
    }
    *p = '\0';
    return buf;
}

char *parse_format(Format_Spec *fs, char *format) {
    if (!*format) return S21_NULL;
    while (*format && *format != '%') format++;
    if (!*format) return S21_NULL;
    format++;

    fs->optional = false;
    fs->minus = false;
    fs->plus = false;
    fs->space = false;
    fs->width = 0;
    fs->precision = -1; // Default: not set
    fs->length = 0;
    fs->specifier = 0;
    fs->isPercent = false;

    // Parse flags
    while (*format == '-' || *format == '+' || *format == ' ') {
        if (*format == '-') fs->minus = true;
        else if (*format == '+') fs->plus = true;
        else if (*format == ' ') fs->space = true;
        format++;
    }

    // Parse width
    int number = 0;
    if (*format >= '0' && *format <= '9') {
        format = s21_stoi(format, &number, 10);
        fs->width = number;
    }

    // Parse precision
    if (*format == '.') {
        format++;
        format = s21_stoi(format, &number, 10);
        fs->precision = number;
    }

    // Parse length
    if (*format == 'h') { fs->length = -1; format++; }
    else if (*format == 'l') { fs->length = 1; format++; }

    // Parse specifier
    if (*format == '%') {
        fs->isPercent = true;
    } else if (*format) {
        fs->specifier = *format;
    } else {
        return S21_NULL;
    }
    format++;
    return format;
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *fstr = (char *)format;
    char *start = str;
    char temp[256] = {0};
    Format_Spec fs;

    while (*fstr) {
        if (*fstr != '%') {
            *str++ = *fstr++;
            continue;
        }

        fstr = parse_format(&fs, fstr);
        if (!fstr) break;

        if (fs.isPercent) {
            *str++ = '%';
            continue;
        }

        // Convert argument to string
        s21_memset(temp, 0, 256);
        int len = 0;
        char sign = 0;

        switch (fs.specifier) {
            case 'c': {
                char c = (char)va_arg(args, int);
                temp[0] = c;
                len = 1;
                break;
            }
            case 'd': {
                long num = (fs.length == -1) ? (short)va_arg(args, int) :
                          (fs.length == 1) ? va_arg(args, long) : va_arg(args, int);
                if (num < 0) sign = '-';
                else if (fs.plus) sign = '+';
                else if (fs.space) sign = ' ';
                s21_itoa(num, temp, 10);
                len = s21_strlen(temp);
                break;
            }
            case 'u': {
                unsigned long num = (fs.length == -1) ? (unsigned short)va_arg(args, unsigned int) :
                                   (fs.length == 1) ? va_arg(args, unsigned long) : va_arg(args, unsigned int);
                s21_itoa(num, temp, 10);
                len = s21_strlen(temp);
                break;
            }
            case 'f': {
                double num = (fs.length == 1) ? va_arg(args, double) : va_arg(args, double);
                if (num < 0) sign = '-';
                else if (fs.plus) sign = '+';
                else if (fs.space) sign = ' ';
                s21_ftoa(num, temp, fs.precision);
                len = s21_strlen(temp);
                break;
            }
            case 's': {
                char *s = va_arg(args, char *);
                s21_strncpy(temp, s, fs.precision >= 0 ? fs.precision : s21_strlen(s));
                len = s21_strlen(temp);
                break;
            }
        }

        // Apply width and flags
        int sign_len = sign ? 1 : 0;
        int pad_len = fs.width > len + sign_len ? fs.width - (len + sign_len) : 0;

        if (!fs.minus) { // Right-justify (default)
            for (int i = 0; i < pad_len; i++) *str++ = ' ';
            if (sign) *str++ = sign;
            s21_strcpy(str, temp);
            str += len;
        } else { // Left-justify
            if (sign) *str++ = sign;
            s21_strcpy(str, temp);
            str += len;
            for (int i = 0; i < pad_len; i++) *str++ = ' ';
        }
    }

    *str = '\0';
    va_end(args);
    return str - start;
}