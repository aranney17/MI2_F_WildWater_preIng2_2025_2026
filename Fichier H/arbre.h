// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct chainon{
	struct arbre_fuite* arbre;
	float fuite;
	struct chainon* suivant;
} Chainon;

typedef struct arbre_fuite{
	char* id;
	Chainon* fils;
} Arbre_fuite;


