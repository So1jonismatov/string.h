#include <check.h>
#include <float.h>
#include <stdio.h>

#include "../io/s21_sprintf.h"
#include "../io/s21_sscanf.h"
#include "../s21_string.h"

START_TEST(test_s21_sprintf_c_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%c", 'A');
  int ret2 = sprintf(buf2, "%c", 'A');
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_c_edge) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%c", '\0');  // Null character
  int ret2 = sprintf(buf2, "%c", '\0');
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_d_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%d", 123);
  int ret2 = sprintf(buf2, "%d", 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_d_negative) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%d", -456);
  int ret2 = sprintf(buf2, "%d", -456);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_d_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%d", 0);
  int ret2 = sprintf(buf2, "%d", 0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_f_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2f", 3.14159);
  int ret2 = sprintf(buf2, "%.2f", 3.14159);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_f_negative) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2f", -3.14159);
  int ret2 = sprintf(buf2, "%.2f", -3.14159);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_f_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2f", 0.0);
  int ret2 = sprintf(buf2, "%.2f", 0.0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_s_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%s", "hello");
  int ret2 = sprintf(buf2, "%s", "hello");
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_s_empty) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%s", "");
  int ret2 = sprintf(buf2, "%s", "");
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_u_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%u", 123);
  int ret2 = sprintf(buf2, "%u", 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_u_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%u", 0);
  int ret2 = sprintf(buf2, "%u", 0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_percent_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%%");
  int ret2 = sprintf(buf2, "%%");
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_flags_width_precision) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%+10.3d", 123);
  int ret2 = sprintf(buf2, "%+10.3d", 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_flags_negative) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%-10.3d", -123);
  int ret2 = sprintf(buf2, "%-10.3d", -123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_width_only) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%10d", 123);
  int ret2 = sprintf(buf2, "%10d", 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_precision_only) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.3f", 3.14159);
  int ret2 = sprintf(buf2, "%.3f", 3.14159);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_length_short) {
  short s = 123;
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%hd", s);
  int ret2 = sprintf(buf2, "%hd", s);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_length_long) {
  long l = 123456L;
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%ld", l);
  int ret2 = sprintf(buf2, "%ld", l);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

// Append these to the end of test_s21_io.c before the Suite definition

START_TEST(test_s21_sprintf_o_zero_hash) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%#o", 0);
  int ret2 = sprintf(buf2, "%#o", 0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "0"
}
END_TEST

START_TEST(test_s21_sprintf_x_hash) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%#x", 0x1a3);
  int ret2 = sprintf(buf2, "%#x", 0x1a3);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "0x1a3"
}
END_TEST

START_TEST(test_s21_sprintf_X_hash) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%#X", 0x1a3);
  int ret2 = sprintf(buf2, "%#X", 0x1a3);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "0X1A3"
}
END_TEST

START_TEST(test_s21_sprintf_p_normal) {
  int x = 42;
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%p", (void *)&x);
  int ret2 = sprintf(buf2, "%p", (void *)&x);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Approximate match due to address
}
END_TEST

START_TEST(test_s21_sprintf_n_normal) {
  char buf1[20], buf2[20] = {0};
  int count1, count2;
  s21_sprintf(buf1, "%d%n", 123, &count1);
  sprintf(buf2, "%d%n", 123, &count2);
  ck_assert_int_eq(count1, count2);
  ck_assert_int_eq(s21_strlen(buf1), count1);
}
END_TEST

START_TEST(test_s21_sprintf_e_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2e", 1234.56);
  int ret2 = sprintf(buf2, "%.2e", 1234.56);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1.23e+03"
}
END_TEST

START_TEST(test_s21_sprintf_E_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2E", 1234.56);
  int ret2 = sprintf(buf2, "%.2E", 1234.56);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1.23E+03"
}
END_TEST

START_TEST(test_s21_sprintf_g_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2g", 1234.56);
  int ret2 = sprintf(buf2, "%.2g", 1234.56);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1.2e+03"
}
END_TEST

START_TEST(test_s21_sprintf_G_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2G", 1234.56);
  int ret2 = sprintf(buf2, "%.2G", 1234.56);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1.2E+03"
}
END_TEST

START_TEST(test_s21_sprintf_space_flag) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "% d", 123);
  int ret2 = sprintf(buf2, "% d", 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should prepend space
}
END_TEST

