% Create New Scene

This howto will add a 5th scene using the 1st scene as a template.

---

**Copy scene1.c and rename it as scene5.c**

---

**In main.c**

---

**Find:**

~~~ {.c}
   if (sceneNumber == 5)
   sceneNumber = 0;
~~~

**And replace with:**

~~~ {.c}
   if (sceneNumber == 6)
   sceneNumber = 0;
~~~

---

**Find:**

~~~ {.c}
   if (sceneNumber == 4)
   {
      #include "scene4.c"
      return;
   }
~~~

**And replace with:**

~~~ {.c}
   if (sceneNumber == 4)
   {
      #include "scene4.c"
      return;
   }
   if (sceneNumber == 5)
   {
      #include "scene5.c"
      return;
   }
~~~

---

The compiler does not need to be told to compile scene5.c because it is apart of main.c. 

Compile and run.

Press enter 5 times to see the 5th scene.

---

---

Now to change the meshes within the scene.

**In main.c**

---

**Add under the includes:**

~~~ {.c}
#include "meshes/course3.h"
~~~

---

**In the meshes folder**

---

**Copy course1.blend and rename it as course3.blend**

**Open course3.blend**

**Goto File --> Export --> "C code tex (.c)..."**

**Click "Export to C (tex)"**

---

**In initialize.c**

---

**Find:**

~~~ {.c}
// Initialize Scene 4 //
////////////////////////////////////////////////////////////////////
~~~

**And replace with:**

~~~ {.c}
// Initialize Scene 4 //
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// Initialize Scene 5 //

static int initializeScene5 = TRUE;

if (initializeScene5)
{
   // control camera lense size relative to the scene
   sceneSz = 20; // used for opengl fog and clipping
   camLenseSz = 1.0 / sceneSz; // used for "applyMeshViewRotLocSz()"
   
   // resize the course
   globalResize(&course3_TRANS[0], course3_MESHCNT, 0, 0, 0, 15, 15, 15);
   
   // copy the mesh data so you will always have the original data
   copyTransFromTo(&course3_TRANS[0], &course3_STATICTRANS[0], course3_MESHCNT);
   copyMeshFromTo(&course3_POINT[0], &course3_POINTDATSZ[0], 0,
                  &course3_STATICPOINT[0], &course3_POINTDATSZ[0], 0, course3_MESHCNT);
   
   initializeScene5 = FALSE;
}

// Initialize Scene 5 //
////////////////////////////////////////////////////////////////////
~~~

---

**In scene5.c**

---

**Find all instances of:**

~~~ {.c}
course1_
~~~

**And replace with:**

~~~ {.c}
course3_
~~~

---

**Find and delete:**

~~~ {.c}
// move the moving platform
animatePlatform = animatePlatform + 0.01;

animateLocFromTo(&course3_TRANS[course3_stopperA*TRSZ],
                 &course3_TRANS[course3_stopperB*TRSZ], 1, &buffer_TRANS[0], &animatePlatform, 0, 2);

animateLocFromTo(&course3_TRANS[course3_stopperB*TRSZ],
                 &course3_TRANS[course3_stopperA*TRSZ], 1, &buffer_TRANS[0], &animatePlatform, 1, 2);

xPlatformNewloc = buffer_TRANS[LOCX] - course3_TRANS[course3_moving*TRSZ+LOCX];
yPlatformNewloc = buffer_TRANS[LOCY] - course3_TRANS[course3_moving*TRSZ+LOCY];
zPlatformNewloc = buffer_TRANS[LOCZ] - course3_TRANS[course3_moving*TRSZ+LOCZ];

localMove(&course3_TRANS[0], course3_moving, xPlatformNewloc, yPlatformNewloc, zPlatformNewloc);


// move the character with the platform when standing on it
localBoxDetectAndMove(&course3_TRANS[course3_moving*TRSZ],
                      &character_TRANS[character_feetBox*TRSZ], 0.001,
                      0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &boxContactData, &contact);

if (contact)
globalMove(&character_TRANS[0], character_MESHCNT, xPlatformNewloc, yPlatformNewloc, zPlatformNewloc);
~~~

---

---

The compiler needs to be told to compile the mesh data.

To compile with gcc:

**In Makefile.win**

---

**Find:**

~~~ {.c}
meshes\course2.o
~~~

**And replace with:**

~~~ {.c}
meshes\course2.o meshes\course3.o 
~~~

---

To compile with tcc:

**In tmake.bat**

---

**Find:**

~~~ {.c}
meshes\course2.o
~~~

**And replace with:**

~~~ {.c}
meshes\course2.o meshes\course3.o 
~~~

---

**Find:**

~~~ {.c}
if NOT exist rsrc.res ..\..\tccAndTools\Gorc\Gorc.exe /r rsrc.rc
~~~

**And replace with:**

~~~ {.c}
if NOT exist meshes\course3.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\course3.c -o meshes\course3.o

if NOT exist rsrc.res ..\..\tccAndTools\Gorc\Gorc.exe /r rsrc.rc
~~~

---

Compile and run.

Press enter 5 times to see the results in the 5th scene.  
The platform should not be moving.

---

---

Now to change the "dome" mesh.

**In main.c**

---

**Add under the includes:**

~~~ {.c}
#include "meshes/dome3.h"
~~~

---

**In the meshes folder**

---

**Copy dome2.blend and rename it as dome3.blend**

**Open dome3.blend**

**Goto File --> Export --> "C code tex (.c)..."**

**Click "Export to C (tex)"**

---

**In initialize.c**

---

**Find:**

~~~ {.c}
if (initializeScene5)
{
~~~

**And replace with:**

~~~ {.c}
if (initializeScene5)
{
   // resize the dome
   globalResize(&dome3_TRANS[0], dome3_MESHCNT, 0, 0, 0, 300, 300, 300);
   
   // copy the mesh data so you will always have the original data
   copyTransFromTo(&dome3_TRANS[0], &dome3_STATICTRANS[0], dome3_MESHCNT);
   copyMeshFromTo(&dome3_POINT[0], &dome3_POINTDATSZ[0], 0,
                  &dome3_STATICPOINT[0], &dome3_POINTDATSZ[0], 0, dome3_MESHCNT);
~~~

---

**In scene5.c**

---

**Find all instances of:**

~~~ {.c}
dome1_
~~~

**And replace with:**

~~~ {.c}
dome3_
~~~

---

**Find all instances of:**

~~~ {.c}
grass
~~~

**And replace with:**

~~~ {.c}
ocean
~~~

---

---

The compiler needs to be told to compile the mesh data.

To compile with gcc:

**In Makefile.win**

---

**Find:**

~~~ {.c}
meshes\dome2.o
~~~

**And replace with:**

~~~ {.c}
meshes\dome2.o meshes\dome3.o 
~~~

---

To compile with tcc:

**In tmake.bat**

---

**Find:**

~~~ {.c}
meshes\dome2.o
~~~

**And replace with:**

~~~ {.c}
meshes\dome2.o meshes\dome3.o 
~~~

---

**Find:**

~~~ {.c}
if NOT exist rsrc.res ..\..\tccAndTools\Gorc\Gorc.exe /r rsrc.rc
~~~

**And replace with:**

~~~ {.c}
if NOT exist meshes\dome3.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\dome3.c -o meshes\dome3.o

if NOT exist rsrc.res ..\..\tccAndTools\Gorc\Gorc.exe /r rsrc.rc
~~~

---

Compile and run.

Press enter 5 times to see the results in the 5th scene.  
The background scenery should be different.

---

