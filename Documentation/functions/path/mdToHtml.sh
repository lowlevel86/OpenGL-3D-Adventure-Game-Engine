#!/bin/bash

mdFile=*.md

htmlFile=`echo $mdFile | sed 's/.md/.html/'`

pandoc -s --toc $mdFile -o $htmlFile
xlinks2 $htmlFile
