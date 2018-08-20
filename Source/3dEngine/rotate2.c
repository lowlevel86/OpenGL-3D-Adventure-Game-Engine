#include <math.h>
#include <stdio.h>
#include "3dEngine.h"

// add rotation to xyz unit circle coordinates
void addRotToXyzUcRot(float *yUc1, float *zUc1,
                      float *xUc2, float *zUc2,
                      float *xUc3, float *yUc3, float xRot, float yRot, float zRot)
{
   degRot(&*yUc1, &*zUc1, xRot);
   degRot(&*xUc2, &*zUc2, yRot);
   degRot(&*xUc3, &*yUc3, zRot);
}

// subtract rotation from unit circle coordinates
void subtractRotFromXyzUcRot(float *yUc1, float *zUc1,
                             float *xUc2, float *zUc2,
                             float *xUc3, float *yUc3, float xRot, float yRot, float zRot)
{
   degRot(&*yUc1, &*zUc1, -xRot);
   degRot(&*xUc2, &*zUc2, -yRot);
   degRot(&*xUc3, &*yUc3, -zRot);
}

// add xyz unit circle coordinates to xyz unit circle coordinates
void addXyzUcRot(float *yUc1A, float *zUc1A,
                 float *xUc2A, float *zUc2A,
                 float *xUc3A, float *yUc3A,
                 float yUc1B, float zUc1B,
                 float xUc2B, float zUc2B,
                 float xUc3B, float yUc3B)
{
   ucRot(yUc1B, zUc1B, &*yUc1A, &*zUc1A);// x-axis
   ucRot(xUc2B, zUc2B, &*xUc2A, &*zUc2A);// y-axis
   ucRot(xUc3B, yUc3B, &*xUc3A, &*yUc3A);// z-axis
}

// subtract xyz unit circle coordinates from xyz unit circle coordinates
void subtractXyzUcRot(float *yUc1A, float *zUc1A,
                      float *xUc2A, float *zUc2A,
                      float *xUc3A, float *yUc3A,
                      float yUc1B, float zUc1B,
                      float xUc2B, float zUc2B,
                      float xUc3B, float yUc3B)
{
   ucRot(xUc3B, -yUc3B, &*xUc3A, &*yUc3A);// z-axis
   ucRot(xUc2B, -zUc2B, &*xUc2A, &*zUc2A);// y-axis
   ucRot(yUc1B, -zUc1B, &*yUc1A, &*zUc1A);// x-axis
}

// apply a rotation to another and recalculate the new xyz unit circle coordinates
void applyXyzUcRot(float *yUc1A, float *zUc1A,
                   float *xUc2A, float *zUc2A,
                   float *xUc3A, float *yUc3A,
                   float yUc1B, float zUc1B,
                   float xUc2B, float zUc2B,
                   float xUc3B, float yUc3B)
{
   float xHori = 1.0, yHori = 0.0, zHori = 0.0;
   float xVert = 0.0, yVert = 1.0, zVert = 0.0;
   float xyHori, xzHori, yzVert;

   // rotate a dual-axis object using the first xyz unit circle coordinates
   applyXyzUcRotToPoint(*yUc1A, *zUc1A,
                        *xUc2A, *zUc2A,
                        *xUc3A, *yUc3A, &xHori, &yHori, &zHori);

   applyXyzUcRotToPoint(*yUc1A, *zUc1A,
                        *xUc2A, *zUc2A,
                        *xUc3A, *yUc3A, &xVert, &yVert, &zVert);


   // rotate the dual-axis object again using the second xyz unit circle coordinates
   applyXyzUcRotToPoint(yUc1B, zUc1B,
                        xUc2B, zUc2B,
                        xUc3B, yUc3B, &xHori, &yHori, &zHori);

   applyXyzUcRotToPoint(yUc1B, zUc1B,
                        xUc2B, zUc2B,
                        xUc3B, yUc3B, &xVert, &yVert, &zVert);


   // normalize the dual-axis object to get the new xyz unit circle coordinates
   xyHori = sqrt(xHori * xHori + yHori * yHori);
   
   if (xyHori == 0.0)// no rotation if the line is parallel with the z-axis
   {
      *xUc3A = 1.0;
      *yUc3A = 0.0;
   }
   else
   {
      *xUc3A = xHori / xyHori;
      *yUc3A = yHori / xyHori;
   }
   
   ucRot(*xUc3A, -*yUc3A, &xHori, &yHori);// z-axis
   ucRot(*xUc3A, -*yUc3A, &xVert, &yVert);// z-axis
   
   
   xzHori = sqrt(xHori * xHori + zHori * zHori);
   
   if (xzHori == 0.0)// no rotation if the line is parallel with the y-axis
   {
      *xUc2A = 1.0;
      *zUc2A = 0.0;
   }
   else
   {
      *xUc2A = xHori / xzHori;
      *zUc2A = -zHori / xzHori;// negative to rotate in opposite direction
   }
   
   ucRot(*xUc2A, *zUc2A, &xHori, &zHori);// y-axis
   ucRot(*xUc2A, *zUc2A, &xVert, &zVert);// y-axis
   
   
   yzVert = sqrt(yVert * yVert + zVert * zVert);
   
   if (yzVert == 0.0)// no rotation if the line is parallel with the x-axis
   {
      *yUc1A = 1.0;
      *zUc1A = 0.0;
   }
   else
   {
      *yUc1A = yVert / yzVert;
      *zUc1A = zVert / yzVert;
   }
   
   //ucRot(*yUc1A, -*zUc1A, &yHori, &zHori);// x-axis
   //ucRot(*yUc1A, -*zUc1A, &yVert, &zVert);// x-axis
}

