#include "histogramme.h"
#include "lecture_ligne.h"
#include"avl.h"

//Remplissage de l'avl
pArbre parcours(pArbre a, const char* fichier_donnees){
    char buffer[255];
    FILE* fichier = fopen(fichier_donnees, "r");      //ouverture ficier
    if(fichier == NULL){
        exit(1);
    }

    Ligne ligne;

    while(fgets(buffer, sizeof(buffer), fichier)){    //lecture d'une ligne
        ligne = stockage_ligne(buffer);     //stockage de ses informations

        if(ligne.type == USINE){
            pArbre n = rechercherNoeud(a, ligne.col2);
            if(n != NULL){        //si noeud touvé
                n->usine->vol_max = ligne.volume /1000;    //mise à jour volume max
            } else {      //création noeud
                Usine u;
                u.id = malloc(strlen(ligne.col2) + 1);
                strcpy(u.id, ligne.col2);
                u.vol_max = ligne.volume / 1000;       //en M.m3
                u.vol_capte = 0;
                u.vol_reel = 0;

                int h = 0;
                a = insertionAVL(a, ligne.col2, &u, &h);
            }
        }
        else if(ligne.type == SOURCE_USINE){
            pArbre n = rechercherNoeud(a, ligne.col3);
            if(n != NULL){     //trouvé
                n->usine->vol_capte += ligne.volume / 1000;      //mise à jour volume capté
                n->usine->vol_reel += (ligne.volume * (1 - ligne.pertes / 100)) / 1000;     //mise à jour volume réel
            } else {        //création noeud
                Usine u;
                u.id = malloc(strlen(ligne.col3) + 1);
                strcpy(u.id, ligne.col3);
                u.vol_capte = ligne.volume / 1000;
                u.vol_reel = ligne.volume * (1 - ligne.pertes / 100) / 1000;

                int h = 0;
                a = insertionAVL(a, ligne.col3, &u, &h);
            }
        }
    }

    fclose(fichier);
    return a;
}

//Remplir le fichier dans l'ordre alphabétique inverse
void remplir_infixe(pArbre a, const char* mode, FILE *f){
    if(a == NULL){
        return;
    }

    remplir_infixe(a->fd, mode, f);

    if(strcmp(mode, "max") == 0){
        fprintf(f,  "%s;%lf\n", a->id, a->usine->vol_max);    //ajout de l'identifiant et du volume
    }
    else if(strcmp(mode, "src") == 0){
        fprintf(f,  "%s;%lf\n", a->id, a->usine->vol_capte);
    } else if(strcmp(mode, "real") == 0){
        fprintf(f,  "%s;%lf\n", a->id, a->usine->vol_reel);
    }

    remplir_infixe(a->fg, mode, f);
    
}

//Création du fichier vol_max.dat
void generer_fichier_max(pArbre a, const char* mode){
    FILE *fmax  = fopen("vol_max.dat", "w+");
    if(fmax == NULL){
        printf("erreur ouverture fichier histogramme");
        exit(1);
    }

    fprintf(fmax,  "identifiant;volume max (M.m3.year-1)\n");

    remplir_infixe(a, mode, fmax);

    fclose(fmax);
}

//Création du fichier vol_captation.dat
void generer_fichier_src(pArbre a, const char* mode){
    FILE *fcap  = fopen("vol_captation.dat", "w+");
    if(fcap == NULL ){
        printf("erreur ouverture fichier histogramme");
        exit(1);
    }

    fprintf(fcap,  "identifiant;volume capté (M.m3.year-1)\n");

    remplir_infixe(a, mode, fcap);

    fclose(fcap);
}

//Création du fichier vol_traitement.dat
void generer_fichier_real(pArbre a, const char* mode){
    FILE *freal = fopen("vol_traitement.dat", "w+");
    if(freal == NULL){
        printf("erreur ouverture fichier histogramme");
        exit(1);
    }

    fprintf(freal, "identifiant;volume traité (M.m3.year-1)\n");

    remplir_infixe(a, mode, freal);
    fclose(freal);
}

void traitement_histogramme(const char* fichier_donnees, const char* mode){
    pArbre a = NULL;
    a = parcours(a, fichier_donnees);     //remplissage avl
    printf("Parcours terminé\n");

    if(strcmp(mode, "max") == 0){     //mode histo : max
         generer_fichier_max(a, mode);
    }
    if(strcmp(mode, "src") == 0){     //mode histo : src
         generer_fichier_src(a, mode);
    }
    if(strcmp(mode, "real") == 0){    //mode histo : real
         generer_fichier_real(a, mode);
    }
}
