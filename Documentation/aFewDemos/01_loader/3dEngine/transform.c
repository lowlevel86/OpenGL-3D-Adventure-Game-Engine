#include <stdio.h>
#include <math.h>
#include "3dEngine.h"

// global rotation
void globalRot(float *mesh_TRANS, int mesh_MESHCNT,
               float xCenter, float yCenter, float zCenter, float xRot, float yRot, float zRot)
{
   int i;
   float yUc1 = 1.0, zUc1 = 0.0;
   float xUc2 = 1.0, zUc2 = 0.0;
   float xUc3 = 1.0, yUc3 = 0.0;
   
   // get coordinates that represet a x, y, z rotation
   addRotToXyzUcRot(&yUc1, &zUc1,
                    &xUc2, &zUc2,
                    &xUc3, &yUc3, xRot, yRot, zRot);
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      // apply the new rotation to each mesh
      applyXyzUcRot(&mesh_TRANS[i+UCXH], &mesh_TRANS[i+UCXV],
                    &mesh_TRANS[i+UCYH], &mesh_TRANS[i+UCYV],
                    &mesh_TRANS[i+UCZH], &mesh_TRANS[i+UCZV],
                    yUc1, zUc1,
                    xUc2, zUc2,
                    xUc3, yUc3);
      
      // apply the new rotation to the location of each mesh
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] - xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] - yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] - zCenter;
      
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3,
                           &mesh_TRANS[i+LOCX], &mesh_TRANS[i+LOCY], &mesh_TRANS[i+LOCZ]);
      
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] + xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] + yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] + zCenter;
      
      // convert the unit circle coordinates into degree rotations for each mesh
      convertXyzUcRotToRot(mesh_TRANS[i+UCXH], mesh_TRANS[i+UCXV],
                           mesh_TRANS[i+UCYH], mesh_TRANS[i+UCYV],
                           mesh_TRANS[i+UCZH], mesh_TRANS[i+UCZV],
                           &mesh_TRANS[i+ROTX], &mesh_TRANS[i+ROTY], &mesh_TRANS[i+ROTZ]);
   }
}

// local rotation
void localRot(float *mesh_TRANS, int meshNum,
              float xCenter, float yCenter, float zCenter, float xRot, float yRot, float zRot)
{
   int dataLoc;
   float yUc1 = 1.0, zUc1 = 0.0;
   float xUc2 = 1.0, zUc2 = 0.0;
   float xUc3 = 1.0, yUc3 = 0.0;
   
   dataLoc = meshNum * TRSZ;
   
   // get coordinates that represet a x, y, z rotation
   addRotToXyzUcRot(&yUc1, &zUc1,
                    &xUc2, &zUc2,
                    &xUc3, &yUc3, xRot, yRot, zRot);
   
   // apply the new rotation to the mesh
   applyXyzUcRot(&mesh_TRANS[dataLoc+UCXH], &mesh_TRANS[dataLoc+UCXV],
                 &mesh_TRANS[dataLoc+UCYH], &mesh_TRANS[dataLoc+UCYV],
                 &mesh_TRANS[dataLoc+UCZH], &mesh_TRANS[dataLoc+UCZV],
                 yUc1, zUc1,
                 xUc2, zUc2,
                 xUc3, yUc3);
   
   // apply the new rotation to the location of the mesh
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] - xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] - yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] - zCenter;
   
   applyXyzUcRotToPoint(yUc1, zUc1,
                        xUc2, zUc2,
                        xUc3, yUc3,
                        &mesh_TRANS[dataLoc+LOCX], &mesh_TRANS[dataLoc+LOCY], &mesh_TRANS[dataLoc+LOCZ]);

   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] + xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] + yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] + zCenter;
   
   // convert the unit circle coordinates into degree rotations for the mesh
   convertXyzUcRotToRot(mesh_TRANS[dataLoc+UCXH], mesh_TRANS[dataLoc+UCXV],
                        mesh_TRANS[dataLoc+UCYH], mesh_TRANS[dataLoc+UCYV],
                        mesh_TRANS[dataLoc+UCZH], mesh_TRANS[dataLoc+UCZV],
                        &mesh_TRANS[dataLoc+ROTX], &mesh_TRANS[dataLoc+ROTY], &mesh_TRANS[dataLoc+ROTZ]);
}


