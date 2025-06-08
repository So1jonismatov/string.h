#include "../s21_string.h"
#include "./s21_sscanf.h"
#include <stdarg.h>
#include <stdlib.h>


// s21_stoi remains unchanged
char *s21_stoi(char *str, int *number) {
    *number = 0;
    int sign = 1;
    if (*str == '-' || (*str == '+' && *(str + 1) >= '0' && *(str + 1) <= '9')) {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }
    while (*str && *str >= '0' && *str <= '9') {
        *number = *number * 10 + (*str - '0');
        str++;
    }
    *number *= sign;
    return str;
}

// s21_stof remains unchanged
char *s21_stof(char *str, double *number) {
    *number = 0;
    int sign = 1;
    int esign = 1;
    int enumber = 0;

    if (*str == '-' || (*str == '+' && *(str + 1) >= '0')) {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }
    while (*str && *str >= '0' && *str <= '9') {
        *number = *number * 10 + (*str - '0');
        str++;
    }
    if (*str == '.') {
        str++;
        double fnum = 0, tenth = 0.1;
        while (*str && *str >= '0' && *str <= '9') {
            fnum += (*str - '0') * tenth;
            tenth /= 10;
            str++;
        }
        *number += fnum;
    }
    *number *= sign;
    if (*str == 'e' || *str == 'E') {
        str++;
        if (*str == '-' || (*str == '+' && *(str + 1) >= '0')) {
            esign = (*str == '-') ? -1 : 1;
            str++;
        }
        if (*str >= '0' && *str <= '9') {
            while (*str && *str >= '0' && *str <= '9') {
                enumber = enumber * 10 + (*str - '0');
                str++;
            }
            double multiplier = 1.0;
            for (int i = 0; i < enumber; i++) {
                multiplier = (esign == 1) ? multiplier * 10.0 : multiplier / 10.0;
            }
            *number *= multiplier;
        }
    }
    return str;
}

