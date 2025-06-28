#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_s21_insert_normal) {
  char str[] = "Hello";
  char *result = s21_insert(str, "World", 5);
  ck_assert_str_eq(result, "HelloWorld");
  free(result);  // Assuming s21_insert allocates memory
}
END_TEST

START_TEST(test_s21_insert_null) {
  char *result = s21_insert(NULL, "World", 0);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_to_lower_normal) {
  char str[] = "HeLLo";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "hello");
  free(result);  // Assuming s21_to_lower allocates memory
}
END_TEST

START_TEST(test_s21_to_lower_null) {
  char *result = s21_to_lower(NULL);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_to_upper_normal) {
  char str[] = "HeLLo";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO");
  free(result);  // Assuming s21_to_upper allocates memory
}
END_TEST

START_TEST(test_s21_to_upper_null) {
  char *result = s21_to_upper(NULL);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_trim_normal) {
  char str[] = "  Hello  ";
  char *result = s21_trim(str, " ");
  ck_assert_str_eq(result, "Hello");
  free(result);  // Assuming s21_trim allocates memory
}
END_TEST

START_TEST(test_s21_trim_null) {
  char *result = s21_trim(NULL, " ");
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_s21_trim_empty) {
  char str[] = "";
  char *result = s21_trim(str, " ");
  ck_assert_str_eq(result, "");
  free(result);  // Assuming s21_trim allocates memory
}
END_TEST

Suite *s21_specials_suite(void) {
  Suite *s = suite_create("specials_suite");
  TCase *tc = tcase_create("specials_tcs");
  tcase_add_test(tc, test_s21_insert_normal);
  tcase_add_test(tc, test_s21_insert_null);
  tcase_add_test(tc, test_s21_to_lower_normal);
  tcase_add_test(tc, test_s21_to_lower_null);
  tcase_add_test(tc, test_s21_to_upper_normal);
  tcase_add_test(tc, test_s21_to_upper_null);
  tcase_add_test(tc, test_s21_trim_normal);
  tcase_add_test(tc, test_s21_trim_null);
  tcase_add_test(tc, test_s21_trim_empty);
  suite_add_tcase(s, tc);
  return s;
}
