#!/bin/bash
gnuplot plot.gnu -p
read -p "Press enter" < "$(tty 0>&2)"