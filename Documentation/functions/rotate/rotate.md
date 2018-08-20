% rotate.c

---

### relativeRot()

Uses rotate() to rotate a point around a relative center.

---

### rotate()

Rotates a point around the x, y, and z axes concurrently.

![](rotate/0.png) ![](rotate/1.png)

For an example of how it rotates the x and y axes at the same time.

![](rotate/0.png) ![](rotate/2.png)

It will first rotate so that the slanted rotation will be around the x axis.

![](rotate/2.png) ![](rotate/3.png)

Then it will rotate the same amount of distance as if it were moving slanted.

![](rotate/3.png) ![](rotate/1.png)

Last it will rotate back to make the rotation slanted.

---

### degRot()

Rotates a point around an axis using degrees. This is slower than using ucRot().

---

### ucRot()

Rotates a point around an axis using unit circle coordinates.

![](rotate/5.png)

Known lengths within similar triangles are used to find the vertical value of the rotated point.

![](rotate/6.png)

The horizontal value is found the same way.

---

[Back to Game Engine Functions](index.html)

