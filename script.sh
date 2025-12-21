#!/bin/bash
set -e

# Mesure du temps
START=$(date +%s%3N)

# Vérification nombre d’arguments
if [ $# -lt 2 ]; then
    echo "Erreur : arguments insuffisants"
    echo "Usage : $0 <datafile> {histo|leaks} [options]"
    exit 1
fi

if [ $# -gt 3 ]; then
    echo "Erreur : trop d’arguments"
    exit 1
fi

# Récupération des arguments
DATAFILE="$1"
COMMAND="$2"
OPTION="$3"

# Vérification fichier de données
if [ ! -f "$DATAFILE" ]; then
    echo "Erreur : fichier de données introuvable : $DATAFILE"
    exit 1
fi

# Compilation du programme C si nécessaire
EXEC="./wildwater"

if [ ! -x "$EXEC" ]; then
    echo "Compilation du programme C..."
    #gcc -Wall -Wextra -o wildwater main.c
    make
fi

# Traitement des commandes
case "$COMMAND" in

    histo)
        # histo nécessite 3 arguments
        if [ $# -ne 3 ]; then
            echo "Erreur : histo nécessite un argument {max|src|real}"
            exit 1
        fi

	case "$OPTION" in
            max)
        	DAT="vol_max"
        	;;
    	    src)
        	DAT="vol_captation"
        	;;
    	    real)
        	DAT="vol_traitement"
        	;;
            *)
                echo "Erreur : option histo invalide ($OPTION)"
                echo "Options possibles : max | src | real"
                exit 1
                ;;
        esac

        # Appel programme C
        "$EXEC" "$DATAFILE" histo "$OPTION"
        RET=$?
        if [ $RET -ne 0 ]; then
            echo "Erreur : le programme C a échoué"
            exit 1
        fi

	# Tri par volume max
	tail -n +2 vol_max.dat | sort -t';' -k2,2n > vol_max_trie.dat

	# Sélection des identifiants
	head -n 50 vol_max_trie.dat | cut -d';' -f1 > ids_petites.txt
	tail -n 10 vol_max_trie.dat | cut -d';' -f1 > ids_grandes.txt

	filtrer_par_ids() {
    		local ids="$1"
    		local src="$2"
		local out="$3"

    	awk -F';' 'NR==FNR {ids[$0]; next} ($1 in ids)' "$ids" "$src" > "$out"
	}

	SRC_FILE="${DAT}.dat"

	filtrer_par_ids ids_petites.txt "$SRC_FILE" "petites_${DAT}.dat"
	filtrer_par_ids ids_grandes.txt "$SRC_FILE" "grandes_${DAT}.dat"


	# Générer histogrammes avec gnuplot
	gnuplot -e "infile='petites_${DAT}.dat'; outfile='petites_${DAT}.png'; mode='${OPTION}'" histo.gp
	gnuplot -e "infile='grandes_${DAT}.dat'; outfile='grandes_${DAT}.png'; mode='${OPTION}'" histo.gp

	echo "Histogrammes générés pour $1"
	;;
    leaks)
        # leaks nécessite 3 arguments
        if [ $# -ne 3 ]; then
            echo "Erreur : leaks nécessite un identifiant d’usine"
            exit 1
        fi

        "$EXEC" "$DATAFILE" leaks "$OPTION"
        RET=$?
        if [ $RET -ne 0 ]; then
            echo "Erreur : le programme C a échoué"
            exit 1
        fi
        ;;

    *)
        echo "Erreur : commande inconnue ($COMMAND)"
        echo "Commandes possibles : histo | leaks"
        exit 1
        ;;
esac

# Affichage du temps total en millisecondes
END=$(date +%s%3N)
DURATION=$((END - START))

echo "Durée totale du script : ${DURATION} millisecondes"

