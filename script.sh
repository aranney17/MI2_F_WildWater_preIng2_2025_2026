#!/bin/bash
set -e

# Vérification argument
if [ $# -ne 1 ]; then
  echo "Usage: $0 {max|src|reel}"
	exit 1
fi

# Choix du fichier
case "$1" in
	max)
	  CSV="vol_max.csv"
	  ;;
  src)
      CSV="vol_captation.csv"
      ;;
  reel)
      CSV="vol_traitement.csv"
      ;;
  *)
      echo "Argument invalide : $1"
      echo "Utiliser : max, src ou reel"
      exit 1
      ;;
esac

# Tri par volume
sort -t';' -k2,2n "$CSV" > vol_trie.csv

# Extraction
head -n 51 vol_trie.csv > petites.csv
tail -n 10 vol_trie.csv > grandes.csv

# Gnuplot
gnuplot -e "infile='petites.csv'; outfile='50_petites_${1}.png'" histo.gp
gnuplot -e "infile='grandes.csv'; outfile='10_grandes_${1}.png'" histo.gp

echo "Histogrammes générés pour $1"


