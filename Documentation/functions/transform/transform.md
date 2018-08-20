% transform.c

---

### globalRot()

Similar to localRot() except it rotates many objects around a center point.

---

### localRot()

Rotates an object in sequence around the x, y, then z axis.

---

### globalRevRot()

Similar to localRevRot() except it rotates many objects around a center point.

---

### localRevRot()

Rotates an object in reverse sequence around the z, y, then x axis.

---

### globalConcurrentAxisRot()

Similar to localConcurrentAxisRot() except it rotates many objects around a center point.

---

### localConcurrentAxisRot()

As opposed to localRot(), localConcurrentAxisRot() can rotate the x,y,z axes at the same time.

![](serialRot.gif) ![](parallelRot.gif)

---

### globalMove()

Similar to localMove() except it moves many objects at a time.

---

### localMove()

Moves an object.

---

### globalResize()

Similar to localResize() except it resizes many objects relative to a center point.

---

### localResize()

Resizes an object.

---

### globalUcRot()

Similar to localUcRot() except it rotates many objects around a center point.

---

### localUcRot()

Rotates an object in sequence around the x, y, then z axis using unit circle values.

---

### globalRevUcRot()

Similar to localRevUcRot() except it rotates many objects around a center point.

---

### localRevUcRot()

Rotates an object in reverse sequence around the z, y, then x axis using unit circle values.

---

### copyTransFromTo()
Copy all of the transformation data from one place to another.  
Transformation data affected:  
* rotation  
* location  
* size  
* unit circle coordinates  
* bounds radius  

---

### copyRotFromTo()
Copy rotation data.  
Transformation data affected:  
* rotation  

---

### copyLocFromTo()
Copy position data.  
Transformation data affected:  
* location

---

### copySizeFromTo()
Copy size data.  
Transformation data affected:  
* size

---

### copyUcRotFromTo()
Copy unit circle coordinate data.  
Transformation data affected:  
* unit circle coordinates  

---

### copyMeshFromTo()
Copy point data.

---

### copyColorFromTo()
Copy vertex colors.

---

### copyTexCoordFromTo()
Copy texture coordinates.

---

