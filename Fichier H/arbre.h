// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Chainon;

typedef struct Arbre_fuite{
        char* id;
        struct Chainon* fils;
} Arbre_fuite;

typedef struct Chainon{
        Arbre_fuite* noeud;
        float fuite;
        struct Chainon* suivant;
} Chainon;
