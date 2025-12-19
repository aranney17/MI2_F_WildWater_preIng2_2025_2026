# Variables

CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = $(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: exec
	
exec : $(OBJ)
	$(CC) $^ -o $@

clean:
	rm -f $(OBJ)
