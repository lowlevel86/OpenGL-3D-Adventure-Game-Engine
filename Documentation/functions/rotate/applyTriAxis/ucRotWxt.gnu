set terminal wxt size 350,210

#set title "Graph Title"
#set xlabel "X"
#set ylabel "Y"

# sets background color
set object 1 rectangle from screen -0.1,-0.1 to screen 1.1,1.1 fillcolor rgb "#ffffff" behind

# changes border color
set border linecolor rgb "#555555"

# displays the x and y axis
set xzeroaxis linewidth 0.5 linecolor rgb "#555555" linetype 1
set yzeroaxis linewidth 0.5 linecolor rgb "#555555" linetype 1

# displays the x and y grid
set grid xtics linecolor rgb "#888888" linewidth 0.2 linetype 9
set grid ytics linecolor rgb "#888888" linewidth 0.2 linetype 9

# sets the axis range
set xrange [-1.16842389107:1.16181254387]
set yrange [-1.11913955212:1.28171288967]
set size ratio 1.03030422398

# moves the key out of the graph
set key outside vertical top right

plot\
"0Unit.dat" title "0Unit" with lines linewidth 2.2 linecolor rgb "#000000",\
"H_002.dat" title "H_002" with lines linewidth 1.1 linecolor rgb "#FF0000",\
"HV2_005.dat" title "HV2_005" with lines linewidth 2.0 linecolor rgb "#888888",\
"Plane.dat" title "Plane" with points pointsize 0.5 pointtype 7,\
"Plane_001.dat" title "Plane_001" with points pointsize 0.5 pointtype 7,\
"V_002.dat" title "V_002" with lines linewidth 1.1 linecolor rgb "#00FF00",\
"V_003.dat" title "V_003" with lines linewidth 1.1 linecolor rgb "#0000FF",\
"zH_003.dat" title "zH_003" with lines linewidth 1.1 linecolor rgb "#FF00FF"
