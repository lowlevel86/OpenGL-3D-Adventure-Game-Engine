#include <stdio.h>
#include <math.h>
#include "3dEngine.h"

#define TRUE 1
#define FALSE 0


// define all 8 corners of a box
#define PPP 0
#define PNP 1
#define NPP 2
#define NNP 3
#define PPN 4
#define PNN 5
#define NPN 6
#define NNN 7


#define X_POS (PPP * 3 + 0)
#define X_NEG (NNN * 3 + 0)
#define Y_POS (PPP * 3 + 1)
#define Y_NEG (NNN * 3 + 1)
#define Z_POS (PPP * 3 + 2)
#define Z_NEG (NNN * 3 + 2)


#define FIXED_POS_X             0b1
#define FIXED_POS_Y            0b10
#define FIXED_POS_Z           0b100
#define FIXED_NEG_X          0b1000
#define FIXED_NEG_Y         0b10000
#define FIXED_NEG_Z        0b100000
#define MOVING_POS_X      0b1000000
#define MOVING_POS_Y     0b10000000
#define MOVING_POS_Z    0b100000000
#define MOVING_NEG_X   0b1000000000
#define MOVING_NEG_Y  0b10000000000
#define MOVING_NEG_Z 0b100000000000



int parallQuadToNormBoxContact(float *mesh_TRANS, float *pt1, float *pt2,
                                                  float *pt3, float *pt4)
{
// pt2 _____ pt1    //
//     \    \       //
//      \    \      //
//   pt3 \____\ pt4 //
   int notALine;
   int parallelToPlane1;
   int parallelToPlane2;
   int parallelToPlane3;
   int parallelToPlane4;
   float x1, y1, z1;
   float x2, y2, z2;
   float x3, y3, z3;
   float x4, y4, z4;
   float xSubPt1, ySubPt1, zSubPt1;
   float xSubPt2, ySubPt2, zSubPt2;
   int foundSubPt1, foundSubPt2;
   float xTestPt, yTestPt, zTestPt;
   
   
   if ((pt1[0] <= mesh_TRANS[SZX]) && (pt1[0] >= -mesh_TRANS[SZX]))
   if ((pt1[1] <= mesh_TRANS[SZY]) && (pt1[1] >= -mesh_TRANS[SZY]))
   if ((pt1[2] <= mesh_TRANS[SZZ]) && (pt1[2] >= -mesh_TRANS[SZZ]))
   return TRUE;
   
   if ((pt2[0] <= mesh_TRANS[SZX]) && (pt2[0] >= -mesh_TRANS[SZX]))
   if ((pt2[1] <= mesh_TRANS[SZY]) && (pt2[1] >= -mesh_TRANS[SZY]))
   if ((pt2[2] <= mesh_TRANS[SZZ]) && (pt2[2] >= -mesh_TRANS[SZZ]))
   return TRUE;
   
   if ((pt3[0] <= mesh_TRANS[SZX]) && (pt3[0] >= -mesh_TRANS[SZX]))
   if ((pt3[1] <= mesh_TRANS[SZY]) && (pt3[1] >= -mesh_TRANS[SZY]))
   if ((pt3[2] <= mesh_TRANS[SZZ]) && (pt3[2] >= -mesh_TRANS[SZZ]))
   return TRUE;
   
   if ((pt4[0] <= mesh_TRANS[SZX]) && (pt4[0] >= -mesh_TRANS[SZX]))
   if ((pt4[1] <= mesh_TRANS[SZY]) && (pt4[1] >= -mesh_TRANS[SZY]))
   if ((pt4[2] <= mesh_TRANS[SZZ]) && (pt4[2] >= -mesh_TRANS[SZZ]))
   return TRUE;
   
   
   
   //////////////////////////////////////////////////////
   // test the positive and negative x face of the box //
   //////////////////////////////////////////////////////
   
   
   
   foundSubPt1 = FALSE;
   foundSubPt2 = FALSE;
   x1 = pt1[0]; y1 = pt1[1]; z1 = pt1[2];
   x2 = pt2[0]; y2 = pt2[1]; z2 = pt2[2];
   x3 = pt3[0]; y3 = pt3[1]; z3 = pt3[2];
   x4 = pt4[0]; y4 = pt4[1]; z4 = pt4[2];
   
   // shrink the non-planar quad lines to the positive x plane of the box
   resizeLineToPlaneX(pt1[0], pt1[1], pt1[2], &x2, &y2, &z2,
                      mesh_TRANS[SZX], &notALine, &parallelToPlane1);
   resizeLineToPlaneX(pt2[0], pt2[1], pt2[2], &x3, &y3, &z3,
                      mesh_TRANS[SZX], &notALine, &parallelToPlane2);
   resizeLineToPlaneX(pt3[0], pt3[1], pt3[2], &x4, &y4, &z4,
                      mesh_TRANS[SZX], &notALine, &parallelToPlane3);
   resizeLineToPlaneX(pt4[0], pt4[1], pt4[2], &x1, &y1, &z1,
                      mesh_TRANS[SZX], &notALine, &parallelToPlane4);
   
   // find 2 points where the quad lines intercept the positive x plane of the box
   if (parallelToPlane1 == FALSE)
   if (((x2 <= pt1[0]) && (x2 >= pt2[0])) || ((x2 >= pt1[0]) && (x2 <= pt2[0])))
   if (((y2 <= pt1[1]) && (y2 >= pt2[1])) || ((y2 >= pt1[1]) && (y2 <= pt2[1])))
   if (((z2 <= pt1[2]) && (z2 >= pt2[2])) || ((z2 >= pt1[2]) && (z2 <= pt2[2])))
   {
      xSubPt1 = x2;
      ySubPt1 = y2;
      zSubPt1 = z2;
      foundSubPt1 = TRUE;
   }
   
   if (parallelToPlane2 == FALSE)
   if (((x3 <= pt2[0]) && (x3 >= pt3[0])) || ((x3 >= pt2[0]) && (x3 <= pt3[0])))
   if (((y3 <= pt2[1]) && (y3 >= pt3[1])) || ((y3 >= pt2[1]) && (y3 <= pt3[1])))
   if (((z3 <= pt2[2]) && (z3 >= pt3[2])) || ((z3 >= pt2[2]) && (z3 <= pt3[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x3;
         ySubPt1 = y3;
         zSubPt1 = z3;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x3) || (ySubPt1 != y3) || (zSubPt1 != z3))
      {
         xSubPt2 = x3;
         ySubPt2 = y3;
         zSubPt2 = z3;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane3 == FALSE)
   if (((x4 <= pt3[0]) && (x4 >= pt4[0])) || ((x4 >= pt3[0]) && (x4 <= pt4[0])))
   if (((y4 <= pt3[1]) && (y4 >= pt4[1])) || ((y4 >= pt3[1]) && (y4 <= pt4[1])))
   if (((z4 <= pt3[2]) && (z4 >= pt4[2])) || ((z4 >= pt3[2]) && (z4 <= pt4[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x4;
         ySubPt1 = y4;
         zSubPt1 = z4;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x4) || (ySubPt1 != y4) || (zSubPt1 != z4))
      {
         xSubPt2 = x4;
         ySubPt2 = y4;
         zSubPt2 = z4;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane4 == FALSE)
   if (((x1 <= pt4[0]) && (x1 >= pt1[0])) || ((x1 >= pt4[0]) && (x1 <= pt1[0])))
   if (((y1 <= pt4[1]) && (y1 >= pt1[1])) || ((y1 >= pt4[1]) && (y1 <= pt1[1])))
   if (((z1 <= pt4[2]) && (z1 >= pt1[2])) || ((z1 >= pt4[2]) && (z1 <= pt1[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x1;
         ySubPt1 = y1;
         zSubPt1 = z1;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x1) || (ySubPt1 != y1) || (zSubPt1 != z1))
      {
         xSubPt2 = x1;
         ySubPt2 = y1;
         zSubPt2 = z1;
         foundSubPt2 = TRUE;
      }
   }
   
   if (foundSubPt1)
   {
      if ((xSubPt1 <= mesh_TRANS[SZX]) && (xSubPt1 >= -mesh_TRANS[SZX]))
      if ((ySubPt1 <= mesh_TRANS[SZY]) && (ySubPt1 >= -mesh_TRANS[SZY]))
      if ((zSubPt1 <= mesh_TRANS[SZZ]) && (zSubPt1 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if (foundSubPt2)
   {
      if ((xSubPt2 <= mesh_TRANS[SZX]) && (xSubPt2 >= -mesh_TRANS[SZX]))
      if ((ySubPt2 <= mesh_TRANS[SZY]) && (ySubPt2 >= -mesh_TRANS[SZY]))
      if ((zSubPt2 <= mesh_TRANS[SZZ]) && (zSubPt2 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if ((foundSubPt1) && (foundSubPt2))
   {
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   
   
   foundSubPt1 = FALSE;
   foundSubPt2 = FALSE;
   x1 = pt1[0]; y1 = pt1[1]; z1 = pt1[2];
   x2 = pt2[0]; y2 = pt2[1]; z2 = pt2[2];
   x3 = pt3[0]; y3 = pt3[1]; z3 = pt3[2];
   x4 = pt4[0]; y4 = pt4[1]; z4 = pt4[2];
   
   // shrink the non-planar quad lines to the negative x plane of the box
   resizeLineToPlaneX(pt1[0], pt1[1], pt1[2], &x2, &y2, &z2,
                      -mesh_TRANS[SZX], &notALine, &parallelToPlane1);
   resizeLineToPlaneX(pt2[0], pt2[1], pt2[2], &x3, &y3, &z3,
                      -mesh_TRANS[SZX], &notALine, &parallelToPlane2);
   resizeLineToPlaneX(pt3[0], pt3[1], pt3[2], &x4, &y4, &z4,
                      -mesh_TRANS[SZX], &notALine, &parallelToPlane3);
   resizeLineToPlaneX(pt4[0], pt4[1], pt4[2], &x1, &y1, &z1,
                      -mesh_TRANS[SZX], &notALine, &parallelToPlane4);
   
   // find 2 points where the quad lines intercept the negative x plane of the box
   if (parallelToPlane1 == FALSE)
   if (((x2 <= pt1[0]) && (x2 >= pt2[0])) || ((x2 >= pt1[0]) && (x2 <= pt2[0])))
   if (((y2 <= pt1[1]) && (y2 >= pt2[1])) || ((y2 >= pt1[1]) && (y2 <= pt2[1])))
   if (((z2 <= pt1[2]) && (z2 >= pt2[2])) || ((z2 >= pt1[2]) && (z2 <= pt2[2])))
   {
      xSubPt1 = x2;
      ySubPt1 = y2;
      zSubPt1 = z2;
      foundSubPt1 = TRUE;
   }
   
   if (parallelToPlane2 == FALSE)
   if (((x3 <= pt2[0]) && (x3 >= pt3[0])) || ((x3 >= pt2[0]) && (x3 <= pt3[0])))
   if (((y3 <= pt2[1]) && (y3 >= pt3[1])) || ((y3 >= pt2[1]) && (y3 <= pt3[1])))
   if (((z3 <= pt2[2]) && (z3 >= pt3[2])) || ((z3 >= pt2[2]) && (z3 <= pt3[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x3;
         ySubPt1 = y3;
         zSubPt1 = z3;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x3) || (ySubPt1 != y3) || (zSubPt1 != z3))
      {
         xSubPt2 = x3;
         ySubPt2 = y3;
         zSubPt2 = z3;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane3 == FALSE)
   if (((x4 <= pt3[0]) && (x4 >= pt4[0])) || ((x4 >= pt3[0]) && (x4 <= pt4[0])))
   if (((y4 <= pt3[1]) && (y4 >= pt4[1])) || ((y4 >= pt3[1]) && (y4 <= pt4[1])))
   if (((z4 <= pt3[2]) && (z4 >= pt4[2])) || ((z4 >= pt3[2]) && (z4 <= pt4[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x4;
         ySubPt1 = y4;
         zSubPt1 = z4;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x4) || (ySubPt1 != y4) || (zSubPt1 != z4))
      {
         xSubPt2 = x4;
         ySubPt2 = y4;
         zSubPt2 = z4;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane4 == FALSE)
   if (((x1 <= pt4[0]) && (x1 >= pt1[0])) || ((x1 >= pt4[0]) && (x1 <= pt1[0])))
   if (((y1 <= pt4[1]) && (y1 >= pt1[1])) || ((y1 >= pt4[1]) && (y1 <= pt1[1])))
   if (((z1 <= pt4[2]) && (z1 >= pt1[2])) || ((z1 >= pt4[2]) && (z1 <= pt1[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x1;
         ySubPt1 = y1;
         zSubPt1 = z1;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x1) || (ySubPt1 != y1) || (zSubPt1 != z1))
      {
         xSubPt2 = x1;
         ySubPt2 = y1;
         zSubPt2 = z1;
         foundSubPt2 = TRUE;
      }
   }
   
   if (foundSubPt1)
   {
      if ((xSubPt1 <= mesh_TRANS[SZX]) && (xSubPt1 >= -mesh_TRANS[SZX]))
      if ((ySubPt1 <= mesh_TRANS[SZY]) && (ySubPt1 >= -mesh_TRANS[SZY]))
      if ((zSubPt1 <= mesh_TRANS[SZZ]) && (zSubPt1 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if (foundSubPt2)
   {
      if ((xSubPt2 <= mesh_TRANS[SZX]) && (xSubPt2 >= -mesh_TRANS[SZX]))
      if ((ySubPt2 <= mesh_TRANS[SZY]) && (ySubPt2 >= -mesh_TRANS[SZY]))
      if ((zSubPt2 <= mesh_TRANS[SZZ]) && (zSubPt2 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if ((foundSubPt1) && (foundSubPt2))
   {
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   
   
   //////////////////////////////////////////////////////
   // test the positive and negative y face of the box //
   //////////////////////////////////////////////////////
   
   
   
   foundSubPt1 = FALSE;
   foundSubPt2 = FALSE;
   x1 = pt1[0]; y1 = pt1[1]; z1 = pt1[2];
   x2 = pt2[0]; y2 = pt2[1]; z2 = pt2[2];
   x3 = pt3[0]; y3 = pt3[1]; z3 = pt3[2];
   x4 = pt4[0]; y4 = pt4[1]; z4 = pt4[2];
   
   // shrink the non-planar quad lines to the positive y plane of the box
   resizeLineToPlaneY(pt1[0], pt1[1], pt1[2], &x2, &y2, &z2,
                      mesh_TRANS[SZY], &notALine, &parallelToPlane1);
   resizeLineToPlaneY(pt2[0], pt2[1], pt2[2], &x3, &y3, &z3,
                      mesh_TRANS[SZY], &notALine, &parallelToPlane2);
   resizeLineToPlaneY(pt3[0], pt3[1], pt3[2], &x4, &y4, &z4,
                      mesh_TRANS[SZY], &notALine, &parallelToPlane3);
   resizeLineToPlaneY(pt4[0], pt4[1], pt4[2], &x1, &y1, &z1,
                      mesh_TRANS[SZY], &notALine, &parallelToPlane4);
   
   // find 2 points where the quad lines intercept the positive y plane of the box
   if (parallelToPlane1 == FALSE)
   if (((x2 <= pt1[0]) && (x2 >= pt2[0])) || ((x2 >= pt1[0]) && (x2 <= pt2[0])))
   if (((y2 <= pt1[1]) && (y2 >= pt2[1])) || ((y2 >= pt1[1]) && (y2 <= pt2[1])))
   if (((z2 <= pt1[2]) && (z2 >= pt2[2])) || ((z2 >= pt1[2]) && (z2 <= pt2[2])))
   {
      xSubPt1 = x2;
      ySubPt1 = y2;
      zSubPt1 = z2;
      foundSubPt1 = TRUE;
   }
   
   if (parallelToPlane2 == FALSE)
   if (((x3 <= pt2[0]) && (x3 >= pt3[0])) || ((x3 >= pt2[0]) && (x3 <= pt3[0])))
   if (((y3 <= pt2[1]) && (y3 >= pt3[1])) || ((y3 >= pt2[1]) && (y3 <= pt3[1])))
   if (((z3 <= pt2[2]) && (z3 >= pt3[2])) || ((z3 >= pt2[2]) && (z3 <= pt3[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x3;
         ySubPt1 = y3;
         zSubPt1 = z3;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x3) || (ySubPt1 != y3) || (zSubPt1 != z3))
      {
         xSubPt2 = x3;
         ySubPt2 = y3;
         zSubPt2 = z3;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane3 == FALSE)
   if (((x4 <= pt3[0]) && (x4 >= pt4[0])) || ((x4 >= pt3[0]) && (x4 <= pt4[0])))
   if (((y4 <= pt3[1]) && (y4 >= pt4[1])) || ((y4 >= pt3[1]) && (y4 <= pt4[1])))
   if (((z4 <= pt3[2]) && (z4 >= pt4[2])) || ((z4 >= pt3[2]) && (z4 <= pt4[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x4;
         ySubPt1 = y4;
         zSubPt1 = z4;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x4) || (ySubPt1 != y4) || (zSubPt1 != z4))
      {
         xSubPt2 = x4;
         ySubPt2 = y4;
         zSubPt2 = z4;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane4 == FALSE)
   if (((x1 <= pt4[0]) && (x1 >= pt1[0])) || ((x1 >= pt4[0]) && (x1 <= pt1[0])))
   if (((y1 <= pt4[1]) && (y1 >= pt1[1])) || ((y1 >= pt4[1]) && (y1 <= pt1[1])))
   if (((z1 <= pt4[2]) && (z1 >= pt1[2])) || ((z1 >= pt4[2]) && (z1 <= pt1[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x1;
         ySubPt1 = y1;
         zSubPt1 = z1;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x1) || (ySubPt1 != y1) || (zSubPt1 != z1))
      {
         xSubPt2 = x1;
         ySubPt2 = y1;
         zSubPt2 = z1;
         foundSubPt2 = TRUE;
      }
   }
   
   if (foundSubPt1)
   {
      if ((xSubPt1 <= mesh_TRANS[SZX]) && (xSubPt1 >= -mesh_TRANS[SZX]))
      if ((ySubPt1 <= mesh_TRANS[SZY]) && (ySubPt1 >= -mesh_TRANS[SZY]))
      if ((zSubPt1 <= mesh_TRANS[SZZ]) && (zSubPt1 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if (foundSubPt2)
   {
      if ((xSubPt2 <= mesh_TRANS[SZX]) && (xSubPt2 >= -mesh_TRANS[SZX]))
      if ((ySubPt2 <= mesh_TRANS[SZY]) && (ySubPt2 >= -mesh_TRANS[SZY]))
      if ((zSubPt2 <= mesh_TRANS[SZZ]) && (zSubPt2 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if ((foundSubPt1) && (foundSubPt2))
   {
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   
   
   foundSubPt1 = FALSE;
   foundSubPt2 = FALSE;
   x1 = pt1[0]; y1 = pt1[1]; z1 = pt1[2];
   x2 = pt2[0]; y2 = pt2[1]; z2 = pt2[2];
   x3 = pt3[0]; y3 = pt3[1]; z3 = pt3[2];
   x4 = pt4[0]; y4 = pt4[1]; z4 = pt4[2];
   
   // shrink the non-planar quad lines to the negative y plane of the box
   resizeLineToPlaneY(pt1[0], pt1[1], pt1[2], &x2, &y2, &z2,
                      -mesh_TRANS[SZY], &notALine, &parallelToPlane1);
   resizeLineToPlaneY(pt2[0], pt2[1], pt2[2], &x3, &y3, &z3,
                      -mesh_TRANS[SZY], &notALine, &parallelToPlane2);
   resizeLineToPlaneY(pt3[0], pt3[1], pt3[2], &x4, &y4, &z4,
                      -mesh_TRANS[SZY], &notALine, &parallelToPlane3);
   resizeLineToPlaneY(pt4[0], pt4[1], pt4[2], &x1, &y1, &z1,
                      -mesh_TRANS[SZY], &notALine, &parallelToPlane4);
   
   // find 2 points where the quad lines intercept the negative y plane of the box
   if (parallelToPlane1 == FALSE)
   if (((x2 <= pt1[0]) && (x2 >= pt2[0])) || ((x2 >= pt1[0]) && (x2 <= pt2[0])))
   if (((y2 <= pt1[1]) && (y2 >= pt2[1])) || ((y2 >= pt1[1]) && (y2 <= pt2[1])))
   if (((z2 <= pt1[2]) && (z2 >= pt2[2])) || ((z2 >= pt1[2]) && (z2 <= pt2[2])))
   {
      xSubPt1 = x2;
      ySubPt1 = y2;
      zSubPt1 = z2;
      foundSubPt1 = TRUE;
   }
   
   if (parallelToPlane2 == FALSE)
   if (((x3 <= pt2[0]) && (x3 >= pt3[0])) || ((x3 >= pt2[0]) && (x3 <= pt3[0])))
   if (((y3 <= pt2[1]) && (y3 >= pt3[1])) || ((y3 >= pt2[1]) && (y3 <= pt3[1])))
   if (((z3 <= pt2[2]) && (z3 >= pt3[2])) || ((z3 >= pt2[2]) && (z3 <= pt3[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x3;
         ySubPt1 = y3;
         zSubPt1 = z3;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x3) || (ySubPt1 != y3) || (zSubPt1 != z3))
      {
         xSubPt2 = x3;
         ySubPt2 = y3;
         zSubPt2 = z3;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane3 == FALSE)
   if (((x4 <= pt3[0]) && (x4 >= pt4[0])) || ((x4 >= pt3[0]) && (x4 <= pt4[0])))
   if (((y4 <= pt3[1]) && (y4 >= pt4[1])) || ((y4 >= pt3[1]) && (y4 <= pt4[1])))
   if (((z4 <= pt3[2]) && (z4 >= pt4[2])) || ((z4 >= pt3[2]) && (z4 <= pt4[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x4;
         ySubPt1 = y4;
         zSubPt1 = z4;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x4) || (ySubPt1 != y4) || (zSubPt1 != z4))
      {
         xSubPt2 = x4;
         ySubPt2 = y4;
         zSubPt2 = z4;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane4 == FALSE)
   if (((x1 <= pt4[0]) && (x1 >= pt1[0])) || ((x1 >= pt4[0]) && (x1 <= pt1[0])))
   if (((y1 <= pt4[1]) && (y1 >= pt1[1])) || ((y1 >= pt4[1]) && (y1 <= pt1[1])))
   if (((z1 <= pt4[2]) && (z1 >= pt1[2])) || ((z1 >= pt4[2]) && (z1 <= pt1[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x1;
         ySubPt1 = y1;
         zSubPt1 = z1;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x1) || (ySubPt1 != y1) || (zSubPt1 != z1))
      {
         xSubPt2 = x1;
         ySubPt2 = y1;
         zSubPt2 = z1;
         foundSubPt2 = TRUE;
      }
   }
   
   if (foundSubPt1)
   {
      if ((xSubPt1 <= mesh_TRANS[SZX]) && (xSubPt1 >= -mesh_TRANS[SZX]))
      if ((ySubPt1 <= mesh_TRANS[SZY]) && (ySubPt1 >= -mesh_TRANS[SZY]))
      if ((zSubPt1 <= mesh_TRANS[SZZ]) && (zSubPt1 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if (foundSubPt2)
   {
      if ((xSubPt2 <= mesh_TRANS[SZX]) && (xSubPt2 >= -mesh_TRANS[SZX]))
      if ((ySubPt2 <= mesh_TRANS[SZY]) && (ySubPt2 >= -mesh_TRANS[SZY]))
      if ((zSubPt2 <= mesh_TRANS[SZZ]) && (zSubPt2 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if ((foundSubPt1) && (foundSubPt2))
   {
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneZ(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   
   
   //////////////////////////////////////////////////////
   // test the positive and negative z face of the box //
   //////////////////////////////////////////////////////
   
   
   
   foundSubPt1 = FALSE;
   foundSubPt2 = FALSE;
   x1 = pt1[0]; y1 = pt1[1]; z1 = pt1[2];
   x2 = pt2[0]; y2 = pt2[1]; z2 = pt2[2];
   x3 = pt3[0]; y3 = pt3[1]; z3 = pt3[2];
   x4 = pt4[0]; y4 = pt4[1]; z4 = pt4[2];
   
   // shrink the non-planar quad lines to the positive z plane of the box
   resizeLineToPlaneZ(pt1[0], pt1[1], pt1[2], &x2, &y2, &z2,
                      mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
   resizeLineToPlaneZ(pt2[0], pt2[1], pt2[2], &x3, &y3, &z3,
                      mesh_TRANS[SZZ], &notALine, &parallelToPlane2);
   resizeLineToPlaneZ(pt3[0], pt3[1], pt3[2], &x4, &y4, &z4,
                      mesh_TRANS[SZZ], &notALine, &parallelToPlane3);
   resizeLineToPlaneZ(pt4[0], pt4[1], pt4[2], &x1, &y1, &z1,
                      mesh_TRANS[SZZ], &notALine, &parallelToPlane4);
   
   // find 2 points where the quad lines intercept the positive z plane of the box
   if (parallelToPlane1 == FALSE)
   if (((x2 <= pt1[0]) && (x2 >= pt2[0])) || ((x2 >= pt1[0]) && (x2 <= pt2[0])))
   if (((y2 <= pt1[1]) && (y2 >= pt2[1])) || ((y2 >= pt1[1]) && (y2 <= pt2[1])))
   if (((z2 <= pt1[2]) && (z2 >= pt2[2])) || ((z2 >= pt1[2]) && (z2 <= pt2[2])))
   {
      xSubPt1 = x2;
      ySubPt1 = y2;
      zSubPt1 = z2;
      foundSubPt1 = TRUE;
   }
   
   if (parallelToPlane2 == FALSE)
   if (((x3 <= pt2[0]) && (x3 >= pt3[0])) || ((x3 >= pt2[0]) && (x3 <= pt3[0])))
   if (((y3 <= pt2[1]) && (y3 >= pt3[1])) || ((y3 >= pt2[1]) && (y3 <= pt3[1])))
   if (((z3 <= pt2[2]) && (z3 >= pt3[2])) || ((z3 >= pt2[2]) && (z3 <= pt3[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x3;
         ySubPt1 = y3;
         zSubPt1 = z3;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x3) || (ySubPt1 != y3) || (zSubPt1 != z3))
      {
         xSubPt2 = x3;
         ySubPt2 = y3;
         zSubPt2 = z3;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane3 == FALSE)
   if (((x4 <= pt3[0]) && (x4 >= pt4[0])) || ((x4 >= pt3[0]) && (x4 <= pt4[0])))
   if (((y4 <= pt3[1]) && (y4 >= pt4[1])) || ((y4 >= pt3[1]) && (y4 <= pt4[1])))
   if (((z4 <= pt3[2]) && (z4 >= pt4[2])) || ((z4 >= pt3[2]) && (z4 <= pt4[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x4;
         ySubPt1 = y4;
         zSubPt1 = z4;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x4) || (ySubPt1 != y4) || (zSubPt1 != z4))
      {
         xSubPt2 = x4;
         ySubPt2 = y4;
         zSubPt2 = z4;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane4 == FALSE)
   if (((x1 <= pt4[0]) && (x1 >= pt1[0])) || ((x1 >= pt4[0]) && (x1 <= pt1[0])))
   if (((y1 <= pt4[1]) && (y1 >= pt1[1])) || ((y1 >= pt4[1]) && (y1 <= pt1[1])))
   if (((z1 <= pt4[2]) && (z1 >= pt1[2])) || ((z1 >= pt4[2]) && (z1 <= pt1[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x1;
         ySubPt1 = y1;
         zSubPt1 = z1;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x1) || (ySubPt1 != y1) || (zSubPt1 != z1))
      {
         xSubPt2 = x1;
         ySubPt2 = y1;
         zSubPt2 = z1;
         foundSubPt2 = TRUE;
      }
   }
   
   if (foundSubPt1)
   {
      if ((xSubPt1 <= mesh_TRANS[SZX]) && (xSubPt1 >= -mesh_TRANS[SZX]))
      if ((ySubPt1 <= mesh_TRANS[SZY]) && (ySubPt1 >= -mesh_TRANS[SZY]))
      if ((zSubPt1 <= mesh_TRANS[SZZ]) && (zSubPt1 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if (foundSubPt2)
   {
      if ((xSubPt2 <= mesh_TRANS[SZX]) && (xSubPt2 >= -mesh_TRANS[SZX]))
      if ((ySubPt2 <= mesh_TRANS[SZY]) && (ySubPt2 >= -mesh_TRANS[SZY]))
      if ((zSubPt2 <= mesh_TRANS[SZZ]) && (zSubPt2 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if ((foundSubPt1) && (foundSubPt2))
   {
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   
   
   foundSubPt1 = FALSE;
   foundSubPt2 = FALSE;
   x1 = pt1[0]; y1 = pt1[1]; z1 = pt1[2];
   x2 = pt2[0]; y2 = pt2[1]; z2 = pt2[2];
   x3 = pt3[0]; y3 = pt3[1]; z3 = pt3[2];
   x4 = pt4[0]; y4 = pt4[1]; z4 = pt4[2];
   
   // shrink the non-planar quad lines to the negative z plane of the box
   resizeLineToPlaneZ(pt1[0], pt1[1], pt1[2], &x2, &y2, &z2,
                      -mesh_TRANS[SZZ], &notALine, &parallelToPlane1);
   resizeLineToPlaneZ(pt2[0], pt2[1], pt2[2], &x3, &y3, &z3,
                      -mesh_TRANS[SZZ], &notALine, &parallelToPlane2);
   resizeLineToPlaneZ(pt3[0], pt3[1], pt3[2], &x4, &y4, &z4,
                      -mesh_TRANS[SZZ], &notALine, &parallelToPlane3);
   resizeLineToPlaneZ(pt4[0], pt4[1], pt4[2], &x1, &y1, &z1,
                      -mesh_TRANS[SZZ], &notALine, &parallelToPlane4);
   
   // find 2 points where the quad lines intercept the negative z plane of the box
   if (parallelToPlane1 == FALSE)
   if (((x2 <= pt1[0]) && (x2 >= pt2[0])) || ((x2 >= pt1[0]) && (x2 <= pt2[0])))
   if (((y2 <= pt1[1]) && (y2 >= pt2[1])) || ((y2 >= pt1[1]) && (y2 <= pt2[1])))
   if (((z2 <= pt1[2]) && (z2 >= pt2[2])) || ((z2 >= pt1[2]) && (z2 <= pt2[2])))
   {
      xSubPt1 = x2;
      ySubPt1 = y2;
      zSubPt1 = z2;
      foundSubPt1 = TRUE;
   }
   
   if (parallelToPlane2 == FALSE)
   if (((x3 <= pt2[0]) && (x3 >= pt3[0])) || ((x3 >= pt2[0]) && (x3 <= pt3[0])))
   if (((y3 <= pt2[1]) && (y3 >= pt3[1])) || ((y3 >= pt2[1]) && (y3 <= pt3[1])))
   if (((z3 <= pt2[2]) && (z3 >= pt3[2])) || ((z3 >= pt2[2]) && (z3 <= pt3[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x3;
         ySubPt1 = y3;
         zSubPt1 = z3;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x3) || (ySubPt1 != y3) || (zSubPt1 != z3))
      {
         xSubPt2 = x3;
         ySubPt2 = y3;
         zSubPt2 = z3;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane3 == FALSE)
   if (((x4 <= pt3[0]) && (x4 >= pt4[0])) || ((x4 >= pt3[0]) && (x4 <= pt4[0])))
   if (((y4 <= pt3[1]) && (y4 >= pt4[1])) || ((y4 >= pt3[1]) && (y4 <= pt4[1])))
   if (((z4 <= pt3[2]) && (z4 >= pt4[2])) || ((z4 >= pt3[2]) && (z4 <= pt4[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x4;
         ySubPt1 = y4;
         zSubPt1 = z4;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x4) || (ySubPt1 != y4) || (zSubPt1 != z4))
      {
         xSubPt2 = x4;
         ySubPt2 = y4;
         zSubPt2 = z4;
         foundSubPt2 = TRUE;
      }
   }
   
   if (parallelToPlane4 == FALSE)
   if (((x1 <= pt4[0]) && (x1 >= pt1[0])) || ((x1 >= pt4[0]) && (x1 <= pt1[0])))
   if (((y1 <= pt4[1]) && (y1 >= pt1[1])) || ((y1 >= pt4[1]) && (y1 <= pt1[1])))
   if (((z1 <= pt4[2]) && (z1 >= pt1[2])) || ((z1 >= pt4[2]) && (z1 <= pt1[2])))
   {
      if (foundSubPt1 == FALSE)
      {
         xSubPt1 = x1;
         ySubPt1 = y1;
         zSubPt1 = z1;
         foundSubPt1 = TRUE;
      }
      else
      if ((xSubPt1 != x1) || (ySubPt1 != y1) || (zSubPt1 != z1))
      {
         xSubPt2 = x1;
         ySubPt2 = y1;
         zSubPt2 = z1;
         foundSubPt2 = TRUE;
      }
   }
   
   if (foundSubPt1)
   {
      if ((xSubPt1 <= mesh_TRANS[SZX]) && (xSubPt1 >= -mesh_TRANS[SZX]))
      if ((ySubPt1 <= mesh_TRANS[SZY]) && (ySubPt1 >= -mesh_TRANS[SZY]))
      if ((zSubPt1 <= mesh_TRANS[SZZ]) && (zSubPt1 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if (foundSubPt2)
   {
      if ((xSubPt2 <= mesh_TRANS[SZX]) && (xSubPt2 >= -mesh_TRANS[SZX]))
      if ((ySubPt2 <= mesh_TRANS[SZY]) && (ySubPt2 >= -mesh_TRANS[SZY]))
      if ((zSubPt2 <= mesh_TRANS[SZZ]) && (zSubPt2 >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   if ((foundSubPt1) && (foundSubPt2))
   {
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneX(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZX], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
      
      
      xTestPt = xSubPt2;
      yTestPt = ySubPt2;
      zTestPt = zSubPt2;
      resizeLineToPlaneY(xSubPt1, ySubPt1, zSubPt1, &xTestPt, &yTestPt, &zTestPt,
                         -mesh_TRANS[SZY], &notALine, &parallelToPlane1);
      
      if (((xTestPt <= xSubPt1) && (xTestPt >= xSubPt2)) || ((xTestPt >= xSubPt1) && (xTestPt <= xSubPt2)))
      if (((yTestPt <= ySubPt1) && (yTestPt >= ySubPt2)) || ((yTestPt >= ySubPt1) && (yTestPt <= ySubPt2)))
      if (((zTestPt <= zSubPt1) && (zTestPt >= zSubPt2)) || ((zTestPt >= zSubPt1) && (zTestPt <= zSubPt2)))
      if ((xTestPt <= mesh_TRANS[SZX]) && (xTestPt >= -mesh_TRANS[SZX]))
      if ((yTestPt <= mesh_TRANS[SZY]) && (yTestPt >= -mesh_TRANS[SZY]))
      if ((zTestPt <= mesh_TRANS[SZZ]) && (zTestPt >= -mesh_TRANS[SZZ]))
      return TRUE;
   }
   
   
   
   return FALSE;
}



int boundsContact(float *mesh_TRANS1, float *mesh_TRANS2)
{
   if (((mesh_TRANS1[LOCX]+mesh_TRANS1[BR] >= mesh_TRANS2[LOCX]+mesh_TRANS2[BR]) &&
        (mesh_TRANS1[LOCX]-mesh_TRANS1[BR] <= mesh_TRANS2[LOCX]+mesh_TRANS2[BR])) ||
       ((mesh_TRANS1[LOCX]+mesh_TRANS1[BR] >= mesh_TRANS2[LOCX]-mesh_TRANS2[BR]) &&
        (mesh_TRANS1[LOCX]-mesh_TRANS1[BR] <= mesh_TRANS2[LOCX]-mesh_TRANS2[BR])))
   if (((mesh_TRANS1[LOCY]+mesh_TRANS1[BR] >= mesh_TRANS2[LOCY]+mesh_TRANS2[BR]) &&
        (mesh_TRANS1[LOCY]-mesh_TRANS1[BR] <= mesh_TRANS2[LOCY]+mesh_TRANS2[BR])) ||
       ((mesh_TRANS1[LOCY]+mesh_TRANS1[BR] >= mesh_TRANS2[LOCY]-mesh_TRANS2[BR]) &&
        (mesh_TRANS1[LOCY]-mesh_TRANS1[BR] <= mesh_TRANS2[LOCY]-mesh_TRANS2[BR])))
   if (((mesh_TRANS1[LOCZ]+mesh_TRANS1[BR] >= mesh_TRANS2[LOCZ]+mesh_TRANS2[BR]) &&
        (mesh_TRANS1[LOCZ]-mesh_TRANS1[BR] <= mesh_TRANS2[LOCZ]+mesh_TRANS2[BR])) ||
       ((mesh_TRANS1[LOCZ]+mesh_TRANS1[BR] >= mesh_TRANS2[LOCZ]-mesh_TRANS2[BR]) &&
        (mesh_TRANS1[LOCZ]-mesh_TRANS1[BR] <= mesh_TRANS2[LOCZ]-mesh_TRANS2[BR])))
   return TRUE;

   if (((mesh_TRANS1[LOCX]+mesh_TRANS2[BR] >= mesh_TRANS2[LOCX]+mesh_TRANS1[BR]) &&
        (mesh_TRANS1[LOCX]-mesh_TRANS2[BR] <= mesh_TRANS2[LOCX]+mesh_TRANS1[BR])) ||
       ((mesh_TRANS1[LOCX]+mesh_TRANS2[BR] >= mesh_TRANS2[LOCX]-mesh_TRANS1[BR]) &&
        (mesh_TRANS1[LOCX]-mesh_TRANS2[BR] <= mesh_TRANS2[LOCX]-mesh_TRANS1[BR])))
   if (((mesh_TRANS1[LOCY]+mesh_TRANS2[BR] >= mesh_TRANS2[LOCY]+mesh_TRANS1[BR]) &&
        (mesh_TRANS1[LOCY]-mesh_TRANS2[BR] <= mesh_TRANS2[LOCY]+mesh_TRANS1[BR])) ||
       ((mesh_TRANS1[LOCY]+mesh_TRANS2[BR] >= mesh_TRANS2[LOCY]-mesh_TRANS1[BR]) &&
        (mesh_TRANS1[LOCY]-mesh_TRANS2[BR] <= mesh_TRANS2[LOCY]-mesh_TRANS1[BR])))
   if (((mesh_TRANS1[LOCZ]+mesh_TRANS2[BR] >= mesh_TRANS2[LOCZ]+mesh_TRANS1[BR]) &&
        (mesh_TRANS1[LOCZ]-mesh_TRANS2[BR] <= mesh_TRANS2[LOCZ]+mesh_TRANS1[BR])) ||
       ((mesh_TRANS1[LOCZ]+mesh_TRANS2[BR] >= mesh_TRANS2[LOCZ]-mesh_TRANS1[BR]) &&
        (mesh_TRANS1[LOCZ]-mesh_TRANS2[BR] <= mesh_TRANS2[LOCZ]-mesh_TRANS1[BR])))
   return TRUE;

   return FALSE;
}



int nonOrientBoxContact(float *ptData1, float *ptData2)
{
   if (((ptData1[X_POS] >= ptData2[X_POS]) &&
        (ptData1[X_NEG] <= ptData2[X_POS])) ||
       ((ptData1[X_POS] >= ptData2[X_NEG]) &&
        (ptData1[X_NEG] <= ptData2[X_NEG])))
   if (((ptData1[Y_POS] >= ptData2[Y_POS]) &&
        (ptData1[Y_NEG] <= ptData2[Y_POS])) ||
       ((ptData1[Y_POS] >= ptData2[Y_NEG]) &&
        (ptData1[Y_NEG] <= ptData2[Y_NEG])))
   if (((ptData1[Z_POS] >= ptData2[Z_POS]) &&
        (ptData1[Z_NEG] <= ptData2[Z_POS])) ||
       ((ptData1[Z_POS] >= ptData2[Z_NEG]) &&
        (ptData1[Z_NEG] <= ptData2[Z_NEG])))
   return TRUE;

   if (((ptData2[X_POS] >= ptData1[X_POS]) &&
        (ptData2[X_NEG] <= ptData1[X_POS])) ||
       ((ptData2[X_POS] >= ptData1[X_NEG]) &&
        (ptData2[X_NEG] <= ptData1[X_NEG])))
   if (((ptData2[Y_POS] >= ptData1[Y_POS]) &&
        (ptData2[Y_NEG] <= ptData1[Y_POS])) ||
       ((ptData2[Y_POS] >= ptData1[Y_NEG]) &&
        (ptData2[Y_NEG] <= ptData1[Y_NEG])))
   if (((ptData2[Z_POS] >= ptData1[Z_POS]) &&
        (ptData2[Z_NEG] <= ptData1[Z_POS])) ||
       ((ptData2[Z_POS] >= ptData1[Z_NEG]) &&
        (ptData2[Z_NEG] <= ptData1[Z_NEG])))
   return TRUE;
   
   
   if ((ptData1[X_POS] <= ptData2[X_POS]) &&
       (ptData1[X_NEG] >= ptData2[X_NEG]))
   if (((ptData1[Y_POS] >= ptData2[Y_POS]) &&
        (ptData1[Y_NEG] <= ptData2[Y_POS])) ||
       ((ptData1[Y_POS] >= ptData2[Y_NEG]) &&
        (ptData1[Y_NEG] <= ptData2[Y_NEG])))
   if (((ptData1[Z_POS] >= ptData2[Z_POS]) &&
        (ptData1[Z_NEG] <= ptData2[Z_POS])) ||
       ((ptData1[Z_POS] >= ptData2[Z_NEG]) &&
        (ptData1[Z_NEG] <= ptData2[Z_NEG])))
   return TRUE;

   if ((ptData2[X_POS] <= ptData1[X_POS]) &&
       (ptData2[X_NEG] >= ptData1[X_NEG]))
   if (((ptData2[Y_POS] >= ptData1[Y_POS]) &&
        (ptData2[Y_NEG] <= ptData1[Y_POS])) ||
       ((ptData2[Y_POS] >= ptData1[Y_NEG]) &&
        (ptData2[Y_NEG] <= ptData1[Y_NEG])))
   if (((ptData2[Z_POS] >= ptData1[Z_POS]) &&
        (ptData2[Z_NEG] <= ptData1[Z_POS])) ||
       ((ptData2[Z_POS] >= ptData1[Z_NEG]) &&
        (ptData2[Z_NEG] <= ptData1[Z_NEG])))
   return TRUE;

   
   if (((ptData1[X_POS] >= ptData2[X_POS]) &&
        (ptData1[X_NEG] <= ptData2[X_POS])) ||
       ((ptData1[X_POS] >= ptData2[X_NEG]) &&
        (ptData1[X_NEG] <= ptData2[X_NEG])))
   if ((ptData1[Y_POS] <= ptData2[Y_POS]) &&
       (ptData1[Y_NEG] >= ptData2[Y_NEG]))
   if (((ptData1[Z_POS] >= ptData2[Z_POS]) &&
        (ptData1[Z_NEG] <= ptData2[Z_POS])) ||
       ((ptData1[Z_POS] >= ptData2[Z_NEG]) &&
        (ptData1[Z_NEG] <= ptData2[Z_NEG])))
   return TRUE;

   if (((ptData2[X_POS] >= ptData1[X_POS]) &&
        (ptData2[X_NEG] <= ptData1[X_POS])) ||
       ((ptData2[X_POS] >= ptData1[X_NEG]) &&
        (ptData2[X_NEG] <= ptData1[X_NEG])))
   if ((ptData2[Y_POS] <= ptData1[Y_POS]) &&
       (ptData2[Y_NEG] >= ptData1[Y_NEG]))
   if (((ptData2[Z_POS] >= ptData1[Z_POS]) &&
        (ptData2[Z_NEG] <= ptData1[Z_POS])) ||
       ((ptData2[Z_POS] >= ptData1[Z_NEG]) &&
        (ptData2[Z_NEG] <= ptData1[Z_NEG])))
   return TRUE;

   
   if (((ptData1[X_POS] >= ptData2[X_POS]) &&
        (ptData1[X_NEG] <= ptData2[X_POS])) ||
       ((ptData1[X_POS] >= ptData2[X_NEG]) &&
        (ptData1[X_NEG] <= ptData2[X_NEG])))
   if (((ptData1[Y_POS] >= ptData2[Y_POS]) &&
        (ptData1[Y_NEG] <= ptData2[Y_POS])) ||
       ((ptData1[Y_POS] >= ptData2[Y_NEG]) &&
        (ptData1[Y_NEG] <= ptData2[Y_NEG])))
   if ((ptData1[Z_POS] <= ptData2[Z_POS]) &&
       (ptData1[Z_NEG] >= ptData2[Z_NEG]))
   return TRUE;

   if (((ptData2[X_POS] >= ptData1[X_POS]) &&
        (ptData2[X_NEG] <= ptData1[X_POS])) ||
       ((ptData2[X_POS] >= ptData1[X_NEG]) &&
        (ptData2[X_NEG] <= ptData1[X_NEG])))
   if (((ptData2[Y_POS] >= ptData1[Y_POS]) &&
        (ptData2[Y_NEG] <= ptData1[Y_POS])) ||
       ((ptData2[Y_POS] >= ptData1[Y_NEG]) &&
        (ptData2[Y_NEG] <= ptData1[Y_NEG])))
   if ((ptData2[Z_POS] <= ptData1[Z_POS]) &&
       (ptData2[Z_NEG] >= ptData1[Z_NEG]))
   return TRUE;
   

   return FALSE;
}



void ptToBoundsCollision(float *mesh_TRANS,
                         float xPast, float yPast, float zPast,
                         float *xPreset, float *yPreset, float *zPreset, int *impactFace, int *outside)
{
   float xP, yP, zP;
   float xFace, yFace, zFace;
   
   *impactFace = 0;
   *outside = TRUE;
   
   // find if the past point is inside the bounds rather than outside
   if (((xPast <= mesh_TRANS[LOCX]+mesh_TRANS[BR]) && (xPast >= mesh_TRANS[LOCX]-mesh_TRANS[BR])) ||
       ((xPast <= mesh_TRANS[LOCX]-mesh_TRANS[BR]) && (xPast >= mesh_TRANS[LOCX]+mesh_TRANS[BR])))
   if (((yPast <= mesh_TRANS[LOCY]+mesh_TRANS[BR]) && (yPast >= mesh_TRANS[LOCY]-mesh_TRANS[BR])) ||
       ((yPast <= mesh_TRANS[LOCY]-mesh_TRANS[BR]) && (yPast >= mesh_TRANS[LOCY]+mesh_TRANS[BR])))
   if (((zPast <= mesh_TRANS[LOCZ]+mesh_TRANS[BR]) && (zPast >= mesh_TRANS[LOCZ]-mesh_TRANS[BR])) ||
       ((zPast <= mesh_TRANS[LOCZ]-mesh_TRANS[BR]) && (zPast >= mesh_TRANS[LOCZ]+mesh_TRANS[BR])))
   *outside = FALSE;
   
   
   if (xPast != *xPreset)
   {
      xFace = mesh_TRANS[LOCX]+mesh_TRANS[BR];
      
      // is the face between the line connecting the past and preset points
      if (((xPast >= xFace) && (*xPreset <= xFace)) ||
          ((xPast <= xFace) && (*xPreset >= xFace)))
      {
         // resize the line to the face
         xP = xFace;
         yP = yPast - (xPast - xFace) / (xPast - *xPreset) * (yPast - *yPreset);
         zP = zPast - (xPast - xFace) / (xPast - *xPreset) * (zPast - *zPreset);
         
         // is the point within the face
         if ((yP <= mesh_TRANS[LOCY]+mesh_TRANS[BR]) && (yP >= mesh_TRANS[LOCY]-mesh_TRANS[BR]))
         if ((zP <= mesh_TRANS[LOCZ]+mesh_TRANS[BR]) && (zP >= mesh_TRANS[LOCZ]-mesh_TRANS[BR]))
         {
            *xPreset = xP;
            *yPreset = yP;
            *zPreset = zP;
            
            *impactFace = 1;
         }
      }
      
      xFace = mesh_TRANS[LOCX]-mesh_TRANS[BR];
      
      // is the face between the line connecting the past and preset points
      if (((xPast >= xFace) && (*xPreset <= xFace)) ||
          ((xPast <= xFace) && (*xPreset >= xFace)))
      {
         // resize the line to the face
         xP = xFace;
         yP = yPast - (xPast - xFace) / (xPast - *xPreset) * (yPast - *yPreset);
         zP = zPast - (xPast - xFace) / (xPast - *xPreset) * (zPast - *zPreset);
         
         // is the point within the face
         if ((yP <= mesh_TRANS[LOCY]+mesh_TRANS[BR]) && (yP >= mesh_TRANS[LOCY]-mesh_TRANS[BR]))
         if ((zP <= mesh_TRANS[LOCZ]+mesh_TRANS[BR]) && (zP >= mesh_TRANS[LOCZ]-mesh_TRANS[BR]))
         {
            *xPreset = xP;
            *yPreset = yP;
            *zPreset = zP;
            
            *impactFace = 2;
         }
      }
   }
   
   
   if (yPast != *yPreset)
   {
      yFace = mesh_TRANS[LOCY]+mesh_TRANS[BR];
      
      // is the face between the line connecting the past and preset points
      if (((yPast >= yFace) && (*yPreset <= yFace)) ||
          ((yPast <= yFace) && (*yPreset >= yFace)))
      {
         // resize the line to the face
         xP = xPast - (yPast - yFace) / (yPast - *yPreset) * (xPast - *xPreset);
         yP = yFace;
         zP = zPast - (yPast - yFace) / (yPast - *yPreset) * (zPast - *zPreset);
         
         // is the point within the face
         if ((xP <= mesh_TRANS[LOCX]+mesh_TRANS[BR]) && (xP >= mesh_TRANS[LOCX]-mesh_TRANS[BR]))
         if ((zP <= mesh_TRANS[LOCZ]+mesh_TRANS[BR]) && (zP >= mesh_TRANS[LOCZ]-mesh_TRANS[BR]))
         {
            *xPreset = xP;
            *yPreset = yP;
            *zPreset = zP;
            
            *impactFace = 3;
         }
      }
      
      yFace = mesh_TRANS[LOCY]-mesh_TRANS[BR];
      
      // is the face between the line connecting the past and preset points
      if (((yPast >= yFace) && (*yPreset <= yFace)) ||
          ((yPast <= yFace) && (*yPreset >= yFace)))
      {
         // resize the line to the face
         xP = xPast - (yPast - yFace) / (yPast - *yPreset) * (xPast - *xPreset);
         yP = yFace;
         zP = zPast - (yPast - yFace) / (yPast - *yPreset) * (zPast - *zPreset);
         
         // is the point within the face
         if ((xP <= mesh_TRANS[LOCX]+mesh_TRANS[BR]) && (xP >= mesh_TRANS[LOCX]-mesh_TRANS[BR]))
         if ((zP <= mesh_TRANS[LOCZ]+mesh_TRANS[BR]) && (zP >= mesh_TRANS[LOCZ]-mesh_TRANS[BR]))
         {
            *xPreset = xP;
            *yPreset = yP;
            *zPreset = zP;
            
            *impactFace = 4;
         }
      }
   }
   
   
   if (zPast != *zPreset)
   {
      zFace = mesh_TRANS[LOCZ]+mesh_TRANS[BR];
      
      // is the face between the line connecting the past and preset points
      if (((zPast >= zFace) && (*zPreset <= zFace)) ||
          ((zPast <= zFace) && (*zPreset >= zFace)))
      {
         // resize the line to the face
         xP = xPast - (zPast - zFace) / (zPast - *zPreset) * (xPast - *xPreset);
         yP = yPast - (zPast - zFace) / (zPast - *zPreset) * (yPast - *yPreset);
         zP = zFace;
         
         // is the point within the face
         if ((xP <= mesh_TRANS[LOCX]+mesh_TRANS[BR]) && (xP >= mesh_TRANS[LOCX]-mesh_TRANS[BR]))
         if ((yP <= mesh_TRANS[LOCY]+mesh_TRANS[BR]) && (yP >= mesh_TRANS[LOCY]-mesh_TRANS[BR]))
         {
            *xPreset = xP;
            *yPreset = yP;
            *zPreset = zP;
            
            *impactFace = 5;
         }
      }
      
      zFace = mesh_TRANS[LOCZ]-mesh_TRANS[BR];
      
      // is the face between the line connecting the past and preset points
      if (((zPast >= zFace) && (*zPreset <= zFace)) ||
          ((zPast <= zFace) && (*zPreset >= zFace)))
      {
         // resize the line to the face
         xP = xPast - (zPast - zFace) / (zPast - *zPreset) * (xPast - *xPreset);
         yP = yPast - (zPast - zFace) / (zPast - *zPreset) * (yPast - *yPreset);
         zP = zFace;
         
         // is the point within the face
         if ((xP <= mesh_TRANS[LOCX]+mesh_TRANS[BR]) && (xP >= mesh_TRANS[LOCX]-mesh_TRANS[BR]))
         if ((yP <= mesh_TRANS[LOCY]+mesh_TRANS[BR]) && (yP >= mesh_TRANS[LOCY]-mesh_TRANS[BR]))
         {
            *xPreset = xP;
            *yPreset = yP;
            *zPreset = zP;
            
            *impactFace = 6;
         }
      }
   }
}



void ptToBoxCollision(float *mesh_TRANS,
                      float xPast, float yPast, float zPast,
                      float *xPreset, float *yPreset, float *zPreset, int *impactFace, int *outside)
{
   float xP, yP, zP;
   float xFace, yFace, zFace;
   float xPastNorm, yPastNorm, zPastNorm;
   float xPresetNorm, yPresetNorm, zPresetNorm;
   
   
   // move and rotate the line connecting the past and preset points
   // in the same way it takes to normalize a box representing the transfomation data
   xPastNorm = xPast - mesh_TRANS[LOCX];
   yPastNorm = yPast - mesh_TRANS[LOCY];
   zPastNorm = zPast - mesh_TRANS[LOCZ];
   
   reverseApplyXyzUcRotToPoint(mesh_TRANS[9], mesh_TRANS[10],
                               mesh_TRANS[11], mesh_TRANS[12],
                               mesh_TRANS[13], mesh_TRANS[14],
                               &xPastNorm, &yPastNorm, &zPastNorm);
   
   xPresetNorm = *xPreset - mesh_TRANS[LOCX];
   yPresetNorm = *yPreset - mesh_TRANS[LOCY];
   zPresetNorm = *zPreset - mesh_TRANS[LOCZ];
   
   reverseApplyXyzUcRotToPoint(mesh_TRANS[9], mesh_TRANS[10],
                               mesh_TRANS[11], mesh_TRANS[12],
                               mesh_TRANS[13], mesh_TRANS[14],
                               &xPresetNorm, &yPresetNorm, &zPresetNorm);
   
   
   *impactFace = 0;
   *outside = TRUE;
   
   // find if the past point is inside the box rather than outside
   if (((xPastNorm <= mesh_TRANS[SZX]) && (xPastNorm >= -mesh_TRANS[SZX])) ||
       ((xPastNorm <= -mesh_TRANS[SZX]) && (xPastNorm >= mesh_TRANS[SZX])))
   if (((yPastNorm <= mesh_TRANS[SZY]) && (yPastNorm >= -mesh_TRANS[SZY])) ||
       ((yPastNorm <= -mesh_TRANS[SZY]) && (yPastNorm >= mesh_TRANS[SZY])))
   if (((zPastNorm <= mesh_TRANS[SZZ]) && (zPastNorm >= -mesh_TRANS[SZZ])) ||
       ((zPastNorm <= -mesh_TRANS[SZZ]) && (zPastNorm >= mesh_TRANS[SZZ])))
   *outside = FALSE;
   
   
   if (xPastNorm != xPresetNorm)
   {
      xFace = mesh_TRANS[SZX];
      
      // is the face between the line connecting the past and preset points
      if (((xPastNorm >= xFace) && (xPresetNorm <= xFace)) ||
          ((xPastNorm <= xFace) && (xPresetNorm >= xFace)))
      {
         // resize the line to the face
         xP = xFace;
         yP = yPastNorm - (xPastNorm - xFace) / (xPastNorm - xPresetNorm) * (yPastNorm - yPresetNorm);
         zP = zPastNorm - (xPastNorm - xFace) / (xPastNorm - xPresetNorm) * (zPastNorm - zPresetNorm);
         
         // is the point within the face
         if ((yP <= mesh_TRANS[SZY]) && (yP >= -mesh_TRANS[SZY]))
         if ((zP <= mesh_TRANS[SZZ]) && (zP >= -mesh_TRANS[SZZ]))
         {
            xPresetNorm = xP;
            yPresetNorm = yP;
            zPresetNorm = zP;
            
            *impactFace = 1;
         }
      }
      
      xFace = -mesh_TRANS[SZX];
      
      // is the face between the line connecting the past and preset points
      if (((xPastNorm >= xFace) && (xPresetNorm <= xFace)) ||
          ((xPastNorm <= xFace) && (xPresetNorm >= xFace)))
      {
         // resize the line to the face
         xP = xFace;
         yP = yPastNorm - (xPastNorm - xFace) / (xPastNorm - xPresetNorm) * (yPastNorm - yPresetNorm);
         zP = zPastNorm - (xPastNorm - xFace) / (xPastNorm - xPresetNorm) * (zPastNorm - zPresetNorm);
         
         // is the point within the face
         if ((yP <= mesh_TRANS[SZY]) && (yP >= -mesh_TRANS[SZY]))
         if ((zP <= mesh_TRANS[SZZ]) && (zP >= -mesh_TRANS[SZZ]))
         {
            xPresetNorm = xP;
            yPresetNorm = yP;
            zPresetNorm = zP;
            
            *impactFace = 2;
         }
      }
   }
   
   
   if (yPastNorm != yPresetNorm)
   {
      yFace = mesh_TRANS[SZY];
      
      // is the face between the line connecting the past and preset points
      if (((yPastNorm >= yFace) && (yPresetNorm <= yFace)) ||
          ((yPastNorm <= yFace) && (yPresetNorm >= yFace)))
      {
         // resize the line to the face
         xP = xPastNorm - (yPastNorm - yFace) / (yPastNorm - yPresetNorm) * (xPastNorm - xPresetNorm);
         yP = yFace;
         zP = zPastNorm - (yPastNorm - yFace) / (yPastNorm - yPresetNorm) * (zPastNorm - zPresetNorm);
         
         // is the point within the face
         if ((xP <= mesh_TRANS[SZX]) && (xP >= -mesh_TRANS[SZX]))
         if ((zP <= mesh_TRANS[SZZ]) && (zP >= -mesh_TRANS[SZZ]))
         {
            xPresetNorm = xP;
            yPresetNorm = yP;
            zPresetNorm = zP;
            
            *impactFace = 3;
         }
      }
      
      yFace = -mesh_TRANS[SZY];
      
      // is the face between the line connecting the past and preset points
      if (((yPastNorm >= yFace) && (yPresetNorm <= yFace)) ||
          ((yPastNorm <= yFace) && (yPresetNorm >= yFace)))
      {
         // resize the line to the face
         xP = xPastNorm - (yPastNorm - yFace) / (yPastNorm - yPresetNorm) * (xPastNorm - xPresetNorm);
         yP = yFace;
         zP = zPastNorm - (yPastNorm - yFace) / (yPastNorm - yPresetNorm) * (zPastNorm - zPresetNorm);
         
         // is the point within the face
         if ((xP <= mesh_TRANS[SZX]) && (xP >= -mesh_TRANS[SZX]))
         if ((zP <= mesh_TRANS[SZZ]) && (zP >= -mesh_TRANS[SZZ]))
         {
            xPresetNorm = xP;
            yPresetNorm = yP;
            zPresetNorm = zP;
            
            *impactFace = 4;
         }
      }
   }
   
   
   if (zPastNorm != zPresetNorm)
   {
      zFace = mesh_TRANS[SZZ];
      
      // is the face between the line connecting the past and preset points
      if (((zPastNorm >= zFace) && (zPresetNorm <= zFace)) ||
          ((zPastNorm <= zFace) && (zPresetNorm >= zFace)))
      {
         // resize the line to the face
         xP = xPastNorm - (zPastNorm - zFace) / (zPastNorm - zPresetNorm) * (xPastNorm - xPresetNorm);
         yP = yPastNorm - (zPastNorm - zFace) / (zPastNorm - zPresetNorm) * (yPastNorm - yPresetNorm);
         zP = zFace;
         
         // is the point within the face
         if ((xP <= mesh_TRANS[SZX]) && (xP >= -mesh_TRANS[SZX]))
         if ((yP <= mesh_TRANS[SZY]) && (yP >= -mesh_TRANS[SZY]))
         {
            xPresetNorm = xP;
            yPresetNorm = yP;
            zPresetNorm = zP;
            
            *impactFace = 5;
         }
      }
      
      zFace = -mesh_TRANS[SZZ];
      
      // is the face between the line connecting the past and preset points
      if (((zPastNorm >= zFace) && (zPresetNorm <= zFace)) ||
          ((zPastNorm <= zFace) && (zPresetNorm >= zFace)))
      {
         // resize the line to the face
         xP = xPastNorm - (zPastNorm - zFace) / (zPastNorm - zPresetNorm) * (xPastNorm - xPresetNorm);
         yP = yPastNorm - (zPastNorm - zFace) / (zPastNorm - zPresetNorm) * (yPastNorm - yPresetNorm);
         zP = zFace;
         
         // is the point within the face
         if ((xP <= mesh_TRANS[SZX]) && (xP >= -mesh_TRANS[SZX]))
         if ((yP <= mesh_TRANS[SZY]) && (yP >= -mesh_TRANS[SZY]))
         {
            xPresetNorm = xP;
            yPresetNorm = yP;
            zPresetNorm = zP;
            
            *impactFace = 6;
         }
      }
   }
   
   // apply rotations and move the preset point to undo the normalization
   applyXyzUcRotToPoint(mesh_TRANS[9], mesh_TRANS[10],
                        mesh_TRANS[11], mesh_TRANS[12],
                        mesh_TRANS[13], mesh_TRANS[14], &xPresetNorm, &yPresetNorm, &zPresetNorm);

   *xPreset = xPresetNorm + mesh_TRANS[LOCX];
   *yPreset = yPresetNorm + mesh_TRANS[LOCY];
   *zPreset = zPresetNorm + mesh_TRANS[LOCZ];
}



void globalBoxKnockOut(float *fixed_TRANS, int fixed_MESHCNT,
                       float *moving_TRANS, float boxMargin,
                       float *xTravel, float *yTravel, float *zTravel, int *globalContact)
{
   int i, contact;
   int lastContactData;
   float xMovingLocSave, yMovingLocSave, zMovingLocSave;
   
   *globalContact = FALSE;
   
   xMovingLocSave = moving_TRANS[LOCX];
   yMovingLocSave = moving_TRANS[LOCY];
   zMovingLocSave = moving_TRANS[LOCZ];
   
   // test every "fixed box" object with the "moving box" object
   for (i=0; i < fixed_MESHCNT*TRSZ; i+=TRSZ)
   {
      // skip if the "fixed box" and the "moving box" are the same box
      if (&fixed_TRANS[i] == &moving_TRANS[0])
      continue;
      
      localBoxKnockOut(&fixed_TRANS[i], &moving_TRANS[0], boxMargin,
                       &*xTravel, &*yTravel, &*zTravel, &lastContactData, &contact);
      
      // add the travel distance to the "moving box" if both boxes are contacting 
      if (contact)
      {
         moving_TRANS[LOCX] += *xTravel;
         moving_TRANS[LOCY] += *yTravel;
         moving_TRANS[LOCZ] += *zTravel;
         
         *globalContact = TRUE;
      }
   }
   
   // find the travel distance
   *xTravel = moving_TRANS[LOCX] - xMovingLocSave;
   *yTravel = moving_TRANS[LOCY] - yMovingLocSave;
   *zTravel = moving_TRANS[LOCZ] - zMovingLocSave;
   
   moving_TRANS[LOCX] = xMovingLocSave;
   moving_TRANS[LOCY] = yMovingLocSave;
   moving_TRANS[LOCZ] = zMovingLocSave;
}



void globalBoxDetectAndMove(float *fixed_TRANS, int fixed_MESHCNT,
                            float *moving_TRANS, float boxMargin,
                            float xArrow, float yArrow, float zArrow, int alwaysMove,
                            float *xTravel, float *yTravel, float *zTravel, int *globalContact)
{
   int i, contact;
   int lastContactData;
   float xLongest = 0, yLongest = 0, zLongest = 0;
   
   *globalContact = FALSE;
   
   // test every "fixed box" object with the "moving box" object
   for (i=0; i < fixed_MESHCNT*TRSZ; i+=TRSZ)
   {
      // skip if the "fixed box" and the "moving box" are the same box
      if (&fixed_TRANS[i] == &moving_TRANS[0])
      continue;
      
      localBoxDetectAndMove(&fixed_TRANS[i], &moving_TRANS[0], boxMargin,
                            xArrow, yArrow, zArrow, alwaysMove,
                            &*xTravel, &*yTravel, &*zTravel, &lastContactData, &contact);
      
      // find the longest travel distance between all objects
      if ((contact) || (alwaysMove))
      if ((fabs(*xTravel) > fabs(xLongest)) ||
          (fabs(*yTravel) > fabs(yLongest)) ||
          (fabs(*zTravel) > fabs(zLongest)))
      {
         xLongest = *xTravel;
         yLongest = *yTravel;
         zLongest = *zTravel;
      }
      
      if (contact)
      *globalContact = TRUE;
   }
   
   *xTravel = xLongest;
   *yTravel = yLongest;
   *zTravel = zLongest;
}



void globalBoxCollision(float *fixed_TRANS, int fixed_MESHCNT,
                        float *moving_TRANS, float boxMargin,
                        float xTravel, float yTravel, float zTravel,
                        float *xActual, float *yActual, float *zActual,
                        int *fixed_MESHNUM, int *globalImpact, int *globalContact)
{
   int i;
   int impact, contact;
   float xShortest, yShortest, zShortest;
   int useAxisX = FALSE, useAxisY = FALSE, useAxisZ = FALSE;
   
   // initialize the shortest travel distance variables
   xShortest = xTravel;
   yShortest = yTravel;
   zShortest = zTravel;
   
   // find which axis to use for finding the shortest travel distance
   if ((fabs(xTravel) >= fabs(yTravel)) && (fabs(xTravel) >= fabs(zTravel)))// if x > y and z
   useAxisX = TRUE;
   
   if ((fabs(yTravel) >= fabs(xTravel)) && (fabs(yTravel) >= fabs(zTravel)))// if y > x and z
   useAxisY = TRUE;

   if ((fabs(zTravel) >= fabs(xTravel)) && (fabs(zTravel) >= fabs(yTravel)))// if z > x and y
   useAxisZ = TRUE;
   
   
   *fixed_MESHNUM = 0;
   *globalImpact = 0;
   *globalContact = FALSE;
   
   // test every "fixed box" object with the "moving box" object
   for (i=0; i < fixed_MESHCNT*TRSZ; i+=TRSZ)
   {
      // skip if the "fixed box" and the "moving box" are the same box
      if (&fixed_TRANS[i] == &moving_TRANS[0])
      continue;
      
      localBoxCollision(&fixed_TRANS[i], &moving_TRANS[0], boxMargin,
                        xTravel, yTravel, zTravel,
                        &*xActual, &*yActual, &*zActual, &impact, &contact);
      
      // find the shortest travel distance between all objects
      if (contact)
      if (((useAxisX) && (fabs(*xActual) < fabs(xShortest))) ||
          ((useAxisY) && (fabs(*yActual) < fabs(yShortest))) ||
          ((useAxisZ) && (fabs(*zActual) < fabs(zShortest))))
      {
         xShortest = *xActual;
         yShortest = *yActual;
         zShortest = *zActual;
         
         *fixed_MESHNUM = i/TRSZ;
         *globalImpact = impact;
      }
      
      if (contact)
      *globalContact = TRUE;
   }
   
   *xActual = xShortest;
   *yActual = yShortest;
   *zActual = zShortest;
}



void localBoxKnockOut(float *fixed_TRANS, float *moving_TRANS, float boxMargin,
                      float *xTravel, float *yTravel, float *zTravel,
                      int *lastContactData, int *contact)
{
   float xArrow, yArrow, zArrow;
   
   
   // get the vector going from the "fixed box" to the "moving box"
   xArrow = moving_TRANS[LOCX] - fixed_TRANS[LOCX];
   yArrow = moving_TRANS[LOCY] - fixed_TRANS[LOCY];
   zArrow = moving_TRANS[LOCZ] - fixed_TRANS[LOCZ];
   
   
   // rotate the arrow in the same way it takes to normalize the "fixed box"
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14], &xArrow, &yArrow, &zArrow);
   
   // resize the arrow vector as you would resize the "fixed box" into a cube
   xArrow = xArrow / fixed_TRANS[SZX];
   yArrow = yArrow / fixed_TRANS[SZY];
   zArrow = zArrow / fixed_TRANS[SZZ];
   
   // rotate the arrow to undo the "fixed box" normalization
   applyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                        fixed_TRANS[11], fixed_TRANS[12],
                        fixed_TRANS[13], fixed_TRANS[14], &xArrow, &yArrow, &zArrow);

   
   // rotate the arrow in the same way it takes to normalize the "moving box"
   reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                               moving_TRANS[11], moving_TRANS[12],
                               moving_TRANS[13], moving_TRANS[14], &xArrow, &yArrow, &zArrow);
   
   // resize the arrow vector as you would resize the "moving box" into a cube
   xArrow = xArrow / moving_TRANS[SZX];
   yArrow = yArrow / moving_TRANS[SZY];
   zArrow = zArrow / moving_TRANS[SZZ];
   
   // rotate the arrow to undo the "moving box" normalization
   applyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                        moving_TRANS[11], moving_TRANS[12],
                        moving_TRANS[13], moving_TRANS[14], &xArrow, &yArrow, &zArrow);

   
   // move the "moving box" in the direction of the arrow
   localBoxDetectAndMove(fixed_TRANS, moving_TRANS, boxMargin,
                         xArrow, yArrow, zArrow, FALSE,
                         &*xTravel, &*yTravel, &*zTravel, &*lastContactData, &*contact);
}



void localBoxDetectAndMove(float *fixed_TRANS, float *moving_TRANS, float boxMargin,
                           float xArrow, float yArrow, float zArrow, int alwaysMove,
                           float *xTravel, float *yTravel, float *zTravel, int *lastContactData, int *contact)
{
   int i, j;
   float xP, yP, zP;
   
   float movBoxCorner[8*3];
   float fixBoxCorner[8*3];
   int boxVertex[8*3];
   float movBoxEdgePt1[12*3];
   float movBoxEdgePt2[12*3];
   float fixBoxEdgePt1[12*3];
   float fixBoxEdgePt2[12*3];
   float fixBoxFace1[12];
   float fixBoxFace2[12];
   int face1[12], face2[12];
   
   float xArrowFixNorm, yArrowFixNorm, zArrowFixNorm;
   float xArrowMovNorm, yArrowMovNorm, zArrowMovNorm;
   
   float xTravelFixNorm, yTravelFixNorm, zTravelFixNorm;
   float xTravelMovNorm, yTravelMovNorm, zTravelMovNorm;
   
   float xEdgePt1, yEdgePt1, zEdgePt1;
   float xEdgePt2, yEdgePt2, zEdgePt2;
   float xFixEdgeContact, yFixEdgeContact, zFixEdgeContact;
   float xMovEdgeContact, yMovEdgeContact, zMovEdgeContact;
   int lastContactDataBuff;
   
   // initialize
   *contact = FALSE;
   *xTravel = 0;
   *yTravel = 0;
   *zTravel = 0;
   *lastContactData = 0;
   
   // if the boxes are not within one another's boundary then return
   if (alwaysMove == FALSE)
   if (boundsContact(fixed_TRANS, moving_TRANS) == FALSE)
   return;
   
   
   // define where each normalized box vertex
   // rests in the coordinate planes
   boxVertex[0*3+0] = 1;// PPP
   boxVertex[0*3+1] = 1;
   boxVertex[0*3+2] = 1;
   boxVertex[1*3+0] = 1;// PNP
   boxVertex[1*3+1] = -1;
   boxVertex[1*3+2] = 1;
   boxVertex[2*3+0] = -1;// NPP
   boxVertex[2*3+1] = 1;
   boxVertex[2*3+2] = 1;
   boxVertex[3*3+0] = -1;// NNP
   boxVertex[3*3+1] = -1;
   boxVertex[3*3+2] = 1;
   boxVertex[4*3+0] = 1;// PPN
   boxVertex[4*3+1] = 1;
   boxVertex[4*3+2] = -1;
   boxVertex[5*3+0] = 1;// PNN
   boxVertex[5*3+1] = -1;
   boxVertex[5*3+2] = -1;
   boxVertex[6*3+0] = -1;// NPN
   boxVertex[6*3+1] = 1;
   boxVertex[6*3+2] = -1;
   boxVertex[7*3+0] = -1;// NNN
   boxVertex[7*3+1] = -1;
   boxVertex[7*3+2] = -1;
   
   
   // create the "moving box" using transformation data
   movBoxCorner[0*3+0] = moving_TRANS[SZX];// PPP
   movBoxCorner[0*3+1] = moving_TRANS[SZY];
   movBoxCorner[0*3+2] = moving_TRANS[SZZ];
   
   movBoxCorner[1*3+0] = moving_TRANS[SZX];// PNP
   movBoxCorner[1*3+1] = -moving_TRANS[SZY];
   movBoxCorner[1*3+2] = moving_TRANS[SZZ];
   
   movBoxCorner[2*3+0] = -moving_TRANS[SZX];// NPP
   movBoxCorner[2*3+1] = moving_TRANS[SZY];
   movBoxCorner[2*3+2] = moving_TRANS[SZZ];

   movBoxCorner[3*3+0] = -moving_TRANS[SZX];// NNP
   movBoxCorner[3*3+1] = -moving_TRANS[SZY];
   movBoxCorner[3*3+2] = moving_TRANS[SZZ];
   
   
   movBoxCorner[4*3+0] = moving_TRANS[SZX];// PPN
   movBoxCorner[4*3+1] = moving_TRANS[SZY];
   movBoxCorner[4*3+2] = -moving_TRANS[SZZ];
   
   movBoxCorner[5*3+0] = moving_TRANS[SZX];// PNN
   movBoxCorner[5*3+1] = -moving_TRANS[SZY];
   movBoxCorner[5*3+2] = -moving_TRANS[SZZ];
   
   movBoxCorner[6*3+0] = -moving_TRANS[SZX];// NPN
   movBoxCorner[6*3+1] = moving_TRANS[SZY];
   movBoxCorner[6*3+2] = -moving_TRANS[SZZ];
   
   movBoxCorner[7*3+0] = -moving_TRANS[SZX];// NNN
   movBoxCorner[7*3+1] = -moving_TRANS[SZY];
   movBoxCorner[7*3+2] = -moving_TRANS[SZZ];
   
   
   // rotate and position the "moving box"
   for (i=0; i < 8*3; i+=3)
   {
      applyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                           moving_TRANS[11], moving_TRANS[12],
                           moving_TRANS[13], moving_TRANS[14],
                           &movBoxCorner[i+0], &movBoxCorner[i+1], &movBoxCorner[i+2]); // rotation
      
      movBoxCorner[i+0] += moving_TRANS[LOCX]; // location
      movBoxCorner[i+1] += moving_TRANS[LOCY];
      movBoxCorner[i+2] += moving_TRANS[LOCZ];
   }
   
   
   // move and rotate the "moving box"
   // in the same way it takes to normalize the "fixed box"
   for (i=0; i < 8*3; i+=3)
   {
      movBoxCorner[i+0] += -fixed_TRANS[LOCX];
      movBoxCorner[i+1] += -fixed_TRANS[LOCY];
      movBoxCorner[i+2] += -fixed_TRANS[LOCZ];
   }
   
   for (i=0; i < 8*3; i+=3)
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14],
                               &movBoxCorner[i+0], &movBoxCorner[i+1], &movBoxCorner[i+2]);
   
   // rotate the arrow in the same way it takes to normalize the "fixed box"
   xArrowFixNorm = xArrow;
   yArrowFixNorm = yArrow;
   zArrowFixNorm = zArrow;
   
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14],
                               &xArrowFixNorm, &yArrowFixNorm, &zArrowFixNorm);
   
   
   
   // create the "fixed box" using transformation data
   fixBoxCorner[0*3+0] = fixed_TRANS[SZX];// PPP
   fixBoxCorner[0*3+1] = fixed_TRANS[SZY];
   fixBoxCorner[0*3+2] = fixed_TRANS[SZZ];
   
   fixBoxCorner[1*3+0] = fixed_TRANS[SZX];// PNP
   fixBoxCorner[1*3+1] = -fixed_TRANS[SZY];
   fixBoxCorner[1*3+2] = fixed_TRANS[SZZ];
   
   fixBoxCorner[2*3+0] = -fixed_TRANS[SZX];// NPP
   fixBoxCorner[2*3+1] = fixed_TRANS[SZY];
   fixBoxCorner[2*3+2] = fixed_TRANS[SZZ];

   fixBoxCorner[3*3+0] = -fixed_TRANS[SZX];// NNP
   fixBoxCorner[3*3+1] = -fixed_TRANS[SZY];
   fixBoxCorner[3*3+2] = fixed_TRANS[SZZ];
   
   
   fixBoxCorner[4*3+0] = fixed_TRANS[SZX];// PPN
   fixBoxCorner[4*3+1] = fixed_TRANS[SZY];
   fixBoxCorner[4*3+2] = -fixed_TRANS[SZZ];
   
   fixBoxCorner[5*3+0] = fixed_TRANS[SZX];// PNN
   fixBoxCorner[5*3+1] = -fixed_TRANS[SZY];
   fixBoxCorner[5*3+2] = -fixed_TRANS[SZZ];
   
   fixBoxCorner[6*3+0] = -fixed_TRANS[SZX];// NPN
   fixBoxCorner[6*3+1] = fixed_TRANS[SZY];
   fixBoxCorner[6*3+2] = -fixed_TRANS[SZZ];
   
   fixBoxCorner[7*3+0] = -fixed_TRANS[SZX];// NNN
   fixBoxCorner[7*3+1] = -fixed_TRANS[SZY];
   fixBoxCorner[7*3+2] = -fixed_TRANS[SZZ];
   
   
   // rotate and position the "fixed box"
   for (i=0; i < 8*3; i+=3)
   {
      applyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                           fixed_TRANS[11], fixed_TRANS[12],
                           fixed_TRANS[13], fixed_TRANS[14],
                           &fixBoxCorner[i+0], &fixBoxCorner[i+1], &fixBoxCorner[i+2]); // rotation
      
      fixBoxCorner[i+0] += fixed_TRANS[LOCX]; // location
      fixBoxCorner[i+1] += fixed_TRANS[LOCY];
      fixBoxCorner[i+2] += fixed_TRANS[LOCZ];
   }
   
   
   // move and rotate the "fixed box"
   // in the same way it takes to normalize the "moving box"
   for (i=0; i < 8*3; i+=3)
   {
      fixBoxCorner[i+0] += -moving_TRANS[LOCX];
      fixBoxCorner[i+1] += -moving_TRANS[LOCY];
      fixBoxCorner[i+2] += -moving_TRANS[LOCZ];
   }
   
   for (i=0; i < 8*3; i+=3)
   reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                               moving_TRANS[11], moving_TRANS[12],
                               moving_TRANS[13], moving_TRANS[14],
                               &fixBoxCorner[i+0], &fixBoxCorner[i+1], &fixBoxCorner[i+2]);
   
   // reverse the arrow relative to the normalized "moving box"
   xArrowMovNorm = -xArrow;
   yArrowMovNorm = -yArrow;
   zArrowMovNorm = -zArrow;
   
   // rotate the arrow in the same way it takes to normalize the "moving box"
   reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                               moving_TRANS[11], moving_TRANS[12],
                               moving_TRANS[13], moving_TRANS[14],
                               &xArrowMovNorm, &yArrowMovNorm, &zArrowMovNorm);
   
   
   
   // check if any of the corners of the boxes are inside one another
   for (i=0; i < 8*3; i+=3)
   {
      // is a vertex of the "moving box" within the "fixed box"
      if ((movBoxCorner[i+0] <= fixed_TRANS[SZX]) &&
          (movBoxCorner[i+0] >= -fixed_TRANS[SZX]))
      if ((movBoxCorner[i+1] <= fixed_TRANS[SZY]) &&
          (movBoxCorner[i+1] >= -fixed_TRANS[SZY]))
      if ((movBoxCorner[i+2] <= fixed_TRANS[SZZ]) &&
          (movBoxCorner[i+2] >= -fixed_TRANS[SZZ]))
      *contact = TRUE;
      
      // is a vertex of the "fixed box" within the "moving box"
      if ((fixBoxCorner[i+0] <= moving_TRANS[SZX]) &&
          (fixBoxCorner[i+0] >= -moving_TRANS[SZX]))
      if ((fixBoxCorner[i+1] <= moving_TRANS[SZY]) &&
          (fixBoxCorner[i+1] >= -moving_TRANS[SZY]))
      if ((fixBoxCorner[i+2] <= moving_TRANS[SZZ]) &&
          (fixBoxCorner[i+2] >= -moving_TRANS[SZZ]))
      *contact = TRUE;
   }
   
   
   // create edge data for the "moving box"
   
   // top
   movBoxEdgePt1[0*3+0] = movBoxCorner[PPP*3+0];// PCP
   movBoxEdgePt1[0*3+1] = movBoxCorner[PPP*3+1];
   movBoxEdgePt1[0*3+2] = movBoxCorner[PPP*3+2];
   movBoxEdgePt2[0*3+0] = movBoxCorner[PNP*3+0];
   movBoxEdgePt2[0*3+1] = movBoxCorner[PNP*3+1];
   movBoxEdgePt2[0*3+2] = movBoxCorner[PNP*3+2];
   
   movBoxEdgePt1[1*3+0] = movBoxCorner[PNP*3+0];// CNP
   movBoxEdgePt1[1*3+1] = movBoxCorner[PNP*3+1];
   movBoxEdgePt1[1*3+2] = movBoxCorner[PNP*3+2];
   movBoxEdgePt2[1*3+0] = movBoxCorner[NNP*3+0];
   movBoxEdgePt2[1*3+1] = movBoxCorner[NNP*3+1];
   movBoxEdgePt2[1*3+2] = movBoxCorner[NNP*3+2];
   
   movBoxEdgePt1[2*3+0] = movBoxCorner[NNP*3+0];// NCP
   movBoxEdgePt1[2*3+1] = movBoxCorner[NNP*3+1];
   movBoxEdgePt1[2*3+2] = movBoxCorner[NNP*3+2];
   movBoxEdgePt2[2*3+0] = movBoxCorner[NPP*3+0];
   movBoxEdgePt2[2*3+1] = movBoxCorner[NPP*3+1];
   movBoxEdgePt2[2*3+2] = movBoxCorner[NPP*3+2];
   
   movBoxEdgePt1[3*3+0] = movBoxCorner[NPP*3+0];// CPP
   movBoxEdgePt1[3*3+1] = movBoxCorner[NPP*3+1];
   movBoxEdgePt1[3*3+2] = movBoxCorner[NPP*3+2];
   movBoxEdgePt2[3*3+0] = movBoxCorner[PPP*3+0];
   movBoxEdgePt2[3*3+1] = movBoxCorner[PPP*3+1];
   movBoxEdgePt2[3*3+2] = movBoxCorner[PPP*3+2];
   
   // bottom
   movBoxEdgePt1[4*3+0] = movBoxCorner[PPN*3+0];// PCN
   movBoxEdgePt1[4*3+1] = movBoxCorner[PPN*3+1];
   movBoxEdgePt1[4*3+2] = movBoxCorner[PPN*3+2];
   movBoxEdgePt2[4*3+0] = movBoxCorner[PNN*3+0];
   movBoxEdgePt2[4*3+1] = movBoxCorner[PNN*3+1];
   movBoxEdgePt2[4*3+2] = movBoxCorner[PNN*3+2];
   
   movBoxEdgePt1[5*3+0] = movBoxCorner[PNN*3+0];// CNN
   movBoxEdgePt1[5*3+1] = movBoxCorner[PNN*3+1];
   movBoxEdgePt1[5*3+2] = movBoxCorner[PNN*3+2];
   movBoxEdgePt2[5*3+0] = movBoxCorner[NNN*3+0];
   movBoxEdgePt2[5*3+1] = movBoxCorner[NNN*3+1];
   movBoxEdgePt2[5*3+2] = movBoxCorner[NNN*3+2];
   
   movBoxEdgePt1[6*3+0] = movBoxCorner[NNN*3+0];// NCN
   movBoxEdgePt1[6*3+1] = movBoxCorner[NNN*3+1];
   movBoxEdgePt1[6*3+2] = movBoxCorner[NNN*3+2];
   movBoxEdgePt2[6*3+0] = movBoxCorner[NPN*3+0];
   movBoxEdgePt2[6*3+1] = movBoxCorner[NPN*3+1];
   movBoxEdgePt2[6*3+2] = movBoxCorner[NPN*3+2];
   
   movBoxEdgePt1[7*3+0] = movBoxCorner[NPN*3+0];// CPN
   movBoxEdgePt1[7*3+1] = movBoxCorner[NPN*3+1];
   movBoxEdgePt1[7*3+2] = movBoxCorner[NPN*3+2];
   movBoxEdgePt2[7*3+0] = movBoxCorner[PPN*3+0];
   movBoxEdgePt2[7*3+1] = movBoxCorner[PPN*3+1];
   movBoxEdgePt2[7*3+2] = movBoxCorner[PPN*3+2];
   
   // sides
   movBoxEdgePt1[8*3+0] = movBoxCorner[PPP*3+0];// PPC
   movBoxEdgePt1[8*3+1] = movBoxCorner[PPP*3+1];
   movBoxEdgePt1[8*3+2] = movBoxCorner[PPP*3+2];
   movBoxEdgePt2[8*3+0] = movBoxCorner[PPN*3+0];
   movBoxEdgePt2[8*3+1] = movBoxCorner[PPN*3+1];
   movBoxEdgePt2[8*3+2] = movBoxCorner[PPN*3+2];
   
   movBoxEdgePt1[9*3+0] = movBoxCorner[PNP*3+0];// PNC
   movBoxEdgePt1[9*3+1] = movBoxCorner[PNP*3+1];
   movBoxEdgePt1[9*3+2] = movBoxCorner[PNP*3+2];
   movBoxEdgePt2[9*3+0] = movBoxCorner[PNN*3+0];
   movBoxEdgePt2[9*3+1] = movBoxCorner[PNN*3+1];
   movBoxEdgePt2[9*3+2] = movBoxCorner[PNN*3+2];
   
   movBoxEdgePt1[10*3+0] = movBoxCorner[NNP*3+0];// NNC
   movBoxEdgePt1[10*3+1] = movBoxCorner[NNP*3+1];
   movBoxEdgePt1[10*3+2] = movBoxCorner[NNP*3+2];
   movBoxEdgePt2[10*3+0] = movBoxCorner[NNN*3+0];
   movBoxEdgePt2[10*3+1] = movBoxCorner[NNN*3+1];
   movBoxEdgePt2[10*3+2] = movBoxCorner[NNN*3+2];
   
   movBoxEdgePt1[11*3+0] = movBoxCorner[NPP*3+0];// NPC
   movBoxEdgePt1[11*3+1] = movBoxCorner[NPP*3+1];
   movBoxEdgePt1[11*3+2] = movBoxCorner[NPP*3+2];
   movBoxEdgePt2[11*3+0] = movBoxCorner[NPN*3+0];
   movBoxEdgePt2[11*3+1] = movBoxCorner[NPN*3+1];
   movBoxEdgePt2[11*3+2] = movBoxCorner[NPN*3+2];
   
   
   // create the edge data for the "fixed box"
   
   // top
   fixBoxEdgePt1[0*3+0] = fixBoxCorner[PPP*3+0];// PCP
   fixBoxEdgePt1[0*3+1] = fixBoxCorner[PPP*3+1];
   fixBoxEdgePt1[0*3+2] = fixBoxCorner[PPP*3+2];
   fixBoxEdgePt2[0*3+0] = fixBoxCorner[PNP*3+0];
   fixBoxEdgePt2[0*3+1] = fixBoxCorner[PNP*3+1];
   fixBoxEdgePt2[0*3+2] = fixBoxCorner[PNP*3+2];
   
   fixBoxEdgePt1[1*3+0] = fixBoxCorner[PNP*3+0];// CNP
   fixBoxEdgePt1[1*3+1] = fixBoxCorner[PNP*3+1];
   fixBoxEdgePt1[1*3+2] = fixBoxCorner[PNP*3+2];
   fixBoxEdgePt2[1*3+0] = fixBoxCorner[NNP*3+0];
   fixBoxEdgePt2[1*3+1] = fixBoxCorner[NNP*3+1];
   fixBoxEdgePt2[1*3+2] = fixBoxCorner[NNP*3+2];
   
   fixBoxEdgePt1[2*3+0] = fixBoxCorner[NNP*3+0];// NCP
   fixBoxEdgePt1[2*3+1] = fixBoxCorner[NNP*3+1];
   fixBoxEdgePt1[2*3+2] = fixBoxCorner[NNP*3+2];
   fixBoxEdgePt2[2*3+0] = fixBoxCorner[NPP*3+0];
   fixBoxEdgePt2[2*3+1] = fixBoxCorner[NPP*3+1];
   fixBoxEdgePt2[2*3+2] = fixBoxCorner[NPP*3+2];
   
   fixBoxEdgePt1[3*3+0] = fixBoxCorner[NPP*3+0];// CPP
   fixBoxEdgePt1[3*3+1] = fixBoxCorner[NPP*3+1];
   fixBoxEdgePt1[3*3+2] = fixBoxCorner[NPP*3+2];
   fixBoxEdgePt2[3*3+0] = fixBoxCorner[PPP*3+0];
   fixBoxEdgePt2[3*3+1] = fixBoxCorner[PPP*3+1];
   fixBoxEdgePt2[3*3+2] = fixBoxCorner[PPP*3+2];
   
   // bottom
   fixBoxEdgePt1[4*3+0] = fixBoxCorner[PPN*3+0];// PCN
   fixBoxEdgePt1[4*3+1] = fixBoxCorner[PPN*3+1];
   fixBoxEdgePt1[4*3+2] = fixBoxCorner[PPN*3+2];
   fixBoxEdgePt2[4*3+0] = fixBoxCorner[PNN*3+0];
   fixBoxEdgePt2[4*3+1] = fixBoxCorner[PNN*3+1];
   fixBoxEdgePt2[4*3+2] = fixBoxCorner[PNN*3+2];
   
   fixBoxEdgePt1[5*3+0] = fixBoxCorner[PNN*3+0];// CNN
   fixBoxEdgePt1[5*3+1] = fixBoxCorner[PNN*3+1];
   fixBoxEdgePt1[5*3+2] = fixBoxCorner[PNN*3+2];
   fixBoxEdgePt2[5*3+0] = fixBoxCorner[NNN*3+0];
   fixBoxEdgePt2[5*3+1] = fixBoxCorner[NNN*3+1];
   fixBoxEdgePt2[5*3+2] = fixBoxCorner[NNN*3+2];
   
   fixBoxEdgePt1[6*3+0] = fixBoxCorner[NNN*3+0];// NCN
   fixBoxEdgePt1[6*3+1] = fixBoxCorner[NNN*3+1];
   fixBoxEdgePt1[6*3+2] = fixBoxCorner[NNN*3+2];
   fixBoxEdgePt2[6*3+0] = fixBoxCorner[NPN*3+0];
   fixBoxEdgePt2[6*3+1] = fixBoxCorner[NPN*3+1];
   fixBoxEdgePt2[6*3+2] = fixBoxCorner[NPN*3+2];
   
   fixBoxEdgePt1[7*3+0] = fixBoxCorner[NPN*3+0];// CPN
   fixBoxEdgePt1[7*3+1] = fixBoxCorner[NPN*3+1];
   fixBoxEdgePt1[7*3+2] = fixBoxCorner[NPN*3+2];
   fixBoxEdgePt2[7*3+0] = fixBoxCorner[PPN*3+0];
   fixBoxEdgePt2[7*3+1] = fixBoxCorner[PPN*3+1];
   fixBoxEdgePt2[7*3+2] = fixBoxCorner[PPN*3+2];
   
   // sides
   fixBoxEdgePt1[8*3+0] = fixBoxCorner[PPP*3+0];// PPC
   fixBoxEdgePt1[8*3+1] = fixBoxCorner[PPP*3+1];
   fixBoxEdgePt1[8*3+2] = fixBoxCorner[PPP*3+2];
   fixBoxEdgePt2[8*3+0] = fixBoxCorner[PPN*3+0];
   fixBoxEdgePt2[8*3+1] = fixBoxCorner[PPN*3+1];
   fixBoxEdgePt2[8*3+2] = fixBoxCorner[PPN*3+2];
   
   fixBoxEdgePt1[9*3+0] = fixBoxCorner[PNP*3+0];// PNC
   fixBoxEdgePt1[9*3+1] = fixBoxCorner[PNP*3+1];
   fixBoxEdgePt1[9*3+2] = fixBoxCorner[PNP*3+2];
   fixBoxEdgePt2[9*3+0] = fixBoxCorner[PNN*3+0];
   fixBoxEdgePt2[9*3+1] = fixBoxCorner[PNN*3+1];
   fixBoxEdgePt2[9*3+2] = fixBoxCorner[PNN*3+2];
   
   fixBoxEdgePt1[10*3+0] = fixBoxCorner[NNP*3+0];// NNC
   fixBoxEdgePt1[10*3+1] = fixBoxCorner[NNP*3+1];
   fixBoxEdgePt1[10*3+2] = fixBoxCorner[NNP*3+2];
   fixBoxEdgePt2[10*3+0] = fixBoxCorner[NNN*3+0];
   fixBoxEdgePt2[10*3+1] = fixBoxCorner[NNN*3+1];
   fixBoxEdgePt2[10*3+2] = fixBoxCorner[NNN*3+2];
   
   fixBoxEdgePt1[11*3+0] = fixBoxCorner[NPP*3+0];// NPC
   fixBoxEdgePt1[11*3+1] = fixBoxCorner[NPP*3+1];
   fixBoxEdgePt1[11*3+2] = fixBoxCorner[NPP*3+2];
   fixBoxEdgePt2[11*3+0] = fixBoxCorner[NPN*3+0];
   fixBoxEdgePt2[11*3+1] = fixBoxCorner[NPN*3+1];
   fixBoxEdgePt2[11*3+2] = fixBoxCorner[NPN*3+2];
   
   
   // check if any of the edges of the boxes are inside one another
   
   for (i=0; i < 12*3; i+=3)
   {
      // does an edge run through the same plane as a face on the "fixed box"
      
      // left and right
      if (((movBoxEdgePt1[i+0] <= fixed_TRANS[SZX]) && (movBoxEdgePt2[i+0] >= fixed_TRANS[SZX])) ||
          ((movBoxEdgePt2[i+0] <= fixed_TRANS[SZX]) && (movBoxEdgePt1[i+0] >= fixed_TRANS[SZX])))
      {
         // find the point where the plane and the edge intercept
         xP = fixed_TRANS[SZX];
         yP = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+0] - fixed_TRANS[SZX]) /
             (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]) * (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]);
         zP = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+0] - fixed_TRANS[SZX]) /
             (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]) * (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]);
         
         // is the point within the face
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      if (((movBoxEdgePt1[i+0] <= -fixed_TRANS[SZX]) && (movBoxEdgePt2[i+0] >= -fixed_TRANS[SZX])) ||
          ((movBoxEdgePt2[i+0] <= -fixed_TRANS[SZX]) && (movBoxEdgePt1[i+0] >= -fixed_TRANS[SZX])))
      {
         // find the point where the plane and the edge intercept
         xP = -fixed_TRANS[SZX];
         yP = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+0] - -fixed_TRANS[SZX]) /
             (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]) * (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]);
         zP = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+0] - -fixed_TRANS[SZX]) /
             (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]) * (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]);
         
         // does an edge go through a face
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      // front and back
      if (((movBoxEdgePt1[i+1] <= fixed_TRANS[SZY]) && (movBoxEdgePt2[i+1] >= fixed_TRANS[SZY])) ||
          ((movBoxEdgePt2[i+1] <= fixed_TRANS[SZY]) && (movBoxEdgePt1[i+1] >= fixed_TRANS[SZY])))
      {
         // find the point where the plane and the edge intercept
         xP = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+1] - fixed_TRANS[SZY]) /
             (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]) * (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]);
         yP = fixed_TRANS[SZY];
         zP = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+1] - fixed_TRANS[SZY]) /
             (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]) * (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]);
         
         // does an edge go through a face
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      if (((movBoxEdgePt1[i+1] <= -fixed_TRANS[SZY]) && (movBoxEdgePt2[i+1] >= -fixed_TRANS[SZY])) ||
          ((movBoxEdgePt2[i+1] <= -fixed_TRANS[SZY]) && (movBoxEdgePt1[i+1] >= -fixed_TRANS[SZY])))
      {
         // find the point where the plane and the edge intercept
         xP = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+1] - -fixed_TRANS[SZY]) /
             (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]) * (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]);
         yP = -fixed_TRANS[SZY];
         zP = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+1] - -fixed_TRANS[SZY]) /
             (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]) * (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]);
         
         // does an edge go through a face
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      // top and bottom
      if (((movBoxEdgePt1[i+2] <= fixed_TRANS[SZZ]) && (movBoxEdgePt2[i+2] >= fixed_TRANS[SZZ])) ||
          ((movBoxEdgePt2[i+2] <= fixed_TRANS[SZZ]) && (movBoxEdgePt1[i+2] >= fixed_TRANS[SZZ])))
      {
         // find the point where the plane and the edge intercept
         xP = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+2] - fixed_TRANS[SZZ]) /
             (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]) * (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]);
         yP = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+2] - fixed_TRANS[SZZ]) /
             (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]) * (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]);
         zP = fixed_TRANS[SZZ];
         
         // does an edge go through a face
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         *contact = TRUE;
      }
      
      if (((movBoxEdgePt1[i+2] <= -fixed_TRANS[SZZ]) && (movBoxEdgePt2[i+2] >= -fixed_TRANS[SZZ])) ||
          ((movBoxEdgePt2[i+2] <= -fixed_TRANS[SZZ]) && (movBoxEdgePt1[i+2] >= -fixed_TRANS[SZZ])))
      {
         // find the point where the plane and the edge intercept
         xP = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+2] - -fixed_TRANS[SZZ]) /
             (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]) * (movBoxEdgePt2[i+0] - movBoxEdgePt1[i+0]);
         yP = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+2] - -fixed_TRANS[SZZ]) /
             (movBoxEdgePt2[i+2] - movBoxEdgePt1[i+2]) * (movBoxEdgePt2[i+1] - movBoxEdgePt1[i+1]);
         zP = -fixed_TRANS[SZZ];
         
         // does an edge go through a face
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         *contact = TRUE;
      }
   }
   
   for (i=0; i < 12*3; i+=3)
   {
      // does an edge run through the same plane as a face on the "moving box"
      
      // left and right
      if (((fixBoxEdgePt1[i+0] <= moving_TRANS[SZX]) && (fixBoxEdgePt2[i+0] >= moving_TRANS[SZX])) ||
          ((fixBoxEdgePt2[i+0] <= moving_TRANS[SZX]) && (fixBoxEdgePt1[i+0] >= moving_TRANS[SZX])))
      {
         // find the point where the plane and the edge intercept
         xP = moving_TRANS[SZX];
         yP = fixBoxEdgePt2[i+1] - (fixBoxEdgePt2[i+0] - moving_TRANS[SZX]) /
              (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]) * (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]);
         zP = fixBoxEdgePt2[i+2] - (fixBoxEdgePt2[i+0] - moving_TRANS[SZX]) /
              (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]) * (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]);
         
         // does an edge go through a face
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      if (((fixBoxEdgePt1[i+0] <= -moving_TRANS[SZX]) && (fixBoxEdgePt2[i+0] >= -moving_TRANS[SZX])) ||
          ((fixBoxEdgePt2[i+0] <= -moving_TRANS[SZX]) && (fixBoxEdgePt1[i+0] >= -moving_TRANS[SZX])))
      {
         // find the point where the plane and the edge intercept
         xP = -moving_TRANS[SZX];
         yP = fixBoxEdgePt2[i+1] - (fixBoxEdgePt2[i+0] - -moving_TRANS[SZX]) /
              (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]) * (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]);
         zP = fixBoxEdgePt2[i+2] - (fixBoxEdgePt2[i+0] - -moving_TRANS[SZX]) /
              (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]) * (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]);
         
         // does an edge go through a face
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      // front and back
      if (((fixBoxEdgePt1[i+1] <= moving_TRANS[SZY]) && (fixBoxEdgePt2[i+1] >= moving_TRANS[SZY])) ||
          ((fixBoxEdgePt2[i+1] <= moving_TRANS[SZY]) && (fixBoxEdgePt1[i+1] >= moving_TRANS[SZY])))
      {
         // find the point where the plane and the edge intercept
         xP = fixBoxEdgePt2[i+0] - (fixBoxEdgePt2[i+1] - moving_TRANS[SZY]) /
              (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]) * (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]);
         yP = moving_TRANS[SZY];
         zP = fixBoxEdgePt2[i+2] - (fixBoxEdgePt2[i+1] - moving_TRANS[SZY]) /
              (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]) * (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]);
         
         // does an edge go through a face
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      if (((fixBoxEdgePt1[i+1] <= -moving_TRANS[SZY]) && (fixBoxEdgePt2[i+1] >= -moving_TRANS[SZY])) ||
          ((fixBoxEdgePt2[i+1] <= -moving_TRANS[SZY]) && (fixBoxEdgePt1[i+1] >= -moving_TRANS[SZY])))
      {
         // find the point where the plane and the edge intercept
         xP = fixBoxEdgePt2[i+0] - (fixBoxEdgePt2[i+1] - -moving_TRANS[SZY]) /
              (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]) * (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]);
         yP = -moving_TRANS[SZY];
         zP = fixBoxEdgePt2[i+2] - (fixBoxEdgePt2[i+1] - -moving_TRANS[SZY]) /
              (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]) * (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]);
         
         // does an edge go through a face
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         *contact = TRUE;
      }
      
      // top and bottom
      if (((fixBoxEdgePt1[i+2] <= moving_TRANS[SZZ]) && (fixBoxEdgePt2[i+2] >= moving_TRANS[SZZ])) ||
          ((fixBoxEdgePt2[i+2] <= moving_TRANS[SZZ]) && (fixBoxEdgePt1[i+2] >= moving_TRANS[SZZ])))
      {
         // find the point where the plane and the edge intercept
         xP = fixBoxEdgePt2[i+0] - (fixBoxEdgePt2[i+2] - moving_TRANS[SZZ]) /
              (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]) * (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]);
         yP = fixBoxEdgePt2[i+1] - (fixBoxEdgePt2[i+2] - moving_TRANS[SZZ]) /
              (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]) * (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]);
         zP = moving_TRANS[SZZ];
         
         // does an edge go through a face
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         *contact = TRUE;
      }
      
      if (((fixBoxEdgePt1[i+2] <= -moving_TRANS[SZZ]) && (fixBoxEdgePt2[i+2] >= -moving_TRANS[SZZ])) ||
          ((fixBoxEdgePt2[i+2] <= -moving_TRANS[SZZ]) && (fixBoxEdgePt1[i+2] >= -moving_TRANS[SZZ])))
      {
         // find the point where the plane and the edge intercept
         xP = fixBoxEdgePt2[i+0] - (fixBoxEdgePt2[i+2] - -moving_TRANS[SZZ]) /
              (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]) * (fixBoxEdgePt2[i+0] - fixBoxEdgePt1[i+0]);
         yP = fixBoxEdgePt2[i+1] - (fixBoxEdgePt2[i+2] - -moving_TRANS[SZZ]) /
              (fixBoxEdgePt2[i+2] - fixBoxEdgePt1[i+2]) * (fixBoxEdgePt2[i+1] - fixBoxEdgePt1[i+1]);
         zP = -moving_TRANS[SZZ];
         
         // does an edge go through a face
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         *contact = TRUE;
      }
   }
   
   if (alwaysMove == FALSE)
   if (!*contact)
   return;
   
   // if no direction given to move the box then return
   if ((!xArrow) && (!yArrow) && (!zArrow))
   return;
   
   
   
   // resize the "moving box" to create the margin
   
   moving_TRANS[SZX] += boxMargin;
   moving_TRANS[SZY] += boxMargin;
   moving_TRANS[SZZ] += boxMargin;
   
   // recreate the "moving box" using transformation data
   movBoxCorner[0*3+0] = moving_TRANS[SZX];// PPP
   movBoxCorner[0*3+1] = moving_TRANS[SZY];
   movBoxCorner[0*3+2] = moving_TRANS[SZZ];
   
   movBoxCorner[1*3+0] = moving_TRANS[SZX];// PNP
   movBoxCorner[1*3+1] = -moving_TRANS[SZY];
   movBoxCorner[1*3+2] = moving_TRANS[SZZ];
   
   movBoxCorner[2*3+0] = -moving_TRANS[SZX];// NPP
   movBoxCorner[2*3+1] = moving_TRANS[SZY];
   movBoxCorner[2*3+2] = moving_TRANS[SZZ];

   movBoxCorner[3*3+0] = -moving_TRANS[SZX];// NNP
   movBoxCorner[3*3+1] = -moving_TRANS[SZY];
   movBoxCorner[3*3+2] = moving_TRANS[SZZ];
   
   
   movBoxCorner[4*3+0] = moving_TRANS[SZX];// PPN
   movBoxCorner[4*3+1] = moving_TRANS[SZY];
   movBoxCorner[4*3+2] = -moving_TRANS[SZZ];
   
   movBoxCorner[5*3+0] = moving_TRANS[SZX];// PNN
   movBoxCorner[5*3+1] = -moving_TRANS[SZY];
   movBoxCorner[5*3+2] = -moving_TRANS[SZZ];
   
   movBoxCorner[6*3+0] = -moving_TRANS[SZX];// NPN
   movBoxCorner[6*3+1] = moving_TRANS[SZY];
   movBoxCorner[6*3+2] = -moving_TRANS[SZZ];
   
   movBoxCorner[7*3+0] = -moving_TRANS[SZX];// NNN
   movBoxCorner[7*3+1] = -moving_TRANS[SZY];
   movBoxCorner[7*3+2] = -moving_TRANS[SZZ];
   
   
   // rotate and position the "moving box"
   for (i=0; i < 8*3; i+=3)
   {
      applyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                           moving_TRANS[11], moving_TRANS[12],
                           moving_TRANS[13], moving_TRANS[14],
                           &movBoxCorner[i+0], &movBoxCorner[i+1], &movBoxCorner[i+2]); // rotation
      
      movBoxCorner[i+0] += moving_TRANS[LOCX]; // location
      movBoxCorner[i+1] += moving_TRANS[LOCY];
      movBoxCorner[i+2] += moving_TRANS[LOCZ];
   }
   
   
   // move and rotate the "moving box"
   // in the same way it takes to normalize the "fixed box"
   for (i=0; i < 8*3; i+=3)
   {
      movBoxCorner[i+0] += -fixed_TRANS[LOCX];
      movBoxCorner[i+1] += -fixed_TRANS[LOCY];
      movBoxCorner[i+2] += -fixed_TRANS[LOCZ];
   }
   
   for (i=0; i < 8*3; i+=3)
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14],
                               &movBoxCorner[i+0], &movBoxCorner[i+1], &movBoxCorner[i+2]);
   
   
   
   xTravelFixNorm = 0; yTravelFixNorm = 0; zTravelFixNorm = 0;
   xTravelMovNorm = 0; yTravelMovNorm = 0; zTravelMovNorm = 0;

   for (i=0; i < 8*3; i+=3)
   {
      // Extend each point of the "moving box" in the direction of the
      // arrow until it hits one of the 6 planes around the "fixed box".
      
      // left and right
      if (((xArrowFixNorm > 0) && (fixed_TRANS[SZX] > movBoxCorner[i+0])) ||
          ((xArrowFixNorm < 0) && (fixed_TRANS[SZX] < movBoxCorner[i+0])))
      {
         xP = fixed_TRANS[SZX];
         yP = movBoxCorner[i+1] - (movBoxCorner[i+0] - fixed_TRANS[SZX]) /
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm)) *
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm));
         zP = movBoxCorner[i+2] - (movBoxCorner[i+0] - fixed_TRANS[SZX]) /
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm)) *
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm));
         
         // if the extended vertex is within a face of the "fixed box"
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         {
            xP = (xP - movBoxCorner[i+0]);// find location relative to corner
            yP = (yP - movBoxCorner[i+1]);
            zP = (zP - movBoxCorner[i+2]);
            
            if (((xArrowFixNorm > 0) && (xP > xTravelFixNorm)) ||// is it the longest travel distance
                ((xArrowFixNorm < 0) && (xP < xTravelFixNorm)))
            {
               xTravelFixNorm = xP;
               yTravelFixNorm = yP;
               zTravelFixNorm = zP;
               
               // add face contact data to variable
               *lastContactData = FIXED_POS_X;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= MOVING_POS_X;
               else
               *lastContactData |= MOVING_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= MOVING_POS_Y;
               else
               *lastContactData |= MOVING_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= MOVING_POS_Z;
               else
               *lastContactData |= MOVING_NEG_Z;
            }
         }
      }
      
      if (((xArrowFixNorm > 0) && (-fixed_TRANS[SZX] > movBoxCorner[i+0])) ||
          ((xArrowFixNorm < 0) && (-fixed_TRANS[SZX] < movBoxCorner[i+0])))
      {
         xP = -fixed_TRANS[SZX];
         yP = movBoxCorner[i+1] - (movBoxCorner[i+0] - -fixed_TRANS[SZX]) /
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm)) *
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm));
         zP = movBoxCorner[i+2] - (movBoxCorner[i+0] - -fixed_TRANS[SZX]) /
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm)) *
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm));
         
         // if the extended vertex is within a face of the "fixed box"
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         {
            xP = (xP - movBoxCorner[i+0]);// find location relative to corner
            yP = (yP - movBoxCorner[i+1]);
            zP = (zP - movBoxCorner[i+2]);
            
            if (((xArrowFixNorm > 0) && (xP > xTravelFixNorm)) ||// is it the longest travel distance
                ((xArrowFixNorm < 0) && (xP < xTravelFixNorm)))
            {
               xTravelFixNorm = xP;
               yTravelFixNorm = yP;
               zTravelFixNorm = zP;
               
               // add face contact data to variable
               *lastContactData = FIXED_NEG_X;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= MOVING_POS_X;
               else
               *lastContactData |= MOVING_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= MOVING_POS_Y;
               else
               *lastContactData |= MOVING_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= MOVING_POS_Z;
               else
               *lastContactData |= MOVING_NEG_Z;
            }
         }
      }
      
      // front and back
      if (((yArrowFixNorm > 0) && (fixed_TRANS[SZY] > movBoxCorner[i+1])) ||
          ((yArrowFixNorm < 0) && (fixed_TRANS[SZY] < movBoxCorner[i+1])))
      {
         xP = movBoxCorner[i+0] - (movBoxCorner[i+1] - fixed_TRANS[SZY]) /
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm)) *
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm));
         yP = fixed_TRANS[SZY];
         zP = movBoxCorner[i+2] - (movBoxCorner[i+1] - fixed_TRANS[SZY]) /
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm)) *
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm));
         
         // if the extended vertex is within a face of the "fixed box"
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         {
            xP = (xP - movBoxCorner[i+0]);// find location relative to corner
            yP = (yP - movBoxCorner[i+1]);
            zP = (zP - movBoxCorner[i+2]);
            
            if (((yArrowFixNorm > 0) && (yP > yTravelFixNorm)) ||// is it the longest travel distance
                ((yArrowFixNorm < 0) && (yP < yTravelFixNorm)))
            {
               xTravelFixNorm = xP;
               yTravelFixNorm = yP;
               zTravelFixNorm = zP;
               
               // add face contact data to variable
               *lastContactData = FIXED_POS_Y;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= MOVING_POS_X;
               else
               *lastContactData |= MOVING_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= MOVING_POS_Y;
               else
               *lastContactData |= MOVING_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= MOVING_POS_Z;
               else
               *lastContactData |= MOVING_NEG_Z;
            }
         }
      }
      
      if (((yArrowFixNorm > 0) && (-fixed_TRANS[SZY] > movBoxCorner[i+1])) ||
          ((yArrowFixNorm < 0) && (-fixed_TRANS[SZY] < movBoxCorner[i+1])))
      {
         xP = movBoxCorner[i+0] - (movBoxCorner[i+1] - -fixed_TRANS[SZY]) /
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm)) *
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm));
         yP = -fixed_TRANS[SZY];
         zP = movBoxCorner[i+2] - (movBoxCorner[i+1] - -fixed_TRANS[SZY]) /
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm)) *
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm));
         
         // if the extended vertex is within a face of the "fixed box"
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((zP <= fixed_TRANS[SZZ]) && (zP >= -fixed_TRANS[SZZ]))
         {
            xP = (xP - movBoxCorner[i+0]);// find location relative to corner
            yP = (yP - movBoxCorner[i+1]);
            zP = (zP - movBoxCorner[i+2]);
            
            if (((yArrowFixNorm > 0) && (yP > yTravelFixNorm)) ||// is it the longest travel distance
                ((yArrowFixNorm < 0) && (yP < yTravelFixNorm)))
            {
               xTravelFixNorm = xP;
               yTravelFixNorm = yP;
               zTravelFixNorm = zP;
               
               // add face contact data to variable
               *lastContactData = FIXED_NEG_Y;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= MOVING_POS_X;
               else
               *lastContactData |= MOVING_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= MOVING_POS_Y;
               else
               *lastContactData |= MOVING_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= MOVING_POS_Z;
               else
               *lastContactData |= MOVING_NEG_Z;
            }
         }
      }
      
      // top and bottom
      if (((zArrowFixNorm > 0) && (fixed_TRANS[SZZ] > movBoxCorner[i+2])) ||
          ((zArrowFixNorm < 0) && (fixed_TRANS[SZZ] < movBoxCorner[i+2])))
      {
         xP = movBoxCorner[i+0] - (movBoxCorner[i+2] - fixed_TRANS[SZZ]) /
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm)) *
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm));
         yP = movBoxCorner[i+1] - (movBoxCorner[i+2] - fixed_TRANS[SZZ]) /
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm)) *
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm));
         zP = fixed_TRANS[SZZ];
         
         // if the extended vertex is within a face of the "fixed box"
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         {
            xP = (xP - movBoxCorner[i+0]);// find location relative to corner
            yP = (yP - movBoxCorner[i+1]);
            zP = (zP - movBoxCorner[i+2]);
            
            if (((zArrowFixNorm > 0) && (zP > zTravelFixNorm)) ||// is it the longest travel distance
                ((zArrowFixNorm < 0) && (zP < zTravelFixNorm)))
            {
               xTravelFixNorm = xP;
               yTravelFixNorm = yP;
               zTravelFixNorm = zP;
               
               // add face contact data to variable
               *lastContactData = FIXED_POS_Z;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= MOVING_POS_X;
               else
               *lastContactData |= MOVING_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= MOVING_POS_Y;
               else
               *lastContactData |= MOVING_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= MOVING_POS_Z;
               else
               *lastContactData |= MOVING_NEG_Z;
            }
         }
      }
      
      if (((zArrowFixNorm > 0) && (-fixed_TRANS[SZZ] > movBoxCorner[i+2])) ||
          ((zArrowFixNorm < 0) && (-fixed_TRANS[SZZ] < movBoxCorner[i+2])))
      {
         xP = movBoxCorner[i+0] - (movBoxCorner[i+2] - -fixed_TRANS[SZZ]) /
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm)) *
             (movBoxCorner[i+0] - (movBoxCorner[i+0]+xArrowFixNorm));
         yP = movBoxCorner[i+1] - (movBoxCorner[i+2] - -fixed_TRANS[SZZ]) /
             (movBoxCorner[i+2] - (movBoxCorner[i+2]+zArrowFixNorm)) *
             (movBoxCorner[i+1] - (movBoxCorner[i+1]+yArrowFixNorm));
         zP = -fixed_TRANS[SZZ];
         
         // if the extended vertex is within a face of the "fixed box"
         if ((xP <= fixed_TRANS[SZX]) && (xP >= -fixed_TRANS[SZX]))
         if ((yP <= fixed_TRANS[SZY]) && (yP >= -fixed_TRANS[SZY]))
         {
            xP = (xP - movBoxCorner[i+0]);// find location relative to corner
            yP = (yP - movBoxCorner[i+1]);
            zP = (zP - movBoxCorner[i+2]);
            
            if (((zArrowFixNorm > 0) && (zP > zTravelFixNorm)) ||// is it the longest travel distance
                ((zArrowFixNorm < 0) && (zP < zTravelFixNorm)))
            {
               xTravelFixNorm = xP;
               yTravelFixNorm = yP;
               zTravelFixNorm = zP;
               
               // add face contact data to variable
               *lastContactData = FIXED_NEG_Z;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= MOVING_POS_X;
               else
               *lastContactData |= MOVING_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= MOVING_POS_Y;
               else
               *lastContactData |= MOVING_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= MOVING_POS_Z;
               else
               *lastContactData |= MOVING_NEG_Z;
            }
         }
      }
   }
   
   // undo the normalization rotations
   applyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                        fixed_TRANS[11], fixed_TRANS[12],
                        fixed_TRANS[13], fixed_TRANS[14],
                        &xTravelFixNorm, &yTravelFixNorm, &zTravelFixNorm);

   *xTravel += xTravelFixNorm;// add the travel distance
   *yTravel += yTravelFixNorm;
   *zTravel += zTravelFixNorm;
   
   
   
   // apply the "moving box" normalization rotations to the travel location
   reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                               moving_TRANS[11], moving_TRANS[12],
                               moving_TRANS[13], moving_TRANS[14],
                               &xTravelFixNorm, &yTravelFixNorm, &zTravelFixNorm);

   // add the travel amount to the duplicated "fixed box" in the
   // opposite direction relative to the normlized "moving box"
   for (i=0; i < 8*3; i+=3)
   {
      fixBoxCorner[i+0] -= xTravelFixNorm;
      fixBoxCorner[i+1] -= yTravelFixNorm;
      fixBoxCorner[i+2] -= zTravelFixNorm;
   }
   
   
   for (i=0; i < 8*3; i+=3)
   {
      // Extend each point of the "fixed box" in the opposite direction of the
      // arrow until it hits one of the 6 planes around the "moving box".
      
      // left and right
      if (((xArrowMovNorm > 0) && (moving_TRANS[SZX] > fixBoxCorner[i+0])) ||
          ((xArrowMovNorm < 0) && (moving_TRANS[SZX] < fixBoxCorner[i+0])))
      {
         xP = moving_TRANS[SZX];
         yP = fixBoxCorner[i+1] - (fixBoxCorner[i+0] - moving_TRANS[SZX]) /
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm)) *
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm));
         zP = fixBoxCorner[i+2] - (fixBoxCorner[i+0] - moving_TRANS[SZX]) /
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm)) *
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm));
         
         // if the extended vertex is within a face of the "moving box"
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         {
            xP = (xP - fixBoxCorner[i+0]);// find location relative to corner
            yP = (yP - fixBoxCorner[i+1]);
            zP = (zP - fixBoxCorner[i+2]);
            
            if (((xArrowMovNorm > 0) && (xP > xTravelMovNorm)) ||// is it the longest travel distance
                ((xArrowMovNorm < 0) && (xP < xTravelMovNorm)))
            {
               xTravelMovNorm = xP;
               yTravelMovNorm = yP;
               zTravelMovNorm = zP;
               
               // add face contact data to variable
               *lastContactData = MOVING_POS_X;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= FIXED_POS_X;
               else
               *lastContactData |= FIXED_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= FIXED_POS_Y;
               else
               *lastContactData |= FIXED_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= FIXED_POS_Z;
               else
               *lastContactData |= FIXED_NEG_Z;
            }
         }
      }
      
      if (((xArrowMovNorm > 0) && (-moving_TRANS[SZX] > fixBoxCorner[i+0])) ||
          ((xArrowMovNorm < 0) && (-moving_TRANS[SZX] < fixBoxCorner[i+0])))
      {
         xP = -moving_TRANS[SZX];
         yP = fixBoxCorner[i+1] - (fixBoxCorner[i+0] - -moving_TRANS[SZX]) /
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm)) *
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm));
         zP = fixBoxCorner[i+2] - (fixBoxCorner[i+0] - -moving_TRANS[SZX]) /
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm)) *
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm));
         
         // if the extended vertex is within a face of the "moving box"
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         {
            xP = (xP - fixBoxCorner[i+0]);// find location relative to corner
            yP = (yP - fixBoxCorner[i+1]);
            zP = (zP - fixBoxCorner[i+2]);
            
            if (((xArrowMovNorm > 0) && (xP > xTravelMovNorm)) ||// is it the longest travel distance
                ((xArrowMovNorm < 0) && (xP < xTravelMovNorm)))
            {
               xTravelMovNorm = xP;
               yTravelMovNorm = yP;
               zTravelMovNorm = zP;
               
               // add face contact data to variable
               *lastContactData = MOVING_NEG_X;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= FIXED_POS_X;
               else
               *lastContactData |= FIXED_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= FIXED_POS_Y;
               else
               *lastContactData |= FIXED_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= FIXED_POS_Z;
               else
               *lastContactData |= FIXED_NEG_Z;
            }
         }
      }
      
      // front and back
      if (((yArrowMovNorm > 0) && (moving_TRANS[SZY] > fixBoxCorner[i+1])) ||
          ((yArrowMovNorm < 0) && (moving_TRANS[SZY] < fixBoxCorner[i+1])))
      {
         xP = fixBoxCorner[i+0] - (fixBoxCorner[i+1] - moving_TRANS[SZY]) /
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm)) *
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm));
         yP = moving_TRANS[SZY];
         zP = fixBoxCorner[i+2] - (fixBoxCorner[i+1] - moving_TRANS[SZY]) /
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm)) *
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm));
         
         // if the extended vertex is within a face of the "moving box"
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         {
            xP = (xP - fixBoxCorner[i+0]);// find location relative to corner
            yP = (yP - fixBoxCorner[i+1]);
            zP = (zP - fixBoxCorner[i+2]);
            
            if (((yArrowMovNorm > 0) && (yP > yTravelMovNorm)) ||// is it the longest travel distance
                ((yArrowMovNorm < 0) && (yP < yTravelMovNorm)))
            {
               xTravelMovNorm = xP;
               yTravelMovNorm = yP;
               zTravelMovNorm = zP;
               
               // add face contact data to variable
               *lastContactData = MOVING_POS_Y;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= FIXED_POS_X;
               else
               *lastContactData |= FIXED_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= FIXED_POS_Y;
               else
               *lastContactData |= FIXED_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= FIXED_POS_Z;
               else
               *lastContactData |= FIXED_NEG_Z;
            }
         }
      }
      
      if (((yArrowMovNorm > 0) && (-moving_TRANS[SZY] > fixBoxCorner[i+1])) ||
          ((yArrowMovNorm < 0) && (-moving_TRANS[SZY] < fixBoxCorner[i+1])))
      {
         xP = fixBoxCorner[i+0] - (fixBoxCorner[i+1] - -moving_TRANS[SZY]) /
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm)) *
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm));
         yP = -moving_TRANS[SZY];
         zP = fixBoxCorner[i+2] - (fixBoxCorner[i+1] - -moving_TRANS[SZY]) /
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm)) *
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm));
         
         // if the extended vertex is within a face of the "moving box"
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((zP <= moving_TRANS[SZZ]) && (zP >= -moving_TRANS[SZZ]))
         {
            xP = (xP - fixBoxCorner[i+0]);// find location relative to corner
            yP = (yP - fixBoxCorner[i+1]);
            zP = (zP - fixBoxCorner[i+2]);
            
            if (((yArrowMovNorm > 0) && (yP > yTravelMovNorm)) ||// is it the longest travel distance
                ((yArrowMovNorm < 0) && (yP < yTravelMovNorm)))
            {
               xTravelMovNorm = xP;
               yTravelMovNorm = yP;
               zTravelMovNorm = zP;
               
               // add face contact data to variable
               *lastContactData = MOVING_NEG_Y;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= FIXED_POS_X;
               else
               *lastContactData |= FIXED_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= FIXED_POS_Y;
               else
               *lastContactData |= FIXED_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= FIXED_POS_Z;
               else
               *lastContactData |= FIXED_NEG_Z;
            }
         }
      }
      
      // top and bottom
      if (((zArrowMovNorm > 0) && (moving_TRANS[SZZ] > fixBoxCorner[i+2])) ||
          ((zArrowMovNorm < 0) && (moving_TRANS[SZZ] < fixBoxCorner[i+2])))
      {
         xP = fixBoxCorner[i+0] - (fixBoxCorner[i+2] - moving_TRANS[SZZ]) /
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm)) *
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm));
         yP = fixBoxCorner[i+1] - (fixBoxCorner[i+2] - moving_TRANS[SZZ]) /
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm)) *
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm));
         zP = moving_TRANS[SZZ];
         
         // if the extended vertex is within a face of the "moving box"
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         {
            xP = (xP - fixBoxCorner[i+0]);// find location relative to corner
            yP = (yP - fixBoxCorner[i+1]);
            zP = (zP - fixBoxCorner[i+2]);
            
            if (((zArrowMovNorm > 0) && (zP > zTravelMovNorm)) ||// is it the longest travel distance
                ((zArrowMovNorm < 0) && (zP < zTravelMovNorm)))
            {
               xTravelMovNorm = xP;
               yTravelMovNorm = yP;
               zTravelMovNorm = zP;
               
               // add face contact data to variable
               *lastContactData = MOVING_POS_Z;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= FIXED_POS_X;
               else
               *lastContactData |= FIXED_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= FIXED_POS_Y;
               else
               *lastContactData |= FIXED_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= FIXED_POS_Z;
               else
               *lastContactData |= FIXED_NEG_Z;
            }
         }
      }
      
      if (((zArrowMovNorm > 0) && (-moving_TRANS[SZZ] > fixBoxCorner[i+2])) ||
          ((zArrowMovNorm < 0) && (-moving_TRANS[SZZ] < fixBoxCorner[i+2])))
      {
         xP = fixBoxCorner[i+0] - (fixBoxCorner[i+2] - -moving_TRANS[SZZ]) /
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm)) *
             (fixBoxCorner[i+0] - (fixBoxCorner[i+0]+xArrowMovNorm));
         yP = fixBoxCorner[i+1] - (fixBoxCorner[i+2] - -moving_TRANS[SZZ]) /
             (fixBoxCorner[i+2] - (fixBoxCorner[i+2]+zArrowMovNorm)) *
             (fixBoxCorner[i+1] - (fixBoxCorner[i+1]+yArrowMovNorm));
         zP = -moving_TRANS[SZZ];
         
         // if the extended vertex is within a face of the "moving box"
         if ((xP <= moving_TRANS[SZX]) && (xP >= -moving_TRANS[SZX]))
         if ((yP <= moving_TRANS[SZY]) && (yP >= -moving_TRANS[SZY]))
         {
            xP = (xP - fixBoxCorner[i+0]);// find location relative to corner
            yP = (yP - fixBoxCorner[i+1]);
            zP = (zP - fixBoxCorner[i+2]);
            
            if (((zArrowMovNorm > 0) && (zP > zTravelMovNorm)) ||// is it the longest travel distance
                ((zArrowMovNorm < 0) && (zP < zTravelMovNorm)))
            {
               xTravelMovNorm = xP;
               yTravelMovNorm = yP;
               zTravelMovNorm = zP;
               
               // add face contact data to variable
               *lastContactData = MOVING_NEG_Z;
               
               if (boxVertex[i+0] > 0)
               *lastContactData |= FIXED_POS_X;
               else
               *lastContactData |= FIXED_NEG_X;
               
               if (boxVertex[i+1] > 0)
               *lastContactData |= FIXED_POS_Y;
               else
               *lastContactData |= FIXED_NEG_Y;
               
               if (boxVertex[i+2] > 0)
               *lastContactData |= FIXED_POS_Z;
               else
               *lastContactData |= FIXED_NEG_Z;
            }
         }
      }
   }
   
   // undo the normalization rotations
   applyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                        moving_TRANS[11], moving_TRANS[12],
                        moving_TRANS[13], moving_TRANS[14],
                        &xTravelMovNorm, &yTravelMovNorm, &zTravelMovNorm);

   *xTravel -= xTravelMovNorm;// add the travel distance
   *yTravel -= yTravelMovNorm;
   *zTravel -= zTravelMovNorm;
   
   
   
   // apply the "fixed box" normalization rotations to the travel location
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14],
                               &xTravelMovNorm, &yTravelMovNorm, &zTravelMovNorm);

   // add the travel amount to the duplicated "moving box" in the
   // opposite direction relative to the normlized "fixed box"
   for (i=0; i < 8*3; i+=3)
   {
      movBoxCorner[i+0] += xTravelMovNorm;
      movBoxCorner[i+1] += yTravelMovNorm;
      movBoxCorner[i+2] += zTravelMovNorm;
   }
   
   
   // create the new edge data for the "moving box"
   
   // top
   movBoxEdgePt1[0*3+0] = movBoxCorner[PPP*3+0];// PCP
   movBoxEdgePt1[0*3+1] = movBoxCorner[PPP*3+1];
   movBoxEdgePt1[0*3+2] = movBoxCorner[PPP*3+2];
   movBoxEdgePt2[0*3+0] = movBoxCorner[PNP*3+0];
   movBoxEdgePt2[0*3+1] = movBoxCorner[PNP*3+1];
   movBoxEdgePt2[0*3+2] = movBoxCorner[PNP*3+2];
   
   movBoxEdgePt1[1*3+0] = movBoxCorner[PNP*3+0];// CNP
   movBoxEdgePt1[1*3+1] = movBoxCorner[PNP*3+1];
   movBoxEdgePt1[1*3+2] = movBoxCorner[PNP*3+2];
   movBoxEdgePt2[1*3+0] = movBoxCorner[NNP*3+0];
   movBoxEdgePt2[1*3+1] = movBoxCorner[NNP*3+1];
   movBoxEdgePt2[1*3+2] = movBoxCorner[NNP*3+2];
   
   movBoxEdgePt1[2*3+0] = movBoxCorner[NNP*3+0];// NCP
   movBoxEdgePt1[2*3+1] = movBoxCorner[NNP*3+1];
   movBoxEdgePt1[2*3+2] = movBoxCorner[NNP*3+2];
   movBoxEdgePt2[2*3+0] = movBoxCorner[NPP*3+0];
   movBoxEdgePt2[2*3+1] = movBoxCorner[NPP*3+1];
   movBoxEdgePt2[2*3+2] = movBoxCorner[NPP*3+2];
   
   movBoxEdgePt1[3*3+0] = movBoxCorner[NPP*3+0];// CPP
   movBoxEdgePt1[3*3+1] = movBoxCorner[NPP*3+1];
   movBoxEdgePt1[3*3+2] = movBoxCorner[NPP*3+2];
   movBoxEdgePt2[3*3+0] = movBoxCorner[PPP*3+0];
   movBoxEdgePt2[3*3+1] = movBoxCorner[PPP*3+1];
   movBoxEdgePt2[3*3+2] = movBoxCorner[PPP*3+2];
   
   // bottom
   movBoxEdgePt1[4*3+0] = movBoxCorner[PPN*3+0];// PCN
   movBoxEdgePt1[4*3+1] = movBoxCorner[PPN*3+1];
   movBoxEdgePt1[4*3+2] = movBoxCorner[PPN*3+2];
   movBoxEdgePt2[4*3+0] = movBoxCorner[PNN*3+0];
   movBoxEdgePt2[4*3+1] = movBoxCorner[PNN*3+1];
   movBoxEdgePt2[4*3+2] = movBoxCorner[PNN*3+2];
   
   movBoxEdgePt1[5*3+0] = movBoxCorner[PNN*3+0];// CNN
   movBoxEdgePt1[5*3+1] = movBoxCorner[PNN*3+1];
   movBoxEdgePt1[5*3+2] = movBoxCorner[PNN*3+2];
   movBoxEdgePt2[5*3+0] = movBoxCorner[NNN*3+0];
   movBoxEdgePt2[5*3+1] = movBoxCorner[NNN*3+1];
   movBoxEdgePt2[5*3+2] = movBoxCorner[NNN*3+2];
   
   movBoxEdgePt1[6*3+0] = movBoxCorner[NNN*3+0];// NCN
   movBoxEdgePt1[6*3+1] = movBoxCorner[NNN*3+1];
   movBoxEdgePt1[6*3+2] = movBoxCorner[NNN*3+2];
   movBoxEdgePt2[6*3+0] = movBoxCorner[NPN*3+0];
   movBoxEdgePt2[6*3+1] = movBoxCorner[NPN*3+1];
   movBoxEdgePt2[6*3+2] = movBoxCorner[NPN*3+2];
   
   movBoxEdgePt1[7*3+0] = movBoxCorner[NPN*3+0];// CPN
   movBoxEdgePt1[7*3+1] = movBoxCorner[NPN*3+1];
   movBoxEdgePt1[7*3+2] = movBoxCorner[NPN*3+2];
   movBoxEdgePt2[7*3+0] = movBoxCorner[PPN*3+0];
   movBoxEdgePt2[7*3+1] = movBoxCorner[PPN*3+1];
   movBoxEdgePt2[7*3+2] = movBoxCorner[PPN*3+2];
   
   // sides
   movBoxEdgePt1[8*3+0] = movBoxCorner[PPP*3+0];// PPC
   movBoxEdgePt1[8*3+1] = movBoxCorner[PPP*3+1];
   movBoxEdgePt1[8*3+2] = movBoxCorner[PPP*3+2];
   movBoxEdgePt2[8*3+0] = movBoxCorner[PPN*3+0];
   movBoxEdgePt2[8*3+1] = movBoxCorner[PPN*3+1];
   movBoxEdgePt2[8*3+2] = movBoxCorner[PPN*3+2];
   
   movBoxEdgePt1[9*3+0] = movBoxCorner[PNP*3+0];// PNC
   movBoxEdgePt1[9*3+1] = movBoxCorner[PNP*3+1];
   movBoxEdgePt1[9*3+2] = movBoxCorner[PNP*3+2];
   movBoxEdgePt2[9*3+0] = movBoxCorner[PNN*3+0];
   movBoxEdgePt2[9*3+1] = movBoxCorner[PNN*3+1];
   movBoxEdgePt2[9*3+2] = movBoxCorner[PNN*3+2];
   
   movBoxEdgePt1[10*3+0] = movBoxCorner[NNP*3+0];// NNC
   movBoxEdgePt1[10*3+1] = movBoxCorner[NNP*3+1];
   movBoxEdgePt1[10*3+2] = movBoxCorner[NNP*3+2];
   movBoxEdgePt2[10*3+0] = movBoxCorner[NNN*3+0];
   movBoxEdgePt2[10*3+1] = movBoxCorner[NNN*3+1];
   movBoxEdgePt2[10*3+2] = movBoxCorner[NNN*3+2];
   
   movBoxEdgePt1[11*3+0] = movBoxCorner[NPP*3+0];// NPC
   movBoxEdgePt1[11*3+1] = movBoxCorner[NPP*3+1];
   movBoxEdgePt1[11*3+2] = movBoxCorner[NPP*3+2];
   movBoxEdgePt2[11*3+0] = movBoxCorner[NPN*3+0];
   movBoxEdgePt2[11*3+1] = movBoxCorner[NPN*3+1];
   movBoxEdgePt2[11*3+2] = movBoxCorner[NPN*3+2];
   
   
   // create the double face data for each edge of the "fixed box"
   
   // top
   fixBoxFace1[0] = fixed_TRANS[SZX];// PCP
   fixBoxFace2[0] = fixed_TRANS[SZZ];
   fixBoxFace1[1] = -fixed_TRANS[SZY];// CNP
   fixBoxFace2[1] = fixed_TRANS[SZZ];
   fixBoxFace1[2] = -fixed_TRANS[SZX];// NCP
   fixBoxFace2[2] = fixed_TRANS[SZZ];
   fixBoxFace1[3] = fixed_TRANS[SZY];// CPP
   fixBoxFace2[3] = fixed_TRANS[SZZ];
   
   // bottom
   fixBoxFace1[4] = fixed_TRANS[SZX];// PCN
   fixBoxFace2[4] = -fixed_TRANS[SZZ];
   fixBoxFace1[5] = -fixed_TRANS[SZY];// CNN
   fixBoxFace2[5] = -fixed_TRANS[SZZ];
   fixBoxFace1[6] = -fixed_TRANS[SZX];// NCN
   fixBoxFace2[6] = -fixed_TRANS[SZZ];
   fixBoxFace1[7] = fixed_TRANS[SZY];// CPN
   fixBoxFace2[7] = -fixed_TRANS[SZZ];
   
   // sides
   fixBoxFace1[8] = fixed_TRANS[SZX];// PPC
   fixBoxFace2[8] = fixed_TRANS[SZY];
   fixBoxFace1[9] = fixed_TRANS[SZX];// PNC
   fixBoxFace2[9] = -fixed_TRANS[SZY];
   fixBoxFace1[10] = -fixed_TRANS[SZX];// NNC
   fixBoxFace2[10] = -fixed_TRANS[SZY];
   fixBoxFace1[11] = -fixed_TRANS[SZX];// NPC
   fixBoxFace2[11] = fixed_TRANS[SZY];
   
   // create the face orientation sequence data
   // relevant to the face data of a normalized box
   
   #define xFace 1
   #define yFace 2
   #define zFace 3
   
   // top
   face1[0] = xFace;// PCP
   face2[0] = zFace;
   face1[1] = -yFace;// CNP
   face2[1] = zFace;
   face1[2] = -xFace;// NCP
   face2[2] = zFace;
   face1[3] = yFace;// CPP
   face2[3] = zFace;
   
   // bottom
   face1[4] = xFace;// PCN
   face2[4] = -zFace;
   face1[5] = -yFace;// CNN
   face2[5] = -zFace;
   face1[6] = -xFace;// NCN
   face2[6] = -zFace;
   face1[7] = yFace;// CPN
   face2[7] = -zFace;
   
   // sides
   face1[8] = xFace;// PPC
   face2[8] = yFace;
   face1[9] = xFace;// PNC
   face2[9] = -yFace;
   face1[10] = -xFace;// NNC
   face2[10] = -yFace;
   face1[11] = -xFace;// NPC
   face2[11] = yFace;
   
   
   
   xTravelFixNorm = 0; yTravelFixNorm = 0; zTravelFixNorm = 0;
   xTravelMovNorm = 0; yTravelMovNorm = 0; zTravelMovNorm = 0;

   for (i=0*3; i < 12*3; i+=3)
   for (j=0; j < 12; j++)
   {
      // top and bottom
      if ((face2[j] == zFace) || (face2[j] == -zFace))
      {
         if ((face1[j] == xFace) || (face1[j] == -xFace))
         {
            // find the "fixed box" face most perpedicalar to the arrow
            if (fabs(zArrowFixNorm) > fabs(xArrowFixNorm))
            {
               // Extend each point of an edge on the "moving box" in the direction or opposite
               // of the arrow until it hits one of the two faces of an edge on the "fixed box".
               xEdgePt1 = movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]+xArrowFixNorm));
               yEdgePt1 = movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]+yArrowFixNorm));
               zEdgePt1 = fixBoxFace2[j];
               
               xEdgePt2 = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]+xArrowFixNorm));
               yEdgePt2 = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]+yArrowFixNorm));
               zEdgePt2 = fixBoxFace2[j];
               
               // if the "fixed box" edge is not between the extended edge
               if (((xEdgePt1 > fixBoxFace1[j]) && (xEdgePt2 > fixBoxFace1[j])) ||
                   ((xEdgePt1 < fixBoxFace1[j]) && (xEdgePt2 < fixBoxFace1[j])))
               continue;
               
               // find where the line between the extended edge vertices on
               // the "moving box" and the edge on the "fixed box" intersect
               xFixEdgeContact = fixBoxFace1[j];
               yFixEdgeContact = yEdgePt1 - (xEdgePt1 - fixBoxFace1[j]) /
                                (xEdgePt1 - xEdgePt2) *
                                (yEdgePt1 - yEdgePt2);
               zFixEdgeContact = zEdgePt1 - (xEdgePt1 - fixBoxFace1[j]) /
                                (xEdgePt1 - xEdgePt2) *
                                (zEdgePt1 - zEdgePt2);
               
               // if the contact point is not within the edge of the "fixed box"
               if ((yFixEdgeContact > fixed_TRANS[SZY]) || (yFixEdgeContact < -fixed_TRANS[SZY]))
               continue;
               
               
               // add face contact data to variable
               if (xFixEdgeContact > 0)
               lastContactDataBuff = FIXED_POS_X;
               else
               lastContactDataBuff = FIXED_NEG_X;
               
               if (zFixEdgeContact > 0)
               lastContactDataBuff |= FIXED_POS_Z;
               else
               lastContactDataBuff |= FIXED_NEG_Z;
            }
            else
            {
               // Extend each point of an edge on the "moving box" in the direction or opposite
               // of the arrow until it hits one of the two faces of an edge on the "fixed box".
               xEdgePt1 = fixBoxFace1[j];
               yEdgePt1 = movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]-yArrowFixNorm));
               zEdgePt1 = movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]-zArrowFixNorm));
               
               xEdgePt2 = fixBoxFace1[j];
               yEdgePt2 = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]-yArrowFixNorm));
               zEdgePt2 = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]-zArrowFixNorm));
               
               // if the "fixed box" edge is not between the extended edge
               if (((zEdgePt1 > fixBoxFace2[j]) && (zEdgePt2 > fixBoxFace2[j])) ||
                   ((zEdgePt1 < fixBoxFace2[j]) && (zEdgePt2 < fixBoxFace2[j])))
               continue;
               
               // find where the line between the extended edge vertices on
               // the "moving box" and the edge on the "fixed box" intersect
               xFixEdgeContact = xEdgePt1 - (zEdgePt1 - fixBoxFace2[j]) /
                                (zEdgePt1 - zEdgePt2) *
                                (xEdgePt1 - xEdgePt2);
               yFixEdgeContact = yEdgePt1 - (zEdgePt1 - fixBoxFace2[j]) /
                                (zEdgePt1 - zEdgePt2) *
                                (yEdgePt1 - yEdgePt2);
               zFixEdgeContact = fixBoxFace2[j];
               
               // if the contact point is not within the edge of the "fixed box"
               if ((yFixEdgeContact > fixed_TRANS[SZY]) || (yFixEdgeContact < -fixed_TRANS[SZY]))
               continue;
               
               
               // add face contact data to variable
               if (xFixEdgeContact > 0)
               lastContactDataBuff = FIXED_POS_X;
               else
               lastContactDataBuff = FIXED_NEG_X;
               
               if (zFixEdgeContact > 0)
               lastContactDataBuff |= FIXED_POS_Z;
               else
               lastContactDataBuff |= FIXED_NEG_Z;
            }
         }
         
         if ((face1[j] == yFace) || (face1[j] == -yFace))
         {
            // find the "fixed box" face most perpedicalar to the arrow
            if (fabs(zArrowFixNorm) > fabs(yArrowFixNorm))
            {
               // Extend each point of an edge on the "moving box" in the direction or opposite
               // of the arrow until it hits one of the two faces of an edge on the "fixed box".
               xEdgePt1 = movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]+xArrowFixNorm));
               yEdgePt1 = movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]+yArrowFixNorm));
               zEdgePt1 = fixBoxFace2[j];
               
               xEdgePt2 = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]+xArrowFixNorm));
               yEdgePt2 = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+2] - fixBoxFace2[j]) /
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]+zArrowFixNorm)) *
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]+yArrowFixNorm));
               zEdgePt2 = fixBoxFace2[j];
               
               // if the "fixed box" edge is not between the extended edge
               if (((yEdgePt1 > fixBoxFace1[j]) && (yEdgePt2 > fixBoxFace1[j])) ||
                   ((yEdgePt1 < fixBoxFace1[j]) && (yEdgePt2 < fixBoxFace1[j])))
               continue;
               
               // find where the line between the extended edge vertices on
               // the "moving box" and the edge on the "fixed box" intersect
               xFixEdgeContact = xEdgePt1 - (yEdgePt1 - fixBoxFace1[j]) /
                                (yEdgePt1 - yEdgePt2) *
                                (xEdgePt1 - xEdgePt2);
               yFixEdgeContact = fixBoxFace1[j];
               zFixEdgeContact = zEdgePt1 - (yEdgePt1 - fixBoxFace1[j]) /
                                (yEdgePt1 - yEdgePt2) *
                                (zEdgePt1 - zEdgePt2);
               
               // if the contact point is not within the edge of the "fixed box"
               if ((xFixEdgeContact > fixed_TRANS[SZX]) || (xFixEdgeContact < -fixed_TRANS[SZX]))
               continue;
               
               
               // add face contact data to variable
               if (yFixEdgeContact > 0)
               lastContactDataBuff = FIXED_POS_Y;
               else
               lastContactDataBuff = FIXED_NEG_Y;
               
               if (zFixEdgeContact > 0)
               lastContactDataBuff |= FIXED_POS_Z;
               else
               lastContactDataBuff |= FIXED_NEG_Z;
            }
            else
            {
               // Extend each point of an edge on the "moving box" in the direction or opposite
               // of the arrow until it hits one of the two faces of an edge on the "fixed box".
               xEdgePt1 = movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+1] - fixBoxFace1[j]) /
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]+xArrowFixNorm));
               yEdgePt1 = fixBoxFace1[j];
               zEdgePt1 = movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+1] - fixBoxFace1[j]) /
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]+zArrowFixNorm));
               
               xEdgePt2 = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+1] - fixBoxFace1[j]) /
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]+xArrowFixNorm));
               yEdgePt2 = fixBoxFace1[j];
               zEdgePt2 = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+1] - fixBoxFace1[j]) /
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]+zArrowFixNorm));
               
               // if the "fixed box" edge is not between the extended edge
               if (((zEdgePt1 > fixBoxFace2[j]) && (zEdgePt2 > fixBoxFace2[j])) ||
                   ((zEdgePt1 < fixBoxFace2[j]) && (zEdgePt2 < fixBoxFace2[j])))
               continue;
               
               // find where the line between the extended edge vertices on
               // the "moving box" and the edge on the "fixed box" intersect
               xFixEdgeContact = xEdgePt1 - (zEdgePt1 - fixBoxFace2[j]) /
                                (zEdgePt1 - zEdgePt2) *
                                (xEdgePt1 - xEdgePt2);
               yFixEdgeContact = yEdgePt1 - (zEdgePt1 - fixBoxFace2[j]) /
                                (zEdgePt1 - zEdgePt2) *
                                (yEdgePt1 - yEdgePt2);
               zFixEdgeContact = fixBoxFace2[j];
               
               // if the contact point is not within the edge of the "fixed box"
               if ((xFixEdgeContact > fixed_TRANS[SZX]) || (xFixEdgeContact < -fixed_TRANS[SZX]))
               continue;
               
               
               // add face contact data to variable
               if (yFixEdgeContact > 0)
               lastContactDataBuff = FIXED_POS_Y;
               else
               lastContactDataBuff = FIXED_NEG_Y;
               
               if (zFixEdgeContact > 0)
               lastContactDataBuff |= FIXED_POS_Z;
               else
               lastContactDataBuff |= FIXED_NEG_Z;
            }
         }
      }
      
      // sides
      if ((face2[j] == yFace) || (face2[j] == -yFace))
      {
         if ((face1[j] == xFace) || (face1[j] == -xFace))
         {
            // find the "fixed box" face most perpedicalar to the arrow
            if (fabs(yArrowFixNorm) > fabs(xArrowFixNorm))
            {
               // Extend each point of an edge on the "moving box" in the direction or opposite
               // of the arrow until it hits one of the two faces of an edge on the "fixed box".
               xEdgePt1 = movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+1] - fixBoxFace2[j]) /
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]+xArrowFixNorm));
               yEdgePt1 = fixBoxFace2[j];
               zEdgePt1 = movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+1] - fixBoxFace2[j]) /
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]+zArrowFixNorm));
               
               xEdgePt2 = movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+1] - fixBoxFace2[j]) /
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]+xArrowFixNorm));
               yEdgePt2 = fixBoxFace2[j];
               zEdgePt2 = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+1] - fixBoxFace2[j]) /
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]+yArrowFixNorm)) *
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]+zArrowFixNorm));
               
               // if the "fixed box" edge is not between the extended edge
               if (((xEdgePt1 > fixBoxFace1[j]) && (xEdgePt2 > fixBoxFace1[j])) ||
                   ((xEdgePt1 < fixBoxFace1[j]) && (xEdgePt2 < fixBoxFace1[j])))
               continue;
               
               // find where the line between the extended edge vertices on
               // the "moving box" and the edge on the "fixed box" intersect
               xFixEdgeContact = fixBoxFace1[j];
               yFixEdgeContact = yEdgePt1 - (xEdgePt1 - fixBoxFace1[j]) /
                                (xEdgePt1 - xEdgePt2) *
                                (yEdgePt1 - yEdgePt2);
               zFixEdgeContact = zEdgePt1 - (xEdgePt1 - fixBoxFace1[j]) /
                                (xEdgePt1 - xEdgePt2) *
                                (zEdgePt1 - zEdgePt2);
               
               // if the contact point is not within the edge of the "fixed box"
               if ((zFixEdgeContact > fixed_TRANS[SZZ]) || (zFixEdgeContact < -fixed_TRANS[SZZ]))
               continue;
               
               
               // add face contact data to variable
               if (xFixEdgeContact > 0)
               lastContactDataBuff = FIXED_POS_X;
               else
               lastContactDataBuff = FIXED_NEG_X;
               
               if (yFixEdgeContact > 0)
               lastContactDataBuff |= FIXED_POS_Y;
               else
               lastContactDataBuff |= FIXED_NEG_Y;
            }
            else
            {
               // Extend each point of an edge on the "moving box" in the direction or opposite
               // of the arrow until it hits one of the two faces of an edge on the "fixed box".
               xEdgePt1 = fixBoxFace1[j];
               yEdgePt1 = movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt1[i+1] - (movBoxEdgePt1[i+1]-yArrowFixNorm));
               zEdgePt1 = movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt1[i+0] - (movBoxEdgePt1[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt1[i+2] - (movBoxEdgePt1[i+2]-zArrowFixNorm));
               
               xEdgePt2 = fixBoxFace1[j];
               yEdgePt2 = movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt2[i+1] - (movBoxEdgePt2[i+1]-yArrowFixNorm));
               zEdgePt2 = movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+0] - fixBoxFace1[j]) /
                         (movBoxEdgePt2[i+0] - (movBoxEdgePt2[i+0]-xArrowFixNorm)) *
                         (movBoxEdgePt2[i+2] - (movBoxEdgePt2[i+2]-zArrowFixNorm));
               
               // if the "fixed box" edge is not between the extended edge
               if (((yEdgePt1 > fixBoxFace2[j]) && (yEdgePt2 > fixBoxFace2[j])) ||
                   ((yEdgePt1 < fixBoxFace2[j]) && (yEdgePt2 < fixBoxFace2[j])))
               continue;
               
               // find where the line between the extended edge vertices on
               // the "moving box" and the edge on the "fixed box" intersect
               xFixEdgeContact = xEdgePt1 - (yEdgePt1 - fixBoxFace2[j]) /
                                (yEdgePt1 - yEdgePt2) *
                                (xEdgePt1 - xEdgePt2);
               yFixEdgeContact = fixBoxFace2[j];
               zFixEdgeContact = zEdgePt1 - (yEdgePt1 - fixBoxFace2[j]) /
                                (yEdgePt1 - yEdgePt2) *
                                (zEdgePt1 - zEdgePt2);
               
               // if the contact point is not within the edge of the "fixed box"
               if ((zFixEdgeContact > fixed_TRANS[SZZ]) || (zFixEdgeContact < -fixed_TRANS[SZZ]))
               continue;
               
               
               // add face contact data to variable
               if (xFixEdgeContact > 0)
               lastContactDataBuff = FIXED_POS_X;
               else
               lastContactDataBuff = FIXED_NEG_X;
               
               if (yFixEdgeContact > 0)
               lastContactDataBuff |= FIXED_POS_Y;
               else
               lastContactDataBuff |= FIXED_NEG_Y;
            }
         }
      }
      
      
      // rotate and move the "fixed box" edge contact point to undo the normalization
      applyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                           fixed_TRANS[11], fixed_TRANS[12],
                           fixed_TRANS[13], fixed_TRANS[14],
                           &xFixEdgeContact, &yFixEdgeContact, &zFixEdgeContact);
      
      xFixEdgeContact += fixed_TRANS[LOCX];
      yFixEdgeContact += fixed_TRANS[LOCY];
      zFixEdgeContact += fixed_TRANS[LOCZ];
      
      // move and rotate the "fixed box" edge contact point
      // in the same way it takes to normalize the "moving box" plus travel distance
      xFixEdgeContact -= moving_TRANS[LOCX] + *xTravel;
      yFixEdgeContact -= moving_TRANS[LOCY] + *yTravel;
      zFixEdgeContact -= moving_TRANS[LOCZ] + *zTravel;
      
      reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                                  moving_TRANS[11], moving_TRANS[12],
                                  moving_TRANS[13], moving_TRANS[14],
                                  &xFixEdgeContact, &yFixEdgeContact, &zFixEdgeContact);
      
      
      // top and bottom
      if ((face2[i/3] == zFace) || (face2[i/3] == -zFace))
      {
         if ((face1[i/3] == xFace) || (face1[i/3] == -xFace))
         {
            // find the "moving box" face most perpedicalar to the arrow
            if (fabs(zArrowMovNorm) > fabs(xArrowMovNorm))
            {
               // find where the "moving box" was first contacted by extending the point, where
               // the "fixed box" was first contacted, in the opposite direction of the arrow
               
               if (face2[i/3] == zFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (zFixEdgeContact - moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = yFixEdgeContact - (zFixEdgeContact - moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm));
                  zMovEdgeContact = moving_TRANS[SZZ];
               }
               
               if (face2[i/3] == -zFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (zFixEdgeContact - -moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = yFixEdgeContact - (zFixEdgeContact - -moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm));
                  zMovEdgeContact = -moving_TRANS[SZZ];
               }
               
               // is the edge contact point between the front and back faces of the "moving box"
               if ((yMovEdgeContact <= moving_TRANS[SZY]) && (yMovEdgeContact >= -moving_TRANS[SZY]))
               {
                  // is it the longest travel distance
                  if (((zArrowMovNorm > 0) && ((zMovEdgeContact - zFixEdgeContact) > zTravelMovNorm)) ||
                      ((zArrowMovNorm < 0) && ((zMovEdgeContact - zFixEdgeContact) < zTravelMovNorm)))
                  {
                     xTravelMovNorm = xMovEdgeContact - xFixEdgeContact;
                     yTravelMovNorm = yMovEdgeContact - yFixEdgeContact;
                     zTravelMovNorm = zMovEdgeContact - zFixEdgeContact;
                     
                     // add face contact data to variable
                     if (xMovEdgeContact > 0)
                     *lastContactData = MOVING_POS_X;
                     else
                     *lastContactData = MOVING_NEG_X;
                     
                     if (zMovEdgeContact > 0)
                     *lastContactData |= MOVING_POS_Z;
                     else
                     *lastContactData |= MOVING_NEG_Z;
                     
                     *lastContactData |= lastContactDataBuff;
                  }
               }
            }
            else
            {
               if (face1[i/3] == xFace)
               {
                  xMovEdgeContact = moving_TRANS[SZX];
                  yMovEdgeContact = yFixEdgeContact - (xFixEdgeContact - moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact-yArrowMovNorm));
                  zMovEdgeContact = zFixEdgeContact - (xFixEdgeContact - moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact-zArrowMovNorm));
               }
               
               if (face1[i/3] == -xFace)
               {
                  xMovEdgeContact = -moving_TRANS[SZX];
                  yMovEdgeContact = yFixEdgeContact - (xFixEdgeContact - -moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact-yArrowMovNorm));
                  zMovEdgeContact = zFixEdgeContact - (xFixEdgeContact - -moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact-zArrowMovNorm));
               }
               
               // is the edge contact point between the front and back faces of the "moving box"
               if ((yMovEdgeContact <= moving_TRANS[SZY]) && (yMovEdgeContact >= -moving_TRANS[SZY]))
               {
                  // is it the longest travel distance
                  if (((xArrowMovNorm > 0) && ((xMovEdgeContact - xFixEdgeContact) > xTravelMovNorm)) ||
                      ((xArrowMovNorm < 0) && ((xMovEdgeContact - xFixEdgeContact) < xTravelMovNorm)))
                  {
                     xTravelMovNorm = xMovEdgeContact - xFixEdgeContact;
                     yTravelMovNorm = yMovEdgeContact - yFixEdgeContact;
                     zTravelMovNorm = zMovEdgeContact - zFixEdgeContact;
                     
                     // add face contact data to variable
                     if (xMovEdgeContact > 0)
                     *lastContactData = MOVING_POS_X;
                     else
                     *lastContactData = MOVING_NEG_X;
                     
                     if (zMovEdgeContact > 0)
                     *lastContactData |= MOVING_POS_Z;
                     else
                     *lastContactData |= MOVING_NEG_Z;
                     
                     *lastContactData |= lastContactDataBuff;
                  }
               }
            }
         }
         
         
         if ((face1[i/3] == yFace) || (face1[i/3] == -yFace))
         {
            // find the "moving box" face most perpedicalar to the arrow
            if (fabs(zArrowMovNorm) > fabs(yArrowMovNorm))
            {
               // find where the "moving box" was first contacted by extending the point, where
               // the "fixed box" was first contacted, in the opposite direction of the arrow
               
               if (face2[i/3] == zFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (zFixEdgeContact - moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = yFixEdgeContact - (zFixEdgeContact - moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm));
                  zMovEdgeContact = moving_TRANS[SZZ];
               }
               
               if (face2[i/3] == -zFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (zFixEdgeContact - -moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = yFixEdgeContact - (zFixEdgeContact - -moving_TRANS[SZZ]) /
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm));
                  zMovEdgeContact = -moving_TRANS[SZZ];
               }
               
               // is the edge contact point between the left and right faces of the "moving box"
               if ((xMovEdgeContact <= moving_TRANS[SZX]) && (xMovEdgeContact >= -moving_TRANS[SZX]))
               {
                  // is it the longest travel distance
                  if (((zArrowMovNorm > 0) && ((zMovEdgeContact - zFixEdgeContact) > zTravelMovNorm)) ||
                      ((zArrowMovNorm < 0) && ((zMovEdgeContact - zFixEdgeContact) < zTravelMovNorm)))
                  {
                     xTravelMovNorm = xMovEdgeContact - xFixEdgeContact;
                     yTravelMovNorm = yMovEdgeContact - yFixEdgeContact;
                     zTravelMovNorm = zMovEdgeContact - zFixEdgeContact;
                     
                     // add face contact data to variable
                     if (yMovEdgeContact > 0)
                     *lastContactData = MOVING_POS_Y;
                     else
                     *lastContactData = MOVING_NEG_Y;
                     
                     if (zMovEdgeContact > 0)
                     *lastContactData |= MOVING_POS_Z;
                     else
                     *lastContactData |= MOVING_NEG_Z;
                     
                     *lastContactData |= lastContactDataBuff;
                  }
               }
            }
            else
            {
               if (face1[i/3] == yFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (yFixEdgeContact - moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = moving_TRANS[SZY];
                  zMovEdgeContact = zFixEdgeContact - (yFixEdgeContact - moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm));
               }
               
               if (face1[i/3] == -yFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (yFixEdgeContact - -moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = -moving_TRANS[SZY];
                  zMovEdgeContact = zFixEdgeContact - (yFixEdgeContact - -moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm));
               }
               
               // is the edge contact point between the left and right faces of the "moving box"
               if ((xMovEdgeContact <= moving_TRANS[SZX]) && (xMovEdgeContact >= -moving_TRANS[SZX]))
               {
                  // is it the longest travel distance
                  if (((yArrowMovNorm > 0) && ((yMovEdgeContact - yFixEdgeContact) > yTravelMovNorm)) ||
                      ((yArrowMovNorm < 0) && ((yMovEdgeContact - yFixEdgeContact) < yTravelMovNorm)))
                  {
                     xTravelMovNorm = xMovEdgeContact - xFixEdgeContact;
                     yTravelMovNorm = yMovEdgeContact - yFixEdgeContact;
                     zTravelMovNorm = zMovEdgeContact - zFixEdgeContact;
                     
                     // add face contact data to variable
                     if (yMovEdgeContact > 0)
                     *lastContactData = MOVING_POS_Y;
                     else
                     *lastContactData = MOVING_NEG_Y;
                     
                     if (zMovEdgeContact > 0)
                     *lastContactData |= MOVING_POS_Z;
                     else
                     *lastContactData |= MOVING_NEG_Z;
                     
                     *lastContactData |= lastContactDataBuff;
                  }
               }
            }
         }
      }
      
      
      // sides
      if ((face2[i/3] == yFace) || (face2[i/3] == -yFace))
      {
         if ((face1[i/3] == xFace) || (face1[i/3] == -xFace))
         {
            // find the "moving box" face most perpedicalar to the arrow
            if (fabs(yArrowMovNorm) > fabs(xArrowMovNorm))
            {
               // find where the "moving box" was first contacted by extending the point, where
               // the "fixed box" was first contacted, in the opposite direction of the arrow
               
               if (face2[i/3] == yFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (yFixEdgeContact - moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = moving_TRANS[SZY];
                  zMovEdgeContact = zFixEdgeContact - (yFixEdgeContact - moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm));
               }
               
               if (face2[i/3] == -yFace)
               {
                  xMovEdgeContact = xFixEdgeContact - (yFixEdgeContact - -moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (xFixEdgeContact - (xFixEdgeContact+xArrowMovNorm));
                  yMovEdgeContact = -moving_TRANS[SZY];
                  zMovEdgeContact = zFixEdgeContact - (yFixEdgeContact - -moving_TRANS[SZY]) /
                                   (yFixEdgeContact - (yFixEdgeContact+yArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact+zArrowMovNorm));
               }
               
               // is the edge contact point between the top and bottom faces of the "moving box"
               if ((zMovEdgeContact <= moving_TRANS[SZZ]) && (zMovEdgeContact >= -moving_TRANS[SZZ]))
               {
                  // is it the longest travel distance
                  if (((yArrowMovNorm > 0) && ((yMovEdgeContact - yFixEdgeContact) > yTravelMovNorm)) ||
                      ((yArrowMovNorm < 0) && ((yMovEdgeContact - yFixEdgeContact) < yTravelMovNorm)))
                  {
                     xTravelMovNorm = xMovEdgeContact - xFixEdgeContact;
                     yTravelMovNorm = yMovEdgeContact - yFixEdgeContact;
                     zTravelMovNorm = zMovEdgeContact - zFixEdgeContact;
                     
                     // add face contact data to variable
                     if (xMovEdgeContact > 0)
                     *lastContactData = MOVING_POS_X;
                     else
                     *lastContactData = MOVING_NEG_X;
                     
                     if (yMovEdgeContact > 0)
                     *lastContactData |= MOVING_POS_Y;
                     else
                     *lastContactData |= MOVING_NEG_Y;
                     
                     *lastContactData |= lastContactDataBuff;
                  }
               }
            }
            else
            {
               if (face1[i/3] == xFace)
               {
                  xMovEdgeContact = moving_TRANS[SZX];
                  yMovEdgeContact = yFixEdgeContact - (xFixEdgeContact - moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact-yArrowMovNorm));
                  zMovEdgeContact = zFixEdgeContact - (xFixEdgeContact - moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact-zArrowMovNorm));
               }
               
               if (face1[i/3] == -xFace)
               {
                  xMovEdgeContact = -moving_TRANS[SZX];
                  yMovEdgeContact = yFixEdgeContact - (xFixEdgeContact - -moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (yFixEdgeContact - (yFixEdgeContact-yArrowMovNorm));
                  zMovEdgeContact = zFixEdgeContact - (xFixEdgeContact - -moving_TRANS[SZX]) /
                                   (xFixEdgeContact - (xFixEdgeContact-xArrowMovNorm)) *
                                   (zFixEdgeContact - (zFixEdgeContact-zArrowMovNorm));
               }
               
               // is the edge contact point between the top and bottom faces of the "moving box"
               if ((zMovEdgeContact <= moving_TRANS[SZZ]) && (zMovEdgeContact >= -moving_TRANS[SZZ]))
               {
                  // is it the longest travel distance
                  if (((xArrowMovNorm > 0) && ((xMovEdgeContact - xFixEdgeContact) > xTravelMovNorm)) ||
                      ((xArrowMovNorm < 0) && ((xMovEdgeContact - xFixEdgeContact) < xTravelMovNorm)))
                  {
                     xTravelMovNorm = xMovEdgeContact - xFixEdgeContact;
                     yTravelMovNorm = yMovEdgeContact - yFixEdgeContact;
                     zTravelMovNorm = zMovEdgeContact - zFixEdgeContact;
                     
                     // add face contact data to variable
                     if (xMovEdgeContact > 0)
                     *lastContactData = MOVING_POS_X;
                     else
                     *lastContactData = MOVING_NEG_X;
                     
                     if (yMovEdgeContact > 0)
                     *lastContactData |= MOVING_POS_Y;
                     else
                     *lastContactData |= MOVING_NEG_Y;
                     
                     *lastContactData |= lastContactDataBuff;
                  }
               }
            }
         }
      }
   }
   
   
   // apply the rotation to undo the "moving box" normalization
   applyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                        moving_TRANS[11], moving_TRANS[12],
                        moving_TRANS[13], moving_TRANS[14],
                        &xTravelMovNorm, &yTravelMovNorm, &zTravelMovNorm);
   
   *xTravel -= xTravelMovNorm;
   *yTravel -= yTravelMovNorm;
   *zTravel -= zTravelMovNorm;
   
   // resize the "moving box" back to its normal size
   moving_TRANS[SZX] -= boxMargin;
   moving_TRANS[SZY] -= boxMargin;
   moving_TRANS[SZZ] -= boxMargin;
}