// global reverse rotation
void globalRevRot(float *mesh_TRANS, int mesh_MESHCNT,
                  float xCenter, float yCenter, float zCenter, float xRot, float yRot, float zRot)
{
   int i;
   float yUc1 = 1.0, zUc1 = 0.0;
   float xUc2 = 1.0, zUc2 = 0.0;
   float xUc3 = 1.0, yUc3 = 0.0;
   
   // get coordinates that represet a x, y, z rotation
   addRotToXyzUcRot(&yUc1, &zUc1,
                    &xUc2, &zUc2,
                    &xUc3, &yUc3, xRot, yRot, zRot);
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      // reverse apply the new rotation to each mesh
      reverseApplyXyzUcRot(&mesh_TRANS[i+UCXH], &mesh_TRANS[i+UCXV],
                           &mesh_TRANS[i+UCYH], &mesh_TRANS[i+UCYV],
                           &mesh_TRANS[i+UCZH], &mesh_TRANS[i+UCZV],
                           yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3);
      
      // reverse apply the new rotation to the location of each mesh
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] - xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] - yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] - zCenter;
      
      reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                                  xUc2, zUc2,
                                  xUc3, yUc3,
                                  &mesh_TRANS[i+LOCX], &mesh_TRANS[i+LOCY], &mesh_TRANS[i+LOCZ]);
      
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] + xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] + yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] + zCenter;
      
      // convert the unit circle coordinates into degree rotations for each mesh
      convertXyzUcRotToRot(mesh_TRANS[i+UCXH], mesh_TRANS[i+UCXV],
                           mesh_TRANS[i+UCYH], mesh_TRANS[i+UCYV],
                           mesh_TRANS[i+UCZH], mesh_TRANS[i+UCZV],
                           &mesh_TRANS[i+ROTX], &mesh_TRANS[i+ROTY], &mesh_TRANS[i+ROTZ]);
   }
}

// local reverse rotation
void localRevRot(float *mesh_TRANS, int meshNum,
                 float xCenter, float yCenter, float zCenter, float xRot, float yRot, float zRot)
{
   int dataLoc;
   float yUc1 = 1.0, zUc1 = 0.0;
   float xUc2 = 1.0, zUc2 = 0.0;
   float xUc3 = 1.0, yUc3 = 0.0;
   
   dataLoc = meshNum * TRSZ;
   
   // get coordinates that represet a x, y, z rotation
   addRotToXyzUcRot(&yUc1, &zUc1,
                    &xUc2, &zUc2,
                    &xUc3, &yUc3, xRot, yRot, zRot);
   
   // reverse apply the new rotation to the mesh
   reverseApplyXyzUcRot(&mesh_TRANS[dataLoc+UCXH], &mesh_TRANS[dataLoc+UCXV],
                        &mesh_TRANS[dataLoc+UCYH], &mesh_TRANS[dataLoc+UCYV],
                        &mesh_TRANS[dataLoc+UCZH], &mesh_TRANS[dataLoc+UCZV],
                        yUc1, zUc1,
                        xUc2, zUc2,
                        xUc3, yUc3);
   
   // reverse apply the new rotation to the location of the mesh
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] - xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] - yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] - zCenter;
   
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3,
                               &mesh_TRANS[dataLoc+LOCX], &mesh_TRANS[dataLoc+LOCY], &mesh_TRANS[dataLoc+LOCZ]);

   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] + xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] + yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] + zCenter;
   
   // convert the unit circle coordinates into degree rotations for the mesh
   convertXyzUcRotToRot(mesh_TRANS[dataLoc+UCXH], mesh_TRANS[dataLoc+UCXV],
                        mesh_TRANS[dataLoc+UCYH], mesh_TRANS[dataLoc+UCYV],
                        mesh_TRANS[dataLoc+UCZH], mesh_TRANS[dataLoc+UCZV],
                        &mesh_TRANS[dataLoc+ROTX], &mesh_TRANS[dataLoc+ROTY], &mesh_TRANS[dataLoc+ROTZ]);
}


