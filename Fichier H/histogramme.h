#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H


// Bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "avl.h"

pArbre parcours(pArbre a, const char* fichier_donnees);
void remplir_infixe(pArbre a, const char* mode, FILE* fmax);
void generer_fichier_max(pArbre a, const char* mode);
void generer_fichier_src(pArbre a, const char* mode);
void generer_fichier_real(pArbre a, const char* mode);
void traitement_histogramme(const char* fichier_donnees, const char* mode);

#endif
