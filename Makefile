CFLAGS = -ansi -pedantic-errors -Wall -Wextra -Werror -g -Og
LFLAGS = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
BIN = driver

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) -MMD -MP -c $< $(CFLAGS)

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ) $(DEP) *~

-include $(DEP)
