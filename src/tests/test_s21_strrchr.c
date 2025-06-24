#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strrchr_normal) {
  const char *str = "hello";
  char *result = s21_strrchr(str, 'l');
  ck_assert_str_eq(result, "lo");
}
END_TEST

START_TEST(test_s21_strrchr_not_found) {
  const char *str = "hello";
  char *result = s21_strrchr(str, 'z');
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_strrchr_null) {
  char *result = s21_strrchr(NULL, 'a');
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *s = suite_create("strrchr_suite");
  TCase *tc = tcase_create("strrchr_tcs");
  tcase_add_test(tc, test_s21_strrchr_normal);
  tcase_add_test(tc, test_s21_strrchr_not_found);
  tcase_add_test(tc, test_s21_strrchr_null);
  suite_add_tcase(s, tc);
  return s;
}