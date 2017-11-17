# Beispielhafter plot mit allem möglichen Zeug.
# alles schön aufräumen:
reset
# output datei und format festlegen:
# set terminal postscript eps
set terminal png size 800,600 enhanced linewidth 4 20
set output 'SplSchEff.png'
# Befehle VOR plot Befehl:

# allgemeine Beschriftungen 
set title "Splitting Scheme Efficiency"
set xlabel "relative error, V_m"
set ylabel "CPU-time / t_{Godunov,dt_\mathrm{1D}=0.5}"

# Pfeil mit Text:
#set label 1 "logarithmic" at 2,20
#set arrow 1 from 2.2,16 to 3,8

# Achsen:
set logscale x
#set xtics ("1e-02" 1e-02, " " 1e-03, "1e-04" 1e-04, " " 1e-05, "1e-06" 1e-06, " " 1e-07, "1e-08" 1e-08, " " 1e-09, "1e-10" 1e-10)
#set xtics ("1e-02" 1e-02,"1e-04" 1e-04, "1e-06" 1e-06, "1e-08" 1e-08, "1e-10" 1e-10)
#set xtics ("1e-02" 1e-02, "1e-03" 1e-03, "1e-04" 1e-04, "1e-05" 1e-05, "1e-06" 1e-06, "1e-07" 1e-07, "1e-08" 1e-08, "1e-09" 1e-09, "1e-10" 1e-10)
#set xrange [1e-10:1e-04]
set yrange [1e-1:1.2*1e00]
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
# V_m = -23.5219216213 (splitt.: strang(CN/Heun), dt_1D=0.00025, ODENSteps=2)
# parabolic solver:1.8378963470458984s, ODE solver:  0.944105148315429691s  (Euler K = 1) 
# parabolic solver:1.7331368923187256s, ODE solver:  2.5334513187408447s    (Euler K = 5)                                                                   [K .neq. Nsteps]
plot 'ConvSplittingi1.txt' u (abs(($3+23.5219216213)/23.5219216213)):(($1+$2)/(1.7331368923187256+2.5334513187408447)) w points linecolor 3 pt 3 ps 2.0 t "Godunov",\
     'ConvSplittingi3.txt' u (abs(($3+23.5219216213)/23.5219216213)):(($1+$2)/(1.7331368923187256+2.5334513187408447)) w points linecolor 2 pt 3 ps 2.0 t "Strang"
#'Heun.txt' u (abs(($2+23.5219216213)/23.5219216213)):($62/0.002) w points linecolor 2 pt 4 ps 2.0 t "Heun"
#     'ConvSplittingi2.txt' u (abs(($3+23.5219216213)/23.5219216213)):(($1+$2)/(1.7331368923187256+2.5334513187408447)) w points linecolor 1 pt 3 ps 2.0 t "Heun,K=2",\
#     'ConvSplittingi4.txt' u (abs(($3+23.5219216213)/23.5219216213)):(($1+$2)/(1.7331368923187256+2.5334513187408447)) w points linecolor 3 pt 3 ps 2.0 t "dirty Srang,K=5"
# 'beenden'
set output
set terminal pop
