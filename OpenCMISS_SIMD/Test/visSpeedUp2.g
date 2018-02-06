reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Test2_SpeedUp.png'
set terminal postscript eps enhanced color font 'Helvetica,18' dashed
set output 'Result_Test2_SpeedUp.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschriftungen 
set title "Achieved Speedups for Heunintegration"
set xlabel "Number of Cells"
set ylabel "Speedup"


# Achsen:
 set logscale x
set xrange [1:10000000]
# set logscale y
set yrange [0:4]

# Legende entfernen:
# unset key
set key left top

# with:w (lines, points)
# linetype: lt  (-1 ,  5)
# linewidth: lw (0.5,3.5)
# linecolor:    (0  ,  6)
# pointtype     (0  ,  6)
# pointsize     (0:0.5:3)

# 1: Zellen N
# 2: "OCV E"
# 3: "V1 E"
# 4: "V4 E"
# 5: "Speedup 1" (euler, {/Symbol a}-Version)
# 6: "Speedup 2" ({/Symbol b}-Version)
# 7: "OCV H"
# 8: "V1 H"
# 9: "V4 H"
# 10: "Speedup 1" (heun)
# 11: "Speedup 2"

# plotten mit Titeln für die Legende
plot 'speedup.txt' u 1:10 w lines linecolor 2 lw 2.0 lt 1 t "{/Symbol a}-Version",\
     'avgHeun.datH' u 1:3 w lines linecolor 2 lw 2.0 lt 0 t "Average",\
     'speedup.txt' u 1:11 w lines linecolor 4 lw 2.0 lt 1 t "{/Symbol b}-Version",\
     'avgHeun.datH' u 1:5 w lines linecolor 4 lw 2.0 lt 0 t "Average"
set output
set terminal pop
