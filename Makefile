CC=g++
CC_FLAGS= -g -Wall -Wextra -Werror -std=c++17
test_flags=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

ifeq ($(OS), Linux)
	test_libs= $(shell pkg-config --libs --cflags gtest) #-lgmock -pthread
	open=xdg-open
else
	test_libs=-lcheck
	open=open
endif

all: clean build #gcov_report

build:
	$(CC) -g $(CC_FLAGS) *.cpp -o test 

test:clean
	rm -f *.txt
	$(CC) $(CC_FLAGS) $(test_flags) *.cpp -o test $(test_libs)
	./test

gcov_report: test
	lcov --ignore-errors inconsistent --ignore-errors usage --ignore-errors path -t "test" -o s21_test.info -c -d .
	genhtml --ignore-errors missing --ignore-errors empty --output-directory report s21_test.info
	$(open) report/index.html

clean:
	find . -name '*.gcda' -o -name '*.gcno' -delete
	rm -f test
	rm -f *.o
	rm -f *.a
	rm -f */*.gcda
	rm -f */*.gcno
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -f log_*
	rm -rf report/

clang:
	clang-format -i -style=Google *.cpp *.h

valgrind:
	$(CC) $(CC_FLAGS) $(test_flags) *.cpp -o test $(test_libs)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./test
