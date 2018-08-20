% asciiOpenGL.c

---

### drawAsciiChar()
Draws a character by finding the correct letter within line data and applying a size, location and rotation (unit circle coordinates) to it before drawing a series of lines.  

The unit circle coordinate data is only calculated when the rotation data is new or changed. This makes it faster.

---

### drawAscii()
Draws a string using the "drawAsciiChar" function.

---

[Back to Game Engine Functions](index.html)