// reverse apply a rotation to another and recalculate the new xyz unit circle coordinates
void reverseApplyXyzUcRot(float *yUc1A, float *zUc1A,
                          float *xUc2A, float *zUc2A,
                          float *xUc3A, float *yUc3A,
                          float yUc1B, float zUc1B,
                          float xUc2B, float zUc2B,
                          float xUc3B, float yUc3B)
{
   float xHori = 1.0, yHori = 0.0, zHori = 0.0;
   float xVert = 0.0, yVert = 1.0, zVert = 0.0;
   float xyHori, xzHori, yzVert;

   // rotate a dual-axis object using the first xyz unit circle coordinates
   applyXyzUcRotToPoint(*yUc1A, *zUc1A,
                        *xUc2A, *zUc2A,
                        *xUc3A, *yUc3A, &xHori, &yHori, &zHori);

   applyXyzUcRotToPoint(*yUc1A, *zUc1A,
                        *xUc2A, *zUc2A,
                        *xUc3A, *yUc3A, &xVert, &yVert, &zVert);

   
   // rotate the dual-axis object in reverse using the second xyz unit circle coordinates
   reverseApplyXyzUcRotToPoint(yUc1B, zUc1B,
                               xUc2B, zUc2B,
                               xUc3B, yUc3B, &xHori, &yHori, &zHori);

   reverseApplyXyzUcRotToPoint(yUc1B, zUc1B,
                               xUc2B, zUc2B,
                               xUc3B, yUc3B, &xVert, &yVert, &zVert);


   // normalize the dual-axis object to get the new xyz unit circle coordinates
   xyHori = sqrt(xHori * xHori + yHori * yHori);
   
   if (xyHori == 0.0)// no rotation if the line is parallel with the z-axis
   {
      *xUc3A = 1.0;
      *yUc3A = 0.0;
   }
   else
   {
      *xUc3A = xHori / xyHori;
      *yUc3A = yHori / xyHori;
   }
   
   ucRot(*xUc3A, -*yUc3A, &xHori, &yHori);// z-axis
   ucRot(*xUc3A, -*yUc3A, &xVert, &yVert);// z-axis
   
   
   xzHori = sqrt(xHori * xHori + zHori * zHori);
   
   if (xzHori == 0.0)// no rotation if the line is parallel with the y-axis
   {
      *xUc2A = 1.0;
      *zUc2A = 0.0;
   }
   else
   {
      *xUc2A = xHori / xzHori;
      *zUc2A = -zHori / xzHori;// negative to rotate in opposite direction
   }
   
   ucRot(*xUc2A, *zUc2A, &xHori, &zHori);// y-axis
   ucRot(*xUc2A, *zUc2A, &xVert, &zVert);// y-axis
   
   
   yzVert = sqrt(yVert * yVert + zVert * zVert);
   
   if (yzVert == 0.0)// no rotation if the line is parallel with the x-axis
   {
      *yUc1A = 1.0;
      *zUc1A = 0.0;
   }
   else
   {
      *yUc1A = yVert / yzVert;
      *zUc1A = zVert / yzVert;
   }
}

// apply a x, y and z rotation to a point.
void applyXyzUcRotToPoint(float yUc1, float zUc1,
                          float xUc2, float zUc2,
                          float xUc3, float yUc3, float *xP, float *yP, float *zP)
{
   ucRot(yUc1, zUc1, &*yP, &*zP);// x-axis
   ucRot(xUc2, -zUc2, &*xP, &*zP);// y-axis  negative to rotate in opposite direction
   ucRot(xUc3, yUc3, &*xP, &*yP);// z-axis
}

// reverse apply a x, y and z rotation to a point.
void reverseApplyXyzUcRotToPoint(float yUc1, float zUc1,
                                 float xUc2, float zUc2,
                                 float xUc3, float yUc3, float *xP, float *yP, float *zP)
{
   ucRot(xUc3, -yUc3, &*xP, &*yP);// z-axis
   ucRot(xUc2, zUc2, &*xP, &*zP);// y-axis  rotate in opposite direction
   ucRot(yUc1, -zUc1, &*yP, &*zP);// x-axis
}

