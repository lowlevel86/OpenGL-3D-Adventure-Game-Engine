#include <math.h>
#include <stdio.h>
#include "3dEngine.h"

// xRot - amount of rotation around the x-axis
// yRot - amount of rotation around the y-axis
// zRot - amount of rotation around the z-axis

void relativeRot(float *xP, float *yP, float *zP,
                 float xCenter, float yCenter, float zCenter, float xRot, float yRot, float zRot)
{
   float xPmem, yPmem, zPmem;
   
   xPmem = *xP - xCenter;
   yPmem = *yP - yCenter;
   zPmem = *zP - zCenter;
   
   rotate(&xPmem, &yPmem, &zPmem, xRot, yRot, zRot);
   
   *xP = xPmem + xCenter;
   *yP = yPmem + yCenter;
   *zP = zPmem + zCenter;
}

void rotate(float *xP, float *yP, float *zP, float xRot, float yRot, float zRot)
{
   float rotLgth;
   float xUc, yUc, zUc;
   float rotLgth1, rotLgth2;
   float xUc1, zUc1, xUc2, yUc2;
   
   if ((xRot) && (!yRot) && (!zRot))
   {
      degRot(&*yP, &*zP, xRot);
      return;
   }
   
   if ((!xRot) && (yRot) && (!zRot))
   {
      degRot(&*xP, &*zP, yRot);
      return;
   }
   
   if ((!xRot) && (!yRot) && (zRot))
   {
      degRot(&*xP, &*yP, zRot);
      return;
   }
   
   if ((xRot) && (yRot) && (!zRot))
   {
      // get the rotation length that xRot and yRot produce
      rotLgth = sqrt(xRot * xRot + yRot * yRot);
      
      // find the amount of rotation to move rotLgth to the x-axis
      xUc = yRot / rotLgth;
      yUc = xRot / rotLgth;
      
      // rotate xRotyRot to the x-axis
      ucRot(xUc, -yUc, &*xP, &*yP);// z-axis
      
      // rotate the amount of rotLgth
      degRot(&*xP, &*zP, rotLgth);// y-axis
      
      // rotate back from the x-axis
      ucRot(xUc, yUc, &*xP, &*yP);// z-axis
      
      return;
   }
   
   if ((xRot) && (!yRot) && (zRot))
   {
      rotLgth = sqrt(xRot * xRot + zRot * zRot);
      
      xUc = zRot / rotLgth;
      zUc = xRot / rotLgth;
      
      ucRot(xUc, zUc, &*xP, &*zP);// y-axis
      degRot(&*xP, &*yP, rotLgth);// x-axis
      ucRot(xUc, -zUc, &*xP, &*zP);// y-axis
      
      return;
   }
   
   if ((!xRot) && (yRot) && (zRot))
   {
      rotLgth = sqrt(yRot * yRot + zRot * zRot);
      
      yUc = zRot / rotLgth;
      zUc = yRot / rotLgth;
      
      ucRot(yUc, -zUc, &*yP, &*zP);// x-axis
      degRot(&*xP, &*yP, rotLgth);// y-axis
      ucRot(yUc, zUc, &*yP, &*zP);// x-axis
      
      return;
   }
   
   if ((xRot) && (yRot) && (zRot))
   {
      rotLgth1 = sqrt(xRot * xRot + yRot * yRot);
      rotLgth2 = sqrt(rotLgth1 * rotLgth1 + zRot * zRot);
      
      xUc1 = zRot / rotLgth2;
      zUc1 = rotLgth1 / rotLgth2;
      
      xUc2 = yRot / rotLgth1;
      yUc2 = xRot / rotLgth1;
      
      ucRot(xUc2, -yUc2, &*xP, &*yP);// z-axis
      ucRot(xUc1, -zUc1, &*xP, &*zP);// y-axis
      
      degRot(&*xP, &*zP, rotLgth2);// y-axis
      
      ucRot(xUc1, zUc1, &*xP, &*zP);// y-axis
      ucRot(xUc2, yUc2, &*xP, &*yP);// z-axis
      
      return;
   }
}

// rotate using degrees
void degRot(float *horiP, float *vertP, float degrees)
{
   float h, v;
   float hUc;
   float vUc;
   float hLine1, vLine1;
   float hLine2, vLine2;
   
   if (degrees != degrees) // check if NaN
   return;
   
   hUc = cos(degrees * (M_PI * 2.0 / 360.0));
   vUc = sin(degrees * (M_PI * 2.0 / 360.0));
   
   hLine1 = hUc;
   vLine1 = vUc;
   hLine2 = -vUc;
   vLine2 = hUc;

   h = *vertP * hLine2 + *horiP * vLine2;
   v = *horiP * vLine1 + *vertP * hLine1;
   *horiP = h;
   *vertP = v;
}

// rotate using coordinates around a unit circle's circumference
void ucRot(float hUc, float vUc, float *hP, float *vP)
{
   float h, v;
   float hLine1, vLine1;
   float hLine2, vLine2;
   
   if (hUc != hUc) // check if NaN
   return;
   
   if (vUc != vUc) // check if NaN
   return;
   
   hLine1 = hUc;
   vLine1 = vUc;
   hLine2 = -vUc;
   vLine2 = hUc;
   
   h = *vP * hLine2 + *hP * vLine2;
   v = *hP * vLine1 + *vP * hLine1;
   
   *hP = h;
   *vP = v;
}
