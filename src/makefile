# Simple Makefile for s21_string.a and tests

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I. -I./io
LIBS = -lcheck
TARGET = s21_string.a
TESTS_DIR = tests
TEST_EXEC = test_runner

# Source files for the library (including io/ for sprintf)
SRC = s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memset.c \
      s21_strlen.c s21_strncat.c s21_strncmp.c s21_strchr.c \
      s21_strncpy.c s21_strcspn.c s21_strpbrk.c s21_strrchr.c \
      s21_strspn.c s21_strstr.c s21_strtok.c s21_strerror.c \
      io/s21_sprintf.c

# Object files
OBJ = $(SRC:.c=.o)

# Test files
TEST_SRC = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Targets
all: $(TARGET)

$(TARGET): $(OBJ)
	@ar rcs $(TARGET) $(OBJ)
	@echo "Library s21_string.a created!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_EXEC)
	@echo "Cleaned up!"

test: $(TARGET) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJ) $(TARGET) $(LIBS)
	@./$(TEST_EXEC)
	@echo "Tests run!"

.PHONY: all clean test