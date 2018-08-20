cat *Wxt.gnu > ucRotWxt2.gnu

sed -i -e 's/title/notitle/g' ucRotWxt2.gnu

findStr=1HL
replaceStr=1st@Half
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=2HL
replaceStr=2nd@Half
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=V
replaceStr=vL1
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=H
replaceStr=hL1
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=V_002
replaceStr=vP
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=H_002
replaceStr=hP
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

sed -i -e 's/@/ /g' ucRotWxt2.gnu
