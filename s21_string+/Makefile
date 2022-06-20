CC = gcc

ASAN_FLAGS:= #-fsanitize=address 
CFLAGS =  -c -g -Wall -Wextra -Werror -std=c11 -pedantic
PROFILE_FLAGS?= -fprofile-arcs -ftest-coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  TST_LIBS=-lcheck -lpthread -lrt -lm -lsubunit
  OPEN=xdg-open
else
  TST_LIBS=-lcheck
  OPEN=open
endif


SRC_FILES_C = s21_string.c s21_sprintf.c
SRC_FILES_O = s21_string.o s21_sprintf.o 
TST_FILES_C = check_s21_string.c
TST_FILES_O = check_s21_string.c
GCOV = gcovr 
GCONV_FLAGS = -r . --html --html-details 


all: test s21_string.a gcov_report.html

$(SRC_FILES_O): $(SRC_FILES_C) s21_string.h
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SRC_FILES_C)  

check_s21_string.o: $(TST_FILES_C)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(TST_FILES_C)

s21_string.a: $(SRC_FILES_O)
	ar -rc s21_string.a $(SRC_FILES_O)
	ranlib s21_string.a

check_s21_string_tests: s21_string.a $(TST_FILES_O)
	$(CC) $(TST_FILES_O) s21_string.a $(TST_LIBS) $(PROFILE_FLAGS) $(ASAN_FLAGS) -o check_s21_string_tests

test: check_s21_string_tests
	./check_s21_string_tests

gcov_report.html: test
	$(GCOV) $(GCONV_FLAGS) -o gcov_report.html

clean:
	-rm *.o *.html *.css *.a *.gcda *.gcno check_s21_string_tests

re:
	make clean
	make all

