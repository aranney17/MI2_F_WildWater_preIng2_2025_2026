// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct chainon{
	struct arbre* arbre;
	float fuite;
	struct chainon* suivant;
} Chainon;

typedef struct arbre{
	char* id;
	Chainon* fils;
} Arbre;


