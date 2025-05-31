#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold the parsed format specifier details
typedef struct {
    bool suppress_assignment; // Corresponds to '*'
    int width;                // Maximum field width
    enum {
        LEN_NONE, LEN_hh, LEN_h, LEN_l, LEN_ll, LEN_L
    } length;                 // Length modifier (h, l, ll, etc.)
    char specifier;           // The conversion specifier (d, s, f, etc.)
} FormatSpec;

// A helper to check if a character is whitespace
static int is_space(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

// Skips whitespace in the input string
static void skip_whitespace(const char **s) {
    while (is_space(**s)) {
        (*s)++;
    }
}

// Parses the format string to extract the next format specifier
static const char *parse_format_spec(const char *format, FormatSpec *fs) {
    // Reset the struct
    *fs = (FormatSpec){.suppress_assignment = false, .width = 0, .length = LEN_NONE, .specifier = 0};

    // Check for assignment suppression
    if (*format == '*') {
        fs->suppress_assignment = true;
        format++;
    }

    // Parse width
    if (isdigit(*format)) {
        // Use strtol for robust parsing of the width number
        fs->width = (int)strtol(format, (char **)&format, 10);
    }

    // Parse length modifier
    switch (*format) {
        case 'h':
            if (*(format + 1) == 'h') {
                fs->length = LEN_hh;
                format += 2;
            } else {
                fs->length = LEN_h;
                format++;
            }
            break;
        case 'l':
            if (*(format + 1) == 'l') {
                fs->length = LEN_ll;
                format += 2;
            } else {
                fs->length = LEN_l;
                format++;
            }
            break;
        case 'L':
            fs->length = LEN_L;
            format++;
            break;
    }

    fs->specifier = *format;
    return format + 1;
}


// Handles all integer specifiers (d, i, o, u, x, p)
static bool handle_integer(const char **input, va_list args, const FormatSpec *fs) {
    char *endptr;
    long long int value = 0;
    unsigned long long int uvalue = 0;
    
    int base = 10;
    if (fs->specifier == 'i') base = 0; // auto-detect octal/hex
    else if (fs->specifier == 'x' || fs->specifier == 'X' || fs->specifier == 'p') base = 16;
    else if (fs->specifier == 'o') base = 8;
    
    // Unsigned specifiers should not match a minus sign in the input
    if ((fs->specifier == 'u' || fs->specifier == 'o' || fs->specifier == 'x' || fs->specifier == 'X') && **input == '-') {
        return false;
    }

    // Use the appropriate standard library function for parsing
    if (fs->specifier == 'd' || fs->specifier == 'i') {
        value = strtoll(*input, &endptr, base);
    } else {
        uvalue = strtoull(*input, &endptr, base);
    }
    
    if (endptr == *input) return false; // No conversion took place
    
    // Update the main input pointer
    *input = endptr;

    if (!fs->suppress_assignment) {
        void* ptr = va_arg(args, void*);
        switch (fs->specifier) {
            case 'd': case 'i':
                if (fs->length == LEN_hh) *(signed char*)ptr = (signed char)value;
                else if (fs->length == LEN_h) *(short*)ptr = (short)value;
                else if (fs->length == LEN_l) *(long*)ptr = (long)value;
                else if (fs->length == LEN_ll) *(long long*)ptr = value;
                else *(int*)ptr = (int)value;
                break;
            case 'u': case 'o': case 'x': case 'X':
                if (fs->length == LEN_hh) *(unsigned char*)ptr = (unsigned char)uvalue;
                else if (fs->length == LEN_h) *(unsigned short*)ptr = (unsigned short)uvalue;
                else if (fs->length == LEN_l) *(unsigned long*)ptr = (unsigned long)uvalue;
                else if (fs->length == LEN_ll) *(unsigned long long*)ptr = uvalue;
                else *(unsigned int*)ptr = (unsigned int)uvalue;
                break;
            case 'p':
                *(void**)ptr = (void*)(uintptr_t)uvalue;
                break;
        }
    }
    return true;
}

// Handles all floating-point specifiers (f, e, g)
static bool handle_float(const char **input, va_list args, const FormatSpec *fs) {
    char *endptr;
    long double value = strtold(*input, &endptr);
    if (endptr == *input) return false; // No conversion
    
    *input = endptr;
    
    if (!fs->suppress_assignment) {
        if (fs->length == LEN_L) {
            *va_arg(args, long double*) = value;
        } else if (fs->length == LEN_l) {
            *va_arg(args, double*) = (double)value;
        } else {
            *va_arg(args, float*) = (float)value;
        }
    }
    return true;
}

int s21_sscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);

    const char *s_ptr = str;
    const char *f_ptr = format;
    int assignments = 0;
    const char *initial_s_ptr = str;

    // Control flag for the main processing loop
    bool processing_active = true;
    
    // Check for empty input string, which can be an immediate EOF condition
    if (*s_ptr == '\0' && *f_ptr != '\0') {
        va_end(args);
        return EOF;
    }

    while (*f_ptr && processing_active) {
        FormatSpec fs;

        if (is_space(*f_ptr)) {
            skip_whitespace(&s_ptr);
            f_ptr++;
            continue;
        }

        if (*f_ptr != '%') {
            if (*s_ptr == *f_ptr) {
                s_ptr++;
                f_ptr++;
            } else {
                processing_active = false; // Literal mismatch, stop processing
            }
            continue;
        }

        // --- Start of a Format Specifier ---
        f_ptr++;

        // Handle the '%%' case
        if (*f_ptr == '%') {
            if (*s_ptr == '%') {
                s_ptr++;
                f_ptr++;
            } else {
                processing_active = false; // Literal '%' mismatch
            }
            continue;
        }
        
        f_ptr = parse_format_spec(f_ptr, &fs);
        
        // Before matching, most specifiers skip leading whitespace
        if (fs.specifier != 'c' && fs.specifier != '[') {
            skip_whitespace(&s_ptr);
        }

        bool matched = false;
        
        // If input is exhausted before a conversion, it's a failure
        if (*s_ptr == '\0' && fs.specifier != 'n') {
            processing_active = false;
            // Set EOF if this is the very first conversion attempt
            if (assignments == 0) {
                assignments = EOF;
            }
            continue;
        }
        
        switch (fs.specifier) {
            case 'd': case 'i': case 'o': case 'u': case 'x': case 'X': case 'p':
                matched = handle_integer(&s_ptr, args, &fs);
                break;

            case 'f': case 'e': case 'E': case 'g': case 'G':
                matched = handle_float(&s_ptr, args, &fs);
                break;
                
            case 's': {
                // Simplified string matching
                const char* start = s_ptr;
                int width = fs.width > 0 ? fs.width : 2048; // Prevent overflow
                char* dest = fs.suppress_assignment ? NULL : va_arg(args, char*);
                int i = 0;
                while (*s_ptr && !is_space(*s_ptr) && i < width) {
                    if (dest) dest[i] = *s_ptr;
                    i++;
                    s_ptr++;
                }
                if (dest) dest[i] = '\0';
                matched = (s_ptr > start);
                break;
            }
            
            case 'c':
                // '%c' does not skip whitespace
                if (*s_ptr) {
                    int width = fs.width > 0 ? fs.width : 1;
                    char* dest = fs.suppress_assignment ? NULL : va_arg(args, char*);
                    for (int i = 0; i < width && s_ptr[i]; ++i) {
                         if (dest) dest[i] = s_ptr[i];
                    }
                    s_ptr += width;
                    matched = true;
                }
                break;
            
            case 'n':
                if (!fs.suppress_assignment) {
                    *va_arg(args, int*) = (int)(s_ptr - initial_s_ptr);
                }
                // '%n' does not consume input or count as an assignment, so we continue
                // without modifying 'matched' or 'assignments'.
                continue;
            
            default:
                // Unsupported or invalid specifier, stop processing
                processing_active = false;
                continue;
        }

        if (matched) {
            if (!fs.suppress_assignment) {
                assignments++;
            }
        } else {
            // A conversion failed, stop processing
            processing_active = false;
        }
    }

    va_end(args);
    return assignments;
}