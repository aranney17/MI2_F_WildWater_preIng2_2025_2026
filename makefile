# Compilateur
CC = gcc
CFLAGS = -Wall -Wextra -g



# Sources et objets
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Exécutable
EXEC = wildwater

# Règle par défaut
all: $(EXEC)

# Édition de liens
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# Compilation des .c
%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@ -lm

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)
