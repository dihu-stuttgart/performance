# Beispielhafter plot mit allem möglichen Zeug.
# alles schön aufräumen:
reset
# output datei und format festlegen:
# set terminal postscript eps
set terminal png size 800,600 enhanced linewidth 4 20
set output 'Efficiency.png'
# Befehle VOR plot Befehl:

# allgemeine Beschriftungen 
set title "Solver Efficiency"
set xlabel "relative error, V_m"
set ylabel "CPU-time / t_{Euler,K=1}"

# Pfeil mit Text:
#set label 1 "logarithmic" at 2,20
#set arrow 1 from 2.2,16 to 3,8

# Achsen:
set logscale x
set xtics ("1e-02" 1e-02, " " 1e-03, "1e-04" 1e-04, " " 1e-05, "1e-06" 1e-06, " " 1e-07, "1e-08" 1e-08, " " 1e-09, "1e-10" 1e-10)
#set xtics ("1e-02" 1e-02,"1e-04" 1e-04, "1e-06" 1e-06, "1e-08" 1e-08, "1e-10" 1e-10)
#set xtics ("1e-02" 1e-02, "1e-03" 1e-03, "1e-04" 1e-04, "1e-05" 1e-05, "1e-06" 1e-06, "1e-07" 1e-07, "1e-08" 1e-08, "1e-09" 1e-09, "1e-10" 1e-10)
#set xrange [1e-10:1e-04]
set logscale y

# zweite Achsen: benötigt im plot-Befehl das Argument 'axes x1y1' oder 'axes x1y2' (x2y2?)
#set x2label "x-Bez."
#set y2label "y-Bez."
#set y2tics autofreq; set ytics nomirror;

# daten plotten

# default ist der plot von spalte 2 über 1. man kann auch spalte n über m machen:'using m:n'
# oder mit rechenoperationen: 'using 1: (0.5*($2+$3))'

# Legende entfernen:
# unset key
# left right bottom top outside
#set key left top

# plotten mit Titeln für die Legende
# with:w (lines, points)
# linetype: lt  (-1 ,  5)
# linewidth: lw (0.5,3.5)
# linecolor:    (0  ,  6)
# pointtype     (0  ,  6)
# pointsize     (0:0.5:3)
plot 'Euler.txt' u (abs(($2+69.9623461445)/69.9623461445)):($62/0.002) w points linecolor 3 pt 3 ps 2.0 t "Euler",\
'Heun.txt' u (abs(($2+69.9623461445)/69.9623461445)):($62/0.002) w points linecolor 2 pt 4 ps 2.0 t "Heun"
# 'beenden'
set output
set terminal pop
