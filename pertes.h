#ifndef PERTES_H
#define PERTES_H



// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "arbre.h"

double calcul_pertes(Arbre_fuite* noeud, double volume);
double rendement(AVL_fuites* avl, char* id_usine);
void Historique(char* id_usine,float pertes);

#endif
