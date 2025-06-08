// s21_sprintf.c (Implementation file)
#include "../s21_string.h" // Main library header, provides s21_strlen, S21_NULL, etc.
#include "s21_sprintf.h"   // Internal header for this module
#include <stdio.h>

// Parses an integer from the string (base 10)
char *s21_sprintf_parse_int(char *str, int *number) {
    *number = 0;
    // No sign parsing here, as width/precision are positive
    while (*str && *str >= '0' && *str <= '9') {
        *number = *number * 10 + (*str - '0');
        str++;
    }
    return str;
}

// Converts a long long integer to a string
// Puts '-' at the beginning for negative numbers.
char *s21_sprintf_itoa(long long num, char *buf, int base) {
    char *p = buf;
    unsigned long long n; // Use unsigned for calculations to handle LLONG_MIN correctly

    if (num == 0) {
        *p++ = '0';
        *p = '\0';
        return buf;
    }

    bool is_neg = false;
    if (num < 0) {
        is_neg = true;
        n = -num; // Convert to positive for digit extraction
    } else {
        n = num;
    }

    while (n) {
        int digit = n % base;
        *p++ = (digit < 10) ? (char)(digit + '0') : (char)(digit - 10 + 'a');
        n /= base;
    }

    if (is_neg) {
        *p++ = '-';
    }
    *p = '\0';

    // Reverse string
    char *start = buf, *end = p - 1;
    while (start < end) {
        char temp_char = *start;
        *start++ = *end;
        *end-- = temp_char;
    }
    return buf;
}

// Converts a double to a string
// Puts '-' at the beginning for negative numbers.
char *s21_sprintf_ftoa(double num, char *buf, int precision) {
    if (precision < 0) precision = 6; // Default precision

    char *p = buf;
    bool is_neg = false;
    if (num < 0) {
        is_neg = true;
        num = -num; // Work with positive number
    }

    // Handle rounding: add 0.5 * 10^(-precision)
    double rounding_factor = 0.5;
    for (int i = 0; i < precision; ++i) {
        rounding_factor /= 10.0;
    }
    num += rounding_factor;


    long long int_part = (long long)num;
    double frac_part = num - int_part;

    if (is_neg) {
        *p++ = '-';
    }

    // Convert integer part
    s21_sprintf_itoa(int_part, p, 10);
    p += s21_strlen(p);

    if (precision > 0) {
        *p++ = '.';
        for (int i = 0; i < precision; i++) {
            frac_part *= 10;
            int digit = (int)frac_part;
            *p++ = (char)(digit + '0');
            frac_part -= digit;
        }
    }
    *p = '\0';
    return buf; // Returns pointer to start of buf, even if sign was added
}

// Parses the format specifier string (e.g., "%-5.2lf")
char *sprintf_parse_format_spec(Sprintf_format_spec *fs, char *format) {
    // format points to the '%' character
    if (!*format || *format != '%') return S21_NULL; // Should not happen if called correctly
    format++; // Skip '%'

    // Initialize struct
    fs->minus = false;
    fs->plus = false;
    fs->space = false;
    fs->width = 0;
    fs->precision = -1; // Default: not set
    fs->length = 0;     // 0: int/double, -1: h (short), 1: l (long)
    fs->specifier = 0;
    fs->isPercent = false;

    // 1. Parse flags
    bool flags_parsing = true;
    while(flags_parsing) {
        switch (*format) {
            case '-': fs->minus = true; format++; break;
            case '+': fs->plus = true; format++; break;
            case ' ': fs->space = true; format++; break;
            default: flags_parsing = false; break;
        }
    }
    if (fs->plus) fs->space = false; // '+' overrides ' '

    // 2. Parse width
    if (*format >= '0' && *format <= '9') {
        format = s21_sprintf_parse_int(format, &fs->width);
    } else if (*format == '*') {
        // Width is passed as an argument (Bonus - not implemented for Part 2)
        // fs->width = va_arg(args, int);
        format++; // Skip '*'
        // For Part 2, we can treat '*' as an error or ignore. Let's ignore for now.
    }

    // 3. Parse precision
    if (*format == '.') {
        format++;
        if (*format >= '0' && *format <= '9') {
            format = s21_sprintf_parse_int(format, &fs->precision);
        } else if (*format == '*') {
            // Precision is passed as an argument (Bonus - not implemented for Part 2)
            // fs->precision = va_arg(args, int);
            format++; // Skip '*'
            // For Part 2, we can treat '*' as an error or ignore. Let's ignore for now.
        } else {
             fs->precision = 0; // ". " or ".*" with no number means 0 precision
        }
    }

    // 4. Parse length modifier
    if (*format == 'h') { fs->length = -1; format++; }
    else if (*format == 'l') { fs->length = 1; format++; }
    // 'L' for long double is a bonus requirement

    // 5. Parse specifier
    if (*format == '%') {
        fs->isPercent = true;
        fs->specifier = '%';
    } else if (*format && (*format == 'c' || *format == 'd' || *format == 'f' ||
                           *format == 's' || *format == 'u')) {
        fs->specifier = *format;
    } else {
        // Invalid or unsupported specifier
        return S21_NULL; // Or handle as an error, e.g., print the '%' literally
    }
    format++; // Consume the specifier character
    return format;
}


