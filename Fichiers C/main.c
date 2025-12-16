int main(){
	
	//Gestion du fichier
	FILE* fichier=NULL;
	fichier=fopen("c-wildwater_v0(1).dat","r+");
	if (fichier==NULL ){
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	
	Ligne ligne;
	ligne=stockage_ligne(fichier);
	return 0;
}
