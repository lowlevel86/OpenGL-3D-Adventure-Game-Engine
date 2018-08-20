#!/bin/bash

echo "<HTML>" > index.html
echo "<HEAD><TITLE>Game Engine Functions</TITLE></HEAD>" >> index.html
echo "<BODY>" >> index.html

# print html url link for the c file
echo "<H3><CENTER>Game Engine Functions</CENTER></H3>" >> index.html

ls -d ./*/ | sed "s/$/*.md/" | sed "s/^/echo /" | sh | while read -r fileToRead ; do

   # remove everthing before "/" and replace ".md" with ".c"
   cFile=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md/.c/")
   
   # remove everthing before "/" and replace ".md" with ".html"
   htmlFile=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md/.html/")
   
   # print html url link for the c file
   echo "<H3><a href='$htmlFile'>$cFile</a></H3>" >> index.html
   
   echo "<UL>" >> index.html
   
   # print a list of functions that are in the specific c file
   cat "$fileToRead" | grep "###" | sed "s/### //" | sed "s/^/<LI>/" | sed "s,$,</LI>," >> index.html
   
   echo "</UL>" >> index.html
   
done

echo "</BODY>" >> index.html
echo "</HTML>" >> index.html