// convert degree rotations to unit circle coordinates
void convertRotToXyzUcRot(float *yUc1, float *zUc1,
                          float *xUc2, float *zUc2,
                          float *xUc3, float *yUc3, float xRot, float yRot, float zRot)
{
   *yUc1 = 1.0; *zUc1 = 0.0;
   *xUc2 = 1.0; *zUc2 = 0.0;
   *xUc3 = 1.0; *yUc3 = 0.0;
   
   degRot(&*yUc1, &*zUc1, xRot);
   degRot(&*xUc2, &*zUc2, yRot);
   degRot(&*xUc3, &*yUc3, zRot);
}

// convert unit circle coordinates to degree rotations 
void convertXyzUcRotToRot(float yUc1, float zUc1,
                          float xUc2, float zUc2,
                          float xUc3, float yUc3, float *xRot, float *yRot, float *zRot)
{
   if (zUc1 < 0)
   *xRot = -acos(yUc1) / (M_PI * 2.0 / 360.0);
   else
   *xRot = acos(yUc1) / (M_PI * 2.0 / 360.0);
   
   if (zUc2 < 0)
   *yRot = -acos(xUc2) / (M_PI * 2.0 / 360.0);
   else
   *yRot = acos(xUc2) / (M_PI * 2.0 / 360.0);
   
   if (yUc3 < 0)
   *zRot = -acos(xUc3) / (M_PI * 2.0 / 360.0);
   else
   *zRot = acos(xUc3) / (M_PI * 2.0 / 360.0);
}

// get the unit circle coordinates to rotate a point to the x-axis
void getUCRotPointToAxisX(float xP, float yP, float zP,
                          float *yUc1, float *zUc1,
                          float *xUc2, float *zUc2,
                          float *xUc3, float *yUc3)
{
   float yzLgth, xyLgth;
   
   // find the x-axis unit circle coordinate
   yzLgth = sqrt(yP * yP + zP * zP);
   
   if (yzLgth == 0.0)// no rotation
   {
      *yUc1 = 1.0;
      *zUc1 = 0.0;
   }
   else
   {
      *yUc1 = yP / yzLgth;
      *zUc1 = -zP / yzLgth;
   }
   
   //rotate to the z-axis
   ucRot(*yUc1, *zUc1, &yP, &zP);// x-axis rotation
   
   // find the z-axis unit circle coordinate
   xyLgth = sqrt(xP * xP + yP * yP);
   
   if (xyLgth == 0.0)// no rotation
   {
      *xUc3 = 1.0;
      *yUc3 = 0.0;
   }
   else
   {
      *xUc3 = xP / xyLgth;
      *yUc3 = -yP / xyLgth;
   }
   
   // y-axis unit circle coordinate
   *xUc2 = 1.0;
   *zUc2 = 0.0;
}

// get the unit circle coordinates to rotate a point to the y-axis
void getUCRotPointToAxisY(float xP, float yP, float zP,
                          float *yUc1, float *zUc1,
                          float *xUc2, float *zUc2,
                          float *xUc3, float *yUc3)
{
   float yzLgth, xyLgth;
   
   // find the x-axis unit circle coordinate
   yzLgth = sqrt(yP * yP + zP * zP);
   
   if (yzLgth == 0.0)// no rotation
   {
      *yUc1 = 1.0;
      *zUc1 = 0.0;
   }
   else
   {
      *yUc1 = yP / yzLgth;
      *zUc1 = -zP / yzLgth;
   }
   
   //rotate to the z-axis
   ucRot(*yUc1, *zUc1, &yP, &zP);// x-axis rotation
   
   // find the z-axis unit circle coordinate
   xyLgth = sqrt(xP * xP + yP * yP);
   
   if (xyLgth == 0.0)// no rotation
   {
      *xUc3 = 1.0;
      *yUc3 = 0.0;
   }
   else
   {
      *xUc3 = yP / xyLgth;
      *yUc3 = xP / xyLgth;
   }
   
   // y-axis unit circle coordinate
   *xUc2 = 1.0;
   *zUc2 = 0.0;
}

// get the unit circle coordinates to rotate a point to the z-axis
void getUCRotPointToAxisZ(float xP, float yP, float zP,
                          float *yUc1, float *zUc1,
                          float *xUc2, float *zUc2,
                          float *xUc3, float *yUc3)
{
   float xzLgth, yzLgth;
   
   // find the x-axis unit circle coordinate
   yzLgth = sqrt(yP * yP + zP * zP);
   
   if (yzLgth == 0.0)// no rotation
   {
      *yUc1 = 1.0;
      *zUc1 = 0.0;
   }
   else
   {
      *yUc1 = zP / yzLgth;
      *zUc1 = yP / yzLgth;
   }
   
   ucRot(*yUc1, *zUc1, &yP, &zP);// x-axis rotation
   
   // find the y-axis unit circle coordinate
   xzLgth = sqrt(xP * xP + zP * zP);
   
   if (xzLgth == 0.0)// no rotation
   {
      *xUc2 = 1.0;
      *zUc2 = 0.0;
   }
   else
   {
      *xUc2 = zP / xzLgth;
      *zUc2 = -xP / xzLgth;
   }
   
   *xUc3 = 1.0;
   *yUc3 = 0.0;
}
