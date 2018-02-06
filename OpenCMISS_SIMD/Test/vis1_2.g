reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Test1_2.png'
set terminal postscript eps enhanced color font 'Helvetica,14' dashed
set output 'Result_Test1_2.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "Percentage of Elapsed Time of code kernels for different implementations. With and without (T0) vectorization."
set xlabel "Number Of Cells"
set ylabel "Portion of elapsed time[%]"


# Achsen:
 set logscale x
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
plot 'OCV_V1.dat1'  u 3:($9/($17-$27-$29)*100) smooth unique w lines linecolor 0 lw 2.0 lt 5 t "State evo. (9), OpenCMISS",\
     'OCV_V0.dat1'  u 3:($9/($17-$27-$29)*100) smooth unique w lines linecolor 1 lw 2.0 lt 5 t "OpenCMISS T0",\
     'V-1_V1.dat1'  u 3:($9/($17-$27-$29)*100) smooth unique w lines linecolor 2 lw 2.0 lt 5 t "{/Symbol a}-Version",\
     'V-1_V0.dat1'  u 3:($9/($17-$27-$29)*100) smooth unique w lines linecolor 3 lw 2.0 lt 5 t "D",\
     'V-4_V1.dat1'  u 3:($9/($17-$27-$29)*100) smooth unique w lines linecolor 4 lw 2.0 lt 5 t "{/Symbol b}-Version",\
     'OCV_V1.daat1'  u 3:($9/($17-$27-$29)*100) w points linecolor 0 pointsize 1.0 pointtype 4 t "P1",\
     'V-4_V1.daat1'  u 3:($9/($17-$27-$29)*100) w points linecolor 4 pointsize 1.0 pointtype 4 notitle,\
     'V-4_V0.dat1'  u 3:($9/($17-$27-$29)*100) smooth unique w lines linecolor 5 lw 2.0 lt 5 t "O",\
     'OCV_V1.dat1'  u 3:($13/($17-$27-$29)*100) smooth unique w lines linecolor 0 lw 2.0 lt 4 t "RHS setup (13)",\
     'OCV_V1.dat1'  u 3:($15/($17-$27-$29)*100) smooth unique w lines linecolor 0 lw 1.5 lt 3 t "RHS rate eval (15)",\
     'OCV_V0.dat1'  u 3:($13/($17-$27-$29)*100) smooth unique w lines linecolor 1 lw 2.0 lt 4 notitle,\
     'OCV_V0.dat1'  u 3:($15/($17-$27-$29)*100) smooth unique w lines linecolor 1 lw 1.5 lt 3 notitle,\
     'V-1_V1.dat1'  u 3:($13/($17-$27-$29)*100) smooth unique w lines linecolor 2 lw 2.0 lt 4 notitle,\
     'V-1_V1.dat1'  u 3:($15/($17-$27-$29)*100) smooth unique w lines linecolor 2 lw 1.5 lt 3 notitle,\
     'V-1_V0.dat1'  u 3:($13/($17-$27-$29)*100) smooth unique w lines linecolor 3 lw 2.0 lt 4 notitle,\
     'V-1_V0.dat1'  u 3:($15/($17-$27-$29)*100) smooth unique w lines linecolor 3 lw 1.5 lt 3 notitle,\
     'V-4_V1.dat1'  u 3:($13/($17-$27-$29)*100) smooth unique w lines linecolor 4 lw 2.0 lt 4 notitle,\
     'V-4_V1.dat1'  u 3:($15/($17-$27-$29)*100) smooth unique w lines linecolor 4 lw 1.5 lt 3 notitle,\
     'OCV_V1.daat1'  u 3:($13/($17-$27-$29)*100) w points linecolor 0 pointsize 1.0 pointtype 2 notitle,\
     'OCV_V1.daat1'  u 3:($15/($17-$27-$29)*100) w points linecolor 0 pointsize 1.0 pointtype 3 notitle,\
     'V-4_V1.daat1'  u 3:($13/($17-$27-$29)*100) w points linecolor 4 pointsize 1.0 pointtype 2 notitle,\
     'V-4_V1.daat1'  u 3:($15/($17-$27-$29)*100) w points linecolor 4 pointsize 1.0 pointtype 3 notitle,\
     'V-4_V0.dat1'  u 3:($13/($17-$27-$29)*100) smooth unique w lines linecolor 5 lw 2.0 lt 4 notitle,\
     'V-4_V0.dat1'  u 3:($15/($17-$27-$29)*100) smooth unique w lines linecolor 5 lw 1.5 lt 3 notitle
#     'OCV_V1.dat1'  u 3:(100-(($9+$13+$15)/($17-$27-$29)*100)) smooth unique w lines linecolor 0 lw 1.5 lt 0 t "OC1, other",\
#     'OCV_V0.dat1'  u 3:(100-(($9+$13+$15)/($17-$27-$29)*100)) smooth unique w lines linecolor 1 lw 1.5 lt 0 t "OC0, other",\
#     'V-1_V1.dat1'  u 3:(100-(($9+$13+$15)/($17-$27-$29)*100)) smooth unique w lines linecolor 2 lw 1.5 lt 0 t "Vs1, other",\
#     'V-1_V0.dat1'  u 3:(100-(($9+$13+$15)/($17-$27-$29)*100)) smooth unique w lines linecolor 3 lw 1.5 lt 0 t "Vs0, other"
set output
set terminal pop
