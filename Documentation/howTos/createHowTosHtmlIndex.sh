#!/bin/bash

echo "<HTML>" > index.html
echo "<HEAD><TITLE>HowTos</TITLE></HEAD>" >> index.html
echo "<BODY>" >> index.html

# print html url link for the c file
echo "<H3><CENTER>HowTos</CENTER></H3>" >> index.html

ls -d ./*/ | sed "s/$/*.md/" | sed "s/^/echo /" | sh | while read -r fileToRead ; do

   # remove everthing before "/" and remove ".md"
   folderName=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md//")
   
   # remove everthing before "/" and replace ".md" with ".c"
   cFile=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md/.c/")
   
   # remove everthing before "/" and replace ".md" with ".html"
   htmlFile=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md/.html/")
   
   # print html url link for the c file
   echo "<H3><a href='$folderName/$htmlFile'>$cFile</a></H3>" >> index.html
   
done

echo "</BODY>" >> index.html
echo "</HTML>" >> index.html
