#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strspn_normal) {
  const char *str1 = "hello";
  const char *str2 = "he";
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_s21_strspn_no_match) {
  const char *str1 = "hello";
  const char *str2 = "xyz";
  s21_size_t result = s21_strspn(str1, str2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_strspn_null) {
  s21_size_t result = s21_strspn(NULL, "a");
  ck_assert_int_eq(result, 0);  // Adjust based on impl
}
END_TEST

Suite *s21_strspn_suite(void) {
  Suite *s = suite_create("strspn_suite");
  TCase *tc = tcase_create("strspn_tcs");
  tcase_add_test(tc, test_s21_strspn_normal);
  tcase_add_test(tc, test_s21_strspn_no_match);
  tcase_add_test(tc, test_s21_strspn_null);
  suite_add_tcase(s, tc);
  return s;
}