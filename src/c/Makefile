CC ?= gcc

# Whether to enable coverage.
COVERAGE ?= false

# The library name.
LIB_NAME = bst

# Shared library output name
LIB_SHARED_NAME = lib$(LIB_NAME).so

# Static library output name
LIB_STATIC_NAME = lib$(LIB_NAME).a

# Source files.
SRC = $(wildcard ./src/*.c)

# Default flags.
CFLAGS = -std=c99 -W -Wall -Werror -ansi -fPIC -g3 -I./include -O3

# Conditionally enable coverage for the compiler.
ifeq ($(COVERAGE),true)
CFLAGS += -fprofile-arcs -ftest-coverage
endif

# Default linker flags.
LDFLAGS = -shared

# Conditionally enable coverage for the linker.
ifeq ($(COVERAGE),true)
LDFLAGS += -lgcov --coverage 
endif

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(OBJ)
	ar -rcs $(LIB_STATIC_NAME) $^
	$(CC) $(LDFLAGS) -o $(LIB_SHARED_NAME) $^

gcov: $(OBJ)
	gcov $(OBJ)

tests: all
	cd tests && $(MAKE)

benchmark: all
	cd benchmark && $(MAKE)

examples: all
	cd examples/insertion && $(MAKE)
	cd examples/removal && $(MAKE)
	cd examples/search && $(MAKE)

re: fclean all

clean:
	$(shell find . -name '*~' -exec rm -r {} \; -o -name '*.o' -exec rm -r {} \; -o -name 'a.out' -exec rm -r {} \;)

fclean: clean
	rm -rf $(LIB_SHARED_NAME) $(LIB_STATIC_NAME)
	rm -rf src/*.gcno
	rm -rf src/*.gcda
	rm -rf src/*.info
	rm -rf src/*.gcov
	cd tests && $(MAKE) fclean
	cd benchmark && $(MAKE) fclean
	cd examples/insertion && $(MAKE) fclean
	cd examples/removal && $(MAKE) fclean
	cd examples/search && $(MAKE) fclean

.PHONY: clean fclean re
