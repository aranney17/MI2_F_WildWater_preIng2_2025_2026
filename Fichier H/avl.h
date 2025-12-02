// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//structure AVL
typedef struct AVL{
	int val;
	struct arbre* fg;
	struct arbre* fd;
	int equilibre;
}AVL;