START_TEST(test_s21_sprintf_hash_f) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%#.0f", 3.14);
  int ret2 = sprintf(buf2, "%#.0f", 3.14);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should include decimal point
}
END_TEST

START_TEST(test_s21_sprintf_zero_pad) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%05d", 123);
  int ret2 = sprintf(buf2, "%05d", 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should pad with zeros
}
END_TEST

START_TEST(test_s21_sprintf_precision_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.0d", 0);
  int ret2 = sprintf(buf2, "%.0d", 0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be empty string
}
END_TEST

START_TEST(test_s21_sprintf_width_star) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%*d", 5, 123);
  int ret2 = sprintf(buf2, "%*d", 5, 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should pad to 5 width
}
END_TEST

START_TEST(test_s21_sprintf_precision_star) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.*f", 2, 3.14159);
  int ret2 = sprintf(buf2, "%.*f", 2, 3.14159);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should limit to 2 decimals
}
END_TEST

START_TEST(test_s21_sprintf_g_small_number) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2g", 1e-5);
  int ret2 = sprintf(buf2, "%.2g", 1e-5);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1,
                   buf2);  // Should trigger exponential form (e.g., "1e-05")
}
END_TEST

START_TEST(test_s21_sprintf_e_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2e", 0.0);
  int ret2 = sprintf(buf2, "%.2e", 0.0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "0.00e+00"
}
END_TEST

START_TEST(test_s21_sprintf_e_small_number) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2e", 0.00123);
  int ret2 = sprintf(buf2, "%.2e", 0.00123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should adjust num < 1.0 (e.g., "1.23e-03")
}
END_TEST

START_TEST(test_s21_sprintf_width_negative_star) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%*d", -5, 123);
  int ret2 = sprintf(buf2, "%*d", -5, 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should apply minus flag and width 5
}
END_TEST

START_TEST(test_s21_sprintf_precision_negative_star) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.*f", -1, 3.14159);
  int ret2 = sprintf(buf2, "%.*f", -1, 3.14159);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should use default precision (6)
}
END_TEST

START_TEST(test_s21_sprintf_u_precision_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.0u", 0);
  int ret2 = sprintf(buf2, "%.0u", 0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be empty
}
END_TEST

START_TEST(test_s21_sprintf_o_precision_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.0o", 0);
  int ret2 = sprintf(buf2, "%.0o", 0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be empty
}
END_TEST

START_TEST(test_s21_sprintf_x_precision_zero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.0x", 0);
  int ret2 = sprintf(buf2, "%.0x", 0);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be empty
}
END_TEST

START_TEST(test_s21_sprintf_precision_padding) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.5d", 123);
  int ret2 = sprintf(buf2, "%.5d", 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should pad with zeros (e.g., "00123")
}
END_TEST

START_TEST(test_s21_sprintf_o_hash_nonzero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%#o", 0123);
  int ret2 = sprintf(buf2, "%#o", 0123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should prepend "0" (e.g., "0123")
}
END_TEST

START_TEST(test_s21_sprintf_x_hash_nonzero) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%#x", 0x1a3);
  int ret2 = sprintf(buf2, "%#x", 0x1a3);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should prepend "0x" (e.g., "0x1a3")
}
END_TEST

START_TEST(test_s21_sprintf_f_space_flag) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "% f", 3.14);
  int ret2 = sprintf(buf2, "% f", 3.14);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should prepend space
}
END_TEST

START_TEST(test_s21_sprintf_f_plus_flag) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%+f", 3.14);
  int ret2 = sprintf(buf2, "%+f", 3.14);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should prepend "+"
}
END_TEST

START_TEST(test_s21_sprintf_zero_pad_f) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%010.2f", 3.14);
  int ret2 = sprintf(buf2, "%010.2f", 3.14);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should pad with zeros (e.g., "0000003.14")
}
END_TEST

