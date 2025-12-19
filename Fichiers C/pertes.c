#include "pertes.h"

double calcul_pertes(Arbre_fuite* noeud, double volume){
    
    if(noeud->fils==NULL){
        return 0.0;
    }
    
    double pertes_totales=0.0;
    double volume_par_fils;
    double perte_troncon;
    double volume_fils;
    
    Chainon* p=noeud->fils;
    
    while(p!=NULL){
        volume_par_fils=volume/nbFils(noeud);
        perte_troncon=volume_par_fils*p->fuite;
        pertes_totales+=perte_troncon;
        volume_fils=volume_par_fils*(100-p->fuite);
        pertes_totales+=calcul_pertes(p->noeud, volume_fils);
        p=p->suivant;
    }
    
    return pertes_totales;
}

double rendement(AVL_fuites* avl, char* id_usine){
    
    AVL_fuites* avl_usine=rechercheAVLfuites(avl, id_usine);
    if(avl_usine==NULL){
        return -1.0;
    }
    double pertes=calcul_pertes(avl_usine->elmt,avl_usine->elmt->volume);
    return pertes/pow(10,6);
}

void Historique(char* id_usine,float pertes){
    FILE* f=fopen("rendements.dat","a");
    if (f==NULL){
        exit(1);
    }
    fprintf(f,"%s;%lf\n",id_usine,pertes);
    fclose(f);
}
