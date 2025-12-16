// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct arbre{
	char* id;
	struct arbre* fils;
}Arbre;

typedef struct chainon{
	Arbre* arbre;
  float fuite;
	struct chainon* suivant;
} Chainon;
