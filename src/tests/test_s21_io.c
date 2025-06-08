#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "../s21_string.h"

START_TEST(test_s21_sprintf_c_normal) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%c", 'A');
    int ret2 = sprintf(buf2, "%c", 'A');
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_c_edge) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%c", '\0');  // Null character
    int ret2 = sprintf(buf2, "%c", '\0');
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_d_normal) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%d", 123);
    int ret2 = sprintf(buf2, "%d", 123);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_d_negative) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%d", -456);
    int ret2 = sprintf(buf2, "%d", -456);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_d_zero) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%d", 0);
    int ret2 = sprintf(buf2, "%d", 0);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_f_normal) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%.2f", 3.14159);
    int ret2 = sprintf(buf2, "%.2f", 3.14159);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_f_negative) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%.2f", -3.14159);
    int ret2 = sprintf(buf2, "%.2f", -3.14159);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_f_zero) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%.2f", 0.0);
    int ret2 = sprintf(buf2, "%.2f", 0.0);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_s_normal) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%s", "hello");
    int ret2 = sprintf(buf2, "%s", "hello");
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_s_empty) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%s", "");
    int ret2 = sprintf(buf2, "%s", "");
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_u_normal) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%u", 123);
    int ret2 = sprintf(buf2, "%u", 123);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_u_zero) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%u", 0);
    int ret2 = sprintf(buf2, "%u", 0);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_percent_normal) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%%");
    int ret2 = sprintf(buf2, "%%");
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_flags_width_precision) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%+10.3d", 123);
    int ret2 = sprintf(buf2, "%+10.3d", 123);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_flags_negative) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%-10.3d", -123);
    int ret2 = sprintf(buf2, "%-10.3d", -123);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_width_only) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%10d", 123);
    int ret2 = sprintf(buf2, "%10d", 123);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_precision_only) {
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%.3f", 3.14159);
    int ret2 = sprintf(buf2, "%.3f", 3.14159);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_length_short) {
    short s = 123;
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%hd", s);
    int ret2 = sprintf(buf2, "%hd", s);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_length_long) {
    long l = 123456L;
    char buf1[20], buf2[20] = {0};
    int ret1 = s21_sprintf(buf1, "%ld", l);
    int ret2 = sprintf(buf2, "%ld", l);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sprintf_null) {
    char buf1[20] = {0};
    int ret1 = s21_sprintf(buf1, "%s", NULL);  // Test your implementation
    ck_assert_int_eq(ret1, 6);  // Length of "(null)"
    ck_assert_str_eq(buf1, "(null)");  // Verify your output
} END_TEST


