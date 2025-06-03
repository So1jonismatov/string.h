
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>


#ifndef SSCANF
#define SSCANF

#include "../s21_string.h"

struct Format_Spec {
    bool optional;    // For '*' to skip assignment
    int width;        // How many characters to read
    int length;       // 0: none, -1: h, 1: l, -2: hh, 2: ll, 3: L
    char specifier;   // Like 'd', 's', 'f'
    bool isPercent;   // For handling %%
    bool minus;       // Flag: - (left justification, affects width parsing)
    bool plus;        // Flag: + (forces sign in input)
    bool space;       // Flag: (space) (expects space before value if no sign)
    bool hash;        // Flag: # (affects format, e.g., 0x for hex)
    bool zero;        // Flag: 0 (left-pad with zeros for width)
};

char *s21_stoi(char *str, int *number);
char *s21_stof(char *str, double *number);
char *parse_format(struct Format_Spec *fs, char *format);
int s21_sscanf(const char *str, const char *format, ...);


#endif