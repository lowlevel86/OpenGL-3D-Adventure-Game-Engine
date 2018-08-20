% animate.c

---

These functions make use of a simple equation:  
result = (B - A) * Percent_of_Change + A

---

### animateTransFromTo()
Animate all of the transformation data from one state to another.  
Transformation data affected:  
* rotation  
* location  
* size  
* unit circle coordinates  
* bounds radius  

---

### animateRotFromTo()
Animate the rotation data and copy it to the unit circle coordinate data.  
Transformation data affected:  
* rotation  
* unit circle coordinates  

---

### animateLocFromTo()
Animate position.  
Transformation data affected:  
* location

---

### animateSizeFromTo()
Animate size.  
Transformation data affected:  
* size

---

### animateUcRotFromTo()
Animate only the unit circle coordinate data.  
Transformation data affected:  
* unit circle coordinates  

---

### animateMeshFromTo()
Animate the point data.

---

### animateColorFromTo()
Animate the vertex colors.

---

### animateTexCoordFromTo()
Animate the texture coordinates.

---

