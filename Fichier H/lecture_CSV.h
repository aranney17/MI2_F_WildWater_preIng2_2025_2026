// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Enumération type de ligne
typedef enum { 
	SOURCE_USINE, USINE, USINE_STOCKAGE, STOCKAGE_JONCTION, JONCTION_RACC, RACC_USAGER, INCONNU
} Type_ligne;

//Structure ligne
typedef struct {
	char* col1;
	char* col2;
	char* col3;
	char* volume;
	char* leak;
	Type_ligne type;
} Ligne;

