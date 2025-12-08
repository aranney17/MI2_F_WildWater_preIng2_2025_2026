#include "lecture_CSV.h"


void lecture(){

	//Gestion du fichier
	FILE* fichier=NULL;
	fichier=fopen("c-wildwater_v0(1).dat","r+");
	if (fichier==NULL ){
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	
	
	// variables locales
	int caractereActuel = 0;
	char* id[];
	int compteur=0;
		
	
	// alloue dynamiquement l'espace nécessaire pour stocker l'id de l'usine
        while(fgetc(fichier)!=';'){ // compte le nb de chiffres dans l'id
            compteur++;
        }
        id=malloc((compteur+1)*sizeof(char));
        if(id==NULL){
            printf("Allocation échouée\n");
            exit(1);
        }
        fseek(fichier,-(compteur+1),SEEK_CUR); //curseur replacé devant le premier chiffre de l'id
        compteur=0;
        printf ("%s",id);
	
	
}


int main(){
	lecture();
	return 0;
}
