reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Test1_5.png'
set terminal postscript eps enhanced color font 'Helvetica,14' dashed
set output 'Result_Test1_5.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "Memory Consumption of different Implementations, using Euler. (All vectorized)"
set xlabel "Number of Cells"
set ylabel "[MB]"


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

# plotten mit Titeln für die Legende        bewusst ohne T0
plot 'V-4_V1.dat1'  u 3:($19/1000) smooth unique w lines linecolor 0 lw 1.5 lt 1 t "Memory (19)",\
     'OCV_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 0 lw 2.0 lt 5 t "Used (23), OpenCMISS",\
     'V-1_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 2 lw 2.0 lt 5 t "{/Symbol a}-Version",\
     'V-4_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 4 lw 2.0 lt 5 t "{/Symbol b}-Version",\
     'Cache_Size.datX' u 1:2 w lines linecolor 1 lw 2.0 lt 1 t "System L3-Cache Size"#,\
#     'V-4_V1.daat1'  u 3:($23/1000) w points linecolor 4 pointsize 2.0 pointtype 1 t "1 Proseccor only",\
#     'Cache_Size.datX' u 3:4 w lines linecolor 1 lw 2.0 lt 0 t "L2",\
#     'Cache_Size.datX' u 5:6 w lines linecolor 1 lw 2.0 lt 2 t "L1"
#plot 'OCV_V1.dat1'  u 3:($19/1000) smooth unique w lines linecolor 0 lw 1.5 lt 1 t "Memory (19)",\
#     'OCV_V0.dat1'  u 3:($19/1000) smooth unique w lines linecolor 1 lw 0.5 lt 1 t "OpenCMISS T0",\
#     'V-1_V1.dat1'  u 3:($19/1000) smooth unique w lines linecolor 2 lw 0.5 lt 1 t "{/Symbol a}-Version",\
#     'V-1_V0.dat1'  u 3:($19/1000) smooth unique w lines linecolor 3 lw 0.5 lt 1 t "D",\
#     'V-4_V1.dat1'  u 3:($19/1000) smooth unique w lines linecolor 4 lw 0.5 lt 1 t "{/Symbol b}-Version",\
#     'V-4_V0.dat1'  u 3:($19/1000) smooth unique w lines linecolor 5 lw 0.5 lt 1 t "O",\
#     'OCV_V1.dat1'  u 3:($21/1000) smooth unique w lines linecolor 0 lw 2.0 lt 4 t "Free (21)",\
#     'OCV_V0.dat1'  u 3:($21/1000) smooth unique w lines linecolor 1 lw 2.0 lt 4 notitle,\
#     'V-1_V1.dat1'  u 3:($21/1000) smooth unique w lines linecolor 2 lw 2.0 lt 4 notitle,\
#     'V-1_V0.dat1'  u 3:($21/1000) smooth unique w lines linecolor 3 lw 2.0 lt 4 notitle,\
#     'V-4_V1.dat1'  u 3:($21/1000) smooth unique w lines linecolor 4 lw 2.0 lt 4 notitle,\
#     'V-4_V0.dat1'  u 3:($21/1000) smooth unique w lines linecolor 5 lw 2.0 lt 4 notitle,\
 #    'OCV_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 0 lw 2.0 lt 1 t "Used (23)",\
 #    'OCV_V0.dat1'  u 3:($23/1000) smooth unique w lines linecolor 1 lw 2.0 lt 1 notitle,\
 #    'V-1_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 2 lw 2.0 lt 1 notitle,\
 #    'V-1_V0.dat1'  u 3:($23/1000) smooth unique w lines linecolor 3 lw 2.0 lt 1 notitle,\
 #    'V-4_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 4 lw 2.0 lt 1 notitle,\
 #    'V-4_V0.dat1'  u 3:($23/1000) smooth unique w lines linecolor 5 lw 2.0 lt 1 notitle,\
 #    'Cache_Size.datX' u 1:2 w lines linecolor 1 lw 2.0 lt 1 t "System Cache Size"
set output
set terminal pop