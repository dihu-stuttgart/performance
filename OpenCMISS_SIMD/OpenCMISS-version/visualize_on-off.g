reset

set terminal png size 1200 , 960 enhanced linewidth 4 20
set output 'Results_on-off.png'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "Difference of vectorizing inductory loops (or not)."
set xlabel "Number Of Cells"
set ylabel "runtime"


# Achsen:
# set logscale x
# set logscale y

# Legende entfernen:
# unset key
set key left top

# with:w (lines, points)
# linetype: lt  (-1 ,  5)
# linewidth: lw (0.5,3.5)
# linecolor:    (0  ,  6)
# pointtype     (0  ,  6)
# pointsize     (0:0.5:3)

# plotten mit Titeln für die Legende
plot 'sse2_off.dat' u 4:5 smooth unique w lines linecolor 0 lw 0.5 lt 1 t "SSE2",\
     'sse3_off.dat' u 4:5 smooth unique w lines linecolor 1 lw 0.5 lt 1 t "SSE3",\
     'avx_off.dat'  u 4:5 smooth unique w lines linecolor 2 lw 0.5 lt 1 t "AVX",\
     'avx2_off.dat' u 4:5 smooth unique w lines linecolor 3 lw 0.5 lt 1 t "AVX2",\
     'sse2_on.dat' u 4:5 smooth unique w lines linecolor 0 lw 0.5 lt 0 t "SSE2 on",\
     'sse3_on.dat' u 4:5 smooth unique w lines linecolor 1 lw 0.5 lt 0 t "SSE3 on",\
     'avx_on.dat'  u 4:5 smooth unique w lines linecolor 2 lw 0.5 lt 0 t "AVX on",\
     'avx2_on.dat' u 4:5 smooth unique w lines linecolor 3 lw 0.5 lt 0 t "AVX2 on"
     #'sse2_off.dat' u 4:6 smooth unique w lines linecolor 0 lw 0.5 lt 2 t "SSE2 p1",\
     #'sse2_off.dat' u 4:7 smooth unique w lines linecolor 0 lw 0.5 lt 3 t "SSE2 p2",\
     #'sse3_off.dat' u 4:6 smooth unique w lines linecolor 1 lw 0.5 lt 1 t "SSE3",\
set output
set terminal pop
