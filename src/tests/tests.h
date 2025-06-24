#ifndef _S21_STRING_TESTS
#define _S21_STRING_TESTS
#include <check.h>

Suite *s21_memchr_suite();
Suite *s21_memcmp_suite();
Suite *s21_memcpy_suite();
Suite *s21_memset_suite();
Suite *s21_strlen_suite();
Suite *s21_strncat_suite();
Suite *s21_strncmp_suite();
Suite *s21_strchr_suite();
Suite *s21_strncpy_suite();
Suite *s21_strcspn_suite();
Suite *s21_strpbrk_suite();
Suite *s21_strrchr_suite();
Suite *s21_strspn_suite();
Suite *s21_strstr_suite();
Suite *s21_strtok_suite();
Suite *s21_io_suite();
Suite *s21_specials_suite();

void run_tests();
void run(Suite *test);



#endif
