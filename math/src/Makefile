CC = gcc
ASAN_FLAGS = #-fsanitize=address
ASAN_FLAGS_G = #-g
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage 
CFLAGS = -std=c11 #-Wall -Werror -Wextra #-pedantic #-Wno-gnu-zero-variadic-macro-arguments
SRC_FILES_C = s21_*.c 
SRC_FILES_O = s21_*.o
TST_FILES_C = check_*.c
TST_FILES_O = check_*.o

OS=$(shell uname)
ifeq ($(OS), Linux)
  TST_LIBS=-lcheck -lpthread -lrt -lm -lsubunit
  OPEN=xdg-open
else
  TST_LIBS=-lcheck
  OPEN=open
endif

all: clean s21_math.a test gcov_report

s21_math.a:
	$(CC) -c $(CFLAGS) $(SRC_FILES_C) 
	ar rc s21_math.a $(SRC_FILES_O)
	ranlib s21_math.a

test: s21_math.a
	$(CC) -c $(CFLAGS) $(TST_FILES_C)
	ar rc suite_cases.a $(TST_FILES_O)
	ranlib suite_cases.a
	$(CC) $(ASAN_FLAGS_G) $(ASAN_FLAGS) $(CFLAGS) $(PROFILE_FLAGS) -o check_s21_math_tests s21_math.a suite_cases.a $(SRC_FILES_C) $(TST_LIBS)
	./check_s21_math_tests

gcov_report: test
	gcov s21_*.gcda	
	gcovr -b 
	gcovr
	gcovr --html-details -o report.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt *.dSYM *.h.gch
	-rm -f check_s21_math_tests
	-rm -f report

check:
	cppcheck —enable=all —suppress=missingIncludeSystem ../src/
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
