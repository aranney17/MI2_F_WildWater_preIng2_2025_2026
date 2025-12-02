#include "lecture_CSV.h"

void lecture(){

  //Gestion du fichier
	FILE* fichier=NULL;
	fichier=fopen("Donnees/c-wildwater_v0(1).dat","r+");
	if (fichier==NULL ){
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	
	while (caractereActuel != EOF){
