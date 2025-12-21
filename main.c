
#include "pertes.h"
#include "arbre.h"
#include "lecture_ligne.h"
#include "avl.h"
#include "histogramme.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Erreur : arguments insuffisants\n");
        return 1;
    }

    char *fichier_donees = argv[1];
    char *commande  = argv[2];

    if(strcmp(commande, "histo") == 0){     //histo max|src|real -> générer histogramme
        if(argc != 4){
            printf("Erreur : histo nécessite max|src|real\n");
            return 1;
        }

        char *mode = argv[3];

        if(strcmp(mode, "max") != 0 &&
        	strcmp(mode, "src") != 0 &&
        	strcmp(mode, "real") != 0){
			printf("Erreur : mode histo invalide\n");
            return 1;
        }
		traitement_histogramme(fichier_donees, mode);   //générer l'histogramme demandé

        return 0;
    }
    else if(strcmp(commande, "leaks") == 0){      //leaks "Usine" -> calcul pertes
        if(argc != 4){
            printf("Erreur : leaks nécessite un identifiant\n");
            return 1;
        }

        char *usine_id = argv[3];

        AVL_fuites* avl = remplissage_arbre(fichier_donees);
    	Historique(usine_id, rendement(avl, usine_id));      //création fichier rendements.dat

        return 0;
    }
    else{
        printf("Erreur : commande inconnue\n");
        return 1;
    }
}

