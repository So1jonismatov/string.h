#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strstr_normal) {
  const char *haystack = "hello world";
  const char *needle = "world";
  char *result = s21_strstr(haystack, needle);
  ck_assert_str_eq(result, "world");
}
END_TEST

START_TEST(test_s21_strstr_not_found) {
  const char *haystack = "hello";
  const char *needle = "xyz";
  char *result = s21_strstr(haystack, needle);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_strstr_null) {
  char *result = s21_strstr(NULL, "a");
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *s = suite_create("strstr_suite");
  TCase *tc = tcase_create("strstr_tcs");
  tcase_add_test(tc, test_s21_strstr_normal);
  tcase_add_test(tc, test_s21_strstr_not_found);
  tcase_add_test(tc, test_s21_strstr_null);
  suite_add_tcase(s, tc);
  return s;
}