int s21_sprintf(char *str, const char *format_const, ...) {
    va_list args;
    va_start(args, format_const);
    char *fstr = (char *)format_const; // Work with a non-const pointer
    char *str_start = str;             // Keep track of the beginning of the output string
    char temp_buffer[4096];          // Temporary buffer for number conversions, etc. (generous size)
    Sprintf_format_spec fs;

    while (*fstr) {
        if (*fstr != '%') {
            *str++ = *fstr++;
            continue;
        }

        // We encountered a '%', try to parse the format specifier
        char *next_fstr = sprintf_parse_format_spec(&fs, fstr);
        if (next_fstr == S21_NULL) { // Invalid format specifier sequence
            *str++ = *fstr++; // Print the '%' literally and continue
            continue;
        }
        fstr = next_fstr; // Move format string pointer past the parsed specifier

        if (fs.isPercent) {
            *str++ = '%';
            continue;
        }

        s21_memset(temp_buffer, 0, sizeof(temp_buffer));
        s21_size_t current_segment_len = 0;
        char sign_char_to_print = 0; // e.g., '+', ' ', or 0 if no explicit sign needed or '-' is in temp_buffer
        char *data_to_print = temp_buffer; // Points to the actual data part in temp_buffer

        switch (fs.specifier) {
            case 'c': {
                char c_val = (char)va_arg(args, int); // char is promoted to int in va_arg
                temp_buffer[0] = c_val;
                current_segment_len = 1;
                break;
            }
            case 'd': {
                long long num_val;
                if (fs.length == -1) num_val = (short)va_arg(args, int);
                else if (fs.length == 1) num_val = va_arg(args, long);
                else num_val = va_arg(args, int);

                s21_sprintf_itoa(num_val, temp_buffer, 10);
                if (temp_buffer[0] == '-') {
                    sign_char_to_print = '-';
                    data_to_print = temp_buffer + 1;
                } else {
                    if (fs.plus) sign_char_to_print = '+';
                    else if (fs.space) sign_char_to_print = ' ';
                    data_to_print = temp_buffer;
                }
                current_segment_len = s21_strlen(data_to_print);
                break;
            }
            case 'u': {
                unsigned long long u_num_val;
                if (fs.length == -1) u_num_val = (unsigned short)va_arg(args, unsigned int);
                else if (fs.length == 1) u_num_val = va_arg(args, unsigned long);
                else u_num_val = va_arg(args, unsigned int);
                // For 'u', plus and space flags are ignored. No sign_char_to_print.
                s21_sprintf_itoa(u_num_val, temp_buffer, 10); // itoa handles unsigned via long long
                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);
                break;
            }
            case 'f': {
                // 'l' length modifier for double is implicit. 'L' for long double is bonus.
                double f_val = va_arg(args, double);
                s21_sprintf_ftoa(f_val, temp_buffer, fs.precision);

                if (temp_buffer[0] == '-') {
                    sign_char_to_print = '-';
                    data_to_print = temp_buffer + 1;
                } else {
                    if (fs.plus) sign_char_to_print = '+';
                    else if (fs.space) sign_char_to_print = ' ';
                    data_to_print = temp_buffer;
                }
                current_segment_len = s21_strlen(data_to_print);
                break;
            }
            case 's': {
                char *s_val = va_arg(args, char *);
                if (s_val == S21_NULL) {
                    s_val = "(null)";
                }
                s21_size_t s_len = s21_strlen(s_val);
                s21_size_t len_to_copy = s_len;

                if (fs.precision >= 0 && (s21_size_t)fs.precision < len_to_copy) {
                    len_to_copy = (s21_size_t)fs.precision;
                }
                
                // Ensure we don't overflow temp_buffer (though it's large)
                if (len_to_copy >= sizeof(temp_buffer)) {
                    len_to_copy = sizeof(temp_buffer) - 1;
                }

                s21_memcpy(temp_buffer, s_val, len_to_copy);
                temp_buffer[len_to_copy] = '\0'; // Ensure null termination
                data_to_print = temp_buffer;
                current_segment_len = len_to_copy;
                // No sign_char_to_print for 's'
                break;
            }
        }

        // Apply padding and justification
        int num_sign_chars = (sign_char_to_print != 0) ? 1 : 0;
        int total_content_width = current_segment_len + num_sign_chars;
        int padding_chars = 0;
        if (fs.width > total_content_width) {
            padding_chars = fs.width - total_content_width;
        }

        if (!fs.minus) { // Right-justify: Pad first
            for (int i = 0; i < padding_chars; i++) *str++ = ' ';
        }

        if (sign_char_to_print) { // Print sign if any
            *str++ = sign_char_to_print;
        }

        s21_memcpy(str, data_to_print, current_segment_len); // Print data
        str += current_segment_len;

        if (fs.minus) { // Left-justify: Pad last
            for (int i = 0; i < padding_chars; i++) *str++ = ' ';
        }
    }

    *str = '\0'; // Null-terminate the output string
    va_end(args);
    return (int)(str - str_start); // Return the number of characters written
}