void localBoxCollision(float *fixed_TRANS, float *moving_TRANS, float boxMargin,
                       float xTravel, float yTravel, float zTravel,
                       float *xActual, float *yActual, float *zActual, int *faceImpact, int *contact)
{
   int i;
   float xP, yP, zP;
   
   float xMovPast[8], yMovPast[8], zMovPast[8];
   float xMovPreset[8], yMovPreset[8], zMovPreset[8];
   float xMovPastCenter, yMovPastCenter, zMovPastCenter;
   float xMovPresetCenter, yMovPresetCenter, zMovPresetCenter;
   
   float xFixPreset[8], yFixPreset[8], zFixPreset[8];
   float xFixMirror[8], yFixMirror[8], zFixMirror[8];
   float xFixPresetCenter, yFixPresetCenter, zFixPresetCenter;
   float xFixMirrorCenter, yFixMirrorCenter, zFixMirrorCenter;
   
   float movPastEdgePt1[12*3];
   float movPastEdgePt2[12*3];
   float movPresetEdgePt1[12*3];
   float movPresetEdgePt2[12*3];
   
   float fixMirrorEdgePt1[12*3];
   float fixMirrorEdgePt2[12*3];
   float fixPresetEdgePt1[12*3];
   float fixPresetEdgePt2[12*3];
   
   float xArrow, yArrow, zArrow;
   int nullVar;
   
   
   // find if the "moving box" is already contacting the "fixed box"
   localBoxDetectAndMove(fixed_TRANS, moving_TRANS, boxMargin,
                         0, 0, 0, FALSE, &xP, &yP, &zP, &*faceImpact, &*contact);
   
   // if both boxes are contacting return
   if (*contact)
   {
      *faceImpact = 0;
      *xActual = 0;
      *yActual = 0;
      *zActual = 0;
      return;
   }
   
   // for later use with localBoxDetectAndMove()
   // The "xArrow", "yArrow", and zArrow variables will be used to give a direction
   // of which way to move the "moving box" out of the "fixed box" it may have collided with.
   xArrow = -xTravel;
   yArrow = -yTravel;
   zArrow = -zTravel;
   
   
   // create the "moving box" using transformation data
   xMovPreset[0] = -moving_TRANS[SZX];
   yMovPreset[0] = moving_TRANS[SZY];
   zMovPreset[0] = moving_TRANS[SZZ];
   
   xMovPreset[1] = moving_TRANS[SZX];
   yMovPreset[1] = moving_TRANS[SZY];
   zMovPreset[1] = moving_TRANS[SZZ];
   
   xMovPreset[2] = -moving_TRANS[SZX];
   yMovPreset[2] = -moving_TRANS[SZY];
   zMovPreset[2] = moving_TRANS[SZZ];

   xMovPreset[3] = moving_TRANS[SZX];
   yMovPreset[3] = -moving_TRANS[SZY];
   zMovPreset[3] = moving_TRANS[SZZ];
   
   
   xMovPreset[4] = -moving_TRANS[SZX];
   yMovPreset[4] = moving_TRANS[SZY];
   zMovPreset[4] = -moving_TRANS[SZZ];
   
   xMovPreset[5] = moving_TRANS[SZX];
   yMovPreset[5] = moving_TRANS[SZY];
   zMovPreset[5] = -moving_TRANS[SZZ];
   
   xMovPreset[6] = -moving_TRANS[SZX];
   yMovPreset[6] = -moving_TRANS[SZY];
   zMovPreset[6] = -moving_TRANS[SZZ];
   
   xMovPreset[7] = moving_TRANS[SZX];
   yMovPreset[7] = -moving_TRANS[SZY];
   zMovPreset[7] = -moving_TRANS[SZZ];
   
   // rotate and position the "moving box"
   for (i=0; i < 8; i++)
   {
      applyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                           moving_TRANS[11], moving_TRANS[12],
                           moving_TRANS[13], moving_TRANS[14],
                           &xMovPreset[i], &yMovPreset[i], &zMovPreset[i]); // rotation
      
      xMovPreset[i] += moving_TRANS[LOCX] + xTravel; // location
      yMovPreset[i] += moving_TRANS[LOCY] + yTravel;
      zMovPreset[i] += moving_TRANS[LOCZ] + zTravel;
   }
   
   
   // move and rotate the preset "moving box"
   // in the same way it takes to normalize the "fixed box"
   for (i=0; i < 8; i++)
   {
      xMovPreset[i] += -fixed_TRANS[LOCX];
      yMovPreset[i] += -fixed_TRANS[LOCY];
      zMovPreset[i] += -fixed_TRANS[LOCZ];
   }
   
   for (i=0; i < 8; i++)
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14],
                               &xMovPreset[i], &yMovPreset[i], &zMovPreset[i]);
   
   
   // get the centers of the past and preset boxes
   xMovPresetCenter = moving_TRANS[LOCX] + xTravel;
   yMovPresetCenter = moving_TRANS[LOCY] + yTravel;
   zMovPresetCenter = moving_TRANS[LOCZ] + zTravel;
   
   xMovPastCenter = moving_TRANS[LOCX];
   yMovPastCenter = moving_TRANS[LOCY];
   zMovPastCenter = moving_TRANS[LOCZ];
   
   // move and rotate the line connecting the centers of the past and preset boxes
   // in the same way it takes to normalize the "fixed box"
   xMovPresetCenter += -fixed_TRANS[LOCX];
   yMovPresetCenter += -fixed_TRANS[LOCY];
   zMovPresetCenter += -fixed_TRANS[LOCZ];
   
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14],
                               &xMovPresetCenter, &yMovPresetCenter, &zMovPresetCenter);
   
   xMovPastCenter += -fixed_TRANS[LOCX];
   yMovPastCenter += -fixed_TRANS[LOCY];
   zMovPastCenter += -fixed_TRANS[LOCZ];
   
   reverseApplyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                               fixed_TRANS[11], fixed_TRANS[12],
                               fixed_TRANS[13], fixed_TRANS[14],
                               &xMovPastCenter, &yMovPastCenter, &zMovPastCenter);
   
   
   // find the past position and orientation of the "moving"
   // box by relocating a copy of the preset "moving box"
   for (i=0; i < 8; i++)
   {
      xMovPast[i] = xMovPastCenter - xMovPresetCenter + xMovPreset[i];
      yMovPast[i] = yMovPastCenter - yMovPresetCenter + yMovPreset[i];
      zMovPast[i] = zMovPastCenter - zMovPresetCenter + zMovPreset[i];
   }
   
   
   
   // create the "fixed box" using transformation data
   xFixPreset[0] = -fixed_TRANS[SZX];
   yFixPreset[0] = fixed_TRANS[SZY];
   zFixPreset[0] = fixed_TRANS[SZZ];
   
   xFixPreset[1] = fixed_TRANS[SZX];
   yFixPreset[1] = fixed_TRANS[SZY];
   zFixPreset[1] = fixed_TRANS[SZZ];
   
   xFixPreset[2] = -fixed_TRANS[SZX];
   yFixPreset[2] = -fixed_TRANS[SZY];
   zFixPreset[2] = fixed_TRANS[SZZ];

   xFixPreset[3] = fixed_TRANS[SZX];
   yFixPreset[3] = -fixed_TRANS[SZY];
   zFixPreset[3] = fixed_TRANS[SZZ];
   
   
   xFixPreset[4] = -fixed_TRANS[SZX];
   yFixPreset[4] = fixed_TRANS[SZY];
   zFixPreset[4] = -fixed_TRANS[SZZ];
   
   xFixPreset[5] = fixed_TRANS[SZX];
   yFixPreset[5] = fixed_TRANS[SZY];
   zFixPreset[5] = -fixed_TRANS[SZZ];
   
   xFixPreset[6] = -fixed_TRANS[SZX];
   yFixPreset[6] = -fixed_TRANS[SZY];
   zFixPreset[6] = -fixed_TRANS[SZZ];
   
   xFixPreset[7] = fixed_TRANS[SZX];
   yFixPreset[7] = -fixed_TRANS[SZY];
   zFixPreset[7] = -fixed_TRANS[SZZ];
   
   // rotate and position the "fixed box"
   for (i=0; i < 8; i++)
   {
      applyXyzUcRotToPoint(fixed_TRANS[9], fixed_TRANS[10],
                           fixed_TRANS[11], fixed_TRANS[12],
                           fixed_TRANS[13], fixed_TRANS[14],
                           &xFixPreset[i], &yFixPreset[i], &zFixPreset[i]); // rotation
      
      xFixPreset[i] += fixed_TRANS[LOCX]; // location
      yFixPreset[i] += fixed_TRANS[LOCY];
      zFixPreset[i] += fixed_TRANS[LOCZ];
   }
   
   
   // move and rotate the preset "fixed box"
   // in the same way it takes to normalize the "moving box"
   for (i=0; i < 8; i++)
   {
      xFixPreset[i] += -moving_TRANS[LOCX];
      yFixPreset[i] += -moving_TRANS[LOCY];
      zFixPreset[i] += -moving_TRANS[LOCZ];
   }
   
   for (i=0; i < 8; i++)
   reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                               moving_TRANS[11], moving_TRANS[12],
                               moving_TRANS[13], moving_TRANS[14],
                               &xFixPreset[i], &yFixPreset[i], &zFixPreset[i]);
   
   
   // get the centers of the mirrored and preset boxes
   xFixPresetCenter = fixed_TRANS[LOCX];
   yFixPresetCenter = fixed_TRANS[LOCY];
   zFixPresetCenter = fixed_TRANS[LOCZ];
   
   xFixMirrorCenter = fixed_TRANS[LOCX] - xTravel;
   yFixMirrorCenter = fixed_TRANS[LOCY] - yTravel;
   zFixMirrorCenter = fixed_TRANS[LOCZ] - zTravel;
   
   // move and rotate the line connecting the centers of the past and mirrored boxes
   // in the same way it takes to normalize the "moving box"
   xFixPresetCenter += -moving_TRANS[LOCX];
   yFixPresetCenter += -moving_TRANS[LOCY];
   zFixPresetCenter += -moving_TRANS[LOCZ];
   
   reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                               moving_TRANS[11], moving_TRANS[12],
                               moving_TRANS[13], moving_TRANS[14],
                               &xFixPresetCenter, &yFixPresetCenter, &zFixPresetCenter);
   
   xFixMirrorCenter += -moving_TRANS[LOCX];
   yFixMirrorCenter += -moving_TRANS[LOCY];
   zFixMirrorCenter += -moving_TRANS[LOCZ];
   
   reverseApplyXyzUcRotToPoint(moving_TRANS[9], moving_TRANS[10],
                               moving_TRANS[11], moving_TRANS[12],
                               moving_TRANS[13], moving_TRANS[14],
                               &xFixMirrorCenter, &yFixMirrorCenter, &zFixMirrorCenter);
   
   
   // find the mirrored position and orientation of the "fixed
   // box" by relocating a copy of the preset "fixed box"
   for (i=0; i < 8; i++)
   {
      xFixMirror[i] = xFixMirrorCenter - xFixPresetCenter + xFixPreset[i];
      yFixMirror[i] = yFixMirrorCenter - yFixPresetCenter + yFixPreset[i];
      zFixMirror[i] = zFixMirrorCenter - zFixPresetCenter + zFixPreset[i];
   }
   
   
   
   // create the edge data for the past and preset "moving box"
   
   // top
   movPastEdgePt1[0*3+0] = xMovPast[1];// PCP
   movPastEdgePt1[0*3+1] = yMovPast[1];
   movPastEdgePt1[0*3+2] = zMovPast[1];
   movPastEdgePt2[0*3+0] = xMovPast[3];
   movPastEdgePt2[0*3+1] = yMovPast[3];
   movPastEdgePt2[0*3+2] = zMovPast[3];
   
   movPastEdgePt1[1*3+0] = xMovPast[3];// CNP
   movPastEdgePt1[1*3+1] = yMovPast[3];
   movPastEdgePt1[1*3+2] = zMovPast[3];
   movPastEdgePt2[1*3+0] = xMovPast[2];
   movPastEdgePt2[1*3+1] = yMovPast[2];
   movPastEdgePt2[1*3+2] = zMovPast[2];
   
   movPastEdgePt1[2*3+0] = xMovPast[2];// NCP
   movPastEdgePt1[2*3+1] = yMovPast[2];
   movPastEdgePt1[2*3+2] = zMovPast[2];
   movPastEdgePt2[2*3+0] = xMovPast[0];
   movPastEdgePt2[2*3+1] = yMovPast[0];
   movPastEdgePt2[2*3+2] = zMovPast[0];
   
   movPastEdgePt1[3*3+0] = xMovPast[0];// CPP
   movPastEdgePt1[3*3+1] = yMovPast[0];
   movPastEdgePt1[3*3+2] = zMovPast[0];
   movPastEdgePt2[3*3+0] = xMovPast[1];
   movPastEdgePt2[3*3+1] = yMovPast[1];
   movPastEdgePt2[3*3+2] = zMovPast[1];
   
   // bottom
   movPastEdgePt1[4*3+0] = xMovPast[5];// PCN
   movPastEdgePt1[4*3+1] = yMovPast[5];
   movPastEdgePt1[4*3+2] = zMovPast[5];
   movPastEdgePt2[4*3+0] = xMovPast[7];
   movPastEdgePt2[4*3+1] = yMovPast[7];
   movPastEdgePt2[4*3+2] = zMovPast[7];
   
   movPastEdgePt1[5*3+0] = xMovPast[7];// CNN
   movPastEdgePt1[5*3+1] = yMovPast[7];
   movPastEdgePt1[5*3+2] = zMovPast[7];
   movPastEdgePt2[5*3+0] = xMovPast[6];
   movPastEdgePt2[5*3+1] = yMovPast[6];
   movPastEdgePt2[5*3+2] = zMovPast[6];
   
   movPastEdgePt1[6*3+0] = xMovPast[6];// NCN
   movPastEdgePt1[6*3+1] = yMovPast[6];
   movPastEdgePt1[6*3+2] = zMovPast[6];
   movPastEdgePt2[6*3+0] = xMovPast[4];
   movPastEdgePt2[6*3+1] = yMovPast[4];
   movPastEdgePt2[6*3+2] = zMovPast[4];
   
   movPastEdgePt1[7*3+0] = xMovPast[4];// CPN
   movPastEdgePt1[7*3+1] = yMovPast[4];
   movPastEdgePt1[7*3+2] = zMovPast[4];
   movPastEdgePt2[7*3+0] = xMovPast[5];
   movPastEdgePt2[7*3+1] = yMovPast[5];
   movPastEdgePt2[7*3+2] = zMovPast[5];
   
   // sides
   movPastEdgePt1[8*3+0] = xMovPast[1];// PPC
   movPastEdgePt1[8*3+1] = yMovPast[1];
   movPastEdgePt1[8*3+2] = zMovPast[1];
   movPastEdgePt2[8*3+0] = xMovPast[5];
   movPastEdgePt2[8*3+1] = yMovPast[5];
   movPastEdgePt2[8*3+2] = zMovPast[5];
   
   movPastEdgePt1[9*3+0] = xMovPast[3];// PNC
   movPastEdgePt1[9*3+1] = yMovPast[3];
   movPastEdgePt1[9*3+2] = zMovPast[3];
   movPastEdgePt2[9*3+0] = xMovPast[7];
   movPastEdgePt2[9*3+1] = yMovPast[7];
   movPastEdgePt2[9*3+2] = zMovPast[7];
   
   movPastEdgePt1[10*3+0] = xMovPast[2];// NNC
   movPastEdgePt1[10*3+1] = yMovPast[2];
   movPastEdgePt1[10*3+2] = zMovPast[2];
   movPastEdgePt2[10*3+0] = xMovPast[6];
   movPastEdgePt2[10*3+1] = yMovPast[6];
   movPastEdgePt2[10*3+2] = zMovPast[6];
   
   movPastEdgePt1[11*3+0] = xMovPast[0];// NPC
   movPastEdgePt1[11*3+1] = yMovPast[0];
   movPastEdgePt1[11*3+2] = zMovPast[0];
   movPastEdgePt2[11*3+0] = xMovPast[4];
   movPastEdgePt2[11*3+1] = yMovPast[4];
   movPastEdgePt2[11*3+2] = zMovPast[4];
   
   
   
   // top
   movPresetEdgePt1[0*3+0] = xMovPreset[1];// PCP
   movPresetEdgePt1[0*3+1] = yMovPreset[1];
   movPresetEdgePt1[0*3+2] = zMovPreset[1];
   movPresetEdgePt2[0*3+0] = xMovPreset[3];
   movPresetEdgePt2[0*3+1] = yMovPreset[3];
   movPresetEdgePt2[0*3+2] = zMovPreset[3];
   
   movPresetEdgePt1[1*3+0] = xMovPreset[3];// CNP
   movPresetEdgePt1[1*3+1] = yMovPreset[3];
   movPresetEdgePt1[1*3+2] = zMovPreset[3];
   movPresetEdgePt2[1*3+0] = xMovPreset[2];
   movPresetEdgePt2[1*3+1] = yMovPreset[2];
   movPresetEdgePt2[1*3+2] = zMovPreset[2];
   
   movPresetEdgePt1[2*3+0] = xMovPreset[2];// NCP
   movPresetEdgePt1[2*3+1] = yMovPreset[2];
   movPresetEdgePt1[2*3+2] = zMovPreset[2];
   movPresetEdgePt2[2*3+0] = xMovPreset[0];
   movPresetEdgePt2[2*3+1] = yMovPreset[0];
   movPresetEdgePt2[2*3+2] = zMovPreset[0];
   
   movPresetEdgePt1[3*3+0] = xMovPreset[0];// CPP
   movPresetEdgePt1[3*3+1] = yMovPreset[0];
   movPresetEdgePt1[3*3+2] = zMovPreset[0];
   movPresetEdgePt2[3*3+0] = xMovPreset[1];
   movPresetEdgePt2[3*3+1] = yMovPreset[1];
   movPresetEdgePt2[3*3+2] = zMovPreset[1];
   
   // bottom
   movPresetEdgePt1[4*3+0] = xMovPreset[5];// PCN
   movPresetEdgePt1[4*3+1] = yMovPreset[5];
   movPresetEdgePt1[4*3+2] = zMovPreset[5];
   movPresetEdgePt2[4*3+0] = xMovPreset[7];
   movPresetEdgePt2[4*3+1] = yMovPreset[7];
   movPresetEdgePt2[4*3+2] = zMovPreset[7];
   
   movPresetEdgePt1[5*3+0] = xMovPreset[7];// CNN
   movPresetEdgePt1[5*3+1] = yMovPreset[7];
   movPresetEdgePt1[5*3+2] = zMovPreset[7];
   movPresetEdgePt2[5*3+0] = xMovPreset[6];
   movPresetEdgePt2[5*3+1] = yMovPreset[6];
   movPresetEdgePt2[5*3+2] = zMovPreset[6];
   
   movPresetEdgePt1[6*3+0] = xMovPreset[6];// NCN
   movPresetEdgePt1[6*3+1] = yMovPreset[6];
   movPresetEdgePt1[6*3+2] = zMovPreset[6];
   movPresetEdgePt2[6*3+0] = xMovPreset[4];
   movPresetEdgePt2[6*3+1] = yMovPreset[4];
   movPresetEdgePt2[6*3+2] = zMovPreset[4];
   
   movPresetEdgePt1[7*3+0] = xMovPreset[4];// CPN
   movPresetEdgePt1[7*3+1] = yMovPreset[4];
   movPresetEdgePt1[7*3+2] = zMovPreset[4];
   movPresetEdgePt2[7*3+0] = xMovPreset[5];
   movPresetEdgePt2[7*3+1] = yMovPreset[5];
   movPresetEdgePt2[7*3+2] = zMovPreset[5];
   
   // sides
   movPresetEdgePt1[8*3+0] = xMovPreset[1];// PPC
   movPresetEdgePt1[8*3+1] = yMovPreset[1];
   movPresetEdgePt1[8*3+2] = zMovPreset[1];
   movPresetEdgePt2[8*3+0] = xMovPreset[5];
   movPresetEdgePt2[8*3+1] = yMovPreset[5];
   movPresetEdgePt2[8*3+2] = zMovPreset[5];
   
   movPresetEdgePt1[9*3+0] = xMovPreset[3];// PNC
   movPresetEdgePt1[9*3+1] = yMovPreset[3];
   movPresetEdgePt1[9*3+2] = zMovPreset[3];
   movPresetEdgePt2[9*3+0] = xMovPreset[7];
   movPresetEdgePt2[9*3+1] = yMovPreset[7];
   movPresetEdgePt2[9*3+2] = zMovPreset[7];
   
   movPresetEdgePt1[10*3+0] = xMovPreset[2];// NNC
   movPresetEdgePt1[10*3+1] = yMovPreset[2];
   movPresetEdgePt1[10*3+2] = zMovPreset[2];
   movPresetEdgePt2[10*3+0] = xMovPreset[6];
   movPresetEdgePt2[10*3+1] = yMovPreset[6];
   movPresetEdgePt2[10*3+2] = zMovPreset[6];
   
   movPresetEdgePt1[11*3+0] = xMovPreset[0];// NPC
   movPresetEdgePt1[11*3+1] = yMovPreset[0];
   movPresetEdgePt1[11*3+2] = zMovPreset[0];
   movPresetEdgePt2[11*3+0] = xMovPreset[4];
   movPresetEdgePt2[11*3+1] = yMovPreset[4];
   movPresetEdgePt2[11*3+2] = zMovPreset[4];
   
   
   
   // find if the boxes had contacted each other
   for (i=0; i < 12*3; i+=3)
   {
      *contact = parallQuadToNormBoxContact(&fixed_TRANS[0],
                                            &movPastEdgePt1[i], &movPastEdgePt2[i],
                                            &movPresetEdgePt2[i], &movPresetEdgePt1[i]);
      
      if (*contact)
      break;
   }
   
   
   
   // if contact find the position where the moving box collided
   if (*contact)
   {
      moving_TRANS[LOCX] += xTravel;
      moving_TRANS[LOCY] += yTravel;
      moving_TRANS[LOCZ] += zTravel;
      
      localBoxDetectAndMove(fixed_TRANS, moving_TRANS, boxMargin,
                            xArrow, yArrow, zArrow, TRUE,
                            &xP, &yP, &zP, &*faceImpact, &nullVar);
      
      moving_TRANS[LOCX] -= xTravel;
      moving_TRANS[LOCY] -= yTravel;
      moving_TRANS[LOCZ] -= zTravel;
      
      // return the actual travel distance
      *xActual = xTravel + xP;
      *yActual = yTravel + yP;
      *zActual = zTravel + zP;
      
      return;
   }
   
   
   
   // create the edge data for the past and preset "fixed box"
   
   // top
   fixMirrorEdgePt1[0*3+0] = xFixMirror[1];// PCP
   fixMirrorEdgePt1[0*3+1] = yFixMirror[1];
   fixMirrorEdgePt1[0*3+2] = zFixMirror[1];
   fixMirrorEdgePt2[0*3+0] = xFixMirror[3];
   fixMirrorEdgePt2[0*3+1] = yFixMirror[3];
   fixMirrorEdgePt2[0*3+2] = zFixMirror[3];
   
   fixMirrorEdgePt1[1*3+0] = xFixMirror[3];// CNP
   fixMirrorEdgePt1[1*3+1] = yFixMirror[3];
   fixMirrorEdgePt1[1*3+2] = zFixMirror[3];
   fixMirrorEdgePt2[1*3+0] = xFixMirror[2];
   fixMirrorEdgePt2[1*3+1] = yFixMirror[2];
   fixMirrorEdgePt2[1*3+2] = zFixMirror[2];
   
   fixMirrorEdgePt1[2*3+0] = xFixMirror[2];// NCP
   fixMirrorEdgePt1[2*3+1] = yFixMirror[2];
   fixMirrorEdgePt1[2*3+2] = zFixMirror[2];
   fixMirrorEdgePt2[2*3+0] = xFixMirror[0];
   fixMirrorEdgePt2[2*3+1] = yFixMirror[0];
   fixMirrorEdgePt2[2*3+2] = zFixMirror[0];
   
   fixMirrorEdgePt1[3*3+0] = xFixMirror[0];// CPP
   fixMirrorEdgePt1[3*3+1] = yFixMirror[0];
   fixMirrorEdgePt1[3*3+2] = zFixMirror[0];
   fixMirrorEdgePt2[3*3+0] = xFixMirror[1];
   fixMirrorEdgePt2[3*3+1] = yFixMirror[1];
   fixMirrorEdgePt2[3*3+2] = zFixMirror[1];
   
   // bottom
   fixMirrorEdgePt1[4*3+0] = xFixMirror[5];// PCN
   fixMirrorEdgePt1[4*3+1] = yFixMirror[5];
   fixMirrorEdgePt1[4*3+2] = zFixMirror[5];
   fixMirrorEdgePt2[4*3+0] = xFixMirror[7];
   fixMirrorEdgePt2[4*3+1] = yFixMirror[7];
   fixMirrorEdgePt2[4*3+2] = zFixMirror[7];
   
   fixMirrorEdgePt1[5*3+0] = xFixMirror[7];// CNN
   fixMirrorEdgePt1[5*3+1] = yFixMirror[7];
   fixMirrorEdgePt1[5*3+2] = zFixMirror[7];
   fixMirrorEdgePt2[5*3+0] = xFixMirror[6];
   fixMirrorEdgePt2[5*3+1] = yFixMirror[6];
   fixMirrorEdgePt2[5*3+2] = zFixMirror[6];
   
   fixMirrorEdgePt1[6*3+0] = xFixMirror[6];// NCN
   fixMirrorEdgePt1[6*3+1] = yFixMirror[6];
   fixMirrorEdgePt1[6*3+2] = zFixMirror[6];
   fixMirrorEdgePt2[6*3+0] = xFixMirror[4];
   fixMirrorEdgePt2[6*3+1] = yFixMirror[4];
   fixMirrorEdgePt2[6*3+2] = zFixMirror[4];
   
   fixMirrorEdgePt1[7*3+0] = xFixMirror[4];// CPN
   fixMirrorEdgePt1[7*3+1] = yFixMirror[4];
   fixMirrorEdgePt1[7*3+2] = zFixMirror[4];
   fixMirrorEdgePt2[7*3+0] = xFixMirror[5];
   fixMirrorEdgePt2[7*3+1] = yFixMirror[5];
   fixMirrorEdgePt2[7*3+2] = zFixMirror[5];
   
   // sides
   fixMirrorEdgePt1[8*3+0] = xFixMirror[1];// PPC
   fixMirrorEdgePt1[8*3+1] = yFixMirror[1];
   fixMirrorEdgePt1[8*3+2] = zFixMirror[1];
   fixMirrorEdgePt2[8*3+0] = xFixMirror[5];
   fixMirrorEdgePt2[8*3+1] = yFixMirror[5];
   fixMirrorEdgePt2[8*3+2] = zFixMirror[5];
   
   fixMirrorEdgePt1[9*3+0] = xFixMirror[3];// PNC
   fixMirrorEdgePt1[9*3+1] = yFixMirror[3];
   fixMirrorEdgePt1[9*3+2] = zFixMirror[3];
   fixMirrorEdgePt2[9*3+0] = xFixMirror[7];
   fixMirrorEdgePt2[9*3+1] = yFixMirror[7];
   fixMirrorEdgePt2[9*3+2] = zFixMirror[7];
   
   fixMirrorEdgePt1[10*3+0] = xFixMirror[2];// NNC
   fixMirrorEdgePt1[10*3+1] = yFixMirror[2];
   fixMirrorEdgePt1[10*3+2] = zFixMirror[2];
   fixMirrorEdgePt2[10*3+0] = xFixMirror[6];
   fixMirrorEdgePt2[10*3+1] = yFixMirror[6];
   fixMirrorEdgePt2[10*3+2] = zFixMirror[6];
   
   fixMirrorEdgePt1[11*3+0] = xFixMirror[0];// NPC
   fixMirrorEdgePt1[11*3+1] = yFixMirror[0];
   fixMirrorEdgePt1[11*3+2] = zFixMirror[0];
   fixMirrorEdgePt2[11*3+0] = xFixMirror[4];
   fixMirrorEdgePt2[11*3+1] = yFixMirror[4];
   fixMirrorEdgePt2[11*3+2] = zFixMirror[4];
   
   
   
   // top
   fixPresetEdgePt1[0*3+0] = xFixPreset[1];// PCP
   fixPresetEdgePt1[0*3+1] = yFixPreset[1];
   fixPresetEdgePt1[0*3+2] = zFixPreset[1];
   fixPresetEdgePt2[0*3+0] = xFixPreset[3];
   fixPresetEdgePt2[0*3+1] = yFixPreset[3];
   fixPresetEdgePt2[0*3+2] = zFixPreset[3];
   
   fixPresetEdgePt1[1*3+0] = xFixPreset[3];// CNP
   fixPresetEdgePt1[1*3+1] = yFixPreset[3];
   fixPresetEdgePt1[1*3+2] = zFixPreset[3];
   fixPresetEdgePt2[1*3+0] = xFixPreset[2];
   fixPresetEdgePt2[1*3+1] = yFixPreset[2];
   fixPresetEdgePt2[1*3+2] = zFixPreset[2];
   
   fixPresetEdgePt1[2*3+0] = xFixPreset[2];// NCP
   fixPresetEdgePt1[2*3+1] = yFixPreset[2];
   fixPresetEdgePt1[2*3+2] = zFixPreset[2];
   fixPresetEdgePt2[2*3+0] = xFixPreset[0];
   fixPresetEdgePt2[2*3+1] = yFixPreset[0];
   fixPresetEdgePt2[2*3+2] = zFixPreset[0];
   
   fixPresetEdgePt1[3*3+0] = xFixPreset[0];// CPP
   fixPresetEdgePt1[3*3+1] = yFixPreset[0];
   fixPresetEdgePt1[3*3+2] = zFixPreset[0];
   fixPresetEdgePt2[3*3+0] = xFixPreset[1];
   fixPresetEdgePt2[3*3+1] = yFixPreset[1];
   fixPresetEdgePt2[3*3+2] = zFixPreset[1];
   
   // bottom
   fixPresetEdgePt1[4*3+0] = xFixPreset[5];// PCN
   fixPresetEdgePt1[4*3+1] = yFixPreset[5];
   fixPresetEdgePt1[4*3+2] = zFixPreset[5];
   fixPresetEdgePt2[4*3+0] = xFixPreset[7];
   fixPresetEdgePt2[4*3+1] = yFixPreset[7];
   fixPresetEdgePt2[4*3+2] = zFixPreset[7];
   
   fixPresetEdgePt1[5*3+0] = xFixPreset[7];// CNN
   fixPresetEdgePt1[5*3+1] = yFixPreset[7];
   fixPresetEdgePt1[5*3+2] = zFixPreset[7];
   fixPresetEdgePt2[5*3+0] = xFixPreset[6];
   fixPresetEdgePt2[5*3+1] = yFixPreset[6];
   fixPresetEdgePt2[5*3+2] = zFixPreset[6];
   
   fixPresetEdgePt1[6*3+0] = xFixPreset[6];// NCN
   fixPresetEdgePt1[6*3+1] = yFixPreset[6];
   fixPresetEdgePt1[6*3+2] = zFixPreset[6];
   fixPresetEdgePt2[6*3+0] = xFixPreset[4];
   fixPresetEdgePt2[6*3+1] = yFixPreset[4];
   fixPresetEdgePt2[6*3+2] = zFixPreset[4];
   
   fixPresetEdgePt1[7*3+0] = xFixPreset[4];// CPN
   fixPresetEdgePt1[7*3+1] = yFixPreset[4];
   fixPresetEdgePt1[7*3+2] = zFixPreset[4];
   fixPresetEdgePt2[7*3+0] = xFixPreset[5];
   fixPresetEdgePt2[7*3+1] = yFixPreset[5];
   fixPresetEdgePt2[7*3+2] = zFixPreset[5];
   
   // sides
   fixPresetEdgePt1[8*3+0] = xFixPreset[1];// PPC
   fixPresetEdgePt1[8*3+1] = yFixPreset[1];
   fixPresetEdgePt1[8*3+2] = zFixPreset[1];
   fixPresetEdgePt2[8*3+0] = xFixPreset[5];
   fixPresetEdgePt2[8*3+1] = yFixPreset[5];
   fixPresetEdgePt2[8*3+2] = zFixPreset[5];
   
   fixPresetEdgePt1[9*3+0] = xFixPreset[3];// PNC
   fixPresetEdgePt1[9*3+1] = yFixPreset[3];
   fixPresetEdgePt1[9*3+2] = zFixPreset[3];
   fixPresetEdgePt2[9*3+0] = xFixPreset[7];
   fixPresetEdgePt2[9*3+1] = yFixPreset[7];
   fixPresetEdgePt2[9*3+2] = zFixPreset[7];
   
   fixPresetEdgePt1[10*3+0] = xFixPreset[2];// NNC
   fixPresetEdgePt1[10*3+1] = yFixPreset[2];
   fixPresetEdgePt1[10*3+2] = zFixPreset[2];
   fixPresetEdgePt2[10*3+0] = xFixPreset[6];
   fixPresetEdgePt2[10*3+1] = yFixPreset[6];
   fixPresetEdgePt2[10*3+2] = zFixPreset[6];
   
   fixPresetEdgePt1[11*3+0] = xFixPreset[0];// NPC
   fixPresetEdgePt1[11*3+1] = yFixPreset[0];
   fixPresetEdgePt1[11*3+2] = zFixPreset[0];
   fixPresetEdgePt2[11*3+0] = xFixPreset[4];
   fixPresetEdgePt2[11*3+1] = yFixPreset[4];
   fixPresetEdgePt2[11*3+2] = zFixPreset[4];
   
   
   
   // find if the boxes had contacted each other
   for (i=0; i < 12*3; i+=3)
   {
      *contact = parallQuadToNormBoxContact(&moving_TRANS[0],
                                            &fixMirrorEdgePt1[i], &fixMirrorEdgePt2[i],
                                            &fixPresetEdgePt2[i], &fixPresetEdgePt1[i]);
      
      if (*contact)
      break;
   }
   
   
   
   // if contact find the position where the moving box collided
   if (*contact)
   {
      moving_TRANS[LOCX] += xTravel;
      moving_TRANS[LOCY] += yTravel;
      moving_TRANS[LOCZ] += zTravel;
      
      localBoxDetectAndMove(fixed_TRANS, moving_TRANS, boxMargin,
                            xArrow, yArrow, zArrow, TRUE,
                            &xP, &yP, &zP, &*faceImpact, &nullVar);
      
      moving_TRANS[LOCX] -= xTravel;
      moving_TRANS[LOCY] -= yTravel;
      moving_TRANS[LOCZ] -= zTravel;
      
      // return the actual travel distance
      *xActual = xTravel + xP;
      *yActual = yTravel + yP;
      *zActual = zTravel + zP;
      
      return;
   }
   
   
   *faceImpact = 0;
   *xActual = xTravel;
   *yActual = yTravel;
   *zActual = zTravel;
}
