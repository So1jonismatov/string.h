#include <check.h>
#include <string.h>
#include "../s21_string.h"

START_TEST(test_s21_strncpy_normal) {
    char dest[10] = "123";
    const char *src = "abcdef";
    char *result = s21_strncpy(dest, src, 3);
    ck_assert_str_eq(dest, "abc");
    ck_assert_ptr_eq(result, dest);
} END_TEST

START_TEST(test_s21_strncpy_zero) {
    char dest[10] = "123";
    const char *src = "abcdef";
    char *result = s21_strncpy(dest, src, 0);
    ck_assert_str_eq(dest, "123");
    ck_assert_ptr_eq(result, dest);
} END_TEST

START_TEST(test_s21_strncpy_null) {
    char *result = s21_strncpy(NULL, "abc", 3);
    ck_assert_ptr_eq(result, S21_NULL);
} END_TEST

Suite *s21_strncpy_suite(void) {
    Suite *s = suite_create("strncpy_suite");
    TCase *tc = tcase_create("strncpy_tcs");
    tcase_add_test(tc, test_s21_strncpy_normal);
    tcase_add_test(tc, test_s21_strncpy_zero);
    tcase_add_test(tc, test_s21_strncpy_null);
    suite_add_tcase(s, tc);
    return s;
}
