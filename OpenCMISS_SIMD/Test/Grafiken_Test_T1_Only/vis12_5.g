reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Test12_5.png'
set terminal postscript eps enhanced color font 'Helvetica,18' dashed
set output 'Result_Test12_5.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "Memory Consumption of different Implementations"
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

# plotten mit Titeln für die Legende
plot 'Data/V-4_V1.dat1'  u 3:($19/1000) smooth unique w lines linecolor 0 lw 1.5 lt 1 t "Total System Memory",\
     'Data/OCV_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 0 lw 2.0 lt 5 t "Used, Euler, OpenCMISS",\
     'Data/V-1_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 2 lw 2.0 lt 5 t "{/Symbol a}-Version",\
     'Data/V-4_V1.dat1'  u 3:($23/1000) smooth unique w lines linecolor 4 lw 2.0 lt 5 t "{/Symbol b}-Version",\
     'Data/OCV_V1.dat2'  u 3:($23/1000) smooth unique w lines linecolor 0 lw 2.0 lt 0 t "Used, Heun",\
     'Data/V-1_V1.dat2'  u 3:($23/1000) smooth unique w lines linecolor 2 lw 2.0 lt 0 notitle,\
     'Data/V-4_V1.dat2'  u 3:($23/1000) smooth unique w lines linecolor 4 lw 2.0 lt 0 notitle,\
     'Data/Cache_Size.datX' u 1:2 w lines linecolor 1 lw 2.0 lt 1 t "System L3-Cache Size"#,\
#     'Data/Cache_Size.datX' u 3:4 w lines linecolor 1 lw 2.0 lt 0 t "L2",\
#     'Data/Cache_Size.datX' u 5:6 w lines linecolor 1 lw 2.0 lt 2 t "L1"
set output
set terminal pop