// sscanf tests
START_TEST(test_s21_sscanf_d_normal) {
  int num1, num2;
  const char *str = "123";
  int ret1 = s21_sscanf(str, "%d", &num1);
  int ret2 = sscanf(str, "%d", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(test_s21_sscanf_d_negative) {
  int num1, num2;
  const char *str = "-456";
  int ret1 = s21_sscanf(str, "%d", &num1);
  int ret2 = sscanf(str, "%d", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(test_s21_sscanf_d_zero) {
  int num1, num2;
  const char *str = "0";
  int ret1 = s21_sscanf(str, "%d", &num1);
  int ret2 = sscanf(str, "%d", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);
}
END_TEST

START_TEST(test_s21_sscanf_f_normal) {
  double num1, num2;
  const char *str = "3.14159";
  int ret1 = s21_sscanf(str, "%lf", &num1);
  int ret2 = sscanf(str, "%lf", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_double_eq(num1, num2);
}
END_TEST

START_TEST(test_s21_sscanf_f_negative) {
  double num1, num2;
  const char *str = "-3.14159";
  int ret1 = s21_sscanf(str, "%lf", &num1);
  int ret2 = sscanf(str, "%lf", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_double_eq(num1, num2);
}
END_TEST

START_TEST(test_s21_sscanf_s_normal) {
  char buf1[20], buf2[20] = {0};
  const char *str = "hello world";
  int ret1 = s21_sscanf(str, "%s", buf1);
  int ret2 = sscanf(str, "%s", buf2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sscanf_s_empty) {
  char buf1[20], buf2[20] = {0};
  const char *str = "";
  int ret1 = s21_sscanf(str, "%s", buf1);
  int ret2 = sscanf(str, "%s", buf2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sscanf_width_precision) {
  int num1, num2;
  const char *str = "123456";
  int ret1 = s21_sscanf(str, "%3d", &num1);
  int ret2 = sscanf(str, "%3d", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 123, not 123456
}
END_TEST

START_TEST(test_s21_sscanf_invalid_format) {
  int num;
  const char *str = "123abc";
  int ret1 = s21_sscanf(str, "%d", &num);  // Should parse only "123"
  int ret2 = sscanf(str, "%d", &num);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num, 123);
}
END_TEST

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
  tcase_add_test(tc, test_s21_sprintf_o_zero_hash);
  tcase_add_test(tc, test_s21_sprintf_x_hash);
  tcase_add_test(tc, test_s21_sprintf_X_hash);
  tcase_add_test(tc, test_s21_sprintf_p_normal);
  tcase_add_test(tc, test_s21_sprintf_n_normal);
  tcase_add_test(tc, test_s21_sprintf_e_normal);
  tcase_add_test(tc, test_s21_sprintf_E_normal);
  tcase_add_test(tc, test_s21_sprintf_g_normal);
  tcase_add_test(tc, test_s21_sprintf_G_normal);
  tcase_add_test(tc, test_s21_sprintf_space_flag);
  tcase_add_test(tc, test_s21_sprintf_hash_f);
  tcase_add_test(tc, test_s21_sprintf_zero_pad);
  tcase_add_test(tc, test_s21_sprintf_precision_zero);
  tcase_add_test(tc, test_s21_sprintf_width_star);
  tcase_add_test(tc, test_s21_sprintf_precision_star);
  tcase_add_test(tc, test_s21_sprintf_g_small_number);
  tcase_add_test(tc, test_s21_sprintf_e_zero);
  tcase_add_test(tc, test_s21_sprintf_e_small_number);
  tcase_add_test(tc, test_s21_sprintf_width_negative_star);
  tcase_add_test(tc, test_s21_sprintf_precision_negative_star);
  tcase_add_test(tc, test_s21_sprintf_u_precision_zero);
  tcase_add_test(tc, test_s21_sprintf_o_precision_zero);
  tcase_add_test(tc, test_s21_sprintf_x_precision_zero);
  tcase_add_test(tc, test_s21_sprintf_precision_padding);
  tcase_add_test(tc, test_s21_sprintf_o_hash_nonzero);
  tcase_add_test(tc, test_s21_sprintf_x_hash_nonzero);
  tcase_add_test(tc, test_s21_sprintf_f_space_flag);
  tcase_add_test(tc, test_s21_sprintf_f_plus_flag);
  tcase_add_test(tc, test_s21_sprintf_zero_pad_f);
  tcase_add_test(tc, test_s21_sscanf_d_normal);
  tcase_add_test(tc, test_s21_sscanf_d_negative);
  tcase_add_test(tc, test_s21_sscanf_d_zero);
  tcase_add_test(tc, test_s21_sscanf_f_normal);
  tcase_add_test(tc, test_s21_sscanf_f_negative);
  tcase_add_test(tc, test_s21_sscanf_s_normal);
  tcase_add_test(tc, test_s21_sscanf_s_empty);
  tcase_add_test(tc, test_s21_sscanf_width_precision);
  tcase_add_test(tc, test_s21_sscanf_invalid_format);
  suite_add_tcase(s, tc);
  return s;
}
