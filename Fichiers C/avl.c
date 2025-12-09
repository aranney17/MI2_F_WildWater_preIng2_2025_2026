#include "avl.h"

int max(int a,int b){
	if(a>b){
		return a;
	}
	return b;
}

int min(int a,int b){
	if(a<b){
		return a;
	}
	return b;
}

pArbre rotationDroite(pArbre a){
	pArbre pivot;
	int eq_a;
	int eq_p;
	pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	eq_a=a->equilibre;
	eq_p=pivot->equilibre;
	a->equilibre=eq_a - min(eq_p,0)+1;
	pivot->equilibre=max(eq_a+2,max(eq_a+eq_p+2,eq_p+1));
	a=pivot;
	return a;
}

pArbre rotationGauche(pArbre a){
	pArbre pivot;
	int eq_a;
	int eq_p;
	pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eq_a=a->equilibre;
	eq_p=pivot->equilibre;
	a->equilibre=eq_a - max(eq_p,0)-1;
	pivot->equilibre=min(eq_a-2,min(eq_a+eq_p-2,eq_p-1));
	a=pivot;
	return a;
}
