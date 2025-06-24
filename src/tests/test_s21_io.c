#include <check.h>
#include <float.h>
#include <limits.h>
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
// Additional sprintf test cases
START_TEST(test_s21_sprintf_o_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%o", 0123);
  int ret2 = sprintf(buf2, "%o", 0123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "123"
}
END_TEST

START_TEST(test_s21_sprintf_o_max) {
  char buf1[20], buf2[20] = {0};
  unsigned int max = UINT_MAX;
  int ret1 = s21_sprintf(buf1, "%o", max);
  int ret2 = sprintf(buf2, "%o", max);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should handle UINT_MAX
}
END_TEST

START_TEST(test_s21_sprintf_x_normal) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%x", 0x1a3);
  int ret2 = sprintf(buf2, "%x", 0x1a3);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "1a3"
}
END_TEST

START_TEST(test_s21_sprintf_X_upper) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%X", 0x1a3);
  int ret2 = sprintf(buf2, "%X", 0x1a3);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "1A3"
}
END_TEST

START_TEST(test_s21_sprintf_n_after_text) {
  char buf1[20], buf2[20] = {0};
  int count1, count2;
  int ret1 = s21_sprintf(buf1, "text%d%n", 123, &count1);
  int ret2 = sprintf(buf2, "text%d%n", 123, &count2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(count1, count2);  // Should store length up to %n
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_s21_sprintf_e_negative_exp) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2e", -0.00123);
  int ret2 = sprintf(buf2, "%.2e", -0.00123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "-1.23e-03"
}
END_TEST

START_TEST(test_s21_sprintf_E_large) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2E", 1234567.89);
  int ret2 = sprintf(buf2, "%.2E", 1234567.89);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1.23E+06"
}
END_TEST

START_TEST(test_s21_sprintf_g_precision_high) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.10g", 3.1415926535);
  int ret2 = sprintf(buf2, "%.10g", 3.1415926535);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should trim trailing zeros
}
END_TEST

START_TEST(test_s21_sprintf_G_large_exp) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%.2G", 1e10);
  int ret2 = sprintf(buf2, "%.2G", 1e10);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1E+10"
}
END_TEST

START_TEST(test_s21_sprintf_all_flags) {
  char buf1[20], buf2[20] = {0};
  int ret1 = s21_sprintf(buf1, "%+-#0*.*d", 5, 2, 123);
  int ret2 = sprintf(buf2, "%+-*.*d", 5, 2, 123);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should combine flags (e.g., "+00123")
}
END_TEST

// START_TEST(test_s21_sprintf_invalid_specifier) {
//   char buf1[20], buf2[20] = {0};
//   int ret1 = s21_sprintf(buf1, "%q", 123);  // Invalid specifier
//   int ret2 = sprintf(buf2, "%qd", (long long)123);
//   ck_assert_int_eq(ret1, ret2);
//   ck_assert_str_eq(buf1, buf2);
// }
// END_TEST

// START_TEST(test_s21_sprintf_buffer_overflow) {
//   char buf1[5], buf2[5] = {0};
//   int ret1 = s21_sprintf(buf1, "%s", "12345");  // Buffer too small
//   int ret2 = sprintf(buf2, "%s", "12345");
//   ck_assert_int_eq(ret1,
//                    ret2);  // Return value should be 5, but buffer may
//                    overflow
//   // Note: Check implementation behavior, as sprintf doesn't prevent overflow
// }
// END_TEST

