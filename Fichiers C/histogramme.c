#include "histogramme.h"

//lecture_CSV pour chaque ligne on recherche dans l'avl on ajoute le volume a la bonne usine
//ecrire vol_max vol_captation vol_traite

pArbre parcours(pArbre a){
	 char buffer[255];
	 int nb;
	
	//Gestion du fichier
	FILE* fichier=NULL;
	fichier = fopen("c-wildwater_v0(1).dat","r+");
	if (fichier == NULL){
		printf("Ouverture du fichier impossible \n");
		exit(1);
	}
	
	while (fgets(buffer, sizeof buffer, fichier) != NULL){
		Ligne ligne;
		ligne=stockage_ligne(fichier);
		
		Usine u;
		u->id = NULL;
		u->vol_max = 0;
		u->vol_capte = 0;
		u->vol_reel = 0;
		
		//convertir les char en double !!
		
		if(ligne.type == 1){
			if(recherche(a, ligne.col2, &nb)){
				u.id = ligne.col2;
				u.vol_max = ligne.col4;
				a = creerArbre(ligne.col2, u);
			}
		}
		else if(ligne.type == 0){
			if(recherche(a, ligne.col3, &nb)){
				u.id = ligne.col3;
				u.vol_capte = ligne.col4;
				u.vol_reel = u.volume
				a = creerArbre(ligne.col2, u);
			}
		}
	}
	fclose(fichier);
}
