% Angular Vertex Color Shading Code

![](Angular_Vertex_Color_Shading_Code/0.png) ![](Angular_Vertex_Color_Shading_Code/1.png)

---

This code will color only every other vertex making a mesh look angular.

**In initialize.c**

---

**Find:**

~~~ {.c}
if (initializeScene4)
{
~~~

**And replace with:**

~~~ {.c}
if (initializeScene4)
{
   char *VCOLOR_PTR = cubes_VCOLOR;
   int VCOLOR_SIZE = sizeof(cubes_VCOLOR);
   float colorAmount = 0.0;
   
   for (i=0; i < VCOLOR_SIZE; i+=4*2)
   {
      VCOLOR_PTR[i+0] = (unsigned char)((float)(VCOLOR_PTR[i+0]&0xFF) * colorAmount);
      VCOLOR_PTR[i+1] = (unsigned char)((float)(VCOLOR_PTR[i+1]&0xFF) * colorAmount);
      VCOLOR_PTR[i+2] = (unsigned char)((float)(VCOLOR_PTR[i+2]&0xFF) * colorAmount);
   }
~~~

---

Compile and run.

Press enter 4 times to see the results in the 4th scene.

---

---

It is possible to change the "colorAmount" variable to increase or decrease the shading. Also the vertex colors data could be saved to file for manually changing a mesh's ".c" file and permanently keeping the changes.

---

**Find:**

~~~ {.c}
   float colorAmount = 0.0;
   
   for (i=0; i < VCOLOR_SIZE; i+=4*2)
   {
      VCOLOR_PTR[i+0] = (unsigned char)((float)(VCOLOR_PTR[i+0]&0xFF) * colorAmount);
      VCOLOR_PTR[i+1] = (unsigned char)((float)(VCOLOR_PTR[i+1]&0xFF) * colorAmount);
      VCOLOR_PTR[i+2] = (unsigned char)((float)(VCOLOR_PTR[i+2]&0xFF) * colorAmount);
   }
~~~

**And replace with:**

~~~ {.c}
   float colorAmount = 0.5;
   
   for (i=0; i < VCOLOR_SIZE; i+=4*2)
   {
      VCOLOR_PTR[i+0] = (unsigned char)((float)(VCOLOR_PTR[i+0]&0xFF) * colorAmount);
      VCOLOR_PTR[i+1] = (unsigned char)((float)(VCOLOR_PTR[i+1]&0xFF) * colorAmount);
      VCOLOR_PTR[i+2] = (unsigned char)((float)(VCOLOR_PTR[i+2]&0xFF) * colorAmount);
   }
   
   FILE *fp;
   fp = fopen("VCOLOR.txt", "w");
   for (i=0; i < VCOLOR_SIZE; i+=4)
   fprintf(fp, "%i, %i, %i, %i,\n", (unsigned char)VCOLOR_PTR[i+0],
                                    (unsigned char)VCOLOR_PTR[i+1],
                                    (unsigned char)VCOLOR_PTR[i+2],
                                    (unsigned char)VCOLOR_PTR[i+3]);
   fclose(fp);
~~~

---

Compile and run.

---

---

[Back to Game Engine HowTos](index.html)

