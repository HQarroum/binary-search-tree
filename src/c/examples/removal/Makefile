CC ?= gcc

# Name of the binary.
APP = removal

# Source files.
SRC = $(wildcard ./*.c)

# Default flags.
CFLAGS = -std=c99 -W -Wall -Werror -I../../include -O3

# Default linker flags.
LDFLAGS = -L../../ -lbst

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJ)
	$(CC) -o $(APP) $^ $(CFLAGS) $(LDFLAGS)

re: fclean all

clean:
	$(shell find . -name '*~' -exec rm -r {} \; -o -name '*.o' -exec rm -r {} \;)

fclean: clean
	rm -f $(APP)

.PHONY: clean fclean re
