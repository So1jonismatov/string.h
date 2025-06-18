#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strncat_normal) {
  char dest[10] = "hello";
  const char *src = "world";
  char *result = s21_strncat(dest, src, 3);
  ck_assert_str_eq(dest, "hellowor");
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_s21_strncat_zero) {
  char dest[10] = "hello";
  const char *src = "world";
  char *result = s21_strncat(dest, src, 0);
  ck_assert_str_eq(dest, "hello");
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_s21_strncat_null) {
  char dest[10] = "hello";
  char *result = s21_strncat(dest, NULL, 3);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *s = suite_create("strncat_suite");
  TCase *tc = tcase_create("strncat_tcs");
  tcase_add_test(tc, test_s21_strncat_normal);
  tcase_add_test(tc, test_s21_strncat_zero);
  tcase_add_test(tc, test_s21_strncat_null);
  suite_add_tcase(s, tc);
  return s;
}