xP = 1.0;
yP = 0.0;
zP = 0.0;

yRadial1 = 0.707;
zRadial1 = 0.707;
xRadial2 = 0.707;
zRadial2 = 0.707;
xRadial3 = 0.707;
yRadial3 = 0.707;

yLine1 = yRadial1;
zLine1 = zRadial1;
yLine2 = -zRadial1;
zLine2 = yRadial1;

y = (yP - yLine2 / zLine2 * zP) * zLine2;
z = (zP - zLine1 / yLine1 * yP) * yLine1;
yP = y;
zP = z;

xLine1 = xRadial2;
zLine1 = zRadial2;
xLine2 = -zRadial2;
zLine2 = xRadial2;

x = (xP - xLine2 / zLine2 * zP) * zLine2;
z = (zP - zLine1 / xLine1 * xP) * xLine1;
xP = x;
zP = z;

xLine1 = xRadial3;
yLine1 = yRadial3;
xLine2 = -yRadial3;
yLine2 = xRadial3;

x = (xP - xLine2 / yLine2 * yP) * yLine2;
y = (yP - yLine1 / xLine1 * xP) * xLine1;
xP = x;
yP = y;

print xP;
print yP;
print zP;

print "-should equal-"
print 0.499849
print -0.499849
print -0.707
print ""


xLine1 = xRadial3;
yLine1 = yRadial3;
xLine2 = -yRadial3;
yLine2 = xRadial3;

x = yP * xLine2 + xP * yLine2;
y = xP * yLine1 + yP * xLine1;
xP = x;
yP = y;

xLine1 = xRadial2;
zLine1 = zRadial2;
xLine2 = -zRadial2;
zLine2 = xRadial2;

x = zP * xLine2 + xP * zLine2;
z = xP * zLine1 + zP * xLine1;
xP = x;
zP = z;

yLine1 = yRadial1;
zLine1 = zRadial1;
yLine2 = -zRadial1;
zLine2 = yRadial1;

y = zP * yLine2 + yP * zLine2;
z = yP * zLine1 + zP * yLine1;
yP = y;
zP = z;

print xP;
print yP;
print zP;

print "-should equal-"
print 1.0
print 0.0
print 0.0
print ""