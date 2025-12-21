
#include "pertes.h"


double calcul_pertes(Arbre_fuite* noeud, double volume){
    //Si usager
    if(noeud->fils==NULL){
        return 0.0;
    }
    
    double pertes_totales=0.0;
    double volume_par_fils;
    double perte_troncon;
    double volume_fils;
    
    Chainon* p=noeud->fils;
    
    while(p!=NULL){
        volume_par_fils = volume / nbFils(noeud);
        
        //perte sur ce tronçon
        perte_troncon = volume_par_fils * (p->fuite / 100);
        
        pertes_totales += perte_troncon;
        volume_fils = volume_par_fils * (1 - p->fuite / 100);

        //pertes aval
        pertes_totales += calcul_pertes(p->noeud, volume_fils);
        
        p=p->suivant;
    }
    
    return pertes_totales;
}

double rendement(AVL_fuites* avl, char* id_usine){
    //Si ce n'est pas un usine
    if(strstr(id_usine, "Unit")==NULL && strstr(id_usine, "Plant")==NULL && strstr(id_usine, "Module")==NULL && strstr(id_usine, "Facility")==NULL){
        return -1.0;
    }
    
    //Recherche de l'usine dans l'AVL des fuites
    AVL_fuites* avl_usine=rechercheAVLfuites(avl, id_usine);

    //Usine non trouvée
    if(avl_usine==NULL){
        printf("usine non trouvée\n");
        return -1.0;
    }

    //sinon
    double vol=avl_usine->elmt->volume;
    //calcul des pertes
    double pertes=calcul_pertes(avl_usine->elmt,vol)/pow(10,3);
    printf("Le volume d'eau potable perdus par %s est de %lf M.m3.\n",id_usine,pertes);
    return pertes;
}

//Procédure qui écrit les résultat dans le fichier rendements
void Historique(char* id_usine,float pertes){
    //Gestion de l'ouverture du fichier
    FILE* f=fopen("rendements.dat","a");
    if (f==NULL){
        exit(1);
    }
    
    fprintf(f,"%s;%lf\n",id_usine,pertes);
    fclose(f);
}
