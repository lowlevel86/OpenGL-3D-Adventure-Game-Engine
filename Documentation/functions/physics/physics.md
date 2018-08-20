% physics.c

---

### ptToPlaneSkid()

Finds the skid direction of a point trajectory on a plane. The plane is created by a mesh's transformation data.

---

### boxSkid()

Finds the skid direction of a box to box collision. It requires an integer containing face contact data in the following format:  

"fixed box" +X face ==             0b1  
"fixed box" +Y face ==            0b10  
"fixed box" +Z face ==           0b100  
"fixed box" -X face ==          0b1000  
"fixed box" -Y face ==         0b10000  
"fixed box" -Z face ==        0b100000  
"moving box" +X face ==      0b1000000  
"moving box" +Y face ==     0b10000000  
"moving box" +Z face ==    0b100000000  
"moving box" -X face ==   0b1000000000  
"moving box" -Y face ==  0b10000000000  
"moving box" -Z face == 0b100000000000  

---

[Back to Game Engine Functions](index.html)

