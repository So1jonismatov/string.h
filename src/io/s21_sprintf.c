#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <stdint.h>
#include "../s21_string.h"
#include "./s21_sprintf.h"

// Reverse a string in place
void reverse(char *str, int len) {
    int i = 0, j = len - 1;
    char temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Parse an integer from a string
char *s21_sprintf_parse_int(char *str, int *number) {
    *number = 0;
    while (*str && *str >= '0' && *str <= '9') {
        *number = *number * 10 + (*str - '0');
        str++;
    }
    return str;
}

// Convert unsigned integer to string with given base
char *s21_sprintf_itoa(unsigned int num, char *buf, int base, bool upper_case) {
    char *p = buf;
    if (num == 0) {
        *p++ = '0';
        *p = '\0';
        return buf;
    }

    do {
        int digit = num % base;
        *p++ = (digit < 10) ? (char)(digit + '0') : (char)(digit - 10 + (upper_case ? 'A' : 'a'));
        num /= base;
    } while (num > 0);

    *p = '\0';
    reverse(buf, p - buf);
    return buf;
}

// Convert floating-point number to string
char *s21_sprintf_ftoa_ext(double num, char *buf, int precision, char specifier, bool hash_flag) {
    char *p = buf;
    bool is_neg = (num < 0);
    if (is_neg) num = -num;

    if (precision < 0) precision = 6; // Default precision

    if (specifier == 'g' || specifier == 'G') {
        double temp_num = num;
        int exponent = 0;
        while (temp_num >= 10.0) {
            temp_num /= 10.0;
            exponent++;
        }
        while (temp_num < 1.0 && temp_num > 0.0) {
            temp_num *= 10.0;
            exponent--;
        }

        int f_precision = precision - (exponent + 1);
        if (f_precision < 0) f_precision = 0;

        if (exponent < -4 || exponent >= precision) {
            int e_precision = precision - 1;
            if (e_precision < 0) e_precision = 0;
            return s21_sprintf_ftoa_ext(num, buf, e_precision, (specifier == 'g' ? 'e' : 'E'), hash_flag);
        } else {
            char *result = s21_sprintf_ftoa_ext(num, buf, f_precision, 'f', hash_flag);
            if (!hash_flag) {
                char *end_p = p + s21_strlen(p) - 1;
                while (end_p > p && *end_p == '0') end_p--;
                if (*end_p == '.') end_p--;
                *(end_p + 1) = '\0';
            }
            return result;
        }
    }

    // Rounding
    double rounding_factor = 0.5;
    for (int i = 0; i < precision; i++) rounding_factor /= 10.0;
    num += rounding_factor;

    if (is_neg) *p++ = '-';
    int int_part = (int)num;
    double frac_part = num - int_part;

    if (specifier == 'f') {
        s21_sprintf_itoa(int_part, p, 10, false);
        p += s21_strlen(p);

        if (precision > 0 || hash_flag) {
            *p++ = '.';
            for (int i = 0; i < precision; i++) {
                frac_part *= 10;
                int digit = (int)frac_part;
                *p++ = (char)(digit + '0');
                frac_part -= digit;
            }
        }
    } else if (specifier == 'e' || specifier == 'E') {
        if (num == 0.0) {
            *p++ = '0';
            if (precision > 0 || hash_flag) {
                *p++ = '.';
                for (int i = 0; i < precision; i++) *p++ = '0';
            }
            *p++ = specifier;
            *p++ = '+';
            *p++ = '0';
            *p++ = '0';
        } else {
            int exponent = 0;
            while (num >= 10.0) {
                num /= 10.0;
                exponent++;
            }
            while (num < 1.0) {
                num *= 10.0;
                exponent--;
            }

            int_part = (int)num;
            frac_part = num - int_part;

            *p++ = (char)(int_part + '0');
            if (precision > 0 || hash_flag) {
                *p++ = '.';
                for (int i = 0; i < precision; i++) {
                    frac_part *= 10;
                    int digit = (int)frac_part;
                    *p++ = (char)(digit + '0');
                    frac_part -= digit;
                }
            }
            *p++ = specifier;
            *p++ = (exponent >= 0) ? '+' : '-';
            int abs_exp = (exponent >= 0) ? exponent : -exponent;
            if (abs_exp < 10) *p++ = '0';
            s21_sprintf_itoa(abs_exp, p, 10, false);
            p += s21_strlen(p);
        }
    }
    *p = '\0';
    return buf;
}

// Parse format specifier
char *sprintf_parse_format_spec(Sprintf_format_spec *fs, char *format, va_list args_copy) {
    if (!*format || *format != '%') return NULL;
    format++; // Skip '%'

    fs->minus = false;
    fs->plus = false;
    fs->space = false;
    fs->hash = false;
    fs->zero_pad = false;
    fs->width = 0;
    fs->precision = -1;
    fs->length = 0;
    fs->specifier = 0;
    fs->isPercent = false;

    // Parse flags
    bool flags_parsing = true;
    while (flags_parsing) {
        switch (*format) {
            case '-': fs->minus = true; format++; break;
            case '+': fs->plus = true; format++; break;
            case ' ': fs->space = true; format++; break;
            case '#': fs->hash = true; format++; break;
            case '0': fs->zero_pad = true; format++; break;
            default: flags_parsing = false; break;
        }
    }
    if (fs->plus) fs->space = false;
    if (fs->minus) fs->zero_pad = false;

    // Parse width
    if (*format >= '0' && *format <= '9') {
        format = s21_sprintf_parse_int(format, &fs->width);
    } else if (*format == '*') {
        fs->width = va_arg(args_copy, int);
        if (fs->width < 0) {
            fs->minus = true;
            fs->width = -fs->width;
        }
        format++;
    }

    // Parse precision
    if (*format == '.') {
        format++;
        if (*format >= '0' && *format <= '9') {
            format = s21_sprintf_parse_int(format, &fs->precision);
        } else if (*format == '*') {
            fs->precision = va_arg(args_copy, int);
            if (fs->precision < 0) fs->precision = -1;
            format++;
        } else {
            fs->precision = 0;
        }
    }

    // Parse specifier
    if (*format == '%') {
        fs->isPercent = true;
        fs->specifier = '%';
    } else if (*format && (*format == 'c' || *format == 'd' || *format == 'i' ||
                           *format == 'e' || *format == 'E' || *format == 'f' ||
                           *format == 'g' || *format == 'G' || *format == 'o' ||
                           *format == 's' || *format == 'u' || *format == 'x' ||
                           *format == 'X' || *format == 'p' || *format == 'n')) {
        fs->specifier = *format;
    } else {
        return NULL;
    }
    format++;
    return format;
}

// Main sprintf function
int s21_sprintf(char *str, const char *format_const, ...) {
    va_list args;
    va_start(args, format_const);
    char *fstr = (char *)format_const;
    char *str_start = str;
    char temp_buffer[4096]; // Temporary buffer

    while (*fstr) {
        if (*fstr != '%') {
            *str++ = *fstr++;
            continue;
        }

        va_list args_copy;
        va_copy(args_copy, args);
        Sprintf_format_spec fs;
        char *next_fstr = sprintf_parse_format_spec(&fs, fstr, args_copy);
        va_end(args_copy);

        if (next_fstr == NULL) {
            *str++ = *fstr++;
            continue;
        }
        fstr = next_fstr;

        if (fs.isPercent) {
            *str++ = '%';
            continue;
        }

        s21_memset(temp_buffer, 0, sizeof(temp_buffer));
        int current_segment_len = 0;
        char sign_char_to_print = 0;
        const char *prefix_to_print = NULL;
        int prefix_len = 0;
        char *data_to_print = temp_buffer;

        switch (fs.specifier) {
            case 'c': {
                char c_val = (char)va_arg(args, int);
                temp_buffer[0] = c_val;
                current_segment_len = 1;
                break;
            }
            case 'd':
            case 'i': {
                int num_val = va_arg(args, int);
                s21_sprintf_itoa((unsigned int)(num_val < 0 ? -num_val : num_val), temp_buffer, 10, false);

                int num_digits = s21_strlen(temp_buffer);
                if (fs.precision == 0 && num_val == 0) {
                    current_segment_len = 0;
                } else if (fs.precision > num_digits) {
                    char temp_formatted[4096];
                    s21_memset(temp_formatted, '0', fs.precision);
                    temp_formatted[fs.precision] = '\0';
                    s21_memcpy(temp_formatted + (fs.precision - num_digits), temp_buffer, num_digits);
                    s21_memcpy(temp_buffer, temp_formatted, fs.precision + 1);
                }

                if (num_val < 0) {
                    sign_char_to_print = '-';
                    data_to_print = temp_buffer;
                } else if (fs.plus) {
                    sign_char_to_print = '+';
                } else if (fs.space) {
                    sign_char_to_print = ' ';
                }
                current_segment_len = s21_strlen(data_to_print);
                break;
            }
            case 'u': {
                unsigned int u_num_val = va_arg(args, unsigned int);
                s21_sprintf_itoa(u_num_val, temp_buffer, 10, false);

                int num_digits = s21_strlen(temp_buffer);
                if (fs.precision == 0 && u_num_val == 0) {
                    current_segment_len = 0;
                } else if (fs.precision > num_digits) {
                    char temp_formatted[4096];
                    s21_memset(temp_formatted, '0', fs.precision);
                    temp_formatted[fs.precision] = '\0';
                    s21_memcpy(temp_formatted + (fs.precision - num_digits), temp_buffer, num_digits);
                    s21_memcpy(temp_buffer, temp_formatted, fs.precision + 1);
                }
                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);
                break;
            }
            case 'o': {
                unsigned int u_num_val = va_arg(args, unsigned int);
                s21_sprintf_itoa(u_num_val, temp_buffer, 8, false);

                int num_digits = s21_strlen(temp_buffer);
                if (fs.precision == 0 && u_num_val == 0) {
                    current_segment_len = 0;
                    if (fs.hash) {
                        current_segment_len = 1;
                        temp_buffer[0] = '0';
                        temp_buffer[1] = '\0';
                    }
                } else if (fs.precision > num_digits) {
                    char temp_formatted[4096];
                    s21_memset(temp_formatted, '0', fs.precision);
                    temp_formatted[fs.precision] = '\0';
                    s21_memcpy(temp_formatted + (fs.precision - num_digits), temp_buffer, num_digits);
                    s21_memcpy(temp_buffer, temp_formatted, fs.precision + 1);
                }

                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);
                if (fs.hash && u_num_val != 0) {
                    prefix_to_print = "0";
                    prefix_len = 1;
                }
                break;
            }
            case 'x':
            case 'X': {
                unsigned int u_num_val = va_arg(args, unsigned int);
                s21_sprintf_itoa(u_num_val, temp_buffer, 16, fs.specifier == 'X');

                int num_digits = s21_strlen(temp_buffer);
                if (fs.precision == 0 && u_num_val == 0) {
                    current_segment_len = 0;
                } else if (fs.precision > num_digits) {
                    char temp_formatted[4096];
                    s21_memset(temp_formatted, '0', fs.precision);
                    temp_formatted[fs.precision] = '\0';
                    s21_memcpy(temp_formatted + (fs.precision - num_digits), temp_buffer, num_digits);
                    s21_memcpy(temp_buffer, temp_formatted, fs.precision + 1);
                }

                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);
                if (fs.hash && u_num_val != 0) {
                    prefix_to_print = (fs.specifier == 'x') ? "0x" : "0X";
                    prefix_len = 2;
                }
                break;
            }
            case 'f':
            case 'e':
            case 'E':
            case 'g':
            case 'G': {
                double f_val = va_arg(args, double);
                s21_sprintf_ftoa_ext(f_val, temp_buffer, fs.precision, fs.specifier, fs.hash);

                if (temp_buffer[0] == '-') {
                    sign_char_to_print = '-';
                    data_to_print = temp_buffer + 1;
                } else if (fs.plus) {
                    sign_char_to_print = '+';
                } else if (fs.space) {
                    sign_char_to_print = ' ';
                }
                current_segment_len = s21_strlen(data_to_print);
                break;
            }
            case 's': {
                char *s_val = va_arg(args, char *);
                if (s_val == NULL) s_val = "(null)";
                int s_len = s21_strlen(s_val);
                int len_to_copy = s_len;

                if (fs.precision >= 0 && fs.precision < len_to_copy) {
                    len_to_copy = fs.precision;
                }
                if (len_to_copy >= sizeof(temp_buffer) - 1) {
                    len_to_copy = sizeof(temp_buffer) - 1;
                }
                s21_memcpy(temp_buffer, s_val, len_to_copy);
                temp_buffer[len_to_copy] = '\0';
                data_to_print = temp_buffer;
                current_segment_len = len_to_copy;
                break;
            }
            case 'p': {
                void *ptr_val = va_arg(args, void *);
                unsigned int ptr_as_uint = (unsigned int)(uintptr_t)ptr_val;
                s21_sprintf_itoa(ptr_as_uint, temp_buffer, 16, false);

                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);
                prefix_to_print = "0x";
                prefix_len = 2;
                break;
            }
            case 'n': {
                int *n_ptr = va_arg(args, int *);
                if (n_ptr != NULL) {
                    *n_ptr = (int)(str - str_start);
                }
                current_segment_len = 0;
                break;
            }
        }

        int num_sign_chars = (sign_char_to_print != 0) ? 1 : 0;
        int total_content_width = current_segment_len + num_sign_chars + prefix_len;
        int padding_chars = (fs.width > total_content_width) ? fs.width - total_content_width : 0;
        char pad_char = (fs.zero_pad && !fs.minus && (fs.specifier == 'd' || fs.specifier == 'i' ||
                                                     fs.specifier == 'u' || fs.specifier == 'o' ||
                                                     fs.specifier == 'x' || fs.specifier == 'X' ||
                                                     fs.specifier == 'f' || fs.specifier == 'e' ||
                                                     fs.specifier == 'E' || fs.specifier == 'g' ||
                                                     fs.specifier == 'G' || fs.specifier == 'p')) ? '0' : ' ';

        if (!fs.minus && pad_char == ' ') {
            for (int i = 0; i < padding_chars; i++) *str++ = ' ';
        }

        if (sign_char_to_print) *str++ = sign_char_to_print;

        if (prefix_to_print) {
            s21_memcpy(str, prefix_to_print, prefix_len);
            str += prefix_len;
        }

        if (!fs.minus && pad_char == '0') {
            for (int i = 0; i < padding_chars; i++) *str++ = '0';
        }

        s21_memcpy(str, data_to_print, current_segment_len);
        str += current_segment_len;

        if (fs.minus) {
            for (int i = 0; i < padding_chars; i++) *str++ = ' ';
        }
    }

    *str = '\0';
    va_end(args);
    return (int)(str - str_start);
}