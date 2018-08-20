#!/bin/bash

echo "### Game Engine Functions" > index.md

ls -d ./*/ | sed "s/$/*.md/" | sed "s/^/echo /" | sh | while read -r fileToRead ; do

   # remove everthing before "/" and remove ".md"
   folderName=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md//")
   
   # print html url link for the c file
   echo "[$folderName.c]($folderName/$folderName.md)" >> index.md
   
   # print a list of functions that are in the specific c file
   cat "$fileToRead" | grep "###" | sed "s/### //" | sed "s/^/* /" >> index.md
   
done
