// Bibliothèques
#ifndef ARBRE_H
#define ARBRE_H

//Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "avl.h"

//Prototypes
Arbre_fuite* creerArbreFuite(char*identifiant, double vol);
Chainon* creerChainon(Arbre_fuite* enfant, double fuite);
void ajouterFils(Arbre_fuite* parent, Arbre_fuite* enfant, double fuite);
int nbFils(Arbre_fuite* noeud);
AVL_fuites* remplissage_arbre(const char* fichier_donnees);

#endif
