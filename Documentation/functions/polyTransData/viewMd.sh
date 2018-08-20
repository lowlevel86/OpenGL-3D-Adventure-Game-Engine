#!/bin/bash
pandoc -s --toc polyTransData.md -o ../polyTransData.html
xlinks2 ../polyTransData.html