// global rotation around all axises simultaneously
void globalConcurrentAxisRot(float *mesh_TRANS, int mesh_MESHCNT,
                             float xCenter, float yCenter, float zCenter, float xRot, float yRot, float zRot)
{
   int i;
   float xHori = 1.0, yHori = 0.0, zHori = 0.0;
   float xVert = 0.0, yVert = 1.0, zVert = 0.0;
   float xyHori, xzHori, yzVert;
   float yUc1, zUc1;
   float xUc2, zUc2;
   float xUc3, yUc3;
   
   // apply x, y, and z rotation to a dual-axis object
   rotate(&xHori, &yHori, &zHori, xRot, yRot, zRot);
   rotate(&xVert, &yVert, &zVert, xRot, yRot, zRot);

   
   // normalize the dual-axis object to get coordinates that represet a x, y, z rotation
   xyHori = sqrt(xHori * xHori + yHori * yHori);
   
   if (xyHori == 0.0)// no rotation if the line is parallel with the z-axis
   {
      xUc3 = 1.0;
      yUc3 = 0.0;
   }
   else
   {
      xUc3 = xHori / xyHori;
      yUc3 = yHori / xyHori;
   }
   
   ucRot(xUc3, -yUc3, &xHori, &yHori);// z-axis
   ucRot(xUc3, -yUc3, &xVert, &yVert);// z-axis
   
   
   xzHori = sqrt(xHori * xHori + zHori * zHori);
   
   if (xzHori == 0.0)// no rotation if the line is parallel with the y-axis
   {
      xUc2 = 1.0;
      zUc2 = 0.0;
   }
   else
   {
      xUc2 = xHori / xzHori;
      zUc2 = -zHori / xzHori;// negative to rotate in opposite direction
   }
   
   ucRot(xUc2, zUc2, &xHori, &zHori);// y-axis
   ucRot(xUc2, zUc2, &xVert, &zVert);// y-axis
   
   
   yzVert = sqrt(yVert * yVert + zVert * zVert);
   
   if (yzVert == 0.0)// no rotation if the line is parallel with the x-axis
   {
      yUc1 = 1.0;
      zUc1 = 0.0;
   }
   else
   {
      yUc1 = yVert / yzVert;
      zUc1 = zVert / yzVert;
   }
   
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      // apply the new rotation to each mesh
      applyXyzUcRot(&mesh_TRANS[i+UCXH], &mesh_TRANS[i+UCXV],
                    &mesh_TRANS[i+UCYH], &mesh_TRANS[i+UCYV],
                    &mesh_TRANS[i+UCZH], &mesh_TRANS[i+UCZV],
                    yUc1, zUc1,
                    xUc2, zUc2,
                    xUc3, yUc3);
      
      // apply the new rotation to the location of each mesh
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] - xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] - yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] - zCenter;
      
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3,
                           &mesh_TRANS[i+LOCX], &mesh_TRANS[i+LOCY], &mesh_TRANS[i+LOCZ]);
      
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] + xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] + yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] + zCenter;
      
      // convert the unit circle coordinates into degree rotations for each mesh
      convertXyzUcRotToRot(mesh_TRANS[i+UCXH], mesh_TRANS[i+UCXV],
                           mesh_TRANS[i+UCYH], mesh_TRANS[i+UCYV],
                           mesh_TRANS[i+UCZH], mesh_TRANS[i+UCZV],
                           &mesh_TRANS[i+ROTX], &mesh_TRANS[i+ROTY], &mesh_TRANS[i+ROTZ]);
   }
}

