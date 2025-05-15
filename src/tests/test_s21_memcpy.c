#include <check.h>
#include "../s21_string.h"
#include <string.h>

START_TEST(test_s21_memcpy_normal){
    char array[] = "Hello";
    char *barray;
    s21_size_t n = 5;
    void * expected_result = memcpy(barray, array, n);
    void * result = s21_memcpy(barray, array, n);

    ck_assert_mem_eq(result, expected_result, n);
}END_TEST

