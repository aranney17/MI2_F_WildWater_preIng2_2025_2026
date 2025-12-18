#!/bin/bash
set -e

# Mesure du temps
START=$(date +%s)

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
    gcc -Wall -Wextra -o wildwater main.c
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
            max|src|real)
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

        # Génération histogrammes avec gnuplot
        gnuplot -e "mode='$OPTION'" histo.gp
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

# Affichage du temps total
END=$(date +%s)
DURATION=$((END - START))

echo "Durée totale du script : ${DURATION} secondes"



