CC = gcc

LIB_NAME = bst

# Shared library extension
LIB_SHARED_EXT = .so

# Static library extension
LIB_STATIC_EXT = .a

# Shared library output name
LIB_SHARED_NAME = lib$(LIB_NAME)$(LIB_SHARED_EXT)

# Static library output name
LIB_STATIC_NAME = lib$(LIB_NAME)$(LIB_STATIC_EXT)

SRC = binary_search_tree.c \
		binary_search_tree_insert.c \
		binary_search_tree_search.c \
		binary_search_tree_remove.c \
		binary_search_tree_compare.c \
		binary_search_tree_iterate.c

CFLAGS = -std=c99 -W -Wall -Werror -ansi -fPIC -fprofile-arcs -ftest-coverage

LDFLAGS = -shared -lgcov --coverage 

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(OBJ)
	ar -rcs $(LIB_STATIC_NAME) $^
	$(CC) $(LDFLAGS) -o $(LIB_SHARED_NAME) $^
	gcov $(OBJ)

re: fclean all

clean:
	$(shell find . -name '*~' -exec rm -r {} \; -o -name '*.o' -exec rm -r {} \;)

fclean: clean
	rm -f $(LIB_SHARED_NAME) $(LIB_STATIC_NAME)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.info
	rm -f *.gcov

.PHONY: clean fclean re