// local rotation around all axises simultaneously
void localConcurrentAxisRot(float *mesh_TRANS, int meshNum,
                            float xCenter, float yCenter, float zCenter, float xRot, float yRot, float zRot)
{
   int dataLoc;
   float xHori = 1.0, yHori = 0.0, zHori = 0.0;
   float xVert = 0.0, yVert = 1.0, zVert = 0.0;
   float xyHori, xzHori, yzVert;
   float yUc1, zUc1;
   float xUc2, zUc2;
   float xUc3, yUc3;
   
   dataLoc = meshNum * TRSZ;
   
   
   // apply x, y, and z rotation to a dual-axis object
   rotate(&xHori, &yHori, &zHori, xRot, yRot, zRot);
   rotate(&xVert, &yVert, &zVert, xRot, yRot, zRot);


   // normalize the dual-axis object to get coordinates that represet a x, y, z rotation
   xyHori = sqrt(xHori * xHori + yHori * yHori);
   
   if (xyHori == 0.0)// no rotation if the line is parallel with the z-axis
   {
      xUc3 = 1.0;
      yUc3 = 0.0;
   }
   else
   {
      xUc3 = xHori / xyHori;
      yUc3 = yHori / xyHori;
   }
   
   ucRot(xUc3, -yUc3, &xHori, &yHori);// z-axis
   ucRot(xUc3, -yUc3, &xVert, &yVert);// z-axis
   
   
   xzHori = sqrt(xHori * xHori + zHori * zHori);
   
   if (xzHori == 0.0)// no rotation if the line is parallel with the y-axis
   {
      xUc2 = 1.0;
      zUc2 = 0.0;
   }
   else
   {
      xUc2 = xHori / xzHori;
      zUc2 = -zHori / xzHori;// negative to rotate in opposite direction
   }
   
   ucRot(xUc2, zUc2, &xHori, &zHori);// y-axis
   ucRot(xUc2, zUc2, &xVert, &zVert);// y-axis
   
   
   yzVert = sqrt(yVert * yVert + zVert * zVert);
   
   if (yzVert == 0.0)// no rotation if the line is parallel with the x-axis
   {
      yUc1 = 1.0;
      zUc1 = 0.0;
   }
   else
   {
      yUc1 = yVert / yzVert;
      zUc1 = zVert / yzVert;
   }
   
   
   // apply the new rotation to the mesh
   applyXyzUcRot(&mesh_TRANS[dataLoc+UCXH], &mesh_TRANS[dataLoc+UCXV],
                 &mesh_TRANS[dataLoc+UCYH], &mesh_TRANS[dataLoc+UCYV],
                 &mesh_TRANS[dataLoc+UCZH], &mesh_TRANS[dataLoc+UCZV],
                 yUc1, zUc1,
                 xUc2, zUc2,
                 xUc3, yUc3);
   
   
   // apply the new rotation to the location of the mesh
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] - xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] - yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] - zCenter;
   
   applyXyzUcRotToPoint(yUc1, zUc1,
                        xUc2, zUc2,
                        xUc3, yUc3,
                        &mesh_TRANS[dataLoc+LOCX], &mesh_TRANS[dataLoc+LOCY], &mesh_TRANS[dataLoc+LOCZ]);

   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] + xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] + yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] + zCenter;
   
   // convert the unit circle coordinates into degree rotations for the mesh
   convertXyzUcRotToRot(mesh_TRANS[dataLoc+UCXH], mesh_TRANS[dataLoc+UCXV],
                        mesh_TRANS[dataLoc+UCYH], mesh_TRANS[dataLoc+UCYV],
                        mesh_TRANS[dataLoc+UCZH], mesh_TRANS[dataLoc+UCZV],
                        &mesh_TRANS[dataLoc+ROTX], &mesh_TRANS[dataLoc+ROTY], &mesh_TRANS[dataLoc+ROTZ]);
}


// global reposition
void globalMove(float *mesh_TRANS, int mesh_MESHCNT, float x, float y, float z)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] + x;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] + y;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] + z;
   }
}

