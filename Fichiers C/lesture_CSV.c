#include "lecture_CSV.h"

	
// procédure qui permet de stocker l'information	
void stockage_info(char* tmp, char caractere,FILE* fichier){

	// variables locales
	int compteur=0;

	// compte le nb de caractères dans l'information
    while(fgetc(fichier)!=caractere){ 
        compteur++;
    }

	//Allocation dynamique
    tmp=malloc((compteur+1)*sizeof(char));
    if(tmp==NULL){
        printf("Allocation échouée\n");
        exit(1);
    }
        
    fseek(fichier,-(compteur+1),SEEK_CUR); //curseur replacé devant le premier caractère de l'information
    fgets(tmp,compteur+1,fichier);
	fseek(fichier,1,SEEK_CUR); //curseur replacé devant le premier caractère de la prochaine information
	
}

//Fonction qui détecte le type de ligne
Type_ligne detecter_type(char *col2, char* col3){
	
	//ligne non détectée
	if(col2 == NULL || col3 == NULL){
		return INCONNU;
    }

	//ligne SOURCE->USINE (captage)
    if((strstr(col2, "Spring") || strstr(col2, "Well") || strstr(col2, "Resurgence")) && strstr(col3, "Plant")){
		return SOURCE_USINE;
    }

	//ligne USINE
    if((strstr(col2, "Plant") || strstr(col2, "Module")) & col3[0] == '-'){
        return USINE;
    }

	//ligne USINE->STOCKAGE (stockage)
    if((strstr(col2, "Spring") || strstr(col2, "Module")) && strstr(col3, "Storage")){
        return USINE_STOCKAGE;
    }

	//ligne STOCKAGE->JONCTION (distribution principale)
    if(strstr(col2, "Storage") && strstr(col3, "Junction")){
        return STOCKAGE_JONCTION;
    }

	//ligne JONCTION->RACCORDEMENT (distribution secondaire)
    if(strstr(col2, "Junction") && strstr(col3, "Service")){
        return JONCTION_RACC;
    }

	//ligne RACCORDEMENT->USAGER (branchement)
    if(strstr(col2, "Service") && strstr(col3, "Cust")){
        return RACC_USAGER;
    }

	//ligne non détectée
    return INCONNU;
	
}

void stockage_ligne(){

	//Gestion du fichier
	FILE* fichier=NULL;
	fichier=fopen("c-wildwater_v0(1).dat","r+");
	if (fichier==NULL ){
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	
	// variables locales
	Ligne ligne;
	
	//Stocke les informations dans les champs correspondants	
	stockage_info(ligne.col1,';',fichier);
	stockage_info(ligne.col2,';',fichier);
	stockage_info(ligne.col3,';',fichier);
	stockage_info(ligne.volume,';',fichier);
	stockage_info(ligne.leak,'\n',fichier);
	ligne.type = detecter_type(ligne.col2, ligne.col3);
	
}
