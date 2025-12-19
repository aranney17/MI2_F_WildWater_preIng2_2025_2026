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

void remplir_fichiers(pArbre a, FILE *fmax, FILE *fcap, FILE *freal){
    if(a == NULL){
         return;
    }

    remplir_fichiers(a->fg, fmax, fcap, freal);

    fprintf(fmax,  "%s;%.2f\n", a->id, a->usine->vol_max);
    fprintf(fcap,  "%s;%.2f\n", a->id, a->usine->vol_capte);
    fprintf(freal, "%s;%.2f\n", a->id, a->usine->vol_reel);

    remplir_fichiers(a->fd, fmax, fcap, freal);
}

void generer_fichiers_histogramme(char* fichier, char* mode, pArbre a){
    FILE *fmax  = fopen("vol_max.dat", "w");
    FILE *fcap  = fopen("vol_captation.dat", "w");
    FILE *freal = fopen("vol_traitement.dat", "w");

    if(fmax == NULL || fcap == NULL || freal == NULL){
        printf("erreur ouverture fichiers histogramme");
        exit(1);
    }

    fprintf(fmax,  "id;volume_max\n");
    fprintf(fcap,  "id;volume_captation\n");
    fprintf(freal, "id;volume_traitement\n");

    remplir_fichiers(a, fmax, fcap, freal);

    fclose(fmax);
    fclose(fcap);
    fclose(freal);
}

