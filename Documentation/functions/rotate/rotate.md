% rotate.c

---

### relativeRot()

Uses rotate() to rotate a point around a relative center.

---

### rotate()

Rotates a point around the x, y, and z axes concurrently.

![](0.png) ![](1.png)

For an example of how it rotates the x and y axes at the same time.

![](0.png) ![](2.png)

It will first rotate so that the slanted rotation will be around the x axis.

![](2.png) ![](3.png)

Then it will rotate the same amount of distance as if it were moving slanted.

![](3.png) ![](1.png)

Last it will rotate back to make the rotation slanted.

---

### degRot()

Rotates a point around an axis using degrees. This is slower than using ucRot().

---

### ucRot()

Rotates a point around an axis using unit circle coordinates.

![](5.png)

Known lengths within similar triangles are used to find the vertical value of the rotated point.

![](6.png)

The horizontal value is found the same way.

---

