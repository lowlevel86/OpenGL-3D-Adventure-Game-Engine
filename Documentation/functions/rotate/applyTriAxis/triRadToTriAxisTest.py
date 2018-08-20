yRadial1 = 0.707;
zRadial1 = 0.707;

xRadial2 = 0.707;
zRadial2 = 0.707;

xRadial3 = 0.707;
yRadial3 = 0.707;

xH = 1.0;
yH = 0.0;
zH = 0.0;
xV = 0.0;
yV = 1.0;
zV = 0.0;
xFB = 0.0;
yFB = 0.0;
zFB = 1.0;

yLine1 = yRadial1;
zLine1 = zRadial1;
yLine2 = -zRadial1;
zLine2 = yRadial1;

y = (yH - yLine2 / zLine2 * zH) * zLine2;
z = (zH - zLine1 / yLine1 * yH) * yLine1;
yH = y;
zH = z;

y = (yV - yLine2 / zLine2 * zV) * zLine2;
z = (zV - zLine1 / yLine1 * yV) * yLine1;
yV = y;
zV = z;

y = (yFB - yLine2 / zLine2 * zFB) * zLine2;
z = (zFB - zLine1 / yLine1 * yFB) * yLine1;
yFB = y;
zFB = z;

xLine1 = xRadial2;
zLine1 = zRadial2;
xLine2 = -zRadial2;
zLine2 = xRadial2;

x = (xH - xLine2 / zLine2 * zH) * zLine2;
z = (zH - zLine1 / xLine1 * xH) * xLine1;
xH = x;
zH = z;

x = (xV - xLine2 / zLine2 * zV) * zLine2;
z = (zV - zLine1 / xLine1 * xV) * xLine1;
xV = x;
zV = z;

x = (xFB - xLine2 / zLine2 * zFB) * zLine2;
z = (zFB - zLine1 / xLine1 * xFB) * xLine1;
xFB = x;
zFB = z;

xLine1 = xRadial3;
yLine1 = yRadial3;
xLine2 = -yRadial3;
yLine2 = xRadial3;

x = (xH - xLine2 / yLine2 * yH) * yLine2;
y = (yH - yLine1 / xLine1 * xH) * xLine1;
xH = x;
yH = y;

x = (xV - xLine2 / yLine2 * yV) * yLine2;
y = (yV - yLine1 / xLine1 * xV) * xLine1;
xV = x;
yV = y;

x = (xFB - xLine2 / yLine2 * yFB) * yLine2;
y = (yFB - yLine1 / xLine1 * xFB) * xLine1;
xFB = x;
yFB = y;

print xH
print yH
print zH
print ""

print xV
print yV
print zV
print ""

print xFB
print yFB
print zFB
print ""

print "-should equal-"
print 0.499849
print -0.499849
print -0.707
print ""

print 0.146455757
print 0.853242243
print -0.499849
print ""

print 0.853242243
print 0.146455757
print 0.499849
