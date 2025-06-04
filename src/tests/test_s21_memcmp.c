#include <check.h>
#include <string.h>
#include "../s21_string.h"

START_TEST(test_s21_memcmp_normal_equal){

    const char *str1 = "Hello";
    const char *str2 = "Hello";

    s21_size_t n = 5;

    int result = s21_memcmp(str1, str2, n);
    int expected_result = memcmp(str1, str2, n);

    ck_assert_int_eq(result, expected_result);

}END_TEST

START_TEST(test_s21_memcmp_normal_not_equal){

    const char *str1 = "Hello";
    const char *str2 = "Hollo";

    s21_size_t n = 5;

    int result = s21_memcmp(str1, str2, n);
    int expected_result = memcmp(str1, str2, n);

    ck_assert_int_eq(result, expected_result);

}END_TEST

START_TEST(test_s21_memcmp_zero_length){

    const char *str1 = "Hello";
    const char *str2 = "Hello";

    s21_size_t n = 0;

    int result = s21_memcmp(str1, str2, n);
    int expected_result = memcmp(str1, str2, n);

    ck_assert_int_eq(result, expected_result);

}END_TEST

START_TEST(test_s21_memcmp_equal_pointers){

    const char *str1 = "Hello";
    const char *str2 = str1;

    s21_size_t n = 5;

    int result = s21_memcmp(str1, str2, n);
    int expected_result = memcmp(str1, str2, n);

    ck_assert_int_eq(result, expected_result);

}END_TEST

START_TEST(test_s21_memcmp_different_length){

    const char *str1 = "Hello";
    const char *str2 = "HelloYaHello";

    s21_size_t n = 5;

    int result = s21_memcmp(str1, str2, n);
    int expected_result = memcmp(str1, str2, n);

    ck_assert_int_eq(result, expected_result);

}END_TEST



Suite *s21_memcmp_suite(){
    Suite *s = suite_create("memcmp_suite");
    TCase *tc = tcase_create("memcmp_tcs");

    tcase_add_test(tc, test_s21_memcmp_normal_equal);
    tcase_add_test(tc, test_s21_memcmp_normal_not_equal);
    tcase_add_test(tc, test_s21_memcmp_zero_length);
    tcase_add_test(tc, test_s21_memcmp_equal_pointers);
    tcase_add_test(tc, test_s21_memcmp_different_length);

    suite_add_tcase(s, tc);
    return s;
}





