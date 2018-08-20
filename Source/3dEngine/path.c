#include <stdio.h>
#include <math.h>
#include "3dEngine.h"

#define TRUE 1
#define FALSE 0


void resizeLineToPlaneX(float xL1, float yL1, float zL1,
                        float *xL2, float *yL2, float *zL2,
                        float planeLoc, int *notALine, int *parallelToPlane)
{
   *notALine = FALSE;
   *parallelToPlane = FALSE;
   
   if ((xL1 == *xL2) && (yL1 == *yL2) && (zL1 == *zL2))
   {
      *notALine = TRUE;
      return;
   }
   
   if (xL1 == *xL2)
   {
      *parallelToPlane = TRUE;
      return;
   }
   
   if (yL1 != *yL2)
   *yL2 = yL1 - (xL1 - planeLoc) / (xL1 - *xL2) * (yL1 - *yL2);
   
   if (zL1 != *zL2)
   *zL2 = zL1 - (xL1 - planeLoc) / (xL1 - *xL2) * (zL1 - *zL2);
   
   *xL2 = planeLoc;
}

void resizeLineToPlaneY(float xL1, float yL1, float zL1,
                        float *xL2, float *yL2, float *zL2,
                        float planeLoc, int *notALine, int *parallelToPlane)
{
   *notALine = FALSE;
   *parallelToPlane = FALSE;
   
   if ((xL1 == *xL2) && (yL1 == *yL2) && (zL1 == *zL2))
   {
      *notALine = TRUE;
      return;
   }
   
   if (yL1 == *yL2)
   {
      *parallelToPlane = TRUE;
      return;
   }
   
   if (xL1 != *xL2)
   *xL2 = xL1 - (yL1 - planeLoc) / (yL1 - *yL2) * (xL1 - *xL2);
   
   if (zL1 != *zL2)
   *zL2 = zL1 - (yL1 - planeLoc) / (yL1 - *yL2) * (zL1 - *zL2);
   
   *yL2 = planeLoc;
}

void resizeLineToPlaneZ(float xL1, float yL1, float zL1,
                        float *xL2, float *yL2, float *zL2,
                        float planeLoc, int *notALine, int *parallelToPlane)
{
   *notALine = FALSE;
   *parallelToPlane = FALSE;
   
   if ((xL1 == *xL2) && (yL1 == *yL2) && (zL1 == *zL2))
   {
      *notALine = TRUE;
      return;
   }
   
   if (zL1 == *zL2)
   {
      *parallelToPlane = TRUE;
      return;
   }
   
   if (xL1 != *xL2)
   *xL2 = xL1 - (zL1 - planeLoc) / (zL1 - *zL2) * (xL1 - *xL2);
   
   if (yL1 != *yL2)
   *yL2 = yL1 - (zL1 - planeLoc) / (zL1 - *zL2) * (yL1 - *yL2);
   
   *zL2 = planeLoc;
}


