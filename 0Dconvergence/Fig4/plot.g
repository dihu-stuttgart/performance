# Beispielhafter plot mit allem möglichen Zeug.
# alles schön aufräumen:
reset
# output datei und format festlegen:
# set terminal postscript eps
set terminal png size 800,600 enhanced linewidth 4 20
set output 'Bild001.png'
# Befehle VOR plot Befehl:

# allgemeine Beschrigtungen 
set title "Convergence of different ODE solvers"
set xlabel "number of steps, K"
set ylabel "rel. error, V_m and I_{ion}"

# Pfeil mit Text:
#set label 1 "logarithmic" at 2,20
#set arrow 1 from 2.2,16 to 3,8

# Achsen:
set logscale x 
set logscale y
set ytics ("1e-04" 0.0001, "1e-05" 0.00001, "1e-06" 0.000001, "1e-07" 0.0000001, "1e-08" 0.00000001, "1e-09" 0.000000001, "1e-10" 0.0000000001)
#set yrange [1e-10:1e-04] #reverse
# zweite Achsen: benötigt im plot-Befehl das Argument 'axes x1y1' oder 'axes x1y2' (x2y2?)
#set x2label "x-Bez."
#set y2label "y-Bez."
#set y2tics autofreq; set ytics nomirror;

# ohne achsen-spezifikatuion: 

# daten plotten

# default ist der plot von spalte 2 über 1. man kann auch spalte n über m machen:'using m:n'
# oder mit rechenoperationen: 'using 1: (0.5*($2+$3))'

# Legende entfernen:
# unset key

# plotten mit Titeln für die Legende
# with:w (lines, points)
# linetype: lt  (-1 ,  5)
# linewidth: lw (0.5,3.5)
# linecolor:    (0  ,  6)
# pointtype     (0  ,  6)
# pointsize     (0:0.5:3)

#heun, K=64, V_m=-78.9451121580 
plot 'Euler.txt' u 1:(abs(($2+78.9451121580)/78.9451121580)) w lines linecolor 3 t "Euler",\
'Heun.txt' u 1:(abs(($2+78.9451121580)/78.9451121580)) w lines linecolor 2 t "Heun",\
'Euler.txt' u 1:(abs(($60+1189.84540438)/1189.84540438)) w lines linecolor 3 lt 0 t "Euler",\
'Heun.txt' u 1:(abs(($60+1189.84540438)/1189.84540438)) w lines linecolor 2 lt 0 t "Heun"
#plot 'ODESolverTest.dat' u 1:($2-) w lines t "sg1"
# 'beenden'
set output
set terminal pop
