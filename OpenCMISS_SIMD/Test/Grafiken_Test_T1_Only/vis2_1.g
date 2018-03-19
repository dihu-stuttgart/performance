reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Test2_1.png'
set terminal postscript eps enhanced color font 'Helvetica,14' dashed
set output 'Result_Test2_1.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "Time spent in code kernels for different implementations"
set xlabel "Number Of Cells"
set ylabel "Time [s]"

# Achsen:
 set logscale x
 set logscale y

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
plot 'Data/OCV_V1.dat2' u 3:($17-$27-$29) smooth unique w lines linecolor 0 lw 1.5 lt 1 t "Elapsed time, OpenCMISS",\
     'Data/OCV_V0.dat2' u 3:($17-$27-$29) smooth unique w lines linecolor 1 lw 1.5 lt 1 t "OpenCMISS T0",\
     'Data/V-1_V1.dat2' u 3:($17-$27-$29) smooth unique w lines linecolor 2 lw 1.5 lt 1 t "{/Symbol a}-Version",\
     'Data/V-1_V0.dat2' u 3:($17-$27-$29) smooth unique w lines linecolor 3 lw 1.5 lt 1 t "D",\
     'Data/V-4_V1.dat2' u 3:($17-$27-$29) smooth unique w lines linecolor 4 lw 1.5 lt 1 t "{/Symbol b}-Version",\
     'Data/V-4_V0.dat2' u 3:($17-$27-$29) smooth unique w lines linecolor 5 lw 1.5 lt 1 t "O",\
     'Data/OCV_V1.dat2' u 3:9 smooth unique w lines linecolor 0 lw 2.0 lt 5 t "State evolution (9)",\
     'Data/OCV_V1.dat2' u 3:13 smooth unique w lines linecolor 0 lw 2.0 lt 4 t "RHS setup (13)",\
     'Data/OCV_V1.dat2' u 3:15 smooth unique w lines linecolor 0 lw 1.5 lt 3 t "RHS rate evaluation (15)",\
     'Data/OCV_V0.dat2' u 3:9 smooth unique w lines linecolor 1 lw 2.0 lt 5 notitle,\
     'Data/OCV_V0.dat2' u 3:13 smooth unique w lines linecolor 1 lw 2.0 lt 4 notitle,\
     'Data/OCV_V0.dat2' u 3:15 smooth unique w lines linecolor 1 lw 1.5 lt 3 notitle,\
     'Data/V-1_V1.dat2' u 3:9 smooth unique w lines linecolor 2 lw 2.0 lt 5 notitle,\
     'Data/V-1_V1.dat2' u 3:13 smooth unique w lines linecolor 2 lw 2.0 lt 4 notitle,\
     'Data/V-1_V1.dat2' u 3:15 smooth unique w lines linecolor 2 lw 1.5 lt 3 notitle,\
     'Data/V-1_V0.dat2' u 3:9 smooth unique w lines linecolor 3 lw 2.0 lt 5 notitle,\
     'Data/V-1_V0.dat2' u 3:13 smooth unique w lines linecolor 3 lw 2.0 lt 4 notitle,\
     'Data/V-1_V0.dat2' u 3:15 smooth unique w lines linecolor 3 lw 1.5 lt 3 notitle,\
     'Data/V-4_V1.dat2' u 3:9 smooth unique w lines linecolor 4 lw 2.0 lt 5 notitle,\
     'Data/V-4_V1.dat2' u 3:13 smooth unique w lines linecolor 4 lw 2.0 lt 4 notitle,\
     'Data/V-4_V1.dat2' u 3:15 smooth unique w lines linecolor 4 lw 1.5 lt 3 notitle,\
     'Data/V-4_V0.dat2' u 3:9 smooth unique w lines linecolor 5 lw 2.0 lt 5 notitle,\
     'Data/V-4_V0.dat2' u 3:13 smooth unique w lines linecolor 5 lw 2.0 lt 4 notitle,\
     'Data/V-4_V0.dat2' u 3:15 smooth unique w lines linecolor 5 lw 1.5 lt 3 notitle
set output
set terminal pop
