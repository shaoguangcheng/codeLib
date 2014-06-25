_xsize=1.50
_ysize=1.00
set size _xsize, _ysize
set term png
set output "demo2.png"
set xrange  [-5:5]
set format x "%g"
set xtics 1
set xlabel "x label"
set multiplot
set label 100 "This is global label" at graph 0.5, 0.1

set label 101 "plot 0" at graph 0.5, 0.5
set format x "%4g"
set xrange  [0:1]
set origin 0, 0
set size 0.5, 1
plot \
sin(0*x)+cos(2*x)
set nolabel 101


set label 102 "plot 1" at graph 0.5, 0.5
set origin 0.5, 0
set size 0.5, 1
plot \
sin(1*x)+cos(3*x)
set nolabel 102


set label 103 "plot 2" at graph 0.5, 0.5
set origin 1, 0
set size 0.5, 1
plot \
sin(2*x)+cos(4*x)
set nolabel 103

set nolabel 100
set nomulti