// local reposition
void localMove(float *mesh_TRANS, int meshNum, float x, float y, float z)
{
   int dataLoc;
   
   dataLoc = meshNum * TRSZ;
   
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] + x;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] + y;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] + z;
}


// global resize
void globalResize(float *mesh_TRANS, int mesh_MESHCNT,
                  float xCenter, float yCenter, float zCenter, float x, float y, float z)
{
   int i;
   float xyLgth;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] - xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] - yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] - zCenter;
   }
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS[i+SZX] = mesh_TRANS[i+SZX] * x;
      mesh_TRANS[i+SZY] = mesh_TRANS[i+SZY] * y;
      mesh_TRANS[i+SZZ] = mesh_TRANS[i+SZZ] * z;
   }
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] * x;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] * y;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] * z;
   }
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] + xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] + yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] + zCenter;
   }
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      xyLgth = sqrt(mesh_TRANS[i+SZX] * mesh_TRANS[i+SZX] +
                    mesh_TRANS[i+SZY] * mesh_TRANS[i+SZY]);
      mesh_TRANS[i+BR] = sqrt(xyLgth * xyLgth + mesh_TRANS[i+SZZ] * mesh_TRANS[i+SZZ]);
   }
}

// local resize
void localResize(float *mesh_TRANS, int meshNum,
                 float xCenter, float yCenter, float zCenter, float x, float y, float z)
{
   int dataLoc;
   float xyLgth;
   
   dataLoc = meshNum * TRSZ;
   
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] - xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] - yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] - zCenter;
   
   mesh_TRANS[dataLoc+SZX] = mesh_TRANS[dataLoc+SZX] * x;
   mesh_TRANS[dataLoc+SZY] = mesh_TRANS[dataLoc+SZY] * y;
   mesh_TRANS[dataLoc+SZZ] = mesh_TRANS[dataLoc+SZZ] * z;
   
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] * x;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] * y;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] * z;
   
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] + xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] + yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] + zCenter;
   
   xyLgth = sqrt(mesh_TRANS[dataLoc+SZX] * mesh_TRANS[dataLoc+SZX] +
                 mesh_TRANS[dataLoc+SZY] * mesh_TRANS[dataLoc+SZY]);
   mesh_TRANS[dataLoc+BR] = sqrt(xyLgth * xyLgth + mesh_TRANS[dataLoc+SZZ] * mesh_TRANS[dataLoc+SZZ]);
}


// global rotation using unit circle data
void globalUcRot(float *mesh_TRANS, int mesh_MESHCNT,
                 float xCenter, float yCenter, float zCenter, float *ucData)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      // apply the new rotation to each mesh
      applyXyzUcRot(&mesh_TRANS[i+UCXH], &mesh_TRANS[i+UCXV],
                    &mesh_TRANS[i+UCYH], &mesh_TRANS[i+UCYV],
                    &mesh_TRANS[i+UCZH], &mesh_TRANS[i+UCZV],
                    ucData[0], ucData[1],
                    ucData[2], ucData[3],
                    ucData[4], ucData[5]);
      
      // apply the new rotation to the location of each mesh
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] - xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] - yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] - zCenter;
      
      applyXyzUcRotToPoint(ucData[0], ucData[1],
                           ucData[2], ucData[3],
                           ucData[4], ucData[5],
                           &mesh_TRANS[i+LOCX], &mesh_TRANS[i+LOCY], &mesh_TRANS[i+LOCZ]);
      
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] + xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] + yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] + zCenter;
   }
}