// find the amount of travel to move a point to the closest plane a destination point is on by following a relative x axis
void travelParallelToAxisX(float yUc1, float zUc1,
                           float xUc2, float zUc2,
                           float xUc3, float yUc3,
                           float xDest, float yDest, float zDest,
                           float *xTravel, float *yTravel, float *zTravel)
{
   int notALine, parallelToPlane;
   
   // initialize values representing the line of travel
   *xTravel = 1.0; *yTravel = 0.0; *zTravel = 0.0;

   // rotate the destination point
   // in the same way it takes to normalize the axis to follow
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xDest, &yDest, &zDest);
   
   
   // find which plane is most perpendicular to the x axis line
   
   if ((fabs(*xTravel) >= fabs(*yTravel)) && (fabs(*xTravel) >= fabs(*zTravel)))
   {
      // move the travel line as close as possible to the destination
      resizeLineToPlaneX(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         xDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
   
   if ((fabs(*yTravel) >= fabs(*xTravel)) && (fabs(*yTravel) >= fabs(*zTravel)))
   {
      // extend the travel line as close as possible to the destination
      resizeLineToPlaneY(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         yDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
   
   if ((fabs(*zTravel) >= fabs(*xTravel)) && (fabs(*zTravel) >= fabs(*yTravel)))
   {
      // extend the travel line as close as possible to the destination
      resizeLineToPlaneZ(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         zDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
}


// find the amount of travel to move a point to the closest plane a destination point is on by following a relative y axis
void travelParallelToAxisY(float yUc1, float zUc1,
                           float xUc2, float zUc2,
                           float xUc3, float yUc3,
                           float xDest, float yDest, float zDest,
                           float *xTravel, float *yTravel, float *zTravel)
{
   int notALine, parallelToPlane;
   
   // initialize values representing the line of travel
   *xTravel = 0.0; *yTravel = 1.0; *zTravel = 0.0;

   // rotate the destination point
   // in the same way it takes to normalize the axis to follow
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xDest, &yDest, &zDest);
   
   
   // find which plane is most perpendicular to the y axis line
   
   if ((fabs(*yTravel) >= fabs(*xTravel)) && (fabs(*yTravel) >= fabs(*zTravel)))
   {
      // extend the travel line as close as possible to the destination
      resizeLineToPlaneY(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         yDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
   
   if ((fabs(*zTravel) >= fabs(*xTravel)) && (fabs(*zTravel) >= fabs(*yTravel)))
   {
      // extend the travel line as close as possible to the destination
      resizeLineToPlaneZ(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         zDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
   
   if ((fabs(*xTravel) >= fabs(*yTravel)) && (fabs(*xTravel) >= fabs(*zTravel)))
   {
      // move the travel line as close as possible to the destination
      resizeLineToPlaneX(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         xDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
}


// find the amount of travel to move a point to the closest plane a destination point is on by following a relative z axis
void travelParallelToAxisZ(float yUc1, float zUc1,
                           float xUc2, float zUc2,
                           float xUc3, float yUc3,
                           float xDest, float yDest, float zDest,
                           float *xTravel, float *yTravel, float *zTravel)
{
   int notALine, parallelToPlane;
   
   // initialize values representing the line of travel
   *xTravel = 0.0; *yTravel = 0.0; *zTravel = 1.0;

   // rotate the destination point
   // in the same way it takes to normalize the axis to follow
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xDest, &yDest, &zDest);
   
   
   // find which plane is most perpendicular to the z axis line
   
   if ((fabs(*zTravel) >= fabs(*xTravel)) && (fabs(*zTravel) >= fabs(*yTravel)))
   {
      // extend the travel line as close as possible to the destination
      resizeLineToPlaneZ(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         zDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
   
   if ((fabs(*xTravel) >= fabs(*yTravel)) && (fabs(*xTravel) >= fabs(*zTravel)))
   {
      // move the travel line as close as possible to the destination
      resizeLineToPlaneX(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         xDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
   
   if ((fabs(*yTravel) >= fabs(*xTravel)) && (fabs(*yTravel) >= fabs(*zTravel)))
   {
      // extend the travel line as close as possible to the destination
      resizeLineToPlaneY(0, 0, 0,
                         &*xTravel, &*yTravel, &*zTravel,
                         yDest, &notALine, &parallelToPlane);
      
      // rotate the travel line to the orientation represented by the unit circle data
      applyXyzUcRotToPoint(yUc1, zUc1,
                           xUc2, zUc2,
                           xUc3, yUc3, &*xTravel, &*yTravel, &*zTravel);
      
      return;
   }
}


void xPlaneSkidPath(float xL1, float yL1, float zL1,
                    float xL2, float yL2, float zL2,
                    float *xLoc, float *yLoc, float *zLoc,
                    float *xArrow, float *yArrow, float *zArrow)
{
   int notALine;
   int parallelToPlane;
   float planeProjectedLgth;
   
   // find the skid direction
   planeProjectedLgth = sqrt((yL2 - yL1) * (yL2 - yL1) + (zL2 - zL1) * (zL2 - zL1));
   
   if (planeProjectedLgth)
   {
      *xArrow = 0;
      *yArrow = (yL2 - yL1) / planeProjectedLgth;
      *zArrow = (zL2 - zL1) / planeProjectedLgth;
   }
   else
   {
      *xArrow = 0;
      *yArrow = 0;
      *zArrow = 0;
   }
   
   // find the starting skid location
   resizeLineToPlaneX(xL1, yL1, zL1, &xL2, &yL2, &zL2, 0, &notALine, &parallelToPlane);
   
   *xLoc = xL2;
   *yLoc = yL2;
   *zLoc = zL2;
}

void yPlaneSkidPath(float xL1, float yL1, float zL1,
                    float xL2, float yL2, float zL2,
                    float *xLoc, float *yLoc, float *zLoc,
                    float *xArrow, float *yArrow, float *zArrow)
{
   int notALine;
   int parallelToPlane;
   float planeProjectedLgth;
   
   // find the skid direction
   planeProjectedLgth = sqrt((xL2 - xL1) * (xL2 - xL1) + (zL2 - zL1) * (zL2 - zL1));
   
   if (planeProjectedLgth)
   {
      *xArrow = (xL2 - xL1) / planeProjectedLgth;
      *yArrow = 0;
      *zArrow = (zL2 - zL1) / planeProjectedLgth;
   }
   else
   {
      *xArrow = 0;
      *yArrow = 0;
      *zArrow = 0;
   }
   
   // find the starting skid location
   resizeLineToPlaneY(xL1, yL1, zL1, &xL2, &yL2, &zL2, 0, &notALine, &parallelToPlane);
   
   *xLoc = xL2;
   *yLoc = yL2;
   *zLoc = zL2;
}

void zPlaneSkidPath(float xL1, float yL1, float zL1,
                    float xL2, float yL2, float zL2,
                    float *xLoc, float *yLoc, float *zLoc,
                    float *xArrow, float *yArrow, float *zArrow)
{
   int notALine;
   int parallelToPlane;
   float planeProjectedLgth;
   
   // find the skid direction
   planeProjectedLgth = sqrt((xL2 - xL1) * (xL2 - xL1) + (yL2 - yL1) * (yL2 - yL1));
   
   if (planeProjectedLgth)
   {
      *xArrow = (xL2 - xL1) / planeProjectedLgth;
      *yArrow = (yL2 - yL1) / planeProjectedLgth;
      *zArrow = 0;
   }
   else
   {
      *xArrow = 0;
      *yArrow = 0;
      *zArrow = 0;
   }
   
   // find the starting skid location
   resizeLineToPlaneZ(xL1, yL1, zL1, &xL2, &yL2, &zL2, 0, &notALine, &parallelToPlane);

   *xLoc = xL2;
   *yLoc = yL2;
   *zLoc = zL2;
}


int getDirectionChgAngle(float xL1, float yL1, float zL1,
                         float xL2, float yL2, float zL2, float *angle)
{
   float a, b, c;
   float xL3, yL3, zL3;
   
   // no angle
   if (((!xL1) && (!yL1) && (!zL1)) ||
       ((!xL2) && (!yL2) && (!zL2)))
   return TRUE;
   if (((!xL1) && (!yL1)) && ((!xL2) && (!yL2)))
   return TRUE;
   if (((!yL1) && (!zL1)) && ((!yL2) && (!zL2)))
   return TRUE;
   if (((!xL1) && (!zL1)) && ((!xL2) && (!zL2)))
   return TRUE;
   
   xL3 = xL1 + xL2;
   yL3 = yL1 + yL2;
   zL3 = zL1 + zL2;
   
   a = sqrt(pow(sqrt(pow(xL1,2)+pow(yL1,2)),2) + pow(zL1,2));
   b = sqrt(pow(sqrt(pow(xL2,2)+pow(yL2,2)),2) + pow(zL2,2));
   c = sqrt(pow(sqrt(pow(xL3,2)+pow(yL3,2)),2) + pow(zL3,2));
   
   *angle = acos((pow(c,2) - (pow(a,2) + pow(b,2))) / (-2*a*b)) / (M_PI*2 / 360.0);
   
   return FALSE;
}


float getTravelLength(float xL1, float yL1, float zL1)
{
   return sqrt(pow(sqrt(pow(xL1,2) +
                        pow(yL1,2)),2) + pow(zL1,2));
}
