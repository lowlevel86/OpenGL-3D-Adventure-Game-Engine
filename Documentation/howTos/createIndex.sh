#!/bin/bash

echo "<HTML>" > index.html
echo "<HEAD><TITLE>Game Engine HowTos</TITLE></HEAD>" >> index.html
echo "<BODY>" >> index.html

echo "<H3><CENTER>Game Engine HowTos</CENTER></H3>" >> index.html

ls -d ./*/ | sed "s/$/*.md/" | sed "s/^/echo /" | sh | while read -r fileToRead ; do

   # remove everthing before "/" and replace ".md" with ""
   cFile=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md//")
   
   # remove everthing before "/" and replace ".md" with ".html"
   htmlFile=$(echo "$fileToRead" | sed -n -e 's,^.*/,,p' | sed "s/.md/.html/")
   
   # print html url link
   echo "<H3><a href='$htmlFile'>$cFile</a></H3>" >> index.html
   
done

echo "</BODY>" >> index.html
echo "</HTML>" >> index.html
