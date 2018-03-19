reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Test2_3b.png'
set terminal postscript eps enhanced color font 'Helvetica,22' dashed
set output 'Result_Test2_3b.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschriftungen 
set title "Elapsed Time and CPU Time" # . With and without (T0) vectorization.
set xlabel "Number of Cells"
set ylabel "Time per Cell [s]"


# Achsen:
 set logscale x
# set logscale y
set yrange [0:0.0035]

# Legende entfernen:
# unset key
set key center top

# with:w (lines, points)
# linetype: lt  (-1 ,  5)
# linewidth: lw (0.5,3.5)
# linecolor:    (0  ,  6)
# pointtype     (0  ,  6)
# pointsize     (0:0.5:3)

# VALUES               COLUMN
# total                   5
# integration             7 
# thereof_state_evolution 9 
# evaluate_L_{hs}        11 
# RHS_setup              13 
# RHS_rate_evaluation    15 
# elapsed_time:          17 
# totalRAM_[kB]:         19 
# freeBeforeMALLOC_[kB]: 21 
# used_[kB]:             23
# malloc_time:           25
# RAM reading time bias: 27 in rhs (affects numerics measurements)
# RAM reading time bias: 29 in numerics (affects NOT the numerics measurements but the elapsed time)

# plotten mit Titeln für die Legende
plot 'OCV_V1.dat2'  u 3:(($17-$27-$29)/($3)*100) smooth unique w lines linecolor 0 lw 2.0 lt 1 t "Elapsed time, OpenCMISS",\
     'V-1_V1.dat2'  u 3:(($17-$27-$29)/($3)*100) smooth unique w lines linecolor 2 lw 2.0 lt 1 t "{/Symbol a}-Version",\
     'V-1_V0.dat2'  u 3:(($17-$27-$29)/($3)*100) smooth unique w lines linecolor 3 lw 2.0 lt 1 t "D",\
     'V-4_V1.dat2'  u 3:(($17-$27-$29)/($3)*100) smooth unique w lines linecolor 4 lw 2.0 lt 1 t "{/Symbol b}-Version",\
     'V-4_V0.dat2'  u 3:(($17-$27-$29)/($3)*100) smooth unique w lines linecolor 5 lw 2.0 lt 1 t "O",\
     'OCV_V1.daat2'  u 3:(($17-$27-$29)/($3)*100) w points linecolor 0 pointsize 0.5 pointtype 1 t "P1",\
     'OCV_V1.dat2'  u 3:(($5-$27-$29)/($3)*100) smooth unique w lines linecolor 0 lw 2.5 lt 4 t "CPU clock [5]",\
     'OCV_V1.daat2'  u 3:(($5-$27-$29)/($3)*100) w points linecolor 0 pointsize 0.5 pointtype 4 t "P1",\
     'V-1_V1.dat2'  u 3:(($5-$27-$29)/($3)*100) smooth unique w lines linecolor 2 lw 2.5 lt 4 notitle,\
     'V-1_V0.dat2'  u 3:(($5-$27-$29)/($3)*100) smooth unique w lines linecolor 3 lw 2.5 lt 4 notitle,\
     'V-4_V1.dat2'  u 3:(($5-$27-$29)/($3)*100) smooth unique w lines linecolor 4 lw 2.5 lt 4 notitle,\
     'V-4_V1.daat2'  u 3:(($5-$27-$29)/($3)*100) w points linecolor 4 pointsize 0.5 pointtype 4 notitle,\
     'V-1_V1.daat2'  u 3:(($5-$27-$29)/($3)*100) w points linecolor 2 pointsize 0.5 pointtype 4 notitle,\
     'V-4_V1.daat2'  u 3:(($17-$27-$29)/($3)*100) w points linecolor 4 pointsize 0.5 pointtype 1 notitle,\
     'V-1_V1.daat2'  u 3:(($17-$27-$29)/($3)*100) w points linecolor 2 pointsize 0.5 pointtype 1 notitle,\
     'V-4_V0.dat2'  u 3:(($5-$27-$29)/($3)*100) smooth unique w lines linecolor 5 lw 2.5 lt 4 notitle
     #'OCV_V0.dat2'  u 3:(($17-$27-$29)/($3)*100) smooth unique w lines linecolor 1 lw 2.0 lt 1 t "OpenCMISS T0",\
     #'OCV_V0.dat2'  u 3:(($5-$27-$29)/($3)*100) smooth unique w lines linecolor 1 lw 2.5 lt 4 notitle,\
set output
set terminal pop
