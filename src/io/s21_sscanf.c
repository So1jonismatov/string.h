#include "../s21_string.h"
#include "./s21_sscanf.h"



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

    // Parse flags
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
    va_list args_ptr;
    va_start(args_ptr, format);
    struct Format_Spec *fs = malloc(sizeof(struct Format_Spec));
    if (!fs) return -1;
    char *fstr = (char *)format;
    char *input = (char *)str;
    int assigned = 0;

    while (*fstr && *input) {
        char *prev_input = input;
        fstr = parse_format(fs, fstr);
        if (!fstr) break;

        // Skip whitespace for all except %c (without width)
        if (fs->width == 0 && fs->specifier != 'c') {
            while (*input == ' ' || *input == '\t' || *input == '\n' ||
                   *input == '\v' || *input == '\f' || *input == '\r') {
                input++;
            }
        }

        if (fs->isPercent) {
            if (*input == '%') input++;
            continue;
        }

        int chars_read = 0;
        char temp[256] = {0};

        switch (fs->specifier) {
            case 'c': {
                if (fs->width == 0) fs->width = 1;
                for (int i = 0; i < fs->width && *input; i++, input++) {
                    temp[i] = *input;
                }
                if (!fs->optional) {
                    *(va_arg(args_ptr, char *)) = temp[0];
                    assigned++;
                }
                break;
            }
            case 'd': {
                int num = 0;
                char *start = input;
                // Check for required sign if + flag is set
                if (fs->plus && (*input != '+' && *input != '-')) break;
                // Allow space before number if space flag is set and no sign
                if (fs->space && *input == ' ' && (*(input + 1) >= '0' || *(input + 1) == '+' || *(input + 1) == '-')) {
                    input++;
                }
                input = s21_stoi(input, &num);
                if (fs->width > 0 && (input - start) > fs->width) input = start + fs->width;
                if (input == start) break;
                if (!fs->optional) {
                    if (fs->length == -2) *(va_arg(args_ptr, char *)) = (char)num;
                    else if (fs->length == -1) *(va_arg(args_ptr, short *)) = (short)num;
                    else if (fs->length == 1) *(va_arg(args_ptr, long *)) = (long)num;
                    else if (fs->length == 2) *(va_arg(args_ptr, long long *)) = num;
                    else *(va_arg(args_ptr, int *)) = num;
                    assigned++;
                }
                break;
            }
            case 'f': {
                double num = 0;
                char *start = input;
                // Check for required sign if + flag is set
                if (fs->plus && (*input != '+' && *input != '-')) break;
                // Allow space before number if space flag is set and no sign
                if (fs->space && *input == ' ' && (*(input + 1) >= '0' || *(input + 1) == '+' || *(input + 1) == '-')) {
                    input++;
                }
                input = s21_stof(input, &num);
                if (fs->width > 0 && (input - start) > fs->width) input = start + fs->width;
                // Handle # flag for decimal point requirement
                if (fs->hash && *start != '.' && num != (int)num) break; // Expect decimal if # and fractional
                if (input == start) break;
                if (!fs->optional) {
                    if (fs->length == 3) *(va_arg(args_ptr, long double *)) = num;
                    else if (fs->length == 1) *(va_arg(args_ptr, double *)) = num;
                    else *(va_arg(args_ptr, float *)) = (float)num;
                    assigned++;
                }
                break;
            }
            case 's': {
                int i = 0;
                while (*input && (*input != ' ' && *input != '\t' && *input != '\n' &&
                                  *input != '\v' && *input != '\f' && *input != '\r') &&
                       (fs->width == 0 || i < fs->width)) {
                    temp[i++] = *input++;
                }
                temp[i] = '\0';
                if (i == 0) break;
                if (!fs->optional) {
                    s21_strcpy(va_arg(args_ptr, char *), temp);
                    assigned++;
                }
                break;
            }
            case 'n': {
                if (!fs->optional) {
                    *(va_arg(args_ptr, int *)) = (int)(input - str);
                }
                continue;
            }
        }
        if (input == prev_input) break;
    }

    va_end(args_ptr);
    free(fs);
    return assigned;
}