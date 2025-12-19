#ifndef AVL_H
#define AVL_H



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

// Déclaration anticipée de Arbre_fuite
typedef struct Arbre_fuite Arbre_fuite;

typedef struct Chainon {
    Arbre_fuite* noeud;   // pointeur vers Arbre_fuite
    double fuite;
    struct Chainon* suivant;
} Chainon;

struct Arbre_fuite {
    char* id;
    double volume;
    Chainon* fils;        // pointeur vers la liste de Chainon
};


typedef struct AVL_fuites{
	char* id;
	struct Arbre_fuite* elmt;
	struct AVL_fuites* fd;
	struct AVL_fuites* fg;
	int equilibre;
}AVL_fuites;

typedef struct arbre* pArbre;




pArbre creerArbre(char* identifiant, Usine u);
pArbre rechercherNoeud(pArbre a, char *id);
int max(int a, int b);
int min(int a,int b);
pArbre rotationDroite(pArbre a);
pArbre rotationGauche(pArbre a);
pArbre doubleRotationGauche(pArbre a);
pArbre doubleRotationDroite(pArbre a);
pArbre equilibreAVL(pArbre a);
pArbre insertionAVL(pArbre a, char* identifiant, Usine* u, int* h);
AVL_fuites* creerAVLfuites(char* identifiant, Arbre_fuite* element);
AVL_fuites* rechercheAVLfuites(AVL_fuites* a, char* identifiant);
AVL_fuites* rotationDroiteAVLfuites(AVL_fuites* a);
AVL_fuites* rotationGaucheAVLfuites(AVL_fuites* a);
AVL_fuites* doubleRotationGaucheAVLfuites(AVL_fuites* a);
AVL_fuites* doubleRotationDroiteAVLfuites(AVL_fuites* a);
AVL_fuites* equilibreAVLfuites(AVL_fuites* a);
AVL_fuites* insertionAVLfuites(AVL_fuites* a, char* identifiant, Arbre_fuite* element, int* h);

#endif
