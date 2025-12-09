// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	char* id;
	double vol_max;
	double vol_capte;
	double vol_reel;
} Usine;

typedef struct arbre {
	char* id;
	Usine* usine;
	struct arbre* fg;
	struct arbre* fd;
	int equilibre;
} Arbre;

typedef struct arbre* pArbre;