// local rotation using unit circle data
void localUcRot(float *mesh_TRANS, int meshNum,
                float xCenter, float yCenter, float zCenter, float *ucData)
{
   int dataLoc;
   
   dataLoc = meshNum * TRSZ;
   
   // apply the new rotation to the mesh
   applyXyzUcRot(&mesh_TRANS[dataLoc+UCXH], &mesh_TRANS[dataLoc+UCXV],
                 &mesh_TRANS[dataLoc+UCYH], &mesh_TRANS[dataLoc+UCYV],
                 &mesh_TRANS[dataLoc+UCZH], &mesh_TRANS[dataLoc+UCZV],
                 ucData[0], ucData[1],
                 ucData[2], ucData[3],
                 ucData[4], ucData[5]);
   
   // apply the new rotation to the location of the mesh
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] - xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] - yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] - zCenter;
   
   applyXyzUcRotToPoint(ucData[0], ucData[1],
                        ucData[2], ucData[3],
                        ucData[4], ucData[5],
                        &mesh_TRANS[dataLoc+LOCX], &mesh_TRANS[dataLoc+LOCY], &mesh_TRANS[dataLoc+LOCZ]);

   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] + xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] + yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] + zCenter;
}


// global reverse rotation using unit circle data
void globalRevUcRot(float *mesh_TRANS, int mesh_MESHCNT,
                    float xCenter, float yCenter, float zCenter, float *ucData)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      // apply the new rotation to each mesh
      reverseApplyXyzUcRot(&mesh_TRANS[i+UCXH], &mesh_TRANS[i+UCXV],
                           &mesh_TRANS[i+UCYH], &mesh_TRANS[i+UCYV],
                           &mesh_TRANS[i+UCZH], &mesh_TRANS[i+UCZV],
                           ucData[0], ucData[1],
                           ucData[2], ucData[3],
                           ucData[4], ucData[5]);
      
      // apply the new rotation to the location of each mesh
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] - xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] - yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] - zCenter;
      
      reverseApplyXyzUcRotToPoint(ucData[0], ucData[1],
                                  ucData[2], ucData[3],
                                  ucData[4], ucData[5],
                                  &mesh_TRANS[i+LOCX], &mesh_TRANS[i+LOCY], &mesh_TRANS[i+LOCZ]);
      
      mesh_TRANS[i+LOCX] = mesh_TRANS[i+LOCX] + xCenter;
      mesh_TRANS[i+LOCY] = mesh_TRANS[i+LOCY] + yCenter;
      mesh_TRANS[i+LOCZ] = mesh_TRANS[i+LOCZ] + zCenter;
   }
}

// local reverse rotation using unit circle data
void localRevUcRot(float *mesh_TRANS, int meshNum,
                   float xCenter, float yCenter, float zCenter, float *ucData)
{
   int dataLoc;
   
   dataLoc = meshNum * TRSZ;
   
   // apply the new rotation to the mesh
   reverseApplyXyzUcRot(&mesh_TRANS[dataLoc+UCXH], &mesh_TRANS[dataLoc+UCXV],
                        &mesh_TRANS[dataLoc+UCYH], &mesh_TRANS[dataLoc+UCYV],
                        &mesh_TRANS[dataLoc+UCZH], &mesh_TRANS[dataLoc+UCZV],
                        ucData[0], ucData[1],
                        ucData[2], ucData[3],
                        ucData[4], ucData[5]);
   
   // apply the new rotation to the location of the mesh
   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] - xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] - yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] - zCenter;
   
   reverseApplyXyzUcRotToPoint(ucData[0], ucData[1],
                               ucData[2], ucData[3],
                               ucData[4], ucData[5],
                               &mesh_TRANS[dataLoc+LOCX], &mesh_TRANS[dataLoc+LOCY], &mesh_TRANS[dataLoc+LOCZ]);

   mesh_TRANS[dataLoc+LOCX] = mesh_TRANS[dataLoc+LOCX] + xCenter;
   mesh_TRANS[dataLoc+LOCY] = mesh_TRANS[dataLoc+LOCY] + yCenter;
   mesh_TRANS[dataLoc+LOCZ] = mesh_TRANS[dataLoc+LOCZ] + zCenter;
}


void copyTransFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i++)
   mesh_TRANS2[i] = mesh_TRANS1[i];
}

void copyRotFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS2[i+ROTX] = mesh_TRANS1[i+ROTX];
      mesh_TRANS2[i+ROTY] = mesh_TRANS1[i+ROTY];
      mesh_TRANS2[i+ROTZ] = mesh_TRANS1[i+ROTZ];
   }
}

void copyLocFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS2[i+LOCX] = mesh_TRANS1[i+LOCX];
      mesh_TRANS2[i+LOCY] = mesh_TRANS1[i+LOCY];
      mesh_TRANS2[i+LOCZ] = mesh_TRANS1[i+LOCZ];
   }
}

void copySizeFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS2[i+SZX] = mesh_TRANS1[i+SZX];
      mesh_TRANS2[i+SZY] = mesh_TRANS1[i+SZY];
      mesh_TRANS2[i+SZZ] = mesh_TRANS1[i+SZZ];
      mesh_TRANS2[i+BR] = mesh_TRANS1[i+BR];
   }
}

void copyUcRotFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT)
{
   int i;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      mesh_TRANS2[i+UCXH] = mesh_TRANS1[i+UCXH];
      mesh_TRANS2[i+UCXV] = mesh_TRANS1[i+UCXV];
      
      mesh_TRANS2[i+UCYH] = mesh_TRANS1[i+UCYH];
      mesh_TRANS2[i+UCYV] = mesh_TRANS1[i+UCYV];
      
      mesh_TRANS2[i+UCZH] = mesh_TRANS1[i+UCZH];
      mesh_TRANS2[i+UCZV] = mesh_TRANS1[i+UCZV];
   }
}


void copyMeshFromTo(float *mesh_POINT1, int *mesh_POINTDATSZ1, int mesh_start1,
                    float *mesh_POINT2, int *mesh_POINTDATSZ2, int mesh_start2, int mesh_MESHCNT)
{
   int i;
   float *input_POINT;
   float *output_POINT;
   
   input_POINT = &mesh_POINT1[mesh_POINTDATSZ1[mesh_start1]];
   output_POINT = &mesh_POINT2[mesh_POINTDATSZ2[mesh_start2]];
   
   for (i=0; i < mesh_POINTDATSZ1[mesh_start1+mesh_MESHCNT]-mesh_POINTDATSZ1[mesh_start1]; i++)
   output_POINT[i] = input_POINT[i];
}

void copyColorFromTo(char *mesh_VCOLOR1, int *mesh_VCOLORDATSZ1, int mesh_start1,
                     char *mesh_VCOLOR2, int *mesh_VCOLORDATSZ2, int mesh_start2, int mesh_MESHCNT)
{
   int i;
   char *input_VCOLOR;
   char *output_VCOLOR;
   
   input_VCOLOR = &mesh_VCOLOR1[mesh_VCOLORDATSZ1[mesh_start1]];
   output_VCOLOR = &mesh_VCOLOR2[mesh_VCOLORDATSZ2[mesh_start2]];
   
   for (i=0; i < mesh_VCOLORDATSZ1[mesh_start1+mesh_MESHCNT]-mesh_VCOLORDATSZ1[mesh_start1]; i++)
   output_VCOLOR[i] = input_VCOLOR[i];
}

void copyTexCoordFromTo(float *mesh_TEXCOORD1, int *mesh_TEXCOORDDATSZ1, int mesh_start1,
                        float *mesh_TEXCOORD2, int *mesh_TEXCOORDDATSZ2, int mesh_start2, int mesh_MESHCNT)
{
   int i;
   float *input_TEXCOORD;
   float *output_TEXCOORD;
   
   input_TEXCOORD = &mesh_TEXCOORD1[mesh_TEXCOORDDATSZ1[mesh_start1]];
   output_TEXCOORD = &mesh_TEXCOORD2[mesh_TEXCOORDDATSZ2[mesh_start2]];
   
   for (i=0; i < mesh_TEXCOORDDATSZ1[mesh_start1+mesh_MESHCNT]-mesh_TEXCOORDDATSZ1[mesh_start1]; i++)
   output_TEXCOORD[i] = input_TEXCOORD[i];
}
