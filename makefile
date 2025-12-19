# Compilateur
CC = gcc
CFLAGS = -Wall -Wextra -g

# Dossiers
SRC_DIR = fichiers_c
INC_DIR = fichiers_h

# Sources et objets
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Exécutable
EXEC = wildwater

# Règle par défaut
all: $(EXEC)

# Édition de liens
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des .c
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)
