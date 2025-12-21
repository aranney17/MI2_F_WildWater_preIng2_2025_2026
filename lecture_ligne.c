#include "lecture_ligne.h"

	
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
}

//Fonction qui détecte le type de ligne
Type_ligne detecter_type(char *col2, char* col3){
        if(col2 == NULL || col3 == NULL){
                return INCONNU;
        }
        if((strstr(col2, "Spring") || strstr(col2, "Well") || strstr(col2, "Resurgence")) && (strstr(col3, "Plant") || strstr(col3, "Module") || strstr(col3, "Unit"))){
                return SOURCE_USINE;
        }
        if((strstr(col2, "Plant") || strstr(col2, "Module") || strstr(col2, "Unit")) && col3[0] == '-'){
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

Type_ligne detecter_type(char* col1, char *col2, char* col3){
        if(col2 == NULL || col3 == NULL){
                return INCONNU;
        }
        if(col1[0] == '-' && col2[0] != '-' && col3[0] != '-' ){
                return SOURCE_USINE;
        }
        if(col1[0] == '-' && col2[0] != '-' && col3[0] == '-'){
                return USINE;
        }
        if(col1[0] == '-' && col2[0] != '-' && strstr(col3, "Storage")){
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
	//printf("%s %s %s %s %s %d",ligne.col1,ligne.col2,ligne.col3,ligne.volume,ligne.leak,ligne.type);
	return ligne;

}*/

Type_ligne detecter_type(char* col1, char* col2, char* col3){
    if(!col1 || !col2 || !col3){
        return INCONNU;
    }

    if(col1[0] == '-' && col2[0] != '-' && col3[0] == '-'){
        return USINE;
    }

    if(col1[0] == '-' && col2[0] != '-' && !strstr(col3, "Storage") && col3[0] != '-'){
        return SOURCE_USINE;
    }

    return INCONNU;
}

/*
int est_tiret(const char* s){
    if(!s) return 0;
    while(*s == ' ') s++;
    return (strcmp(s, "-") == 0);
}



Type_ligne detecter_type(char* col1, char* col2, char* col3){
    if(!col1 || !col2 || !col3){
        return INCONNU;
    }

    int c1_tiret = est_tiret(col1);
    int c2_tiret = est_tiret(col2);
    int c3_tiret = est_tiret(col3);

    // Déclaration d’une usine 
    if(c1_tiret && !c2_tiret && c3_tiret){
        return USINE;
    }

    // Source → Usine 
    if(c1_tiret && !c2_tiret && !c3_tiret){
        return SOURCE_USINE;
    }

    return INCONNU;
}*/

void nettoyer(char *s){
    if(!s) return;
    char *p = s;
    while(*p){
        if(*p == '\n' || *p == '\r'){
            *p = '\0';
            return;
        }
        p++;
    }
}

/*Type_ligne detecter_type(char* col1, char* col2, char* col3){
    if(!col1 || !col2 || !col3){
        return INCONNU;
    }

    // SOURCE -> USINE 
    if(col1[0] == '-' && col2[0] != '-' && col3[0] != '-'){
        return SOURCE_USINE;
    }

    // USINE seule
    if(col1[0] == '-' && col2[0] != '-' && col3[0] == '-'){
        return USINE;
    }

    // USINE -> STOCKAGE
    if(col1[0] == '-' && col2[0] != '-' && col3[0] != '-' ){
        return USINE_STOCKAGE;
    }

    // STOCKAGE -> JONCTION
    if(col1[0] != '-' && col2[0] != '-' && col3[0] != '-'){
        return STOCKAGE_JONCTION;
    }

    return INCONNU;
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
	nettoyer(ligne.col1);

        tmp = strtok(NULL, ";");
        if(tmp != NULL){
                strcpy(ligne.col2, tmp);
				//printf("COL2 = [%s]\n", ligne.col2);
        }
        else{
                strcpy(ligne.col2, "");
				//printf("COL2 = [%s]\n", ligne.col2);
        }
	nettoyer(ligne.col2);
        tmp = strtok(NULL, ";");
        if(tmp != NULL){
                strcpy(ligne.col3, tmp);
        }
        else{
                strcpy(ligne.col3, "");
        }
	nettoyer(ligne.col3);

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

        ligne.type = detecter_type(ligne.col1,ligne.col2, ligne.col3);

        return ligne;
}
