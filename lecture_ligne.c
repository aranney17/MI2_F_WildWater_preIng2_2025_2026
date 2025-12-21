#include "lecture_ligne.h"

	/*

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

*/

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

