#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strcspn_normal) {
  const char *str1 = "hello";
  const char *str2 = "ae";
  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 1);  // 'e' is the first match
}
END_TEST

START_TEST(test_s21_strcspn_no_match) {
  const char *str1 = "hello";
  const char *str2 = "xyz";
  s21_size_t result = s21_strcspn(str1, str2);
  ck_assert_int_eq(result, 5);
}
END_TEST

START_TEST(test_s21_strcspn_null) {
  s21_size_t result = s21_strcspn(NULL, "a");
  ck_assert_int_eq(result, 0);  // Adjust based on impl
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s = suite_create("strcspn_suite");
  TCase *tc = tcase_create("strcspn_tcs");
  tcase_add_test(tc, test_s21_strcspn_normal);
  tcase_add_test(tc, test_s21_strcspn_no_match);
  tcase_add_test(tc, test_s21_strcspn_null);
  suite_add_tcase(s, tc);
  return s;
}
