#include "../s21_string.h"
#include "./s21_sscanf.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>


char *s21_stoi(char *str, int *number) {
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

char *s21_stof(char *str, double *number) {
    bool isScience = false;
    *number = 0;
    int sign = 1;
    int esign = 1;
    int enumber = 0;

    // Handle sign
    if (*str == '-') { sign = -1; str++; }

    // Parse integer part
    while (*str && *str >= '0' && *str <= '9') {
        *number = *number * 10 + (*str - '0');
        str++;
    }

    // Parse decimal part if present
    double fnum = 0, tenth = 0.1;
    if (*str == '.') {
        str++;
        while (*str && *str >= '0' && *str <= '9') {
            fnum += (*str - '0') * tenth;
            tenth /= 10;
            str++;
        }
    }
    *number += fnum;
    *number *= sign;

    // Parse scientific notation if present
    if (*str == 'e' || *str == 'E') {
        isScience = true;
        str++;
        if (*str == '-') { esign = -1; str++; }
        else if (*str == '+') str++;

        // Validate exponent digits
        if (!(*str >= '0' && *str <= '9')) return str;
        while (*str && *str >= '0' && *str <= '9') {
            enumber = enumber * 10 + (*str - '0');
            str++;
        }

        // Manual exponentiation
        double multiplier = 1.0;
        for (int i = 0; i < enumber; i++) {
            if (esign == 1) multiplier *= 10.0;
            else multiplier /= 10.0;
        }
        *number *= multiplier;
    }

    return str;
}

char *parse_format(Format_Spec *fs, char *format) {
    if (!*format) return S21_NULL;
    while (*format && *format != '%') format++;
    if (!*format) return S21_NULL;
    format++;

    fs->optional = false;
    fs->width = 0;
    fs->length = 0;
    fs->specifier = 0;
    fs->isPercent = false;

    if (*format == '*') {
        fs->optional = true;
        format++;
    }

    int number = 0;
    if (*format >= '0' && *format <= '9') {
        format = s21_stoi(format, &number);
        fs->width = number;
    }

    if (*format == 'h' || *format == 'l') {
        fs->length = (*format == 'h') ? -1 : 1;
        format++;
    }

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



int s21_sscanf(const char *str, const char *format, ...) {
    va_list args_ptr;
    va_start(args_ptr, format);
    Format_Spec *fs = malloc(sizeof(Format_Spec));
    if (!fs) return -1; // Handle malloc failure
    char *fstr = (char *)format;
    char *input = (char *)str;
    int assigned = 0;

    while (*fstr && *input) {
        char *prev_input = input; // Track position
        fstr = parse_format(fs, fstr);
        if (!fstr) break;

        // Skip whitespace for all except %c (without width)
        if (fs->width == 0 && fs->specifier != 'c') while (*input == ' ') input++;

        if (fs->isPercent) {
            if (*input == '%') input++;
            continue;
        }

        int chars_read = 0;
        char temp[256] = {0};

        switch (fs->specifier) {
            case 'c': {
                if (fs->width == 0) fs->width = 1;
                for (int i = 0; i < fs->width && *input; i++, input++) temp[i] = *input;
                if (!fs->optional) {
                    *(va_arg(args_ptr, char *)) = temp[0];
                    assigned++;
                }
                break;
            }
            case 'd': {
                int num = 0;
                char *start = input;
                input = s21_stoi(input, &num);
                if (fs->width > 0 && (input - start) > fs->width) input = start + fs->width; // Enforce width
                if (input == start) break; // No digits read, fail
                if (!fs->optional) {
                    if (fs->length == -1) *(va_arg(args_ptr, short *)) = (short)num;
                    else if (fs->length == 1) *(va_arg(args_ptr, long *)) = (long)num;
                    else *(va_arg(args_ptr, int *)) = num;
                    assigned++;
                }
                break;
            }
            case 'u': {
                unsigned int num = 0;
                char *start = input;
                input = s21_stoi(input, (int *)&num);
                if (fs->width > 0 && (input - start) > fs->width) input = start + fs->width;
                if (input == start) break;
                if (!fs->optional) {
                    if (fs->length == -1) *(va_arg(args_ptr, unsigned short *)) = (unsigned short)num;
                    else if (fs->length == 1) *(va_arg(args_ptr, unsigned long *)) = (unsigned long)num;
                    else *(va_arg(args_ptr, unsigned int *)) = num;
                    assigned++;
                }
                break;
            }
            case 'f': {
                double num = 0;
                char *start = input;
                input = s21_stof(input, &num);
                if (fs->width > 0 && (input - start) > fs->width) input = start + fs->width;
                if (input == start) break;
                if (!fs->optional) {
                    if (fs->length == 1) *(va_arg(args_ptr, double *)) = num;
                    else *(va_arg(args_ptr, float *)) = (float)num;
                    assigned++;
                }
                break;
            }
            case 's': {
                int i = 0;
                while (*input && *input != ' ' && (fs->width == 0 || i < fs->width)) {
                    temp[i++] = *input++;
                }
                temp[i] = '\0';
                if (i == 0) break; // No chars read, fail
                if (!fs->optional) {
                    s21_strcpy(va_arg(args_ptr, char *), temp);
                    assigned++;
                }
                break;
            }
        }
        if (input == prev_input) break; // No progress, avoid infinite loop
    }

    va_end(args_ptr);
    free(fs);
    return assigned;
}