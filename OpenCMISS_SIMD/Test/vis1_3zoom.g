reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Test1_3zoom.png'
set terminal postscript eps enhanced color font 'Helvetica,22' dashed
set output 'Result_Test1_3zoom.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "CPU Time portions. Zoom into State Evolution."
set xlabel "Number of Cells"
set ylabel "Runtime per Cell [s]"


# Achsen:
 set logscale x
# set logscale y
set yrange [0:0.00025]

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
# RAM reading time bias: 29 in numerics (affects NOT the numerics measurements)

# plotten mit Titeln für die Legende
plot 'OCV_V1.dat1'  u 3:($9/($3)*100) smooth unique w lines linecolor 0 lw 2.0 lt 5 t "State evo. (9), OpenCMISS",\
     'V-1_V1.dat1'  u 3:($9/($3)*100) smooth unique w lines linecolor 2 lw 2.0 lt 5 t "{/Symbol a}-Version",\
     'V-1_V0.dat1'  u 3:($9/($3)*100) smooth unique w lines linecolor 3 lw 2.0 lt 5 t "D",\
     'V-4_V1.dat1'  u 3:($9/($3)*100) smooth unique w lines linecolor 4 lw 2.0 lt 5 t "{/Symbol b}-Version",\
     'OCV_V1.daat1'  u 3:($9/($3)*100) w points linecolor 0 pointsize 1.0 pointtype 4 t "P1",\
     'V-4_V1.daat1'  u 3:($9/($3)*100) w points linecolor 4 pointsize 1.0 pointtype 4 notitle,\
     'V-1_V1.daat1'  u 3:($9/($3)*100) w points linecolor 2 pointsize 1.0 pointtype 4 notitle,\
     'V-4_V0.dat1'  u 3:($9/($3)*100) smooth unique w lines linecolor 5 lw 2.0 lt 5 t "O"
#     'OCV_V0.dat1'  u 3:($9/($3)*100) smooth unique w lines linecolor 1 lw 2.0 lt 5 t "OpenCMISS T0",\
set output
set terminal pop