#include "tests.h"
#include <stdio.h>

int main() {
  run_tests();

  return 0;
}

void run_tests() {
  Suite *tests_array[] = {
      s21_memchr_suite(),  s21_memcmp_suite(),   s21_memcpy_suite(),
      s21_memset_suite(),  s21_strlen_suite(),   s21_strncat_suite(),
      s21_strncmp_suite(), s21_strchr_suite(),   s21_strncpy_suite(),
      s21_strcspn_suite(), s21_strpbrk_suite(),  s21_strrchr_suite(),
      s21_strspn_suite(),  s21_strstr_suite(),   s21_strtok_suite(),
      s21_io_suite(),      s21_specials_suite(), NULL};
  for (Suite **current_test = tests_array; *current_test != NULL;
       current_test++) {
    run(*current_test);
  }
}

void run(Suite *test) {
  // int fail_count = 0;
  static int test_count = 1;

  if (test_count > 1) putchar('\n');
  printf("%s%d%s", "Current Test: ", test_count, "\n");

  test_count++;

  SRunner *sr = srunner_create(test);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}
