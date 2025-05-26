#include "../s21_string.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>


struct Format_Spec{
    bool optional;
    int width;
    short length;
    char specifier;
    bool isPercent
};

char * s21_stoi(char * str, int * number){
    *number = 0;
    while(*str && *str >= '0' && *str <= '9'){
        number *= 10;
        number += (int)(*str - 48); // '0' <=> 48
        *str++;
    }
    return str;
}

char * s21_stof(char * str, double * number){
    *number = 0;

    while(*str && *str >= '0' && *str <= '9'){
        *number *= 10;
        *number += (int)(*str - 48); // '0' <=> 48
        str++;
    }

    if(*str != '.') ;// idk how to throw an error
    str++;
    double fnum = 0;
    double tenth = 0.1;
    while(*str && *str >= '0' && *str <= '9'){
        fnum = fnum + (*str-48)* tenth;
        tenth /= 10;
        str++;
    }

    *number+= fnum;
    return str;
}

#include "../s21_string.h"

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


int sscanf(const char *str, const char *format, ...){
    va_list args_ptr;
    va_start(args_ptr, format);
    Format_Spec * fs = malloc(sizeof(Format_Spec));
    
    char * fstr = format;


    while (true){
        fstr = parse_format(fs, fstr);

        if (fs->width == 0) while (*str == ' ') str++;
    
        if (fs->specifier == 'c') *va_arg()
        
        






    }
    
    
    va_end(args_ptr);
    free(fs);
}

