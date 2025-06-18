#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strncmp_equal) {
  const char *str1 = "hello";
  const char *str2 = "hello";
  int result = s21_strncmp(str1, str2, 5);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_strncmp_different) {
  const char *str1 = "hello";
  const char *str2 = "help";
  int result = s21_strncmp(str1, str2, 4);
  ck_assert_int_eq(result, -4);
}
END_TEST

START_TEST(test_s21_strncmp_null) {
  const char *str1 = "hello";
  int result = s21_strncmp(str1, NULL, 5);
  ck_assert_int_eq(result, 0);  // Adjust based on your impl
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *s = suite_create("strncmp_suite");
  TCase *tc = tcase_create("strncmp_tcs");
  tcase_add_test(tc, test_s21_strncmp_equal);
  tcase_add_test(tc, test_s21_strncmp_different);
  tcase_add_test(tc, test_s21_strncmp_null);
  suite_add_tcase(s, tc);
  return s;
}
