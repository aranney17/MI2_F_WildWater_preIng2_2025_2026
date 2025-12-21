# ---------- Paramètres généraux ----------
set terminal png size 1400,700
set output outfile
set datafile separator ";"

set style data histograms
set style histogram clustered gap 1
set style fill solid 0.8 border -1
set boxwidth 0.9

set xtics rotate by -45 font ",8"
set grid ytics
unset key

# ---------- Titres & labels selon le mode ----------
if (mode eq "max") {
    set title "Capacité maximale des usines"
    set ylabel "Volume maximal (M.m³.year⁻¹)"
}
if (mode eq "src") {
    set title "Volume total capté par les usines"
    set ylabel "Volume capté (M.m³.year⁻¹)"
}
if (mode eq "real") {
    set title "Volume réellement traité par les usines"
    set ylabel "Volume traité (M.m³.year⁻¹)"
}

set xlabel "Identifiant de l'usine"

# ---------- Tracé ----------
plot infile using 2:xtic(1) title ""
