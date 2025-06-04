#ifndef S21_SPRINTF
#define S21_SPRINTF

#include <stdarg.h>
#include <stdbool.h>


typedef struct Sprintf_format_spec {
    // bool optional; // This field was removed as it was unused.
    bool minus;      
    bool plus;       
    bool space;      
    int width;       
    int precision;   
    short length;    
    char specifier;  
    bool isPercent;  
} Sprintf_format_spec;


char *s21_sprintf_parse_int(char *str, int *number);
char *s21_sprintf_itoa(long long num, char *buf, int base);
char *s21_sprintf_ftoa(double num, char *buf, int precision);
char *sprintf_parse_format_spec(Sprintf_format_spec *fs, char *format);


int s21_sprintf(char *str, const char *format, ...);

#endif
