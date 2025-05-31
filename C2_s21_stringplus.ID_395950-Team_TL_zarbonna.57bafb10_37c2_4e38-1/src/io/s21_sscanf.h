#ifndef SPRINTF
#define SPRINTF

#include "../s21_string.h"

struct Format_Spec{
    bool optional;
    int width;
    short length;
    char specifier;
    bool isPercent
};

char * s21_stoi(char * str, int * number);
char * s21_stof(char * str, double * number);
char *parse_format(Format_Spec *fs, char *format) ;
int sscanf(const char *str, const char *format, ...);





#endif