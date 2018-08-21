#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "3dEngine.h"

//x, y, z, rotation
//x, y, z, location
//x, y, z, size
//y, z, unit circle coordinates for x rotation
//x, z, unit circle coordinates for y rotation
//x, y, unit circle coordinates for z rotation
//bounds radius,

void makeTriTransData(int mesh_start, int mesh_MESHCNT,
                      float *mesh_POINT, int *mesh_POINTDATSZ,
                      short *mesh_TRI, int *mesh_TRIDATSZ, float *tri_TRANS)
{
   int i, transInc;
   int pt1, pt2, pt3;
   float xPt1, yPt1, zPt1;
   float xPt2, yPt2, zPt2;
   float xPt3, yPt3, zPt3;
   float xPt1Save, yPt1Save, zPt1Save;
   float xyLine, xzLine, yzLine;
   float xSize, ySize;
   
   
   transInc = 0;
   
   for (i=mesh_TRIDATSZ[mesh_start]; i < mesh_TRIDATSZ[mesh_start+mesh_MESHCNT]; i+=3)
   {
      // get a triangle
      pt1 = mesh_TRI[i+1]*3;
      pt2 = mesh_TRI[i+2]*3;
      pt3 = mesh_TRI[i+0]*3;
      xPt1 = mesh_POINT[pt1+0]; yPt1 = mesh_POINT[pt1+1]; zPt1 = mesh_POINT[pt1+2];
      xPt2 = mesh_POINT[pt2+0]; yPt2 = mesh_POINT[pt2+1]; zPt2 = mesh_POINT[pt2+2];
      xPt3 = mesh_POINT[pt3+0]; yPt3 = mesh_POINT[pt3+1]; zPt3 = mesh_POINT[pt3+2];
      
      // save to help find location later
      xPt1Save = xPt1; yPt1Save = yPt1; zPt1Save = zPt1;
      
      
      // move the triangle so that the first vertex is at the center
      xPt2 -= xPt1; yPt2 -= yPt1; zPt2 -= zPt1;
      xPt3 -= xPt1; yPt3 -= yPt1; zPt3 -= zPt1;
      xPt1 = 0; yPt1 = 0; zPt1 = 0;
      
      
      // rotate the triangle around the z-axis and y-axis in a way
      // that makes the first line parallel with the x-axis
      
      // find the unit circle coordinates representing the z rotation
      xyLine = sqrt(xPt2 * xPt2 + yPt2 * yPt2);
      
      if (xyLine == 0.0)// no rotation if the line is parallel with the z-axis
      {
         tri_TRANS[transInc+UCZH] = 1.0;
         tri_TRANS[transInc+UCZV] = 0.0;
      }
      else
      {
         tri_TRANS[transInc+UCZH] = xPt2 / xyLine;
         tri_TRANS[transInc+UCZV] = yPt2 / xyLine;
      }
      
      // rotate the triangle in reverse using the unit circle coordinates
      ucRot(tri_TRANS[transInc+UCZH], -tri_TRANS[transInc+UCZV], &xPt2, &yPt2);// z-axis
      ucRot(tri_TRANS[transInc+UCZH], -tri_TRANS[transInc+UCZV], &xPt3, &yPt3);// z-axis
      
      
      // find the unit circle coordinates representing the y rotation
      xzLine = sqrt(xPt2 * xPt2 + zPt2 * zPt2);
      
      if (xzLine == 0.0)// no rotation if the line is parallel with the y-axis
      {
         tri_TRANS[transInc+UCYH] = 1.0;
         tri_TRANS[transInc+UCYV] = 0.0;
      }
      else
      {
         tri_TRANS[transInc+UCYH] = xPt2 / xzLine;
         tri_TRANS[transInc+UCYV] = -zPt2 / xzLine;// negative to rotate in opposite direction
      }
      
      // rotate the triangle in reverse using the unit circle coordinates
      ucRot(tri_TRANS[transInc+UCYH], tri_TRANS[transInc+UCYV], &xPt2, &zPt2);// y-axis
      ucRot(tri_TRANS[transInc+UCYH], tri_TRANS[transInc+UCYV], &xPt3, &zPt3);// y-axis
      
      
      // rotate the triangle around the x-axis in a way
      // that makes the triangle parallel with the z-plane
      
      // find the unit circle coordinates representing the x rotation
      yzLine = sqrt(yPt3 * yPt3 + zPt3 * zPt3);
      
      if (yzLine == 0.0)// no rotation if the line is parallel with the x-axis
      {
         tri_TRANS[transInc+UCXH] = 1.0;
         tri_TRANS[transInc+UCXV] = 0.0;
      }
      else
      {
         tri_TRANS[transInc+UCXH] = yPt3 / yzLine;
         tri_TRANS[transInc+UCXV] = zPt3 / yzLine;
      }
      
      // rotate the triangle in reverse using the unit circle coordinates
      ucRot(tri_TRANS[transInc+UCXH], -tri_TRANS[transInc+UCXV], &yPt3, &zPt3);// x-axis
      
      
      
      // find the x, y and z size
      xSize = xPt2 / 2.0;
      ySize = yPt3 / 2.0;
      tri_TRANS[transInc+SZX] = xSize;
      tri_TRANS[transInc+SZY] = ySize;
      tri_TRANS[transInc+SZZ] = 0;
      
      
      
      // find the x, y and z location
      xPt1 -= xSize;
      yPt1 -= ySize;
      
      applyXyzUcRotToPoint(tri_TRANS[transInc+UCXH], tri_TRANS[transInc+UCXV],
                           tri_TRANS[transInc+UCYH], tri_TRANS[transInc+UCYV],
                           tri_TRANS[transInc+UCZH], tri_TRANS[transInc+UCZV],
                           &xPt1, &yPt1, &zPt1);
      
      tri_TRANS[transInc+LOCX] = xPt1Save - xPt1;
      tri_TRANS[transInc+LOCY] = yPt1Save - yPt1;
      tri_TRANS[transInc+LOCZ] = zPt1Save - zPt1;
      
      
      
      // find the x, y and z rotation
      convertXyzUcRotToRot(tri_TRANS[transInc+UCXH], tri_TRANS[transInc+UCXV],
                           tri_TRANS[transInc+UCYH], tri_TRANS[transInc+UCYV],
                           tri_TRANS[transInc+UCZH], tri_TRANS[transInc+UCZV],
                           &tri_TRANS[transInc+ROTX],
                           &tri_TRANS[transInc+ROTY],
                           &tri_TRANS[transInc+ROTZ]);
      
      
      
      // find the bounds radius
      tri_TRANS[transInc+BR] = sqrt(tri_TRANS[transInc+SZX] * tri_TRANS[transInc+SZX] +
                                    tri_TRANS[transInc+SZY] * tri_TRANS[transInc+SZY]);
      
      
      
      transInc += TRSZ;
   }
}


