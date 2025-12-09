#include "lecture_CSV.h"

	
	
void stockage(char* tmp, char caractere,FILE* fichier){
	int compteur=0;
		
	// alloue dynamiquement l'espace nécessaire pour stocker l'id de l'usine
        while(fgetc(fichier)!=caractere){ // compte le nb de chiffres dans l'id
            compteur++;
        }
        
        tmp=malloc((compteur+1)*sizeof(char));
        if(tmp==NULL){
            printf("Allocation échouée\n");
            exit(1);
        }
        
        fseek(fichier,-(compteur+1),SEEK_CUR); //curseur replacé devant le premier chiffre de l'id
        fgets(tmp,compteur+1,fichier);
        printf("%s\n",tmp);
	fseek(fichier,1,SEEK_CUR);
}
	
	


void lecture(){

	//Gestion du fichier
	FILE* fichier=NULL;
	fichier=fopen("c-wildwater_v0(1).dat","r+");
	if (fichier==NULL ){
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	
	
	// variables locales
	Info ligne;
	int type=-1;
		
	stockage(ligne.col1,';',fichier);
	stockage(ligne.col2,';',fichier);
	stockage(ligne.col3,';',fichier);
	stockage(ligne.volume,';',fichier);
	stockage(ligne.leak,'\n',fichier);
	
       
}
