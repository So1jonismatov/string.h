#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_memchr_normal) {
  // setup qilish
  const char *str = "Hello";
  int c = 'H';
  s21_size_t n = 5;
  // tekshirilsh logikasi
  void *result = s21_memchr(str, c, n);
  void *expected_result = memchr(str, c, n);

  ck_assert_ptr_eq(result, expected_result);
}
END_TEST

START_TEST(test_s21_memchr_test_iteration) {
  // setup qilish
  const char *str = "Hello";
  int c = 'o';
  s21_size_t n = 5;
  // tekshirilsh logikasi
  void *result = s21_memchr(str, c, n);
  void *expected_result = memchr(str, c, n);

  ck_assert_ptr_eq(result, expected_result);
}
END_TEST

START_TEST(test_s21_memchr_null_at_the_end) {
  const char *str = "NIGGA";
  int c = '\0';
  s21_size_t n = 6;

  void *result = s21_memchr(str, c, n);
  void *expected_result = memchr(str, c, n);

  ck_assert_ptr_eq(result, expected_result);
}
END_TEST

START_TEST(test_s21_memchr_null) {
  void *result = s21_memchr(S21_NULL, 'A', 5);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_memchr_zero_test) {
  void *result = s21_memchr("Hello", 'o', 0);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_memchr_no_match) {
  void *result = s21_memchr("Hello", 'u', 5);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_memchr_negative_c) {
  const char *str = "\xFF";
  int c = -1;
  void *result = s21_memchr(str, c, 1);
  void *expected_result = memchr(str, c, 1);
  ck_assert_ptr_eq(result, expected_result);
}
END_TEST

START_TEST(test_s21_memchr_intstr) {
  int array[] = {10, 15, 20, 25, 30};
  int c = 15;
  s21_size_t n = 5 * sizeof(int);
  void *result = s21_memchr(array, c, n);
  void *expected_result = memchr(array, c, n);
  ck_assert_ptr_eq(result, expected_result);
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *s = suite_create("memchr_suite");
  TCase *tc = tcase_create("memchr_tcs");

  tcase_add_test(tc, test_s21_memchr_normal);
  tcase_add_test(tc, test_s21_memchr_null_at_the_end);
  tcase_add_test(tc, test_s21_memchr_null);
  tcase_add_test(tc, test_s21_memchr_negative_c);
  tcase_add_test(tc, test_s21_memchr_intstr);
  tcase_add_test(tc, test_s21_memchr_test_iteration);
  tcase_add_test(tc, test_s21_memchr_zero_test);
  tcase_add_test(tc, test_s21_memchr_no_match);

  suite_add_tcase(s, tc);
  return s;
}