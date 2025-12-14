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


Type_ligne detecter_type(char *col2, char* col3){
	if(col2 == NULL || col3 == NULL){
		return INCONNU;
    }
    if((strstr(col2, "Spring") || strstr(col2, Well) || strstr(col2, Resurgence)) && strstr(col3, "Plant")){
		return SOURCE_USINE;
    }
    if((strstr(col2, "Plant") || strstr(col2, "Module")) & col3[0] == '-'){
        return USINE;
    }
    if((strstr(col2, "Spring") || strstr(col2, "Module")) && strstr(col3, "Storage")){
        return USINE_STOCKAGE;
    }
    if(strstr(col2, "Storage") && strstr(col3, "Junction")){
        return STOCKAGE_JONCTION;
    }
    if(strstr(col2, "Junction") && strstr(col3, "Service")){
        return JONCTION_RACC;
    }
    if(strstr(col2, "Service") && strstr(col3, "Cust")){
        return RACC_USAGER;
    }
    return INCONNU;
}
