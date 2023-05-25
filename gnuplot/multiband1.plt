set xrange [0:1.2]
set yrange [0:2.3]

set bmargin 4

set xlabel "T/Tc" font "Arial,16"
set ylabel "C/{/Symbol g}T" font "Arial,16"

set key font "Arial, 16"
set key left top

ratio1 = 65.0 / (65.0 + 35.0)
ratio2 = 35.0 / (65.0 + 35.0)

set label 1 "{/Symbol D}_{1} : {/Symbol D}_{2} = 1.76 : 0.7" at 0.07, 1.7 font "Arial, 16"
set label 2 "{/Symbol g}_{1} : {/Symbol g}_{2} = 65 : 35" at 0.07, 1.5 font "Arial, 16"

plot "heatCapacityAll.csv" using 1:($3 * ratio1) with lines title "C_{1}*{/Symbol g}_{1}/({/Symbol g}_{1} + {/Symbol g}_{2})" \
, "heatCapacityAll.csv" using 1:($5 * ratio2) with lines title "C_{2}*{/Symbol g}_{1}/({/Symbol g}_{1} + {/Symbol g}_{2})" \
, "heatCapacityAll.csv" using 1:($3 * ratio1 + $5 * ratio2) with linespoints title "C_{e}"
