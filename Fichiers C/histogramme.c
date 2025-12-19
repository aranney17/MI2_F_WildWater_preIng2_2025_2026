#include "histogramme.h"

//lecture_CSV pour chaque ligne on recherche dans l'avl on ajoute le volume a la bonne usine
//ecrire vol_max vol_captation vol_traite

pArbre parcours(pArbre a, const char* fichier_donnees){
    char buffer[255];
    FILE* fichier = fopen(fichier_donnees,"r");
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

void remplir_infixe(pArbre a, const char* mode){
    if(a == NULL){
        return;
    }

    remplir_infixe(a->fg, mode);
    
    if(strcmp(mode, "max") == 0){
        fprintf(fmax,  "%s;%lf\n", a->id, a->usine->vol_max);
    }
    else if(strcmp(mode, "src") == 0){
        fprintf(fmax,  "%s;%lf\n", a->id, a->usine->vol_capte);
    } else if(strcmp(mode, "real") == 0){
        fprintf(fmax,  "%s;%lf\n", a->id, a->usine->vol_reel);
    }

    remplir_infixe(a->fd, mode);
    
}

/*void remplir_fichier(pArbre a, FILE *fmax, FILE *fcap, FILE *freal){
    if(a == NULL){
         return;
    }

    remplir_fichiers(a->fg, fmax, fcap, freal);

    fprintf(fmax,  "%s;%lf\n", a->id, a->usine->vol_max);
    fprintf(fcap,  "%s;%lf\n", a->id, a->usine->vol_capte);
    fprintf(freal, "%s;%lf\n", a->id, a->usine->vol_reel);

    remplir_fichiers(a->fd, fmax, fcap, freal);
}*/

void generer_fichier_max(pArbre a, const char* mode){
    FILE *fmax  = fopen("vol_max.dat", "w");
    if(fmax == NULL){
        printf("erreur ouverture fichier histogramme");
        exit(1);
    }

    fprintf(fmax,  "identifiant;volume max (k.m3.year-1)\n");

    remplir_infixe(a, mode);

    fclose(fmax);
}

void generer_fichier_src(pArbre a, const char* mode){
    FILE *fcap  = fopen("vol_captation.dat", "w");
    if(fcap == NULL ){
        printf("erreur ouverture fichier histogramme");
        exit(1);
    }

    fprintf(fcap,  "identifiant;volume capté (k.m3.year-1)\n");

    remplir_infixe(a, mode);

    fclose(fcap);
}

void generer_fichier_max(pArbre a, const char* mode){
    FILE *freal = fopen("vol_traitement.dat", "w");
    if(freal == NULL){
        printf("erreur ouverture fichier histogramme");
        exit(1);
    }

    fprintf(freal, "identifiant;volume traité (k.m3.year-1)\n");

    remplir_infixe(a, mode);

    fclose(freal);
}

void traitement_histogramme(const char* fichier_donnees, const char* mode){
    pArbre a = NULL;
    a = parcours(a, fichier_donnees);
    if(strcmp(mode, max) == 0){
         generer_fichier_max(a, mode);
    }
    if(strcmp(mode, max) == 0){
         generer_fichier_max(a, mode);
    }
    if(strcmp(mode, max) == 0){
         generer_fichier_max(a, mode);
    }
}
