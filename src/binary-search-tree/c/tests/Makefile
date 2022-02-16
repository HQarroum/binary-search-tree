CXX = g++

APP = launch_tests

SRC = main.cpp \
	unit_test_insertion_int.cpp \
	unit_test_insertion_string.cpp \
	unit_test_initialization.cpp \
	unit_test_search.cpp \
	unit_test_iteration.cpp \
	unit_test_deletion.cpp

CXXFLAGS = -std=c++11 -W -Wall -fprofile-arcs -ftest-coverage

LDFLAGS = -lgtest -lpthread -lgcov -L../ -lbst

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CXX) $(CXXFLAGS) -o $@ -c $<

all: $(OBJ)
	$(CXX) -o $(APP) $^ $(CXXFLAGS) $(LDFLAGS)

coverage: $(OBJ)
	$(CXX) -o $(APP) $^ $(CXXFLAGS) $(LDFLAGS) --coverage
	gcov $(OBJ)

coverage_html:
	lcov --capture --directory .. --output-file coverage.info
	lcov --remove coverage.info "/usr*" "*tests*" --output-file coverage.info
	genhtml coverage.info --output-directory CODE_COVERAGE

re: fclean all

clean:
	$(shell find . -name '*~' -exec rm -r {} \; -o -name '*.o' -exec rm -r {} \;)

fclean: clean
	rm -f $(APP)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.info
	rm -f *.gcov
	rm -rf CODE_COVERAGE

.PHONY: clean fclean re
