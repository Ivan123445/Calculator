CC = gcc
DELETE = rm -rf

VALGRIND_OUTPUT = valgrind.txt

#BUILD_FLAGS = -Wall -Wextra -std=c11 -pedantic -fanalyzer -rdynamic
BUILD_FLAGS = -rdynamic
GTK_FLAGS = `pkg-config gtk+-3.0 --cflags`
GTK_LIBS = `pkg-config gtk+-3.0 --libs`
VALGRIND_FLAGS = --log-file="$(VALGRIND_OUTPUT)" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
LIBS_FLAGS = -lcheck

SRC_C_FILES = utils/*.c calculate/*.c gui/*.c
#GUI_C_FILES = gui/*.glade
TEST_C_FILES = test/*.c

TEST_TARGET  = s21_test
EXECUTABLE = smart_calc

REPORT_DIR = report

INCLUDES = .

BUILD_DIR = ../build/

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS_FLAGS += -lsubunit -lm
endif

all: clean test build gcov_report dist

apply_clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.[ch] || true
	clang-format -i */*.[ch] || true
	rm -f .clang-format

test: apply_clang $(SRC_C_FILES)
	$(CC) $(BUILD_FLAGS) $(GTK_FLAGS) $(addprefix -I , $(INCLUDES)) utils/*.c calculate/*.c $(TEST_C_FILES) -o $(TEST_TARGET) $(LIBS_FLAGS)
	./$(TEST_TARGET)

build_test: apply_clang $(SRC_C_FILES)
	$(CC) $(BUILD_FLAGS) $(GTK_FLAGS) $(addprefix -I , $(INCLUDES)) utils/*.c calculate/*.c $(TEST_C_FILES) -o $(TEST_TARGET) $(LIBS_FLAGS)

build: apply_clang $(SRC_C_FILES)
	$(CC) $(BUILD_FLAGS) $(GTK_FLAGS) $(addprefix -I , $(INCLUDES)) $(GUI_C_FILES) $(SRC_C_FILES) -o $(EXECUTABLE) $(LIBS_FLAGS) $(GTK_LIBS)

run: build
	./$(EXECUTABLE)

gcov_report: apply_clang
	$(CC) --coverage $(BUILD_FLAGS) $(GTK_FLAGS) $(addprefix -I , $(INCLUDES)) utils/*.c calculate/*.c $(TEST_C_FILES) -o $(TEST_TARGET) $(LIBS_FLAGS)
	./$(TEST_TARGET)
	lcov -t "$(TEST_TARGET)" -o $(TEST_TARGET).info -c -d .
	genhtml -o report $(TEST_TARGET).info
	rm *.gcda *.gcno *.info
	open report/index.html

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

uninstall:
	$(DELETE) $(BUILD_DIR)

install: uninstall build
	mkdir $(BUILD_DIR)
	cp $(EXECUTABLE) $(BUILD_DIR)

clean:
	$(DELETE) $(TEST_TARGET)
	$(DELETE) $(EXECUTABLE)
	$(DELETE) $(REPORT_DIR)
	$(DELETE) *.info
	$(DELETE) *.o
	$(DELETE) *.gc*
	$(DELETE) $(VALGRIND_OUTPUT)
	$(DELETE) function.*
	$(DELETE) docs.aux
	$(DELETE) docs.log
	$(DELETE) docs.dvi
	$(DELETE) $(EXECUTABLE).tgz

valgrind: apply_clang build_test
	valgrind $(VALGRIND_FLAGS) ./$(TEST_TARGET)
	grep --color=always -n "ERROR SUMMARY" $(VALGRIND_OUTPUT) | grep -v "0 errors from 0 contexts" || true
	grep --color=always -n "definitely lost:" $(VALGRIND_OUTPUT) | grep -v "0 bytes in 0 blocks" || true

dvi:
	texi2dvi docs.tex
	open docs.dvi

dist: build
	tar -czvf $(EXECUTABLE).tgz $(EXECUTABLE)