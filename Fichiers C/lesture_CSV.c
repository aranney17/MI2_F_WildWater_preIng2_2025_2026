#include "lecture_CSV.h"

	
// procédure qui permet de stocker l'information	
char* stockage_info(char* tmp, char caractere,FILE* fichier){

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
	return tmp;
}

//Fonction qui détecte le type de ligne
Type_ligne detecter_type(char *col2, char* col3){
	
	//ligne non détectée
	if(col2 == NULL || col3 == NULL){
		return INCONNU;
    }

	//ligne SOURCE->USINE (captage)
    if((strstr(col2, "Spring") || strstr(col2, "Well") || strstr(col2, "Resurgence") || strstr(col2, "Source") || strstr(col2, "Fountain")) && (strstr(col3, "Plant") || strstr(col3, "Module") || strstr(col3, "Unit"))){
		return SOURCE_USINE;
    }

	//ligne USINE
    if((strstr(col2, "Plant") || strstr(col2, "Module") || strstr(col2, "Unit")) && col3[0] == '-'){
        return USINE;
    }

	//ligne USINE->STOCKAGE (stockage)
    if((strstr(col2, "Plant") || strstr(col2, "Module") || strstr(col2, "Unit")) && strstr(col3, "Storage")){
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

Ligne stockage_ligne(FILE* fichier){
	
	// variables locales
	Ligne ligne;
	
	//Stocke les informations dans les champs correspondants	
	ligne.col1=stockage_info(ligne.col1,';',fichier);
	ligne.col2=stockage_info(ligne.col2,';',fichier);
	ligne.col3=stockage_info(ligne.col3,';',fichier);
	ligne.volume=stockage_info(ligne.volume,';',fichier);
	ligne.leak=stockage_info(ligne.leak,'\n',fichier);
	ligne.type = detecter_type(ligne.col2, ligne.col3);
	printf("%s %s %s %s %s %d",ligne.col1,ligne.col2,ligne.col3,ligne.volume,ligne.leak,ligne.type);
	return ligne;
	
}
