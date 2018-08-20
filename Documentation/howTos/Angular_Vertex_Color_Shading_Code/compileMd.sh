#!/bin/bash

mdFile=*.md

htmlFile=`echo $mdFile | sed 's/.md/.html/'`

/home/coder/.cabal/bin/pandoc -s --toc $mdFile -o ../$htmlFile
#/home/coder/.cabal/bin/pandoc -s -H listings-setup.txt --toc $mdFile -o ../$htmlFile
#markdown $mdFile
#markdown_py $mdFile -f ../$htmlFile
#xlinks2 ../$htmlFile
