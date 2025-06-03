#include <check.h>
#include <string.h>
#include "../s21_string.h"

START_TEST(test_s21_strpbrk_normal) {
    const char *str1 = "hello";
    const char *str2 = "ae";
    char *result = s21_strpbrk(str1, str2);
    ck_assert_str_eq(result, "ello");
} END_TEST

START_TEST(test_s21_strpbrk_no_match) {
    const char *str1 = "hello";
    const char *str2 = "xyz";
    char *result = s21_strpbrk(str1, str2);
    ck_assert_ptr_eq(result, S21_NULL);
} END_TEST

START_TEST(test_s21_strpbrk_null) {
    char *result = s21_strpbrk(NULL, "a");
    ck_assert_ptr_eq(result, S21_NULL);
} END_TEST

Suite *s21_strpbrk_suite(void) {
    Suite *s = suite_create("strpbrk_suite");
    TCase *tc = tcase_create("strpbrk_tcs");
    tcase_add_test(tc, test_s21_strpbrk_normal);
    tcase_add_test(tc, test_s21_strpbrk_no_match);
    tcase_add_test(tc, test_s21_strpbrk_null);
    suite_add_tcase(s, tc);
    return s;
}
