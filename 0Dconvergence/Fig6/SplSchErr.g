# Beispielhafter plot mit allem möglichen Zeug.
# alles schön aufräumen:
reset
# output datei und format festlegen:
# set terminal postscript eps
set terminal png size 800,600 enhanced linewidth 4 20
set output 'SplSchErr.png'
# Befehle VOR plot Befehl:

# allgemeine Beschrigtungen 
set title "Comparison of different splitting schemes"
set xlabel "dt_\mathrm{1D} [microseconds]"
set ylabel "rel. error of V_m"

# Pfeil mit Text:
#set label 1 "logarithmic" at 2,20
#set arrow 1 from 2.2,16 to 3,8

# Achsen:
set logscale x 
set logscale y
#set ytics ("1e-04" 0.0001, "1e-05" 0.00001, "1e-06" 0.000001, "1e-07" 0.0000001, "1e-08" 0.00000001, "1e-09" 0.000000001, "1e-10" 0.0000000001)
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
set key top left

# plotten mit Titeln für die Legende
# with:w (lines, points)
# linetype: lt  (-1 ,  5)
# linewidth: lw (0.5,3.5)
# linecolor:    (0  ,  6)
# pointtype     (0  ,  6)
# pointsize     (0:0.5:3)
# V_m = -23.5219216213 (splitt.: strang(CN/Heun), dt_1D=0.00025, ODENSteps=2)
# parabolic solver:1.8378963470458984s, ODE solver:  0.944105148315429691s  (Euler K = 1) 
# parabolic solver:1.7331368923187256s, ODE solver:  2.5334513187408447s    (Euler K = 5)                                                                   [K .neq. Nsteps]
plot 'ConvSplittingi1.txt' u 4:(abs(($3+23.5219216213)/23.5219216213)) w points linecolor 3 pt 3 ps 2.0 t "Godunov",\
     'ConvSplittingi3.txt' u 4:(abs(($3+23.5219216213)/23.5219216213)) w points linecolor 2 pt 3 ps 2.0 t "Strang",\
     'ConvSplittingi1.txt' u 4:($4/240) w lines linecolor 3 lw 0.5 t "Slope 1",\
     'ConvSplittingi1.txt' u 4:($5+0.4*$5) w lines linecolor 2 lw 0.5 t "Slope 2"
#     'ConvSplittingi2.txt' u 4:(abs(($3+23.5219216213)/23.5219216213)) w points linecolor 1 pt 3 ps 2.0 t "Heun,K=2",\
#     'ConvSplittingi4.txt' u 4:(abs(($3+23.5219216213)/23.5219216213)) w points linecolor 4 pt 3 ps 2.0 t "dirty Srang,K=5",\
# 'beenden'
set output
set terminal pop