void makeQuadTransData(int mesh_start, int mesh_MESHCNT,
                       float *mesh_POINT, int *mesh_POINTDATSZ,
                       short *mesh_QUAD, int *mesh_QUADDATSZ, float *quad_TRANS)
{
   int i, transInc;

   float *triangle_POINT;
   int triangle_POINTDATSZ[2] = {0, 9};
   short triangle_TRI[3];
   int triangle_TRIDATSZ[2] = {0, 3};
   float *tri_TRANS;
   
   
   triangle_POINT = mesh_POINT;
   
   transInc = 0;
   
   for (i=mesh_QUADDATSZ[mesh_start]; i < mesh_QUADDATSZ[mesh_start+mesh_MESHCNT]; i+=4)
   {
      // find the transfomation data of the first triangle within the quad
      triangle_TRI[0] = mesh_QUAD[i+2];
      triangle_TRI[1] = mesh_QUAD[i+0];
      triangle_TRI[2] = mesh_QUAD[i+1];
      
      tri_TRANS = &quad_TRANS[transInc];
      
      makeTriTransData(0, 1, &triangle_POINT[0], &triangle_POINTDATSZ[0],
                       &triangle_TRI[0], &triangle_TRIDATSZ[0], &tri_TRANS[0]);
      
      transInc += TRSZ;
      
      // find the transfomation data of the second triangle within the quad
      triangle_TRI[0] = mesh_QUAD[i+0];
      triangle_TRI[1] = mesh_QUAD[i+2];
      triangle_TRI[2] = mesh_QUAD[i+3];
      
      tri_TRANS = &quad_TRANS[transInc];
      
      makeTriTransData(0, 1, &triangle_POINT[0], &triangle_POINTDATSZ[0],
                       &triangle_TRI[0], &triangle_TRIDATSZ[0], &tri_TRANS[0]);
      
      transInc += TRSZ;
   }
}
