% Debug

![](Debug/0.png)

This howto will demonstrate functions that can be used for debugging.

---

**In scene1.c**

---

The printfScrn function works like printf except it prints text on to the render screen.  
Here is an example of how to use printfScrn to print the frames per second using the frame time (ft) variable.

---

**Find:**

~~~ {.c}
// END OF ADD TEXTURES
~~~

**And replace with:**

~~~ {.c}
// END OF ADD TEXTURES

printfScrn(0, 0, 18, 0x0, rI, "fps: %.2f", 1.0 / ft);
~~~

---

Compile and run.

The results should show up in the 1st scene.

---

---

Here is an example of how to use drawPt to draw a point in front of the character.

---

**Find:**

~~~ {.c}
drawMesh(&character_POINT[0], &character_QUAD[0], &character_TRI[0], &character_VCOLOR[0],
         &character_TEX[0], &character_TEXCOORD[0], &character_TEXLINKDAT[0],
         &character_QUADDATSZ[0], &character_TRIDATSZ[0], &character_HIDE[0], 0, character_MESHCNT, rI);
~~~

**And replace with:**

~~~ {.c}
drawMesh(&character_POINT[0], &character_QUAD[0], &character_TRI[0], &character_VCOLOR[0],
         &character_TEX[0], &character_TEXCOORD[0], &character_TEXLINKDAT[0],
         &character_QUADDATSZ[0], &character_TRIDATSZ[0], &character_HIDE[0], 0, character_MESHCNT, rI);

float frontBoxPt[3];// only 1 point
int frontBoxPtDataCnt[2];// the POINTDATSZ array always starts with 0

frontBoxPt[0] = character_TRANS[character_frontBox*TRSZ+LOCX];
frontBoxPt[1] = character_TRANS[character_frontBox*TRSZ+LOCY];
frontBoxPt[2] = character_TRANS[character_frontBox*TRSZ+LOCZ];
frontBoxPtDataCnt[0] = 0;
frontBoxPtDataCnt[1] = 1 * 3;

applyMeshViewRotLocSz(&frontBoxPt[0], &frontBoxPtDataCnt[0], 0, 1, &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);
drawPt(frontBoxPt[0], frontBoxPt[1], frontBoxPt[2], 0xFF00FF, 5.0);
~~~

---

Compile and run.

The results should show up in the 1st scene.

---

---

Here is an example of how to use drawLine to draw a line from the character to the finishing platform.

---

**Find:**

~~~ {.c}
drawMesh(&character_POINT[0], &character_QUAD[0], &character_TRI[0], &character_VCOLOR[0],
         &character_TEX[0], &character_TEXCOORD[0], &character_TEXLINKDAT[0],
         &character_QUADDATSZ[0], &character_TRIDATSZ[0], &character_HIDE[0], 0, character_MESHCNT, rI);
~~~

**And replace with:**

~~~ {.c}
drawMesh(&character_POINT[0], &character_QUAD[0], &character_TRI[0], &character_VCOLOR[0],
         &character_TEX[0], &character_TEXCOORD[0], &character_TEXLINKDAT[0],
         &character_QUADDATSZ[0], &character_TRIDATSZ[0], &character_HIDE[0], 0, character_MESHCNT, rI);

float linePt[6];// 2 points
int linePtDataCnt[2];// the POINTDATSZ array always starts with 0

linePt[0] = character_TRANS[character_box*TRSZ+LOCX];
linePt[1] = character_TRANS[character_box*TRSZ+LOCY];
linePt[2] = character_TRANS[character_box*TRSZ+LOCZ];
linePt[3] = course1_TRANS[course1_finish*TRSZ+LOCX];
linePt[4] = course1_TRANS[course1_finish*TRSZ+LOCY];
linePt[5] = course1_TRANS[course1_finish*TRSZ+LOCZ];
linePtDataCnt[0] = 0;
linePtDataCnt[1] = 2 * 3;

applyMeshViewRotLocSz(&linePt[0], &linePtDataCnt[0], 0, 1, &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);
drawLine(linePt[0], linePt[1], linePt[2], linePt[3], linePt[4], linePt[5], 0x00FFFF, 2.0);
~~~

---

Compile and run.

The results should show up in the 1st scene.

---

---

Here is an example of how to draw transformation boxes, bounds boxes, and axes for meshes.

---

**Find:**

~~~ {.c}
drawMesh(&course1_POINT[0], &course1_QUAD[0], &course1_TRI[0], &course1_VCOLOR[0],
         &course1_TEX[0], &course1_TEXCOORD[0], &course1_TEXLINKDAT[0],
         &course1_QUADDATSZ[0], &course1_TRIDATSZ[0], &course1_HIDE[0], 0, course1_MESHCNT, rI);
~~~

**And replace with:**

~~~ {.c}
drawMesh(&course1_POINT[0], &course1_QUAD[0], &course1_TRI[0], &course1_VCOLOR[0],
         &course1_TEX[0], &course1_TEXCOORD[0], &course1_TEXLINKDAT[0],
         &course1_QUADDATSZ[0], &course1_TRIDATSZ[0], &course1_HIDE[0], 0, course1_MESHCNT, rI);

drawTransBox(&course1_TRANS[0], course1_MESHCNT, &camera_TRANS[camera_camera*TRSZ], camLenseSz, 2, 0xFF00FF, rI);
drawBounds(&course1_TRANS[0], course1_MESHCNT, &camera_TRANS[camera_camera*TRSZ], camLenseSz, 2, 0xFFFF00, rI);
drawXyzAxis(&course1_TRANS[0], course1_MESHCNT, &camera_TRANS[camera_camera*TRSZ], camLenseSz, 2, rI);
~~~

---

Compile and run.

The results should show up in the 1st scene.

---

---

Here is an example of how to take a screen shot.

---

**Find:**

~~~ {.c}
deleteTextures();
~~~

**And replace with:**

~~~ {.c}
if (keyPress[83])// S key
screenShot(".\\", 3);// no more than 3 shots can be taken

deleteTextures();
~~~

---

Compile and run.

In the 1st scene press 'S' to save a screen shot to a .ppm image file.

---

---

[Back to Game Engine HowTos](index.html)

