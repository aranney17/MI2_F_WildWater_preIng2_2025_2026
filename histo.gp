set terminal png size 1200,600
set output outfile

set datafile separator ";"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
set xtics rotate by -45
set key off

plot infile using 2:xtic(1)
