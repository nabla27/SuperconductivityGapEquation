set xrange [0:1.2]
set yrange [0:3.5]

set bmargin 4

set xlabel "T/Tc" font "Arial,16"
set ylabel "C_{e}/{/Symbol g}T" font "Arial,16"

set key font "Arial, 16"
set key left top

plot "heatCapacity_2p100000.csv" using 1:3 with linespoints title "{/Symbol a}=2.1" \
, "heatCapacity_1p760000.csv" using 1:3 with linespoints title "{/Symbol a}=1.76" \
, "heatCapacity_1p200000.csv" using 1:3 with linespoints title "{/Symbol a}=1.2" \
, "heatCapacity_0p700000.csv" using 1:3 with linespoints title "{/Symbol a}=0.7"