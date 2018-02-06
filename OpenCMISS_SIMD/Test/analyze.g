reset

set terminal png size 1200 , 960 enhanced linewidth 3 20
set output 'Correctness.png'

# Befehle VOR plot Befehl:
# allgemeine Beschrigtungen 
set title "sum of integration and evaluation."
set xlabel "Number Of Cells"
set ylabel "precision [%]"


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

# total 5 integration 7 thereof_state_evolution 9 evaluate_L_{hs} 11 RHS_setup 13 RHS_rate_evaluation 15 

# plotten mit Titeln für die Legende
plot 'OCV_V1.dat2'  u 3:(100-($7+$11)/$5*100) smooth unique w lines linecolor 0 lw 1 lt 1 t "OpenCmiss 1",\
     'OCV_V0.dat2'  u 3:(100-($7+$11)/$5*100) smooth unique w lines linecolor 1 lw 1 lt 1 t "OpenCmiss 0",\
     'V-1_V1.dat2'  u 3:(100-($7+$11)/$5*100) smooth unique w lines linecolor 2 lw 1.0 lt 1 t "Version1 1",\
     'V-1_V0.dat2'  u 3:(100-($7+$11)/$5*100) smooth unique w lines linecolor 3 lw 1.0 lt 1 t "Version1 0"

set output
set terminal pop
