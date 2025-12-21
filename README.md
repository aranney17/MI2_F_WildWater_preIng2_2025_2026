Projet WildWater:

Le projet WildWater a pour objectif d’analyser et de simuler le fonctionnement d’un réseau de distribution d’eau potable.  À partir d’un fichier de données décrivant les sources, usines, stockages, jonctions et usagers, le programme permet : de calculer les volumes d’eau captés, traités et maximaux par usine, d’analyser les pertes d’eau dans le réseau, de générer des fichiers exploitables pour la visualisation sous forme d’histogrammes, de conserver un historique des pertes par usine.
Les données sont lues depuis un fichier texte  c-wildwater_v0.dat et traitées dynamiquement à l’aide de structures de données avancées (arbres AVL et arbres de fuites).

FONCTIONNALITÉS

Le programme se lance en ligne de commande et propose deux grandes fonctionnalités :

1. Génération d’histogrammes (histo)
Permet de produire des fichiers de données pour représenter graphiquement :
Volume maximal traité par usine (max)
Volume capté par les sources (src)
Volume réellement traité après pertes (real)
Les résultats sont exportés dans des fichiers .dat et peuvent être visualisés à l’aide de gnuplot.

2. Analyse des pertes (leaks)
Calcule les pertes d’eau à partir d’une usine donnée
Parcourt le réseau en tenant compte des fuites sur chaque tronçon
Affiche le volume total perdu
Enregistre le résultat dans un fichier d’historique (rendements.dat)

ORGANISATION DU PROJET

Voici les fichiers principaux :

Un dossier Données contient le fichier de données c-wildwater_v0.dat du réseau de distribution d’eau potable. 
arbre.h : contient les prototypes des fonctions et des procédures liés à l’arbre de fuites (création et de manipulation des nœuds).

avl.h : contient les structures des arbres et des AVL et les prototypes des fonctions pour la gestion des arbres AVL (usines et arbres de fuites).

lecture_ligne.h : contient la structure Ligne et l’énumération Type_ligne et les prototypes des fonctions qui gère la lecture et l’interprétation des lignes du fichier de données.

histogramme.h : contient les prototypes des fonctions et des procédures permettant de parcourir les AVL et de générer les fichiers nécessaires aux histogrammes.

pertes.h : contient les prototypes des fonctions de calcul du rendement et de l’historique de ces calculs.

arbre.c : construit l’arbre de fuites à partir du fichier de données.

avl.c : implémente les opérations sur les arbres AVL (insertions, rotations, équilibrage).

lecture_ligne.c : analyse et stocke les lignes du fichier de données et leur type.

histogramme.c : parcourt l’AVL, calcule les volumes par usine et génère les fichiers .dat pour les histogrammes.

pertes.c : calcule les pertes d’eau récursivement dans le réseau et les écrit dans l’historique.

main.c : point d’entrée du programme, gère les arguments et appelle les fonctionnalités principales.

makefile : permet de compiler rapidement le projet.

script.sh : script Bash facilitant l’exécution du programme et la génération des histogrammes.

histo.gp : script gnuplot pour produire les histogrammes à partir des fichiers .dat.

LANCER LE PROGRAMME

1. Compiler le projet avec : make

2. Lancer le programme avec l'executable : 
Pour la génération d’histogrammes:
bash script.sh <fichier_donnees> histo {max|src|real}
Pour l’analyse des pertes:
bash script.sh <fichier_donnees> leaks <identifiant_usine>
