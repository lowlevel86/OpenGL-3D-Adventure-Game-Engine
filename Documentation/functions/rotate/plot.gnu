# gnuplot plot.gnu -p
# set terminal png transparent nocrop enhanced size 450,320 font "arial,8" 
# set output 'plot.png'
set style arrow 1 head filled size char 1.5,20,50 

unset border
set xzeroaxis lt -1
set yzeroaxis lt -1
set xtics nomirror axis
set ytics nomirror axis

set tmargin 2
set rmargin 4
set arrow 1 from graph 1,first 0 to screen 0.99,first 0 arrowstyle 1
set arrow 2 from first 0,graph 1 to first 0,screen 0.99 arrowstyle 1
plot x

plot "/home/coder/C_programming/windows/CAGEopenGL/81_doc/Documentation/functions/rotate/tri.dat" title "triangles"

