#include "arbre.h"
#include "lecture_ligne.h"
#include "avl.h"

/*-------Fonctions utiles à la gestion des avl----------*/

pArbre creerArbre(char* identifiant, Usine u){
	pArbre noeud = malloc(sizeof(Arbre));
	if(noeud == NULL){
		exit(1);
	}

	noeud->id = malloc(strlen(identifiant) + 1);
	if(noeud->id == NULL){
		exit(1);
	}
	strcpy(noeud->id, identifiant);

	noeud->usine = malloc(sizeof(Usine));
	if(noeud->usine == NULL){
		exit(1);
	}
	*(noeud->usine) = u;

	noeud->fg = NULL;
	noeud->fd = NULL;
	noeud->equilibre = 0;
	return noeud;
}

pArbre rechercherNoeud(pArbre a, char *id){
    if(a == NULL){
	 return NULL;
    }
    int cmp = strcmp(id, a->id);
    if(cmp == 0){
	return a;
    }
    if(cmp < 0){
	return rechercherNoeud(a->fg, id);
    }
    return rechercherNoeud(a->fd, id);
}

int max(int a, int b){
	if(a >= b){
		return a;
	}
	return b;
}

int min(int a,int b){
	if(a <= b){
		return a;
	}
	return b;
}

pArbre rotationDroite(pArbre a){
	if(a == NULL || a->fg == NULL){
		 return a;
	}
	pArbre pivot;
	int eq_a;
	int eq_p;
	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - min(eq_p,0)+1;
	pivot->equilibre = max(eq_a+2,max(eq_a+eq_p+2,eq_p+1));
	a = pivot;
	return a;
}

pArbre rotationGauche(pArbre a){
	if(a == NULL || a->fd == NULL){
                 return a;
        }
	pArbre pivot;
	int eq_a;
	int eq_p;
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - max(eq_p,0)-1;
	pivot->equilibre = min(eq_a-2,min(eq_a+eq_p-2,eq_p-1));
	a = pivot;
	return a;
}

pArbre doubleRotationGauche(pArbre a){
	if(a == NULL){
		exit(1);
	}
	a->fd = rotationDroite(a->fd);
	return rotationGauche(a);
}

pArbre doubleRotationDroite(pArbre a){
	if(a == NULL){
		exit(1);
	}
	a->fg = rotationGauche(a->fg);
	return rotationDroite(a);
}



pArbre equilibreAVL(pArbre a){
	if(a == NULL){
		exit(1);
	}
	if(a->equilibre >= 2){
		if(a->fd->equilibre >= 0){
			return rotationGauche(a);
		}
		else{
			return doubleRotationGauche(a);
		}
	}
	else if(a->equilibre <= -2){
		if(a->fg->equilibre <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);
		}
	}
	return a;
}

pArbre insertionAVL(pArbre a, char* identifiant, Usine* u, int* h){
	if(a == NULL){
		*h = 1;
		return creerArbre(identifiant, *u);
	}
	if(strcmp(a->id, identifiant) > 0){
		a->fg = insertionAVL(a->fg, identifiant, u, h);
		*h = -*h;
	}
	else if(strcmp(identifiant, a->id) > 0){
		a->fd = insertionAVL(a->fd, identifiant, u, h);
	}
	else{
		*h = 0;
		return a;
	}
	if(*h != 0){
		a->equilibre += *h;
		a = equilibreAVL(a);
		if(a->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return a;
}

AVL_fuites* creerAVLfuites(char* identifiant, Arbre_fuite* element){
	AVL_fuites* nv = malloc(sizeof(AVL_fuites));
	if(nv == NULL){
		exit(1);
	}
	nv->id = strdup(identifiant);
	nv->elmt = element;
	nv->fg = NULL;
	nv->fd = NULL;
	nv->equilibre = 0;
	return nv;
}

AVL_fuites* rechercheAVLfuites(AVL_fuites* a, char* identifiant){
	if(a == NULL){
		return NULL;
	}
	if(strcmp(a->id, identifiant) == 0){
		return a;
	}
	if(strcmp(a->id, identifiant) > 0){
		return rechercheAVLfuites(a->fg, identifiant);
	}
	return rechercheAVLfuites(a->fd, identifiant);
}

AVL_fuites* rotationDroiteAVLfuites(AVL_fuites* a){
	AVL_fuites* pivot;
	int eq_a;
	int eq_p;
	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - min(eq_p,0)+1;
	pivot->equilibre = max(eq_a+2,max(eq_a+eq_p+2,eq_p+1));
	a = pivot;
	return a;
}

AVL_fuites* rotationGaucheAVLfuites(AVL_fuites* a){
	AVL_fuites* pivot;
	int eq_a;
	int eq_p;
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - max(eq_p,0)-1;
	pivot->equilibre = min(eq_a-2,min(eq_a+eq_p-2,eq_p-1));
	a = pivot;
	return a;
}

AVL_fuites* doubleRotationGaucheAVLfuites(AVL_fuites* a){
	if(a == NULL){
		exit(1);
	}
	a->fd = rotationDroiteAVLfuites(a->fd);
	return rotationGaucheAVLfuites(a);
}

AVL_fuites* doubleRotationDroiteAVLfuites(AVL_fuites* a){
	if(a == NULL){
		exit(1);
	}
	a->fg = rotationGaucheAVLfuites(a->fg);
	return rotationDroiteAVLfuites(a);
}

AVL_fuites* equilibreAVLfuites(AVL_fuites* a){
	if(a == NULL){
		exit(1);
	}
	if(a->equilibre >= 2){
		if(a->fd->equilibre >= 0){
			return rotationGaucheAVLfuites(a);
		}
		else{
			return doubleRotationGaucheAVLfuites(a);
		}
	}
	else if(a->equilibre <= -2){
		if(a->fg->equilibre <= 0){
			return rotationDroiteAVLfuites(a);
		}
		else{
			return doubleRotationDroiteAVLfuites(a);
		}
	}
	return a;
}

AVL_fuites* insertionAVLfuites(AVL_fuites* a, char* identifiant, Arbre_fuite* element, int* h){
	if(a == NULL){
		*h = 1;
		return creerAVLfuites(identifiant,element);
	}
	if(strcmp(a->id, identifiant) > 0){
		a->fg = insertionAVLfuites(a->fg, identifiant, element, h);
		*h = -*h;
	}
	else if(strcmp(identifiant, a->id) > 0){
		a->fd = insertionAVLfuites(a->fd, identifiant, element, h);
	}
	else{
		*h = 0;
		return a;
	}
	if(*h != 0){
		a->equilibre += *h;
		a = equilibreAVLfuites(a);
		if(a->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return a;
}

