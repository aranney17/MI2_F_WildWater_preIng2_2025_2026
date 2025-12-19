#include "lecture_CSV.h"

	
// procédure qui permet de stocker l'information	
/*char* stockage_info(char* tmp, char caractere,FILE* fichier){

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
}*/

//Fonction qui détecte le type de ligne
Type_ligne detecter_type(char *col2, char* col3){
        if(col2 == NULL || col3 == NULL){
                return INCONNU;
        }
        if((strstr(col2, "Spring") || strstr(col2, "Well") || strstr(col2, "Resurgence")) && (strstr(col3, "Plant") || strstr(col3, "Module") || strstr(col3, "Unit"))){
                return SOURCE_USINE;
        }
        if((strstr(col2, "Plant") || strstr(col2, "Module")) && col3[0] == '-'){
                return USINE;
        }
        if((strstr(col2, "Plant") || strstr(col2, "Module") || strstr(col2, "Unit")) && strstr(col3, "Storage")){
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

/*Ligne stockage_ligne(FILE* fichier){
	
	// variables locales
	Ligne ligne;
	
	//Stocke les informations dans les champs correspondants	
	ligne.col1=stockage_info(ligne.col1,';',fichier);
	ligne.col2=stockage_info(ligne.col2,';',fichier);
	ligne.col3=stockage_info(ligne.col3,';',fichier);
	ligne.volume=stockage_info(ligne.volume,';',fichier);
	ligne.leak=stockage_info(ligne.leak,'\n',fichier);
	ligne.type = detecter_type(ligne.col2, ligne.col3);
	//printf("%s %s %s %s %s %d",ligne.col1,ligne.col2,ligne.col3,ligne.volume,ligne.leak,ligne.type);
	return ligne;
	
}*/

Ligne stockage_ligne(char* buffer){
	if(buffer == NULL){
		exit(1);
	}
        Ligne ligne;
        char* tmp;

        tmp = strtok(buffer, ";");
        if(tmp != NULL){
                strcpy(ligne.col1, tmp);
        }
        else{
                strcpy(ligne.col1, "");
        }

        tmp = strtok(NULL, ";");
        if(tmp != NULL){
                strcpy(ligne.col2, tmp);
				//printf("COL2 = [%s]\n", ligne.col2);
        }
        else{
                strcpy(ligne.col2, "");
				//printf("COL2 = [%s]\n", ligne.col2);
        }
        tmp = strtok(NULL, ";");
        if(tmp != NULL){
                strcpy(ligne.col3, tmp);
        }
        else{
                strcpy(ligne.col3, "");
        }
        tmp = strtok(NULL, ";");
        if(tmp != NULL){
                ligne.volume = atof(tmp);
        }
        else{
                ligne.volume = 0;
        }
        tmp = strtok(NULL, ";");
        if(tmp != NULL){
                ligne.pertes = atof(tmp);
        }
        else{
                ligne.pertes = 0;
	 }

        ligne.type = detecter_type(ligne.col2, ligne.col3);

        return ligne;
}

