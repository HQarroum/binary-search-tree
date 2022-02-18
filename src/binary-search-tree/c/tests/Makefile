CXX ?= g++

# Whether to enable coverage.
COVERAGE ?= false

# Name of the binary.
APP = launch_tests

# Source files.
SRC = $(wildcard ./*.cpp) $(wildcard ../*.c)

# Default flags.
CXXFLAGS = -std=c++11 -W -Wall -g3

# Conditionally enable coverage for the compiler.
ifeq ($(COVERAGE),true)
CFLAGS += -fprofile-arcs -ftest-coverage
endif

# Default linker flags.
LDFLAGS = -lgtest -lpthread #-L../ -lbst

# Conditionally enable coverage for the linker.
ifeq ($(COVERAGE),true)
LDFLAGS += -lgcov --coverage 
endif

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
