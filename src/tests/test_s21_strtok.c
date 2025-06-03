#include <check.h>
#include <string.h>
#include "../s21_string.h"

START_TEST(test_s21_strtok_normal) {
    char str[] = "hello,world,again";
    const char *delim = ",";
    char *token = s21_strtok(str, delim);
    ck_assert_str_eq(token, "hello");
    token = s21_strtok(NULL, delim);
    ck_assert_str_eq(token, "world");
} END_TEST

START_TEST(test_s21_strtok_no_delim) {
    char str[] = "hello";
    const char *delim = ",";
    char *token = s21_strtok(str, delim);
    ck_assert_str_eq(token, "hello");
} END_TEST

START_TEST(test_s21_strtok_null) {
    char *token = s21_strtok(NULL, ",");
    ck_assert_ptr_eq(token, S21_NULL);
} END_TEST

Suite *s21_strtok_suite(void) {
    Suite *s = suite_create("strtok_suite");
    TCase *tc = tcase_create("strtok_tcs");
    tcase_add_test(tc, test_s21_strtok_normal);
    tcase_add_test(tc, test_s21_strtok_no_delim);
    tcase_add_test(tc, test_s21_strtok_null);
    suite_add_tcase(s, tc);
    return s;
}