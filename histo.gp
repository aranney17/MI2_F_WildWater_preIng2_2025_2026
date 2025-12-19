set terminal png size 1200,600
set output "histogramme_source.png"
set datafile separator ";"

# Style histogramme
set style data histograms
set style fill solid 1.0 border -1   # Rempli complètement avec bordure automatique
set boxwidth 0.8
set xtics rotate by -45

# Tracer le fichier
plot "vol_captation.dat" using 2:xtic(1) title ""
