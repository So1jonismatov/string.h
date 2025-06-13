
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h> 
#include <float.h> 

#include "../s21_string.h"
#include "./s21_sprintf.h"

void reverse(char* str, int len) {
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

char *s21_sprintf_parse_int(char *str, int *number) {
    *number = 0;
    while (*str && *str >= '0' && *str <= '9') {
        *number = *number * 10 + (*str - '0');
        str++;
    }
    return str;
}

char *s21_sprintf_itoa(unsigned long long num, char *buf, int base, bool is_signed, bool upper_case) {
    char *p = buf;
    unsigned long long n = num;
    bool is_neg = false;

    if (is_signed && (long long)num < 0) {
        is_neg = true;
        n = -((long long)num);
    }

    if (n == 0) {
        *p++ = '0';
        *p = '\0';
        return buf;
    }

    do {
        int digit = n % base;
        *p++ = (digit < 10) ? (char)(digit + '0') : (char)(digit - 10 + (upper_case ? 'A' : 'a'));
        n /= base;
    } while (n > 0);

    if (is_neg) {
        *p++ = '-';
    }
    *p = '\0';

    char *start = buf;
    char *end = p - 1;
    while (start < end) {
        char temp_char = *start;
        *start++ = *end;
        *end-- = temp_char;
    }
    return buf;
}

char *s21_sprintf_ftoa_ext(long double num, char *buf, int precision, char specifier, bool hash_flag) {
    char *p = buf;
    bool is_neg = false;
    if (num < 0) {
        is_neg = true;
        num = -num;
    }

    if (precision == -1) precision = 6; // default is 6

    if (specifier == 'g' || specifier == 'G') {
        // Rule: If exponent < -4 or exponent >= precision, use scientific notation.
        // Otherwise, use fixed-point notation.
        // Precision for g/G is SIGNIFICANT DIGITS.

        long double temp_num = num;
        int exponent = 0;
        if (temp_num != 0.0) {
            while (temp_num >= 10.0) {
                temp_num /= 10.0;
                exponent++;
            }
            while (temp_num < 1.0 && temp_num > 0.0) {
                temp_num *= 10.0;
                exponent--;
            }
        } else {
            exponent = 0;
        }

        // Adjust precision for fixed-point output based on exponent
        int f_precision_for_g = precision - (exponent + 1);

        if (exponent < -4 || exponent >= precision) { // Use scientific notation
            // Precision for e/E means digits AFTER decimal point
            int e_precision_for_g = precision - 1; // total significant - 1 (for integer part)
            if (e_precision_for_g < 0) e_precision_for_g = 0;
            return s21_sprintf_ftoa_ext(num, buf, e_precision_for_g, (specifier == 'g' ? 'e' : 'E'), hash_flag);
        } else { // Use fixed-point notation
            if (f_precision_for_g < 0) f_precision_for_g = 0; // Don't allow negative precision
            char *result = s21_sprintf_ftoa_ext(num, buf, f_precision_for_g, 'f', hash_flag);

            // For g/G, remove trailing zeros unless '#' flag is present
            if (!hash_flag) {
                char *end_p = p + s21_strlen(p) - 1;
                while (end_p > p && *end_p == '0') {
                    end_p--;
                }
                if (*end_p == '.') { // If we removed all digits after '.', remove '.' too
                    end_p--;
                }
                *(end_p + 1) = '\0';
            }
            return result;
        }
    }

    // --- Common rounding logic for f and e/E ---
    long double rounding_factor = 0.5;
    for (int i = 0; i < precision; ++i) {
        rounding_factor /= 10.0L; // Use L for long double literal
    }
    num += rounding_factor;

    if (is_neg) {
        *p++ = '-';
    }

    if (specifier == 'f') { // Fixed-point (f)
        long long int_part = (long long)num;
        long double frac_part = num - int_part;

        s21_sprintf_itoa(int_part, p, 10, false, false);
        p += s21_strlen(p);

        if (precision > 0 || hash_flag) { // Add '.' if precision > 0 or '#' is set
            *p++ = '.';
            for (int i = 0; i < precision; i++) {
                frac_part *= 10;
                int digit = (int)frac_part;
                *p++ = (char)(digit + '0');
                frac_part -= digit;
            }
        }
    } else if (specifier == 'e' || specifier == 'E') { // Scientific notation (e/E)
        if (num == 0.0L) { // Special case for 0.0
            *p++ = '0';
            if (precision > 0 || hash_flag) {
                *p++ = '.';
                for (int i = 0; i < precision; i++) {
                    *p++ = '0';
                }
            }
            *p++ = specifier;
            *p++ = '+';
            *p++ = '0';
            *p++ = '0';
        } else {
            int exponent = 0;
            // Adjust number to be between 1 and 10
            while (num >= 10.0L) {
                num /= 10.0L;
                exponent++;
            }
            while (num < 1.0L) {
                num *= 10.0L;
                exponent--;
            }

            long long int_part = (long long)num;
            long double frac_part = num - int_part;

            *p++ = (char)(int_part + '0'); // First digit (before decimal)

            if (precision > 0 || hash_flag) {
                *p++ = '.';
                for (int i = 0; i < precision; i++) {
                    frac_part *= 10;
                    int digit = (int)frac_part;
                    *p++ = (char)(digit + '0');
                    frac_part -= digit;
                }
            }

            *p++ = specifier; // 'e' or 'E'
            *p++ = (exponent >= 0) ? '+' : '-';

            // Print exponent (always 2 digits, pad with 0 if needed)
            int abs_exp = (exponent >= 0) ? exponent : -exponent;
            if (abs_exp < 10) {
                *p++ = '0';
            }
            s21_sprintf_itoa(abs_exp, p, 10, false, false);
            p += s21_strlen(p);
        }
    }
    *p = '\0';
    return buf;
}


char *sprintf_parse_format_spec(Sprintf_format_spec *fs, char *format, va_list args_copy) {
    // args_copy is used here because va_arg advances the list, and we might need to read width/precision
    // without altering the main args for the actual data.
    // However, for this simplified approach, we'll just advance the main args if we see '*'.
    // A more robust solution might pass va_list by value or use va_copy.
    // For now, we'll assume the width/precision '*' arguments appear correctly.

    if (!*format || *format != '%') return S21_NULL;
    format++; // Skip '%'

    // Initialize struct
    fs->minus = false;
    fs->plus = false;
    fs->space = false;
    fs->hash = false;
    fs->zero_pad = false;
    fs->width = 0;
    fs->precision = -1; // Default: not set
    fs->length = 0;
    fs->specifier = 0;
    fs->isPercent = false;

    // 1. Parse flags
    bool flags_parsing = true;
    while(flags_parsing) {
        switch (*format) {
            case '-': fs->minus = true; format++; break;
            case '+': fs->plus = true; format++; break;
            case ' ': fs->space = true; format++; break;
            case '#': fs->hash = true; format++; break;
            case '0': fs->zero_pad = true; format++; break;
            default: flags_parsing = false; break;
        }
    }
    if (fs->plus) fs->space = false; // '+' overrides ' '
    if (fs->minus) fs->zero_pad = false; // '-' overrides '0' padding

    // 2. Parse width
    if (*format >= '0' && *format <= '9') {
        format = s21_sprintf_parse_int(format, &fs->width);
    } else if (*format == '*') {
        fs->width = va_arg(args_copy, int); // Get width from arguments
        if (fs->width < 0) { // If width is negative, it implies '-' flag
            fs->minus = true;
            fs->width = -fs->width;
        }
        format++; // Skip '*'
    }

    // 3. Parse precision
    if (*format == '.') {
        format++;
        if (*format >= '0' && *format <= '9') {
            format = s21_sprintf_parse_int(format, &fs->precision);
        } else if (*format == '*') {
            fs->precision = va_arg(args_copy, int); // Get precision from arguments
            // If precision is negative, it means no precision (default behavior)
            if (fs->precision < 0) fs->precision = -1; // -1 indicates default precision
            format++; // Skip '*'
        } else {
             fs->precision = 0; // ". " or ".*" with no number means 0 precision
        }
    }

    // 4. Parse length modifier
    if (*format == 'h') { fs->length = -1; format++; }
    else if (*format == 'l') { fs->length = 1; format++; }
    else if (*format == 'L') { fs->length = 2; format++; } // For long double

    // 5. Parse specifier
    if (*format == '%') {
        fs->isPercent = true;
        fs->specifier = '%';
    } else if (*format && (
                           *format == 'c' || *format == 'd' || *format == 'i' || // Added 'i'
                           *format == 'e' || *format == 'E' || *format == 'f' || // Added 'e', 'E'
                           *format == 'g' || *format == 'G' || // Added 'g', 'G'
                           *format == 'o' || *format == 's' || *format == 'u' ||
                           *format == 'x' || *format == 'X' || *format == 'p' || // Added 'p'
                           *format == 'n' // Added 'n'
                           )) {
        fs->specifier = *format;
    } else {
        // Invalid or unsupported specifier
        return S21_NULL;
    }
    format++; // Consume the specifier character
    return format;
}


int s21_sprintf(char *str, const char *format_const, ...) {
    va_list args;
    va_start(args, format_const);
    char *fstr = (char *)format_const;
    char *str_start = str;
    char temp_buffer[4096]; // Generous temporary buffer
    Sprintf_format_spec fs;

    while (*fstr) {
        if (*fstr != '%') {
            *str++ = *fstr++;
            continue;
        }

        va_list args_copy; // Create a copy for parsing width/precision '*'
        va_copy(args_copy, args);
        char *next_fstr = sprintf_parse_format_spec(&fs, fstr, args_copy);
        va_end(args_copy); // Clean up the copy

        if (next_fstr == S21_NULL) { // Invalid format specifier sequence
            *str++ = *fstr++; // Print the '%' literally and continue why
            continue;
        }
        fstr = next_fstr; // Move format string pointer past the parsed specifier

        if (fs.isPercent) {
            *str++ = '%';
            continue;
        }

        s21_memset(temp_buffer, 0, sizeof(temp_buffer));
        s21_size_t current_segment_len = 0;
        char sign_char_to_print = 0;
        const char *prefix_to_print = S21_NULL;
        s21_size_t prefix_len = 0;
        char *data_to_print = temp_buffer; // Points to the actual data part in temp_buffer

        switch (fs.specifier) {
            case 'c': {
                if (fs.length == 1) { // 'l' length modifier for wide character
                    // wint_t is promoted to int
                    wchar_t wc_val = (wchar_t)va_arg(args, wint_t);
                    // For now, simple conversion if within ASCII range
                    if (wc_val >= 0 && wc_val <= 127) {
                        temp_buffer[0] = (char)wc_val;
                        current_segment_len = 1;
                    } else {
                        // Complex wide char handling (multibyte conversion) is beyond simple sprintf
                        // For this exercise, we'll just represent non-ASCII as a placeholder
                        s21_memcpy(temp_buffer, "?", 1);
                        current_segment_len = 1;
                    }
                } else {
                    char c_val = (char)va_arg(args, int);
                    temp_buffer[0] = c_val;
                    current_segment_len = 1;
                }
                // Precision has no effect on 'c'
                break;
            }
            case 'd':
            case 'i': { // 'i' is handled identically to 'd'
                long long num_val;
                if (fs.length == -1) num_val = (short)va_arg(args, int); // h
                else if (fs.length == 1) num_val = va_arg(args, long);   // l
                else num_val = va_arg(args, int);                         // default

                s21_sprintf_itoa(num_val, temp_buffer, 10, true, false);

                // Handle precision for 'd'/'i' (leading zeros)
                int num_digits = s21_strlen(temp_buffer);
                bool is_negative_d = false;
                if (temp_buffer[0] == '-') {
                    is_negative_d = true;
                    num_digits--; // Don't count the '-' as a digit
                }

                // If precision is explicitly 0 and value is 0, print nothing
                if (fs.precision == 0 && num_val == 0) {
                    current_segment_len = 0;
                } else if (fs.precision != -1 && fs.precision > num_digits) {
                    char temp_formatted[4096]; // Buffer for precision padding
                    s21_memset(temp_formatted, '0', fs.precision);
                    temp_formatted[fs.precision] = '\0';
                    s21_memcpy(temp_formatted + (fs.precision - num_digits), (is_negative_d ? temp_buffer + 1 : temp_buffer), num_digits);
                    s21_memcpy(temp_buffer, temp_formatted, fs.precision + 1);
                    temp_buffer[fs.precision] = '\0';
                }

                if (temp_buffer[0] == '-' && current_segment_len > 0) { // Check if sign is part of the converted string
                    sign_char_to_print = '-';
                    data_to_print = temp_buffer + 1; // Data starts after the sign
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
                if (fs.length == -1) u_num_val = (unsigned short)va_arg(args, unsigned int); // h
                else if (fs.length == 1) u_num_val = va_arg(args, unsigned long);  // l
                else u_num_val = va_arg(args, unsigned int);                        // default

                s21_sprintf_itoa(u_num_val, temp_buffer, 10, false, false);
                
                // Handle precision for 'u' (leading zeros)
                int num_digits = s21_strlen(temp_buffer);
                 if (fs.precision == 0 && u_num_val == 0) {
                    current_segment_len = 0;
                } else if (fs.precision != -1 && fs.precision > num_digits) {
                    char temp_formatted[4096];
                    s21_memset(temp_formatted, '0', fs.precision);
                    temp_formatted[fs.precision] = '\0';
                    s21_memcpy(temp_formatted + (fs.precision - num_digits), temp_buffer, num_digits);
                    s21_memcpy(temp_buffer, temp_formatted, fs.precision + 1);
                    temp_buffer[fs.precision] = '\0';
                }
                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);
                break;
            }
            case 'o':
            case 'x':
            case 'X': {
                unsigned long long u_num_val;
                if (fs.length == -1) u_num_val = (unsigned short)va_arg(args, unsigned int);
                else if (fs.length == 1) u_num_val = va_arg(args, unsigned long);
                else u_num_val = va_arg(args, unsigned int);

                int base = (fs.specifier == 'o') ? 8 : 16;
                bool upper_case = (fs.specifier == 'X');

                s21_sprintf_itoa(u_num_val, temp_buffer, base, false, upper_case);

                // Handle precision for 'o', 'x', 'X' (leading zeros)
                int num_digits = s21_strlen(temp_buffer);
                if (fs.precision == 0 && u_num_val == 0) {
                    current_segment_len = 0;
                    if (fs.hash && fs.specifier == 'o') { // For '0' with '#' and 'o', print '0'
                        current_segment_len = 1;
                        temp_buffer[0] = '0';
                        temp_buffer[1] = '\0';
                    }
                } else if (fs.precision != -1 && fs.precision > num_digits) {
                    char temp_formatted[4096];
                    s21_memset(temp_formatted, '0', fs.precision);
                    temp_formatted[fs.precision] = '\0';
                    s21_memcpy(temp_formatted + (fs.precision - num_digits), temp_buffer, num_digits);
                    s21_memcpy(temp_buffer, temp_formatted, fs.precision + 1);
                    temp_buffer[fs.precision] = '\0';
                }

                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);
                
                // Handle '#' flag for prefixes
                if (fs.hash && u_num_val != 0) { // Only add prefix if value is non-zero (except for 0o with # and 0)
                    if (fs.specifier == 'o') {
                        prefix_to_print = "0";
                    } else if (fs.specifier == 'x') {
                        prefix_to_print = "0x";
                    } else if (fs.specifier == 'X') {
                        prefix_to_print = "0X";
                    }
                    if (prefix_to_print) {
                        prefix_len = s21_strlen(prefix_to_print);
                    }
                }
                break;
            }
            case 'f':
            case 'e':
            case 'E':
            case 'g':
            case 'G': {
                long double f_val;
                if (fs.length == 2) f_val = va_arg(args, long double); // L
                else f_val = va_arg(args, double); // default or l (for double)

                s21_sprintf_ftoa_ext(f_val, temp_buffer, fs.precision, fs.specifier, fs.hash);

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
                if (fs.length == 1) { // 'l' length modifier for wide string
                    // Wide string handling (multibyte conversion) is complex.
                    // For this exercise, we'll just print a placeholder.
                    // A proper implementation would convert wchar_t* to char* using wcstombs.
                    s21_memcpy(temp_buffer, "(wide string not fully supported)", s21_strlen("(wide string not fully supported)"));
                    current_segment_len = s21_strlen(temp_buffer);
                } else {
                    char *s_val = va_arg(args, char *);
                    if (s_val == S21_NULL) {
                        s_val = "(null)";
                    }
                    s21_size_t s_len = s21_strlen(s_val);
                    s21_size_t len_to_copy = s_len;

                    if (fs.precision >= 0 && (s21_size_t)fs.precision < len_to_copy) {
                        len_to_copy = (s21_size_t)fs.precision;
                    }
                    
                    if (len_to_copy >= sizeof(temp_buffer)) { // Prevent overflow
                         len_to_copy = sizeof(temp_buffer) - 1;
                    }
                    s21_memcpy(temp_buffer, s_val, len_to_copy);
                    temp_buffer[len_to_copy] = '\0';
                    data_to_print = temp_buffer;
                    current_segment_len = len_to_copy;
                }
                break;
            }
            case 'p': { // Pointer address
                void *ptr_val = va_arg(args, void *);
                // Pointer addresses are typically printed in hexadecimal
                // Cast to unsigned long long to handle 64-bit addresses
                unsigned long long ptr_as_ull = (unsigned long long)ptr_val;

                s21_sprintf_itoa(ptr_as_ull, temp_buffer, 16, false, false); // Lowercase hex
                data_to_print = temp_buffer;
                current_segment_len = s21_strlen(data_to_print);

                // Add "0x" prefix
                prefix_to_print = "0x";
                prefix_len = 2;
                break;
            }
            case 'n': { // Number of characters written so far
                int *n_ptr = va_arg(args, int *);
                if (n_ptr != S21_NULL) {
                    *n_ptr = (int)(str - str_start);
                }
                current_segment_len = 0; // %n does not print anything
                break;
            }
        }

        // Apply padding and justification
        int num_sign_chars = (sign_char_to_print != 0) ? 1 : 0;
        int total_content_width = current_segment_len + num_sign_chars + prefix_len;
        int padding_chars = 0;
        if (fs.width > total_content_width) {
            padding_chars = fs.width - total_content_width;
        }

        // Zero-padding logic
        // '0' flag is ignored if '-' flag is set
        // '0' flag only applies to numeric conversions
        char pad_char = ' ';
        if (fs.zero_pad && !fs.minus && (fs.specifier == 'd' || fs.specifier == 'i' ||
                                          fs.specifier == 'u' || fs.specifier == 'o' ||
                                          fs.specifier == 'x' || fs.specifier == 'X' ||
                                          fs.specifier == 'f' || fs.specifier == 'e' ||
                                          fs.specifier == 'E' || fs.specifier == 'g' ||
                                          fs.specifier == 'G' || fs.specifier == 'p')) {
            pad_char = '0';
        }

        // Right-justify (pad before sign/prefix/data)
        if (!fs.minus) {
            if (pad_char == ' ') { // Pad with spaces before everything
                for (int i = 0; i < padding_chars; i++) *str++ = ' ';
            }
        }

        // Print sign
        if (sign_char_to_print) {
            *str++ = sign_char_to_print;
        }
        
        // Print prefix (e.g., 0x, 0X, 0)
        if (prefix_to_print) {
            s21_memcpy(str, prefix_to_print, prefix_len);
            str += prefix_len;
        }

        // Zero-padding for numbers (after sign/prefix)
        if (!fs.minus && pad_char == '0') {
             for (int i = 0; i < padding_chars; i++) *str++ = '0';
        }

        // Print the actual data
        s21_memcpy(str, data_to_print, current_segment_len);
        str += current_segment_len;

        // Left-justify (pad after data)
        if (fs.minus) {
            for (int i = 0; i < padding_chars; i++) *str++ = ' ';
        }
    }

    *str = '\0'; // Null-terminate the output string
    va_end(args);
    return (int)(str - str_start); // Return the number of characters written
}