// parse_format remains unchanged
char *parse_format(struct Format_Spec *fs, char *format) {
    if (!*format) return S21_NULL;
    while (*format && *format != '%') format++;
    if (!*format) return S21_NULL;
    format++;

    fs->optional = false;
    fs->width = 0;
    fs->length = 0;
    fs->specifier = 0;
    fs->isPercent = false;
    fs->minus = false;
    fs->plus = false;
    fs->space = false;
    fs->hash = false;
    fs->zero = false;

    while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' || *format == '0') {
        if (*format == '-') fs->minus = true;
        else if (*format == '+') fs->plus = true;
        else if (*format == ' ') fs->space = true;
        else if (*format == '#') fs->hash = true;
        else if (*format == '0') fs->zero = true;
        format++;
    }

    if (*format == '*') {
        fs->optional = true;
        format++;
    }

    int number = 0;
    if (*format >= '0' && *format <= '9') {
        format = s21_stoi(format, &number);
        fs->width = number;
    }

    if (*format == 'h' && *(format + 1) == 'h') {
        fs->length = -2;
        format += 2;
    } else if (*format == 'h') {
        fs->length = -1;
        format++;
    } else if (*format == 'l' && *(format + 1) == 'l') {
        fs->length = 2;
        format += 2;
    } else if (*format == 'l') {
        fs->length = 1;
        format++;
    } else if (*format == 'L') {
        fs->length = 3;
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
    if (!str || !format) return -1;
    va_list args_ptr;
    va_start(args_ptr, format);
    struct Format_Spec *fs = malloc(sizeof(struct Format_Spec));
    if (!fs) return -1;
    char *fstr = (char *)format;
    char *input = (char *)str;
    int assigned = 0;
    int initial_assigned = 0; // To handle %n correctly

    while (*fstr) {
        if (*fstr != '%') {
            if (*input == *fstr) {
                input++;
                fstr++;
            } else {
                while (*input == ' ' || *input == '\t' || *input == '\n') input++;
                if (*input == *fstr) {
                    input++;
                    fstr++;
                } else {
                    break; // Exit loop on mismatch
                }
            }
            continue;
        }

        char *prev_fstr = fstr;
        fstr = parse_format(fs, fstr);
        if (!fstr || fstr == prev_fstr) break; // Exit loop on parse failure

        // Skip leading whitespace for all specifiers except 'c', '[', and 'n'
        if (fs->specifier != 'c' && fs->specifier != 'n' && fs->specifier != '[') {
            while (*input == ' ' || *input == '\t' || *input == '\n' ||
                   *input == '\v' || *input == '\f' || *input == '\r') {
                input++;
            }
        }
        
        if (!*input && fs->specifier != 'n' && fs->specifier != '%') {
            break; // Exit loop if input ends and not a special case
        }

        if (fs->isPercent) {
            if (*input == '%') {
                input++;
            } else {
                break; // Exit loop on mismatch
            }
            continue;
        }

        initial_assigned = assigned;
        
        switch (fs->specifier) {
            case 'c': {
                if (!fs->width) fs->width = 1;
                if (!fs->optional) {
                    char *dest = va_arg(args_ptr, char *);
                    int count = 0;
                    while (*input && count < fs->width) {
                        *dest++ = *input++;
                        count++;
                    }
                    if (count > 0) assigned++;
                } else {
                    int count = 0;
                    while (*input && count < fs->width) {
                        input++;
                        count++;
                    }
                }
                break;
            }
            case 'd': {
                char temp_num[512] = {0};
                int i = 0;
                char *start_ptr = input;
                
                if ((*input == '+' || *input == '-') && (fs->width == 0 || i < fs->width)) {
                    temp_num[i++] = *input++;
                }
                
                while (*input >= '0' && *input <= '9' && (fs->width == 0 || i < fs->width)) {
                    temp_num[i++] = *input++;
                }

                if (i > 0 && ((temp_num[0] >= '0' && temp_num[0] <= '9') || i > 1)) {
                    if (!fs->optional) {
                        int num;
                        s21_stoi(temp_num, &num);
                        if (fs->length == -2) *(va_arg(args_ptr, signed char *)) = (signed char)num;
                        else if (fs->length == -1) *(va_arg(args_ptr, short *)) = (short)num;
                        else if (fs->length == 1) *(va_arg(args_ptr, long *)) = (long)num;
                        else if (fs->length == 2) *(va_arg(args_ptr, long long *)) = (long long)num;
                        else *(va_arg(args_ptr, int *)) = num;
                        assigned++;
                    }
                } else {
                    input = start_ptr;
                    break; // Exit loop on invalid input
                }
                break;
            }
            case 'f':
            case 'e':
            case 'E':
            case 'g':
            case 'G': {
                char temp_num[512] = {0};
                int i = 0;
                char* start_ptr = input;

                if ((*input == '+' || *input == '-') && (fs->width == 0 || i < fs->width)) {
                    temp_num[i++] = *input++;
                }
                while (*input >= '0' && *input <= '9' && (fs->width == 0 || i < fs->width)) {
                    temp_num[i++] = *input++;
                }
                if (*input == '.' && (fs->width == 0 || i < fs->width)) {
                    temp_num[i++] = *input++;
                    while (*input >= '0' && *input <= '9' && (fs->width == 0 || i < fs->width)) {
                        temp_num[i++] = *input++;
                    }
                }
                if ((*input == 'e' || *input == 'E') && (fs->width == 0 || i < fs->width)) {
                    temp_num[i++] = *input++;
                    if ((*input == '+' || *input == '-') && (fs->width == 0 || i < fs->width)) {
                        temp_num[i++] = *input++;
                    }
                    while (*input >= '0' && *input <= '9' && (fs->width == 0 || i < fs->width)) {
                        temp_num[i++] = *input++;
                    }
                }

                if (i > 0 && ((temp_num[0] >= '0' && temp_num[0] <= '9') || i > 1)) {
                    if (!fs->optional) {
                        double num;
                        s21_stof(temp_num, &num);
                        if (fs->length == 3) *(va_arg(args_ptr, long double *)) = num;
                        else if (fs->length == 1) *(va_arg(args_ptr, double *)) = num;
                        else *(va_arg(args_ptr, float *)) = (float)num;
                        assigned++;
                    }
                } else {
                    input = start_ptr;
                    break; // Exit loop on invalid input
                }
                break;
            }
            case 's': {
                if (!fs->optional) {
                    char *dest = va_arg(args_ptr, char *);
                    int i = 0;
                    while (*input && (*input != ' ' && *input != '\t' && *input != '\n' &&
                                    *input != '\v' && *input != '\f' && *input != '\r') &&
                           (fs->width == 0 || i < fs->width)) {
                        dest[i++] = *input++;
                    }
                    if (i > 0) {
                        dest[i] = '\0';
                        assigned++;
                    }
                } else {
                    int i = 0;
                    while (*input && (*input != ' ' && *input != '\t' && *input != '\n' &&
                                    *input != '\v' && *input != '\f' && *input != '\r') &&
                           (fs->width == 0 || i < fs->width)) {
                        input++;
                        i++;
                    }
                }
                break;
            }
            case 'n': {
                if (!fs->optional) {
                    *(va_arg(args_ptr, int *)) = (int)(input - str);
                }
                break; // 'n' does not count as an assignment
            }
            default:
                break; // Exit loop on unsupported specifier
        }

        if (initial_assigned == assigned && fs->specifier != 'n') {
            break; // Exit loop if no assignment and not 'n'
        }
    }

    va_end(args_ptr);
    free(fs);
    return assigned? assigned : -1;
}