#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_memcpy_normal) {
  char dest[10] = "123";
  const char *src = "abc";
  s21_size_t n = 3;
  void *result = s21_memcpy(dest, src, n);
  ck_assert_str_eq(dest, "abc");
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_s21_memcpy_zero) {
  char dest[10] = "123";
  const char *src = "abc";
  void *result = s21_memcpy(dest, src, 0);
  ck_assert_str_eq(dest, "123");
  ck_assert_ptr_eq(result, dest);
}
END_TEST

START_TEST(test_s21_memcpy_null) {
  void *result = s21_memcpy(NULL, "abc", 3);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s = suite_create("memcpy_suite");
  TCase *tc = tcase_create("memcpy_tcs");
  tcase_add_test(tc, test_s21_memcpy_normal);
  tcase_add_test(tc, test_s21_memcpy_zero);
  tcase_add_test(tc, test_s21_memcpy_null);
  suite_add_tcase(s, tc);
  return s;
}