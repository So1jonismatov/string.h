#include <check.h>
#include <string.h>
#include "../s21_string.h"

START_TEST(test_s21_strchr_normal) {
    const char *str = "hello";
    char *result = s21_strchr(str, 'l');
    ck_assert_str_eq(result, "llo");
} END_TEST

START_TEST(test_s21_strchr_not_found) {
    const char *str = "hello";
    char *result = s21_strchr(str, 'z');
    ck_assert_ptr_eq(result, S21_NULL);
} END_TEST

START_TEST(test_s21_strchr_null) {
    char *result = s21_strchr(NULL, 'a');
    ck_assert_ptr_eq(result, S21_NULL);
} END_TEST

Suite *s21_strchr_suite(void) {
    Suite *s = suite_create("strchr_suite");
    TCase *tc = tcase_create("strchr_tcs");
    tcase_add_test(tc, test_s21_strchr_normal);
    tcase_add_test(tc, test_s21_strchr_not_found);
    tcase_add_test(tc, test_s21_strchr_null);
    suite_add_tcase(s, tc);
    return s;
}
