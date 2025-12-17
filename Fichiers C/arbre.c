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

