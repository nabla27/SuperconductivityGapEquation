set xrange [0:1.2]
set yrange [0:1.8]

set bmargin 4

set xlabel "T/Tc" font "Arial,16"
set ylabel "{/Symbol d}" font "Arial,16"

plot "gap.csv" using 1:2