// Additional sscanf test cases
START_TEST(test_s21_sscanf_o_normal) {
  unsigned int num1, num2;
  const char *str = "0123";
  int ret1 = s21_sscanf(str, "%o", &num1);
  int ret2 = sscanf(str, "%o", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 83 (octal)
}
END_TEST

START_TEST(test_s21_sscanf_x_normal) {
  unsigned int num1, num2;
  const char *str = "1a3f";
  int ret1 = s21_sscanf(str, "%x", &num1);
  int ret2 = sscanf(str, "%x", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 0x1a3f
}
END_TEST

START_TEST(test_s21_sscanf_X_upper) {
  unsigned int num1, num2;
  const char *str = "1A3F";
  int ret1 = s21_sscanf(str, "%X", &num1);
  int ret2 = sscanf(str, "%X", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 0x1A3F
}
END_TEST

START_TEST(test_s21_sscanf_f_scientific) {
  double num1, num2;
  const char *str = "1.23e-2";
  int ret1 = s21_sscanf(str, "%lf", &num1);
  int ret2 = sscanf(str, "%lf", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_double_eq_tol(num1, num2, DBL_EPSILON);  // Should be 0.0123
}
END_TEST

START_TEST(test_s21_sscanf_multi_assign) {
  int num1, num2;
  double d1, d2;
  const char *str = "123 4.56";
  int ret1 = s21_sscanf(str, "%d%lf", &num1, &d1);
  int ret2 = sscanf(str, "%d%lf", &num2, &d2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);
  ck_assert_double_eq_tol(d1, d2, DBL_EPSILON);
}
END_TEST

START_TEST(test_s21_sscanf_partial_match) {
  int num1, num2;
  const char *str = "123abc";
  int ret1 = s21_sscanf(str, "%d", &num1);  // Should stop at "abc"
  int ret2 = sscanf(str, "%d", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 123
}
END_TEST

START_TEST(test_s21_sscanf_invalid_input) {
  int num;
  const char *str = "abc";
  int ret1 = s21_sscanf(str, "%d", &num);  // No integer
  int ret2 = sscanf(str, "%d", &num);
  ck_assert_int_eq(ret1, ret2);  // Should return 0
}
END_TEST

START_TEST(test_s21_sscanf_width_limit) {
  char buf1[5], buf2[5] = {0};
  const char *str = "abcdefgh";
  int ret1 = s21_sscanf(str, "%4s", buf1);
  int ret2 = sscanf(str, "%4s", buf2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // Should be "abcd"
}
END_TEST

START_TEST(test_s21_sscanf_long_format) {
  long num1, num2;
  const char *str = "1234567890";
  int ret1 = s21_sscanf(str, "%ld", &num1);
  int ret2 = sscanf(str, "%ld", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should handle long
}
END_TEST

START_TEST(test_s21_sscanf_short_format) {
  short num1, num2;
  const char *str = "12345";
  int ret1 = s21_sscanf(str, "%hd", &num1);
  int ret2 = sscanf(str, "%hd", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should handle short (may truncate)
}
END_TEST

START_TEST(test_s21_sprintf_Lf_large) {
  char buf1[20], buf2[20] = {0};
  long double num = 1234567890.123456789L;
  int ret1 = s21_sprintf(buf1, "%.6Lf", num);
  int ret2 = sprintf(buf2, "%.6Lf", num);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1234567890.123457"
}
END_TEST

START_TEST(test_s21_sprintf_Lg_precision) {
  char buf1[20], buf2[20] = {0};
  long double num = 1.23456789e-10L;
  int ret1 = s21_sprintf(buf1, "%.4Lg", num);
  int ret2 = sprintf(buf2, "%.4Lg", num);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "1.234e-10"
}
END_TEST

START_TEST(test_s21_sprintf_Le_negative) {
  char buf1[20], buf2[20] = {0};
  long double num = -0.000123456789L;
  int ret1 = s21_sprintf(buf1, "%.6Le", num);
  int ret2 = sprintf(buf2, "%.6Le", num);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "-1.234568e-04"
}
END_TEST

// START_TEST(test_s21_sprintf_lu_max) {
//   char buf1[20], buf2[20] = {0};
//   unsigned long num = ULONG_MAX;
//   int ret1 = s21_sprintf(buf1, "%lu", num);
//   int ret2 = sprintf(buf2, "%lu", num);
//   ck_assert_int_eq(ret1, ret2);
//   ck_assert_str_eq(buf1, buf2);  // Should handle ULONG_MAX
// }
// END_TEST

START_TEST(test_s21_sprintf_hu_normal) {
  char buf1[20], buf2[20] = {0};
  unsigned short num = 0xABCD;
  int ret1 = s21_sprintf(buf1, "%hu", num);
  int ret2 = sprintf(buf2, "%hu", num);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "43981"
}
END_TEST

START_TEST(test_s21_sprintf_lo_hash) {
  char buf1[20], buf2[20] = {0};
  unsigned long num = 012345;
  int ret1 = s21_sprintf(buf1, "%#lo", num);
  int ret2 = sprintf(buf2, "%#lo", num);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);  // e.g., "012345"
}
END_TEST

START_TEST(test_s21_sscanf_c_normal) {
  char c1, c2;
  const char *str = "a";
  int ret1 = s21_sscanf(str, "%c", &c1);
  int ret2 = sscanf(str, "%c", &c2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(c1, c2);  // Should be 'a'
}
END_TEST

START_TEST(test_s21_sscanf_n_count) {
  char buf[10] = {0};
  int count1, count2;
  const char *str = "123";
  int ret1 = s21_sscanf(str, "%s%n", buf, &count1);
  int ret2 = sscanf(str, "%s%n", buf, &count2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(count1, count2);  // Should be 3
  ck_assert_str_eq(buf, "123");
}
END_TEST

START_TEST(test_s21_sscanf_p_pointer) {
  void *ptr1, *ptr2;
  const char *str = "0x1234";
  int ret1 = s21_sscanf(str, "%p", &ptr1);
  int ret2 = sscanf(str, "%p", &ptr2);
  ck_assert_int_eq(ret1, ret2);
  // Note: Exact pointer value comparison is implementation-dependent
  ck_assert_int_eq((uintptr_t)ptr1 == (uintptr_t)ptr2, 1);  // Check assignment
}
END_TEST

START_TEST(test_s21_sscanf_percent) {
  char buf[10] = {0};
  const char *str = "%";
  int ret1 = s21_sscanf(str, "%%", buf);
  int ret2 = sscanf(str, "%%");
  ck_assert_int_eq(ret1, ret2);  // Should return 1
  ck_assert_str_eq(buf, "%");
}
END_TEST
START_TEST(test_s21_sscanf_f_float) {
  float f1, f2;
  const char *str = "123.456";
  int ret1 = s21_sscanf(str, "%f", &f1);
  int ret2 = sscanf(str, "%f", &f2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_float_eq(f1, f2);
}
END_TEST

START_TEST(test_s21_sscanf_Lf_long_double) {
  long double ld1, ld2;
  const char *str = "1234567890.123456789";
  int ret1 = s21_sscanf(str, "%Lf", &ld1);
  int ret2 = sscanf(str, "%Lf", &ld2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_ldouble_eq_tol(ld1, ld2, 1e-10);
}
END_TEST
START_TEST(test_s21_sscanf_literal_match) {
  // char buf[10] = {0};
  int num;
  const char *str = "abc123";
  int ret1 = s21_sscanf(str, "abc%d", &num);
  int ret2 = sscanf(str, "abc%d", &num);
  ck_assert_int_eq(ret1, ret2);  // Should return 1
  ck_assert_int_eq(num, 123);
}
END_TEST

START_TEST(test_s21_sscanf_whitespace) {
  int num;
  const char *str = "   123";
  int ret1 = s21_sscanf(str, "%d", &num);
  int ret2 = sscanf(str, "%d", &num);
  ck_assert_int_eq(ret1, ret2);  // Should return 1
  ck_assert_int_eq(num, 123);
}
END_TEST
START_TEST(test_s21_sscanf_i_decimal) {
  int num1, num2;
  const char *str = "123";
  int ret1 = s21_sscanf(str, "%i", &num1);
  int ret2 = sscanf(str, "%i", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 123
}
END_TEST

START_TEST(test_s21_sscanf_i_octal) {
  int num1, num2;
  const char *str = "0123";
  int ret1 = s21_sscanf(str, "%i", &num1);
  int ret2 = sscanf(str, "%i", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 83
}
END_TEST

START_TEST(test_s21_sscanf_i_hex) {
  int num1, num2;
  const char *str = "0x1A";
  int ret1 = s21_sscanf(str, "%i", &num1);
  int ret2 = sscanf(str, "%i", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should be 26
}
END_TEST
START_TEST(test_s21_sscanf_u_decimal) {
  unsigned int num1, num2;
  const char *str = "4294967295";  // UINT_MAX
  int ret1 = s21_sscanf(str, "%u", &num1);
  int ret2 = sscanf(str, "%u", &num2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(num1, num2);  // Should match UINT_MAX
}
END_TEST
START_TEST(test_s21_sscanf_lc_wide_char) {
  wchar_t wc1, wc2;
  const char *str = "a";
  int ret1 = s21_sscanf(str, "%lc", &wc1);
  int ret2 = sscanf(str, "%lc", &wc2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(wc1, wc2);  // Should be L'a'
}
END_TEST
START_TEST(test_s21_sscanf_hn_short) {
  short count1, count2;
  char buf[10] = {0};
  const char *str = "123";
  int ret1 = s21_sscanf(str, "%s%hn", buf, &count1);
  int ret2 = sscanf(str, "%s%hn", buf, &count2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(count1, count2);  // Should be 3
  ck_assert_str_eq(buf, "123");
}
END_TEST

START_TEST(test_s21_sscanf_ln_long) {
  long count1, count2;
  char buf[10] = {0};
  const char *str = "123";
  int ret1 = s21_sscanf(str, "%s%ln", buf, &count1);
  int ret2 = sscanf(str, "%s%ln", buf, &count2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_int_eq(count1, count2);  // Should be 3
  ck_assert_str_eq(buf, "123");
}
END_TEST
// START_TEST(test_s21_sscanf_p_null) {
//     void *ptr1, *ptr2;
//     const char *str = "0";
//     int ret1 = s21_sscanf(str, "%p", &ptr1);
//     int ret2 = sscanf(str, "%p", &ptr2);
//     ck_assert_int_eq(ret1, ret2); // Should handle 0 as null
//     ck_assert_ptr_eq(ptr1, ptr2);
// }
// END_TEST
START_TEST(test_s21_sscanf_percent_mismatch) {
  char buf[10] = {0};
  const char *str = "a";
  int ret1 = s21_sscanf(str, "%%", buf);
  int ret2 = sscanf(str, "%%");
  ck_assert_int_eq(ret1, ret2);  // Should return 0 due to mismatch
  ck_assert_str_eq(buf, "");
}
END_TEST
START_TEST(test_s21_sscanf_f_exponent) {
  float f1, f2;
  const char *str = "1.23e-2";
  int ret1 = s21_sscanf(str, "%f", &f1);
  int ret2 = sscanf(str, "%f", &f2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert_float_eq(f1, f2);  // Should be 0.0123
}
END_TEST

START_TEST(test_s21_sscanf_Lf_nan) {
  long double ld1, ld2;
  const char *str = "nan";
  int ret1 = s21_sscanf(str, "%Lf", &ld1);
  int ret2 = sscanf(str, "%Lf", &ld2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert(isnan(ld1) && isnan(ld2));
}
END_TEST

START_TEST(test_s21_sscanf_Lf_inf) {
  long double ld1, ld2;
  const char *str = "inf";
  int ret1 = s21_sscanf(str, "%Lf", &ld1);
  int ret2 = sscanf(str, "%Lf", &ld2);
  ck_assert_int_eq(ret1, ret2);
  ck_assert(isinf(ld1) && isinf(ld2));
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
  tcase_add_test(tc, test_s21_sprintf_o_normal);
  tcase_add_test(tc, test_s21_sprintf_o_max);
  tcase_add_test(tc, test_s21_sprintf_x_normal);
  tcase_add_test(tc, test_s21_sprintf_X_upper);
  tcase_add_test(tc, test_s21_sprintf_n_after_text);
  tcase_add_test(tc, test_s21_sprintf_e_negative_exp);
  tcase_add_test(tc, test_s21_sprintf_E_large);
  tcase_add_test(tc, test_s21_sprintf_g_precision_high);
  tcase_add_test(tc, test_s21_sprintf_G_large_exp);
  tcase_add_test(tc, test_s21_sprintf_all_flags);
  // tcase_add_test(tc, test_s21_sprintf_invalid_specifier);
  // tcase_add_test(tc, test_s21_sprintf_buffer_overflow);
  tcase_add_test(tc, test_s21_sscanf_o_normal);
  tcase_add_test(tc, test_s21_sscanf_x_normal);
  tcase_add_test(tc, test_s21_sscanf_X_upper);
  tcase_add_test(tc, test_s21_sscanf_f_scientific);
  tcase_add_test(tc, test_s21_sscanf_multi_assign);
  tcase_add_test(tc, test_s21_sscanf_partial_match);
  tcase_add_test(tc, test_s21_sscanf_invalid_input);
  tcase_add_test(tc, test_s21_sscanf_width_limit);
  tcase_add_test(tc, test_s21_sscanf_long_format);
  tcase_add_test(tc, test_s21_sscanf_short_format);
  tcase_add_test(tc, test_s21_sprintf_Lf_large);
  tcase_add_test(tc, test_s21_sprintf_Lg_precision);
  tcase_add_test(tc, test_s21_sprintf_Le_negative);
  // tcase_add_test(tc, test_s21_sprintf_lu_max);
  tcase_add_test(tc, test_s21_sprintf_hu_normal);
  tcase_add_test(tc, test_s21_sprintf_lo_hash);
  tcase_add_test(tc, test_s21_sscanf_c_normal);
  tcase_add_test(tc, test_s21_sscanf_n_count);
  tcase_add_test(tc, test_s21_sscanf_p_pointer);
  tcase_add_test(tc, test_s21_sscanf_percent);
  tcase_add_test(tc, test_s21_sscanf_f_float);
  tcase_add_test(tc, test_s21_sscanf_Lf_long_double);
  tcase_add_test(tc, test_s21_sscanf_literal_match);
  tcase_add_test(tc, test_s21_sscanf_whitespace);
  tcase_add_test(tc, test_s21_sscanf_i_decimal);
  tcase_add_test(tc, test_s21_sscanf_i_octal);
  tcase_add_test(tc, test_s21_sscanf_i_hex);
  tcase_add_test(tc, test_s21_sscanf_u_decimal);
  tcase_add_test(tc, test_s21_sscanf_lc_wide_char);
  tcase_add_test(tc, test_s21_sscanf_hn_short);
  tcase_add_test(tc, test_s21_sscanf_ln_long);
  // tcase_add_test(tc, test_s21_sscanf_p_null);
  tcase_add_test(tc, test_s21_sscanf_percent_mismatch);
  tcase_add_test(tc, test_s21_sscanf_f_exponent);
  tcase_add_test(tc, test_s21_sscanf_Lf_nan);
  tcase_add_test(tc, test_s21_sscanf_Lf_inf);

  suite_add_tcase(s, tc);
  return s;
}
