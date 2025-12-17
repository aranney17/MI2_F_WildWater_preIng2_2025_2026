#include "arbre.h"

Arbre_fuite* creerArbreFuite(char*identifiant){
    Arbre_fuite* nv = malloc(sizeof(Arbre_fuite));
    if(nv==NULL){
        printf("Allocation échouée");
        exit(1);
    }
    nv->id=strdup(identifiant);
    nv->fils = NULL;
    return nv;
}

Chainon* creerChainon(Arbre_fuite* enfant, float fuite){
    Chainon* c=malloc(sizeof(Chainon));
    if(c==NULL){
        printf("Allocation échouée");
        exit(1);
    }
    c->noeud=enfant;
    c->fuite = fuite;
    c->suivant=NULL;
    return c;
}
