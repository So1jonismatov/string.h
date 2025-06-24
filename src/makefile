# Compiler and linker flags
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
COV_CFLAGS = -fprofile-arcs -ftest-coverage -lgcov
LDFLAGS = -lcheck -lm -lsubunit -lcheck_pic -pthread -lrt -lgcov

# Source and object files
SOURCES = s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_strlen.c s21_strcpy.c \
          s21_strncat.c s21_strncmp.c s21_strchr.c s21_strncpy.c s21_strcspn.c \
          s21_strpbrk.c s21_strrchr.c s21_strspn.c s21_strstr.c s21_strtok.c \
          io/s21_sprintf.c io/s21_sscanf.c s21_utils.c \
          specials/s21_insert.c specials/s21_to_lower.c specials/s21_to_upper.c specials/s21_trim.c
OBJECTS = $(SOURCES:.c=.o)

TEST_SOURCES = tests/test_s21_io.c tests/test_s21_memchr.c tests/test_s21_memcmp.c \
               tests/test_s21_memcpy.c tests/test_s21_memset.c tests/test_s21_specials.c \
               tests/test_s21_strchr.c tests/test_s21_strcspn.c tests/test_s21_strlen.c \
               tests/test_s21_strncat.c tests/test_s21_strncmp.c tests/test_s21_strncpy.c \
               tests/test_s21_strpbrk.c tests/test_s21_strrchr.c tests/test_s21_strspn.c \
               tests/test_s21_strstr.c tests/test_s21_strtok.c tests/tests.c
TEST_OBJS = $(TEST_SOURCES:.c=.o)

all: s21_string.a test

s21_string.a: $(OBJECTS)
	ar rcs s21_string.a $(OBJECTS)

test: s21_string.a $(TEST_OBJS)
	gcc $(CFLAGS) $(COV_CFLAGS) -o test_runner $(TEST_OBJS) s21_string.a $(LDFLAGS)
	./test_runner

gcov_report:
	gcc $(CFLAGS) $(COV_CFLAGS) -o test_runner $(SOURCES) $(TEST_SOURCES) $(LDFLAGS)
	./test_runner
	mkdir -p gcov_report
	lcov --capture --directory . --output-file gcov_report/coverage.info
	lcov --remove gcov_report/coverage.info 'tests/*' --output-file gcov_report/coverage.info
	genhtml gcov_report/coverage.info --output-directory gcov_report

clean:
	rm -rf $(OBJECTS) $(TEST_OBJS) s21_string.a test_runner *.gcno *.gcda *.gcov */*.gcno */*.gcda */*.gcov *.o */*.o
	rm -rf gcov_report

format:
	clang-format -i *.c */*.c
	clang-format -n *.c */*.c

.PHONY: all test gcov_report clean format
