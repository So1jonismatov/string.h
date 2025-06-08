#include <check.h>
#include <string.h>
#include "../s21_string.h"

START_TEST(test_s21_memset_normal) {
    char str[5] = "abcd";
    void *result = s21_memset(str, 'x', 3);
    ck_assert_str_eq(str, "xxxd");
    ck_assert_ptr_eq(result, str);
} END_TEST

START_TEST(test_s21_memset_zero) {
    char str[5] = "abcd";
    void *result = s21_memset(str, 'x', 0);
    ck_assert_str_eq(str, "abcd");
    ck_assert_ptr_eq(result, str);
} END_TEST

START_TEST(test_s21_memset_null) {
    void *result = s21_memset(NULL, 'x', 3);
    ck_assert_ptr_eq(result, S21_NULL);
} END_TEST

Suite *s21_memset_suite(void) {
    Suite *s = suite_create("memset_suite");
    TCase *tc = tcase_create("memset_tcs");
    tcase_add_test(tc, test_s21_memset_normal);
    tcase_add_test(tc, test_s21_memset_zero);
    tcase_add_test(tc, test_s21_memset_null);
    suite_add_tcase(s, tc);
    return s;
}