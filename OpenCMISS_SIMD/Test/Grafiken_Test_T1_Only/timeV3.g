reset

#set terminal png size 1200 , 960 enhanced linewidth 3 20
#set output 'Result_Time_V3.png'
set terminal postscript eps enhanced color font 'Helvetica,14' dashed
set output 'Result_Time_V3.eps'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "time measurements of beta-Version"
set xlabel "Number of Cells"
set ylabel "Value devided by elapsed time"


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
plot 'V-4_V1.dat1'  u 3:(($5-$27-$29)/($17-$27-$29)) smooth unique w lines linecolor 0 lw 2.0 lt 1 t "total (5)",\
     'V-4_V1.dat1'  u 3:($7/($17-$27-$29)) smooth unique w lines linecolor 1 lw 2.0 lt 1 t "integration             (7)",\
     'V-4_V1.dat1'  u 3:(($7+$11)/($17-$27-$29)) smooth unique w lines linecolor 1 lw 1.0 lt 1 t "+ L_{hs} eval        (11+7)",\
     'V-4_V1.dat1'  u 3:(($7+$11-$27)/($17-$27-$29)) smooth unique w lines linecolor 1 lw 1.0 lt 2 t "- getRAM (-27+11+7)",\
     'V-4_V1.dat1'  u 3:($9/($17-$27-$29)) smooth unique w lines linecolor 2 lw 2.0 lt 1 t "state evolution         (9)",\
     'V-4_V1.dat1'  u 3:(($9+$15)/($17-$27-$29)) smooth unique w lines linecolor 2 lw 1.0 lt 1 t "+ RHS rate eval (15+9)",\
     'V-4_V1.dat1'  u 3:($13/($17-$27-$29)) smooth unique w lines linecolor 5 lw 2.0 lt 1 t       "RHS setup   (13)",\
     'V-4_V1.dat1'  u 3:(($13+$25)/($17-$27-$29)) smooth unique w lines linecolor 5 lw 1.0 lt 0 t " + malloc (25+13)"
set output
set terminal pop
