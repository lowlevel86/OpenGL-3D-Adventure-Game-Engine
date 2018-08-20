cat *Wxt.gnu > ucRotWxt2.gnu

sed -i -e 's/title/notitle/g' ucRotWxt2.gnu

findStr=0Unit
replaceStr=Unit@Circle
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=H_002
replaceStr=hL1
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=V_002
replaceStr=vL1
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=zH_003
replaceStr=vL2
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

findStr=V_003
replaceStr=hL2
title=title
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/"'$findStr'"/"'$replaceStr'"/g' ucRotWxt2.gnu
sed -i -e 's/'$findStr'.dat" notitle/'$findStr'.dat" '$title'/g' ucRotWxt2.gnu

sed -i -e 's/@/ /g' ucRotWxt2.gnu