// sscanf tests
START_TEST(test_s21_sscanf_d_normal) {
    int num1, num2;
    const char *str = "123";
    int ret1 = s21_sscanf(str, "%d", &num1);
    int ret2 = sscanf(str, "%d", &num2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_int_eq(num1, num2);
} END_TEST

START_TEST(test_s21_sscanf_d_negative) {
    int num1, num2;
    const char *str = "-456";
    int ret1 = s21_sscanf(str, "%d", &num1);
    int ret2 = sscanf(str, "%d", &num2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_int_eq(num1, num2);
} END_TEST

START_TEST(test_s21_sscanf_d_zero) {
    int num1, num2;
    const char *str = "0";
    int ret1 = s21_sscanf(str, "%d", &num1);
    int ret2 = sscanf(str, "%d", &num2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_int_eq(num1, num2);
} END_TEST

START_TEST(test_s21_sscanf_f_normal) {
    double num1, num2;
    const char *str = "3.14159";
    int ret1 = s21_sscanf(str, "%lf", &num1);
    int ret2 = sscanf(str, "%lf", &num2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_double_eq(num1, num2);
} END_TEST

START_TEST(test_s21_sscanf_f_negative) {
    double num1, num2;
    const char *str = "-3.14159";
    int ret1 = s21_sscanf(str, "%lf", &num1);
    int ret2 = sscanf(str, "%lf", &num2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_double_eq(num1, num2);
} END_TEST

START_TEST(test_s21_sscanf_s_normal) {
    char buf1[20], buf2[20] = {0};
    const char *str = "hello world";
    int ret1 = s21_sscanf(str, "%s", buf1);
    int ret2 = sscanf(str, "%s", buf2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sscanf_s_empty) {
    char buf1[20], buf2[20] = {0};
    const char *str = "";
    int ret1 = s21_sscanf(str, "%s", buf1);
    int ret2 = sscanf(str, "%s", buf2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_str_eq(buf1, buf2);
} END_TEST

START_TEST(test_s21_sscanf_width_precision) {
    int num1, num2;
    const char *str = "123456";
    int ret1 = s21_sscanf(str, "%3d", &num1);
    int ret2 = sscanf(str, "%3d", &num2);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_int_eq(num1, num2);  // Should be 123, not 123456
} END_TEST



START_TEST(test_s21_sscanf_null) {
    int num;
    int ret1 = s21_sscanf(NULL, "%d", &num);  // Should fail
    ck_assert_int_eq(ret1, -1);  // Expect failure
} END_TEST

START_TEST(test_s21_sscanf_invalid_format) {
    int num;
    const char *str = "123abc";
    int ret1 = s21_sscanf(str, "%d", &num);  // Should parse only "123"
    int ret2 = sscanf(str, "%d", &num);
    ck_assert_int_eq(ret1, ret2);
    ck_assert_int_eq(num, 123);
} END_TEST

Suite *s21_io_suite(void) {
    Suite *s = suite_create("io_suite");
    TCase *tc = tcase_create("io_tcs");
    tcase_add_test(tc, test_s21_sprintf_c_normal);
    tcase_add_test(tc, test_s21_sprintf_c_edge);
    tcase_add_test(tc, test_s21_sprintf_d_normal);
    tcase_add_test(tc, test_s21_sprintf_d_negative);
    tcase_add_test(tc, test_s21_sprintf_d_zero);
    tcase_add_test(tc, test_s21_sprintf_f_normal);
    tcase_add_test(tc, test_s21_sprintf_f_negative);
    tcase_add_test(tc, test_s21_sprintf_f_zero);
    tcase_add_test(tc, test_s21_sprintf_s_normal);
    tcase_add_test(tc, test_s21_sprintf_s_empty);
    tcase_add_test(tc, test_s21_sprintf_u_normal);
    tcase_add_test(tc, test_s21_sprintf_u_zero);
    tcase_add_test(tc, test_s21_sprintf_percent_normal);
    tcase_add_test(tc, test_s21_sprintf_flags_width_precision);
    tcase_add_test(tc, test_s21_sprintf_flags_negative);
    tcase_add_test(tc, test_s21_sprintf_width_only);
    tcase_add_test(tc, test_s21_sprintf_precision_only);
    tcase_add_test(tc, test_s21_sprintf_length_short);
    tcase_add_test(tc, test_s21_sprintf_length_long);
    tcase_add_test(tc, test_s21_sprintf_null);
    tcase_add_test(tc, test_s21_sscanf_d_normal);
    tcase_add_test(tc, test_s21_sscanf_d_negative);
    tcase_add_test(tc, test_s21_sscanf_d_zero);
    tcase_add_test(tc, test_s21_sscanf_f_normal);
    tcase_add_test(tc, test_s21_sscanf_f_negative);
    tcase_add_test(tc, test_s21_sscanf_s_normal);
    tcase_add_test(tc, test_s21_sscanf_s_empty);
    tcase_add_test(tc, test_s21_sscanf_width_precision);
    tcase_add_test(tc, test_s21_sscanf_null);
    tcase_add_test(tc, test_s21_sscanf_invalid_format);
    suite_add_tcase(s, tc);
    return s;
}