#!/bin/bash

echo "### HowTos" > index.md

ls -d ./*/ | sed "s/$/*.md/" | sed "s/^/echo /" | sh | while read -r fileToRead ; do

   # remove everthing before "/" and remove ".md"
   folderName=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md//")
   
   # print html url link for the c file
   echo "[$folderName.c]($folderName/$folderName.md)  " >> index.md
   
   #echo "" >> index.md
   
done
