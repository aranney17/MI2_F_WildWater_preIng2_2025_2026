#include "histogramme.h"

//lecture_CSV pour chaque ligne on recherche dans l'avl on ajoute le volume a la bonne usine
//ecrire vol_max vol_captation vol_traite

pArbre parcours(pArbre a){
    char buffer[255];
    FILE* fichier = fopen("c-wildwater_v0.dat","r");
    if(fichier == NULL){
        exit(1);
    }

    Ligne ligne;

    while(fgets(buffer, sizeof(buffer), fichier)){
        ligne = stockage_ligne(buffer);

        if(ligne.type == USINE){
            Usine u;
            u.id = malloc(strlen(ligne.col2) + 1);
            strcpy(u.id, ligne.col2);
            u.vol_max = ligne.volume;
            u.vol_capte = 0;
            u.vol_reel = 0;

            int h = 0;
            a = insertionAVL(a, ligne.col2, &u, &h);
        }
        else if(ligne.type == SOURCE_USINE){
            pArbre n = rechercherNoeud(a, ligne.col3);
            if(n != NULL){
                n->usine->vol_capte += ligne.volume;
                n->usine->vol_reel += ligne.volume * (1 - ligne.pertes/100);
            }
        }
    }

    fclose(fichier);
    return a;
}

