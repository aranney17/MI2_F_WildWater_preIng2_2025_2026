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

void ajouterFils(Arbre_fuite* parent, Arbre_fuite* enfant, float fuite){
    Chainon* nv=creerChainon(enfant,fuite);
    nv->suivant=parent->fils;
    parent->fils=nv;
}

int nbFils(Arbre_fuite* noeud){
    int nb=0;
    Chainon* p=noeud->fils;
    while(p!=NULL){
        nb++;
        p=p->suivant;
    }
    return nb;
}

void remplissage_arbre(FILE* fichier){        
    //variables locales
    int caractereActuel = EOF+1;
    Ligne ligne;
    float fuite;
    AVL_fuites* avl_fuites=NULL;
    int h= 0;
    AVL_fuites* parent;
    AVL_fuites* enfant;
    Arbre_fuite* parent_arbre;
    Arbre_fuite* enfant_arbre;
        
    while(caractereActuel!=EOF){
        ligne=stockage_ligne(fichier);
        if (ligne.type!=SOURCE_USINE && ligne.type!=USINE){
            if (strcmp(ligne.leak,"-")==0){
                fuite=0.0;
            }
            else{
                fuite=strtof(ligne.leak,NULL);
            }
            parent = rechercheAVLfuites(avl_fuites, ligne.col2);
            if(parent==NULL){
                parent_arbre=creerArbreFuite(ligne.col2);
                avl_fuites=insertionAVLfuites(avl_fuites, parent_arbre->id, parent_arbre, &h);
            }
            else{
                parent_arbre=parent->elmt;
            }
            enfant = rechercheAVLfuites(avl_fuites, ligne.col3);
            if(enfant==NULL){
                enfant_arbre=creerArbreFuite(ligne.col3);
                avl_fuites=insertionAVLfuites(avl_fuites, enfant_arbre->id, enfant_arbre, &h);
            }
            else{
                enfant_arbre=enfant->elmt;
            }
            ajouterFils(parent_arbre,enfant_arbre,fuite);
        }
        free(ligne.col1);
        free(ligne.col2);
        free(ligne.col3);
        free(ligne.volume);
        free(ligne.leak);
        
        caractereActuel=fgetc(fichier);
        fseek(fichier,-1,SEEK_CUR);
    } 
        
}
