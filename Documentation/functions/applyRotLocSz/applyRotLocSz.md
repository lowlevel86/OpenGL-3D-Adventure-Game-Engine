% applyRotLocSz.c

---

Instead of changing the rotation, location or size of a mesh by moving each vertex again and again, it is possible to change only a few numbers representing many transformations and later applying those numbers to each vertex. This allows less computation for multiple transformations on a mesh.  
These functions are typically used right before rendering.  
The order of how transformations are applied is imported because different orders can give different results.

---

### applyRotLocSz()
Applies transformation data to the point data of each mesh.  
The transformation is applied in the following order:  
1) size  
2) unit circle coordinates (for rotation)  
3) location  
  
The unit circle coordinate data is used instead of the rotation data to calculate rotations because it is faster.

---

### applyMeshViewRotLocSz()
This function will use a mesh as a camera.  
If the "camLenseSz" variable is 0 then the camera lense size will be taken from the camera mesh.  
The camera mesh transformation is applied in the following order:  
1) location  
2) unit circle coordinates (for rotation)  
3) size  

---

