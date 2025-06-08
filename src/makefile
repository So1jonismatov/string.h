# Compiler flags
CFLAGS = -std=c11 -pedantic -I. -I./io -I./specials -D_POSIX_C_SOURCE=200809L -fprofile-arcs -ftest-coverage
LDFLAGS = -lcheck -lm -lsubunit

# Source and object files
SOURCES = s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c s21_strlen.c \
          s21_strncat.c s21_strncmp.c s21_strchr.c s21_strncpy.c s21_strcspn.c \
          s21_strpbrk.c s21_strrchr.c s21_strspn.c s21_strstr.c s21_strtok.c \
          s21_strerror.c io/s21_sprintf.c io/s21_sscanf.c s21_utils.c \
          specials/s21_insert.c specials/s21_to_lower.c specials/s21_to_upper.c specials/s21_trim.c
OBJECTS = $(SOURCES:.c=.o)

# Test files
TEST_SOURCES = tests/test_s21_io.c tests/test_s21_memchr.c tests/test_s21_memcmp.c \
               tests/test_s21_memcpy.c tests/test_s21_memset.c tests/test_s21_specials.c \
               tests/test_s21_strchr.c tests/test_s21_strcspn.c tests/test_s21_strlen.c \
               tests/test_s21_strncat.c tests/test_s21_strncmp.c tests/test_s21_strncpy.c \
               tests/test_s21_strpbrk.c tests/test_s21_strrchr.c tests/test_s21_strspn.c \
               tests/test_s21_strstr.c tests/test_s21_strtok.c tests/tests.c
TEST_OBJS = $(TEST_SOURCES:.c=.o)

# Default target: build the library
all: s21_string.a

# Build the library from object files
s21_string.a: $(OBJECTS)
	ar rcs s21_string.a $(OBJECTS)

# Build and run tests
test: s21_string.a $(TEST_OBJS)
	gcc $(CFLAGS) -o test_runner $(TEST_OBJS) s21_string.a $(LDFLAGS)
	./test_runner

# Generate coverage report
gcov_report: s21_string.a $(TEST_OBJS)
	gcc $(CFLAGS) -o test_runner $(TEST_OBJS) s21_string.a $(LDFLAGS)
	./test_runner
	gcov $(SOURCES) io/*.c specials/*.c
	mkdir -p gcov_report
	geninfo . --toolname lcov --output-filename gcov_report/coverage.info
	genhtml gcov_report/coverage.info --output-directory gcov_report

# Clean up generated files
clean:
	rm -rf $(OBJECTS) $(TEST_OBJS) s21_string.a test_runner *.gcno *.gcda *.gcov */*.gcno */*.gcda */*.gcov
	rm -rf gcov_report

# Declare targets as not representing files
.PHONY: all test gcov_report clean