#include "arbre.h"
#include "lecture_ligne.h"

//Fonction qui crée un noeud de l'arbre fuite
Arbre_fuite* creerArbreFuite(char*identifiant, double vol){
    Arbre_fuite* nv = malloc(sizeof(Arbre_fuite));
    if(nv==NULL){
        printf("Allocation échouée");
        exit(1);
    }
    nv->id=strdup(identifiant);
    nv->volume=vol;
    nv->fils = NULL;
    return nv;
}

//Fonction qui crée un chaînon dans la liste chaînée 
Chainon* creerChainon(Arbre_fuite* enfant, double fuite){
    Chainon* c=malloc(sizeof(Chainon));
    if(c==NULL){
        printf("Allocation échouée");
        exit(1);
    }
    c->noeud=enfant;
    c->fuite = fuite;
    c->suivant=NULL;
    return c;
}

//Procédure qui ajoute un chaînon au début de la liste chaînée
void ajouterFils(Arbre_fuite* parent, Arbre_fuite* enfant, double fuite){
    Chainon* nv=creerChainon(enfant,fuite);
    nv->suivant=parent->fils;
    parent->fils=nv;
}

//Fonction qui compte le nombre de fils d'un noeud donc le nombre d'élément dans la liste chaînée
int nbFils(Arbre_fuite* noeud){
    int nb=0;
    Chainon* p=noeud->fils;
    while(p!=NULL){
        nb++;
        p=p->suivant;
    }
    return nb;
}

//Fonction qui remplit l'AVL et l'arbre des fuites
AVL_fuites* remplissage_arbre(const char* fichier_donnees){

    //Ouverture du fichier
    char buffer[255];
    FILE* fichier = fopen(fichier_donnees,"r");
    if(fichier == NULL){
        exit(1);
    }

    //variables locales
    Ligne ligne;
    
    AVL_fuites* avl_fuites=NULL;
    int h= 0;
    AVL_fuites* parent;
    AVL_fuites* enfant;
    Arbre_fuite* parent_arbre;
    Arbre_fuite* enfant_arbre;

    while(fgets(buffer, sizeof(buffer), fichier)){
        //Stocke les champs de la ligne
        ligne = stockage_ligne(buffer);
            
            parent = rechercheAVLfuites(avl_fuites, ligne.col2);
            //si le noeud amont n'existe pas dans l'AVL des fuites
            if(parent==NULL){
                parent_arbre=creerArbreFuite(ligne.col2,ligne.volume);
                avl_fuites=insertionAVLfuites(avl_fuites, parent_arbre->id, parent_arbre, &h);
            }
            //s'il existe 
            else{
                parent_arbre=parent->elmt;
            }

            enfant = rechercheAVLfuites(avl_fuites, ligne.col3);
            //si le noeud aval n'existe pas dans l'AVL des fuites
            if(enfant==NULL){
                enfant_arbre=creerArbreFuite(ligne.col3,ligne.volume);
                avl_fuites=insertionAVLfuites(avl_fuites, enfant_arbre->id, enfant_arbre, &h);
            }
            //s'il existe
            else{
                enfant_arbre=enfant->elmt;
            }
            //Ajout d'un élément dans la liste des enfants du parent
            ajouterFils(parent_arbre,enfant_arbre,ligne.pertes);
        
    } 
    fclose(fichier);
    return avl_fuites;   
}
