// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Chainon{
	struct arbre_fuite* noeud;
	float fuite;
	struct chainon* suivant;
} Chainon;

typedef struct Arbre_fuite{
	char* id;
	Chainon* fils;
} Arbre_fuite;


