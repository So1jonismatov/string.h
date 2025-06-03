#include <check.h>
#include <string.h>
#include "../s21_string.h"

START_TEST(test_s21_strlen_normal) {
    const char *str = "hello";
    s21_size_t result = s21_strlen(str);
    ck_assert_int_eq(result, 5);
} END_TEST

START_TEST(test_s21_strlen_empty) {
    const char *str = "";
    s21_size_t result = s21_strlen(str);
    ck_assert_int_eq(result, 0);
} END_TEST

START_TEST(test_s21_strlen_null) {
    s21_size_t result = s21_strlen(NULL);
    ck_assert_int_eq(result, 0); // Assuming NULL returns 0, adjust if your impl differs
} END_TEST

Suite *s21_strlen_suite(void) {
    Suite *s = suite_create("strlen_suite");
    TCase *tc = tcase_create("strlen_tcs");
    tcase_add_test(tc, test_s21_strlen_normal);
    tcase_add_test(tc, test_s21_strlen_empty);
    tcase_add_test(tc, test_s21_strlen_null);
    suite_add_tcase(s, tc);
    return s;
}