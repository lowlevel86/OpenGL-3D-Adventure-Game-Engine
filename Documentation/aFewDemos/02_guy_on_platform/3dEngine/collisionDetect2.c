#include <stdio.h>
#include <math.h>
#include "3dEngine.h"

#define TRUE 1
#define FALSE 0


// the mesh must be inside the transformation box
void ptToTriMeshCollision(float *mesh_TRANS, int mesh_MESHNUM, float *mesh_POINT,
                          short *mesh_TRI, int *mesh_TRIDATSZ, float *tri_TRANS,
                          float xPast, float yPast, float zPast,
                          float *xPreset, float *yPreset, float *zPreset,
                          float errorMargin, int *impactFaceNum, int *outside)
{
   int i;
   float xPresetBounds, yPresetBounds, zPresetBounds;
   int impactFaceBounds, outsideBounds;
   float xExtend, yExtend, zExtend;
   float largestCoord, extendAmount;
   float xPastNorm, yPastNorm, zPastNorm;
   float xExtendNorm, yExtendNorm, zExtendNorm;
   
   int pt1, pt2, pt3;
   float xPt1, yPt1, zPt1;
   float xPt2, yPt2, zPt2;
   float xPt3, yPt3, zPt3;
   int collide, front;
   float xPt, yPt, zPt;
   float xShortest, yShortest, zShortest;
   int polyNum = -1;
   int outsideOfMesh = TRUE;
   
   
   // initialize
   *impactFaceNum = polyNum;// -1 equals no polygon
   *outside = outsideOfMesh;
   
   
   // find if the point goes through or is inside the bounds of the mesh
   xPresetBounds = *xPreset;
   yPresetBounds = *yPreset;
   zPresetBounds = *zPreset;
   
   ptToBoundsCollision(&mesh_TRANS[mesh_MESHNUM*TRSZ], xPast, yPast, zPast,
                       &xPresetBounds, &yPresetBounds, &zPresetBounds, &impactFaceBounds, &outsideBounds);
   
   // if not then return
   if ((impactFaceBounds == 0) && (outsideBounds == TRUE))
   return;
   
   // initialize for later use
   // when the preset point has to be extended
   xExtend = *xPreset;
   yExtend = *yPreset;
   zExtend = *zPreset;
   
   
   // make sure the past and preset points make a line and not a point
   if (xPast == *xPreset)
   if (yPast == *yPreset)
   if (zPast == *zPreset)
   zExtend = zExtend + 1.0;
   
   
   // extend the line connecting the past and preset
   // points beyound the bounds box of the mesh to
   // insure it will go through the bounds of a polygon
   // this will help determine if the point was inside or outside the mesh
   
   // if the direction traveled is closer to the x coordinate
   if ((fabs(xExtend-xPast) >= fabs(yExtend-yPast)) &&
       (fabs(xExtend-xPast) >= fabs(zExtend-zPast)))
   largestCoord = fabs(xExtend - xPast);
   
   // if the direction traveled is closer to the y coordinate
   if ((fabs(yExtend-yPast) >= fabs(xExtend-xPast)) &&
       (fabs(yExtend-yPast) >= fabs(zExtend-zPast)))
   largestCoord = fabs(yExtend - yPast);
   
   // if the direction traveled is closer to the z coordinate
   if ((fabs(zExtend-zPast) >= fabs(xExtend-xPast)) &&
       (fabs(zExtend-zPast) >= fabs(yExtend-yPast)))
   largestCoord = fabs(zExtend - zPast);
   
   // to insure the line connecting the past and preset points
   // is extended beyound the bounds box of the mesh
   if (largestCoord >= 1.0)
   extendAmount = mesh_TRANS[mesh_MESHNUM*TRSZ+BR] * 4;
   else
   extendAmount = mesh_TRANS[mesh_MESHNUM*TRSZ+BR] * 4 / largestCoord;
   
   // extend the line
   xExtend = (xExtend - xPast) * extendAmount + xPast;
   yExtend = (yExtend - yPast) * extendAmount + yPast;
   zExtend = (zExtend - zPast) * extendAmount + zPast;
   
   
   // move, rotate and resize the line connecting the past and extended points
   // in the same way it takes to normalize the mesh using the transfomation data
   xPastNorm = xPast - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
   yPastNorm = yPast - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
   zPastNorm = zPast - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
   
   reverseApplyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                               &xPastNorm, &yPastNorm, &zPastNorm);
   
   xPastNorm = xPastNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
   yPastNorm = yPastNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
   zPastNorm = zPastNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
   
   
   xExtendNorm = xExtend - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
   yExtendNorm = yExtend - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
   zExtendNorm = zExtend - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
   
   reverseApplyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                               &xExtendNorm, &yExtendNorm, &zExtendNorm);
   
   xExtendNorm = xExtendNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
   yExtendNorm = yExtendNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
   zExtendNorm = zExtendNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
   
   
   xShortest = xExtendNorm;
   yShortest = yExtendNorm;
   zShortest = zExtendNorm;
   
   for (i=mesh_TRIDATSZ[mesh_MESHNUM]/3; i < mesh_TRIDATSZ[mesh_MESHNUM+1]/3; i++)
   {
      xPresetBounds = xExtendNorm;
      yPresetBounds = yExtendNorm;
      zPresetBounds = zExtendNorm;
      
      ptToBoundsCollision(&tri_TRANS[i*TRSZ], xPastNorm, yPastNorm, zPastNorm,
                          &xPresetBounds, &yPresetBounds, &zPresetBounds,
                          &impactFaceBounds, &outsideBounds);
      
      // if the line goes through or is inside the bounds of a polygon
      if ((impactFaceBounds != 0) || (outsideBounds == FALSE))
      {
         // get a triangle
         pt1 = mesh_TRI[i*3+1]*3;
         pt2 = mesh_TRI[i*3+2]*3;
         pt3 = mesh_TRI[i*3+0]*3;
         xPt1 = mesh_POINT[pt1+0]; yPt1 = mesh_POINT[pt1+1]; zPt1 = mesh_POINT[pt1+2];
         xPt2 = mesh_POINT[pt2+0]; yPt2 = mesh_POINT[pt2+1]; zPt2 = mesh_POINT[pt2+2];
         xPt3 = mesh_POINT[pt3+0]; yPt3 = mesh_POINT[pt3+1]; zPt3 = mesh_POINT[pt3+2];
         
         ptToTriCollision(tri_TRANS[i*TRSZ+9], tri_TRANS[i*TRSZ+10],
                          tri_TRANS[i*TRSZ+11], tri_TRANS[i*TRSZ+12],
                          tri_TRANS[i*TRSZ+13], tri_TRANS[i*TRSZ+14],
                          xPt1, yPt1, zPt1,// triangle
                          xPt2, yPt2, zPt2,
                          xPt3, yPt3, zPt3,
                          xPastNorm, yPastNorm, zPastNorm,// line
                          xExtendNorm, yExtendNorm, zExtendNorm,
                          errorMargin, &collide, &front, &xPt, &yPt, &zPt);
         
         
         // find the closest polygon to the past point
         if (collide)
         {
            // if the direction traveled is closer to the x coordinate
            if ((fabs(xExtendNorm-xPastNorm) >= fabs(yExtendNorm-yPastNorm)) &&
                (fabs(xExtendNorm-xPastNorm) >= fabs(zExtendNorm-zPastNorm)))
            if (fabs(xPt-xPastNorm) < fabs(xShortest-xPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
            
            // if the direction traveled is closer to the y coordinate
            if ((fabs(yExtendNorm-yPastNorm) >= fabs(xExtendNorm-xPastNorm)) &&
                (fabs(yExtendNorm-yPastNorm) >= fabs(zExtendNorm-zPastNorm)))
            if (fabs(yPt-yPastNorm) < fabs(yShortest-yPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
            
            // if the direction traveled is closer to the z coordinate
            if ((fabs(zExtendNorm-zPastNorm) >= fabs(xExtendNorm-xPastNorm)) &&
                (fabs(zExtendNorm-zPastNorm) >= fabs(yExtendNorm-yPastNorm)))
            if (fabs(zPt-zPastNorm) < fabs(zShortest-zPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
         }
      }
   }
   
   
   // resize, rotate and move  "xShortest, yShortest, zShortest"
   // in the same way it takes to undo normalization of the mesh using the transfomation data
   xShortest = xShortest * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
   yShortest = yShortest * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
   zShortest = zShortest * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
   
   applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                        mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                        mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                        &xShortest, &yShortest, &zShortest);
   
   xShortest = xShortest + mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
   yShortest = yShortest + mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
   zShortest = zShortest + mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
   
   // if the direction traveled is closer to the x coordinate
   if ((fabs(xExtend-xPast) >= fabs(yExtend-yPast)) &&
       (fabs(xExtend-xPast) >= fabs(zExtend-zPast)))
   if (fabs(xShortest-xPast) < fabs(*xPreset-xPast))// if shorter
   {
      *xPreset = xShortest;
      *yPreset = yShortest;
      *zPreset = zShortest;
      
      *impactFaceNum = polyNum;
   }
   
   // if the direction traveled is closer to the y coordinate
   if ((fabs(yExtend-yPast) >= fabs(xExtend-xPast)) &&
       (fabs(yExtend-yPast) >= fabs(zExtend-zPast)))
   if (fabs(yShortest-yPast) < fabs(*yPreset-yPast))// if shorter
   {
      *xPreset = xShortest;
      *yPreset = yShortest;
      *zPreset = zShortest;
      
      *impactFaceNum = polyNum;
   }
   
   // if the direction traveled is closer to the z coordinate
   if ((fabs(zExtend-zPast) >= fabs(xExtend-xPast)) &&
       (fabs(zExtend-zPast) >= fabs(yExtend-yPast)))
   if (fabs(zShortest-zPast) < fabs(*zPreset-zPast))// if shorter
   {
      *xPreset = xShortest;
      *yPreset = yShortest;
      *zPreset = zShortest;
      
      *impactFaceNum = polyNum;
   }
   
   *outside = outsideOfMesh;
}


// the mesh must be inside the transformation box
void ptToQuadMeshCollision(float *mesh_TRANS, int mesh_MESHNUM, float *mesh_POINT,
                           short *mesh_QUAD, int *mesh_QUADDATSZ, float *quadSubtri_TRANS,
                           float xPast, float yPast, float zPast,
                           float *xPreset, float *yPreset, float *zPreset,
                           float errorMargin, int *impactFaceNum, int *outside)
{
   int i;
   float xPresetBounds, yPresetBounds, zPresetBounds;
   int impactFaceBounds, outsideBounds;
   float xExtend, yExtend, zExtend;
   float largestCoord, extendAmount;
   float xPastNorm, yPastNorm, zPastNorm;
   float xExtendNorm, yExtendNorm, zExtendNorm;
   
   int pt1, pt2, pt3;
   float xPt1, yPt1, zPt1;
   float xPt2, yPt2, zPt2;
   float xPt3, yPt3, zPt3;
   int collide, front;
   float xPt, yPt, zPt;
   float xShortest, yShortest, zShortest;
   int polyNum = -1;
   int outsideOfMesh = TRUE;
   
   
   // initialize
   *impactFaceNum = polyNum;// -1 equals no polygon
   *outside = outsideOfMesh;
   
   
   // find if the point goes through or is inside the bounds of the mesh
   xPresetBounds = *xPreset;
   yPresetBounds = *yPreset;
   zPresetBounds = *zPreset;
   
   ptToBoundsCollision(&mesh_TRANS[mesh_MESHNUM*TRSZ], xPast, yPast, zPast,
                       &xPresetBounds, &yPresetBounds, &zPresetBounds, &impactFaceBounds, &outsideBounds);
   
   // if not then return
   if ((impactFaceBounds == 0) && (outsideBounds == TRUE))
   return;
   
   // initialize for later use
   // when the preset point has to be extended
   xExtend = *xPreset;
   yExtend = *yPreset;
   zExtend = *zPreset;
   
   
   // make sure the past and preset points make a line and not a point
   if (xPast == *xPreset)
   if (yPast == *yPreset)
   if (zPast == *zPreset)
   zExtend = zExtend + 1.0;
   
   
   // extend the line connecting the past and preset
   // points beyound the bounds box of the mesh to
   // insure it will go through the bounds of a polygon
   // this will help determine if the point was inside or outside the mesh
   
   // if the direction traveled is closer to the x coordinate
   if ((fabs(xExtend-xPast) >= fabs(yExtend-yPast)) &&
       (fabs(xExtend-xPast) >= fabs(zExtend-zPast)))
   largestCoord = fabs(xExtend - xPast);
   
   // if the direction traveled is closer to the y coordinate
   if ((fabs(yExtend-yPast) >= fabs(xExtend-xPast)) &&
       (fabs(yExtend-yPast) >= fabs(zExtend-zPast)))
   largestCoord = fabs(yExtend - yPast);
   
   // if the direction traveled is closer to the z coordinate
   if ((fabs(zExtend-zPast) >= fabs(xExtend-xPast)) &&
       (fabs(zExtend-zPast) >= fabs(yExtend-yPast)))
   largestCoord = fabs(zExtend - zPast);
   
   // to insure the line connecting the past and preset points
   // is extended beyound the bounds box of the mesh
   if (largestCoord >= 1.0)
   extendAmount = mesh_TRANS[mesh_MESHNUM*TRSZ+BR] * 4;
   else
   extendAmount = mesh_TRANS[mesh_MESHNUM*TRSZ+BR] * 4 / largestCoord;
   
   // extend the line
   xExtend = (xExtend - xPast) * extendAmount + xPast;
   yExtend = (yExtend - yPast) * extendAmount + yPast;
   zExtend = (zExtend - zPast) * extendAmount + zPast;
   
   
   // move, rotate and resize the line connecting the past and extended points
   // in the same way it takes to normalize the mesh using the transfomation data
   xPastNorm = xPast - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
   yPastNorm = yPast - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
   zPastNorm = zPast - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
   
   reverseApplyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                               &xPastNorm, &yPastNorm, &zPastNorm);
   
   xPastNorm = xPastNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
   yPastNorm = yPastNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
   zPastNorm = zPastNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
   
   
   xExtendNorm = xExtend - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
   yExtendNorm = yExtend - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
   zExtendNorm = zExtend - mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
   
   reverseApplyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                               mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                               &xExtendNorm, &yExtendNorm, &zExtendNorm);
   
   xExtendNorm = xExtendNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
   yExtendNorm = yExtendNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
   zExtendNorm = zExtendNorm / mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
   
   
   xShortest = xExtendNorm;
   yShortest = yExtendNorm;
   zShortest = zExtendNorm;
   
   for (i=mesh_QUADDATSZ[mesh_MESHNUM]/4*2; i < mesh_QUADDATSZ[mesh_MESHNUM+1]/4*2; i++)
   {
      xPresetBounds = xExtendNorm;
      yPresetBounds = yExtendNorm;
      zPresetBounds = zExtendNorm;
      
      ptToBoundsCollision(&quadSubtri_TRANS[i*TRSZ], xPastNorm, yPastNorm, zPastNorm,
                          &xPresetBounds, &yPresetBounds, &zPresetBounds,
                          &impactFaceBounds, &outsideBounds);
      
      // if the line goes through or is inside the bounds of a polygon
      if ((impactFaceBounds != 0) || (outsideBounds == FALSE))
      {
         // get a triangle
         pt1 = mesh_QUAD[i/2*4+0]*3;
         pt2 = mesh_QUAD[i/2*4+1]*3;
         pt3 = mesh_QUAD[i/2*4+2]*3;
         xPt1 = mesh_POINT[pt1+0]; yPt1 = mesh_POINT[pt1+1]; zPt1 = mesh_POINT[pt1+2];
         xPt2 = mesh_POINT[pt2+0]; yPt2 = mesh_POINT[pt2+1]; zPt2 = mesh_POINT[pt2+2];
         xPt3 = mesh_POINT[pt3+0]; yPt3 = mesh_POINT[pt3+1]; zPt3 = mesh_POINT[pt3+2];
         
         ptToTriCollision(quadSubtri_TRANS[i*TRSZ+9], quadSubtri_TRANS[i*TRSZ+10],
                          quadSubtri_TRANS[i*TRSZ+11], quadSubtri_TRANS[i*TRSZ+12],
                          quadSubtri_TRANS[i*TRSZ+13], quadSubtri_TRANS[i*TRSZ+14],
                          xPt1, yPt1, zPt1,// triangle
                          xPt2, yPt2, zPt2,
                          xPt3, yPt3, zPt3,
                          xPastNorm, yPastNorm, zPastNorm,// line
                          xExtendNorm, yExtendNorm, zExtendNorm,
                          errorMargin, &collide, &front, &xPt, &yPt, &zPt);
         
         
         // find the closest polygon to the past point
         if (collide)
         {
            // if the direction traveled is closer to the x coordinate
            if ((fabs(xExtendNorm-xPastNorm) >= fabs(yExtendNorm-yPastNorm)) &&
                (fabs(xExtendNorm-xPastNorm) >= fabs(zExtendNorm-zPastNorm)))
            if (fabs(xPt-xPastNorm) < fabs(xShortest-xPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
            
            // if the direction traveled is closer to the y coordinate
            if ((fabs(yExtendNorm-yPastNorm) >= fabs(xExtendNorm-xPastNorm)) &&
                (fabs(yExtendNorm-yPastNorm) >= fabs(zExtendNorm-zPastNorm)))
            if (fabs(yPt-yPastNorm) < fabs(yShortest-yPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
            
            // if the direction traveled is closer to the z coordinate
            if ((fabs(zExtendNorm-zPastNorm) >= fabs(xExtendNorm-xPastNorm)) &&
                (fabs(zExtendNorm-zPastNorm) >= fabs(yExtendNorm-yPastNorm)))
            if (fabs(zPt-zPastNorm) < fabs(zShortest-zPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
         }
      }
      
      
      i++;
      
      xPresetBounds = xExtendNorm;
      yPresetBounds = yExtendNorm;
      zPresetBounds = zExtendNorm;
      
      ptToBoundsCollision(&quadSubtri_TRANS[i*TRSZ], xPastNorm, yPastNorm, zPastNorm,
                          &xPresetBounds, &yPresetBounds, &zPresetBounds,
                          &impactFaceBounds, &outsideBounds);
      
      // if the line goes through or is inside the bounds of a polygon
      if ((impactFaceBounds != 0) || (outsideBounds == FALSE))
      {
         // get a triangle
         pt1 = mesh_QUAD[i/2*4+2]*3;
         pt2 = mesh_QUAD[i/2*4+3]*3;
         pt3 = mesh_QUAD[i/2*4+0]*3;
         xPt1 = mesh_POINT[pt1+0]; yPt1 = mesh_POINT[pt1+1]; zPt1 = mesh_POINT[pt1+2];
         xPt2 = mesh_POINT[pt2+0]; yPt2 = mesh_POINT[pt2+1]; zPt2 = mesh_POINT[pt2+2];
         xPt3 = mesh_POINT[pt3+0]; yPt3 = mesh_POINT[pt3+1]; zPt3 = mesh_POINT[pt3+2];
         
         ptToTriCollision(quadSubtri_TRANS[i*TRSZ+9], quadSubtri_TRANS[i*TRSZ+10],
                          quadSubtri_TRANS[i*TRSZ+11], quadSubtri_TRANS[i*TRSZ+12],
                          quadSubtri_TRANS[i*TRSZ+13], quadSubtri_TRANS[i*TRSZ+14],
                          xPt1, yPt1, zPt1,// triangle
                          xPt2, yPt2, zPt2,
                          xPt3, yPt3, zPt3,
                          xPastNorm, yPastNorm, zPastNorm,// line
                          xExtendNorm, yExtendNorm, zExtendNorm,
                          errorMargin, &collide, &front, &xPt, &yPt, &zPt);
         
         
         // find the closest polygon to the past point
         if (collide)
         {
            // if the direction traveled is closer to the x coordinate
            if ((fabs(xExtendNorm-xPastNorm) >= fabs(yExtendNorm-yPastNorm)) &&
                (fabs(xExtendNorm-xPastNorm) >= fabs(zExtendNorm-zPastNorm)))
            if (fabs(xPt-xPastNorm) < fabs(xShortest-xPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
            
            // if the direction traveled is closer to the y coordinate
            if ((fabs(yExtendNorm-yPastNorm) >= fabs(xExtendNorm-xPastNorm)) &&
                (fabs(yExtendNorm-yPastNorm) >= fabs(zExtendNorm-zPastNorm)))
            if (fabs(yPt-yPastNorm) < fabs(yShortest-yPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
            
            // if the direction traveled is closer to the z coordinate
            if ((fabs(zExtendNorm-zPastNorm) >= fabs(xExtendNorm-xPastNorm)) &&
                (fabs(zExtendNorm-zPastNorm) >= fabs(yExtendNorm-yPastNorm)))
            if (fabs(zPt-zPastNorm) < fabs(zShortest-zPastNorm))// if shorter
            {
               xShortest = xPt;
               yShortest = yPt;
               zShortest = zPt;
               
               polyNum = i;
               outsideOfMesh = !front;
            }
         }
      }
   }
   
   
   // resize, rotate and move  "xShortest, yShortest, zShortest"
   // in the same way it takes to undo normalization of the mesh using the transfomation data
   xShortest = xShortest * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
   yShortest = yShortest * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
   zShortest = zShortest * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
   
   applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                        mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                        mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                        &xShortest, &yShortest, &zShortest);
   
   xShortest = xShortest + mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
   yShortest = yShortest + mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
   zShortest = zShortest + mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
   
   // if the direction traveled is closer to the x coordinate
   if ((fabs(xExtend-xPast) >= fabs(yExtend-yPast)) &&
       (fabs(xExtend-xPast) >= fabs(zExtend-zPast)))
   if (fabs(xShortest-xPast) < fabs(*xPreset-xPast))// if shorter
   {
      *xPreset = xShortest;
      *yPreset = yShortest;
      *zPreset = zShortest;
      
      *impactFaceNum = polyNum;
   }
   
   // if the direction traveled is closer to the y coordinate
   if ((fabs(yExtend-yPast) >= fabs(xExtend-xPast)) &&
       (fabs(yExtend-yPast) >= fabs(zExtend-zPast)))
   if (fabs(yShortest-yPast) < fabs(*yPreset-yPast))// if shorter
   {
      *xPreset = xShortest;
      *yPreset = yShortest;
      *zPreset = zShortest;
      
      *impactFaceNum = polyNum;
   }
   
   // if the direction traveled is closer to the z coordinate
   if ((fabs(zExtend-zPast) >= fabs(xExtend-xPast)) &&
       (fabs(zExtend-zPast) >= fabs(yExtend-yPast)))
   if (fabs(zShortest-zPast) < fabs(*zPreset-zPast))// if shorter
   {
      *xPreset = xShortest;
      *yPreset = yShortest;
      *zPreset = zShortest;
      
      *impactFaceNum = polyNum;
   }
   
   *outside = outsideOfMesh;
}


// when reverse applying the rotation using yUc1, zUc1, xUc2... it must normalize the triangle
void ptToTriCollision(float yUc1, float zUc1,
                      float xUc2, float zUc2,
                      float xUc3, float yUc3,
                      float xT1, float yT1, float zT1,// triangle
                      float xT2, float yT2, float zT2,
                      float xT3, float yT3, float zT3,
                      float xLPast, float yLPast, float zLPast,// line
                      float xLPreset, float yLPreset, float zLPreset,
                      float errorMargin, int *collide, int *front, float *x, float *y, float *z)
{
   float xP, yP, zP;
   float xT1toT2;
   float xT2toT3;
   float xT3toT1;
   
   
   // normalize the triangle to the x,y plane
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xT1, &yT1, &zT1);
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xT2, &yT2, &zT2);
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xT3, &yT3, &zT3);

   // rotate the line with the triangle
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xLPreset, &yLPreset, &zLPreset);
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &xLPast, &yLPast, &zLPast);
   
   *collide = 0;
   
   // find the point where the triangle and the line intercept
   // by extending or contracting the line
   xP = xLPast - (zLPast - zT1) / (zLPast - zLPreset) * (xLPast - xLPreset);
   yP = yLPast - (zLPast - zT1) / (zLPast - zLPreset) * (yLPast - yLPreset);
   zP = zT1;
   
   // extend or contract each edge of the triangle to the same height as the point "yP"
   xT1toT2 = xT1 - (yT1 - yP) / (yT2 - yT1) * (xT2 - xT1);
   
   xT2toT3 = xT2 - (yT2 - yP) / (yT3 - yT2) * (xT3 - xT2);
   
   xT3toT1 = xT3 - (yT3 - yP) / (yT3 - yT1) * (xT3 - xT1);
   
   
   if (((zLPreset <= zT1) && (zLPast >= zT1)) || // did the line go through the plane the triangle is in
       ((zLPast <= zT1) && (zLPreset >= zT1)))
   {
      if (((yP-errorMargin <= yT1) && (yP+errorMargin >= yT2)) || // is the point within the vertical area of a triangle edge
          ((yP+errorMargin >= yT1) && (yP-errorMargin <= yT2)))
      if (((yP-errorMargin <= yT2) && (yP+errorMargin >= yT3)) || // is the point within the vertical area of a triangle edge
          ((yP+errorMargin >= yT2) && (yP-errorMargin <= yT3)))
      if (((xP-errorMargin <= xT1toT2) && (xP+errorMargin >= xT2toT3)) || // is the point not too far to the left or right
          ((xP+errorMargin >= xT1toT2) && (xP-errorMargin <= xT2toT3)))
      *collide = 1;
      
      if (((yP-errorMargin <= yT2) && (yP+errorMargin >= yT3)) ||
          ((yP+errorMargin >= yT2) && (yP-errorMargin <= yT3)))
      if (((yP-errorMargin <= yT3) && (yP+errorMargin >= yT1)) ||
          ((yP+errorMargin >= yT3) && (yP-errorMargin <= yT1)))
      if (((xP-errorMargin <= xT2toT3) && (xP+errorMargin >= xT3toT1)) ||
          ((xP+errorMargin >= xT2toT3) && (xP-errorMargin <= xT3toT1)))
      *collide = 1;
      
      if (((yP-errorMargin <= yT3) && (yP+errorMargin >= yT1)) ||
          ((yP+errorMargin >= yT3) && (yP-errorMargin <= yT1)))
      if (((yP-errorMargin <= yT1) && (yP+errorMargin >= yT2)) ||
          ((yP+errorMargin >= yT1) && (yP-errorMargin <= yT2)))
      if (((xP-errorMargin <= xT3toT1) && (xP+errorMargin >= xT1toT2)) ||
          ((xP+errorMargin >= xT3toT1) && (xP-errorMargin <= xT1toT2)))
      *collide = 1;
   }

   
   // find if the first point of the line is in front of the triangle
   if (zLPreset > zT1)
   *front = 1;
   else
   *front = 0;
   
   // rotate the collision point back to where it is suppose to be
   applyXyzUcRotToPoint(yUc1, zUc1,
                        xUc2, zUc2,
                        xUc3, yUc3, &xP, &yP, &zP);
   
   // return the collision point
   if (zLPreset != zLPast)
   {
      *x = xP;
      *y = yP;
      *z = zP;
   }
}


void ptToTriMeshZCollision(float *mesh_TRANS, int mesh_MESHNUM, float *mesh_POINT,
                           short *mesh_TRI, int *mesh_TRIDATSZ,
                           float xPast, float yPast, float zPast,
                           float *zPreset, int *impactFaceNum, int *outside)
{
   int i;
   int t1, t2, t3;
   float xT1, yT1, zT1;
   float xT2, yT2, zT2;
   float xT3, yT3, zT3;
   float xT1toT2, zT1toT2;
   float xT2toT3, zT2toT3;
   float xT3toT1, zT3toT1;
   float zPresetKeep, zPt;
   int impactPoly = -1;
   float zExtend, zExtendKeep;
   int outsideOfMesh;
   
   
   zPresetKeep = *zPreset;
   *impactFaceNum = -1;
   *outside = TRUE;
   
   
   // check that the x, y location is inside the bounds of the mesh
   if ((mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX]+mesh_TRANS[mesh_MESHNUM*TRSZ+BR] < xPast) ||
       (mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX]-mesh_TRANS[mesh_MESHNUM*TRSZ+BR] > xPast) ||
       (mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY]+mesh_TRANS[mesh_MESHNUM*TRSZ+BR] < yPast) ||
       (mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY]-mesh_TRANS[mesh_MESHNUM*TRSZ+BR] > yPast))
   return;
   
   
   // extend the line connecting the past and preset
   // points beyound the bounds box of the mesh to
   // insure it will go through a polygon this will
   // help determine if the point was inside or outside the mesh
   zExtend = zPast + mesh_TRANS[mesh_MESHNUM*TRSZ+BR] * 4;
   zExtendKeep = zExtend;
   
   
   for (i=mesh_TRIDATSZ[mesh_MESHNUM]/3; i < mesh_TRIDATSZ[mesh_MESHNUM+1]/3; i++)
   {
      t1 = mesh_TRI[i*3+1]*3;
      t2 = mesh_TRI[i*3+2]*3;
      t3 = mesh_TRI[i*3+0]*3;
      
      // apply the mesh size
      xT1 = mesh_POINT[t1+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT1 = mesh_POINT[t1+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT1 = mesh_POINT[t1+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      xT2 = mesh_POINT[t2+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT2 = mesh_POINT[t2+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT2 = mesh_POINT[t2+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      xT3 = mesh_POINT[t3+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT3 = mesh_POINT[t3+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT3 = mesh_POINT[t3+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      
      // apply the mesh rotation
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT1, &yT1, &zT1);
      
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT2, &yT2, &zT2);
      
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT3, &yT3, &zT3);
      
      // apply the mesh location
      xT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      xT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      xT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      
      
      // extend or contract each edge of the triangle to the same y-plane as "yPast"
      xT1toT2 = xT1 - (yT1 - yPast) / (yT2 - yT1) * (xT2 - xT1);
      zT1toT2 = zT1 - (yT1 - yPast) / (yT2 - yT1) * (zT2 - zT1);
      
      xT2toT3 = xT2 - (yT2 - yPast) / (yT3 - yT2) * (xT3 - xT2);
      zT2toT3 = zT2 - (yT2 - yPast) / (yT3 - yT2) * (zT3 - zT2);
      
      xT3toT1 = xT3 - (yT3 - yPast) / (yT3 - yT1) * (xT3 - xT1);
      zT3toT1 = zT3 - (yT3 - yPast) / (yT3 - yT1) * (zT3 - zT1);
      
      
      outsideOfMesh = TRUE;
      
      if (((yPast <= yT1) && (yPast >= yT2)) || // is the point within the vertical area of a triangle edge
          ((yPast >= yT1) && (yPast <= yT2)))
      if (((yPast <= yT2) && (yPast >= yT3)) || // is the point within the vertical area of a triangle edge
          ((yPast >= yT2) && (yPast <= yT3)))
      if (((xPast <= xT1toT2) && (xPast >= xT2toT3)) || // is the point not too far to the left or right
          ((xPast >= xT1toT2) && (xPast <= xT2toT3)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT2toT3 != zT1toT2)
         zPt = zT1toT2 - (xT1toT2 - xPast) / (xT2toT3 - xT1toT2) * (zT2toT3 - zT1toT2);
         else
         zPt = zT1toT2;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT2)
         if ((xPast <= xT1toT2) && (xPast >= xT2toT3))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT2)
         if ((xPast >= xT1toT2) && (xPast <= xT2toT3))
         outsideOfMesh = FALSE;
      }
      
      if (((yPast <= yT2) && (yPast >= yT3)) ||
          ((yPast >= yT2) && (yPast <= yT3)))
      if (((yPast <= yT3) && (yPast >= yT1)) ||
          ((yPast >= yT3) && (yPast <= yT1)))
      if (((xPast <= xT2toT3) && (xPast >= xT3toT1)) ||
          ((xPast >= xT2toT3) && (xPast <= xT3toT1)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT3toT1 != zT2toT3)
         zPt = zT2toT3 - (xT2toT3 - xPast) / (xT3toT1 - xT2toT3) * (zT3toT1 - zT2toT3);
         else
         zPt = zT2toT3;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT3)
         if ((xPast <= xT2toT3) && (xPast >= xT3toT1))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT3)
         if ((xPast >= xT2toT3) && (xPast <= xT3toT1))
         outsideOfMesh = FALSE;
      }
      
      if (((yPast <= yT3) && (yPast >= yT1)) ||
          ((yPast >= yT3) && (yPast <= yT1)))
      if (((yPast <= yT1) && (yPast >= yT2)) ||
          ((yPast >= yT1) && (yPast <= yT2)))
      if (((xPast <= xT3toT1) && (xPast >= xT1toT2)) ||
          ((xPast >= xT3toT1) && (xPast <= xT1toT2)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT1toT2 != zT3toT1)
         zPt = zT3toT1 - (xT3toT1 - xPast) / (xT1toT2 - xT3toT1) * (zT1toT2 - zT3toT1);
         else
         zPt = zT3toT1;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT1)
         if ((xPast <= xT3toT1) && (xPast >= xT1toT2))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT1)
         if ((xPast >= xT3toT1) && (xPast <= xT1toT2))
         outsideOfMesh = FALSE;
      }
      
      if (impactPoly != -1)
      if (((zExtend <= zPt) && (zPast >= zPt)) || // is the polygon between the past and extended points
          ((zPast <= zPt) && (zExtend >= zPt)))
      if (fabs(zExtend-zPt) > fabs(zExtend-zExtendKeep))// closest polygon
      {
         zExtendKeep = zPt;
         *outside = outsideOfMesh;
      }
      
      if (impactPoly != -1)
      if (((*zPreset <= zPt) && (zPast >= zPt)) || // is the polygon between the past and preset points
          ((zPast <= zPt) && (*zPreset >= zPt)))
      if (fabs(*zPreset-zPt) > fabs(*zPreset-zPresetKeep))// closest polygon
      {
         zPresetKeep = zPt;
         *impactFaceNum = impactPoly;
      }
   }
   
   // return the collision point
   *zPreset = zPresetKeep;
}


void ptToQuadMeshZCollision(float *mesh_TRANS, int mesh_MESHNUM, float *mesh_POINT,
                            short *mesh_QUAD, int *mesh_QUADDATSZ,
                            float xPast, float yPast, float zPast,
                            float *zPreset, int *impactFaceNum, int *outside)
{
   int i;
   int t1, t2, t3;
   float xT1, yT1, zT1;
   float xT2, yT2, zT2;
   float xT3, yT3, zT3;
   float xT1toT2, zT1toT2;
   float xT2toT3, zT2toT3;
   float xT3toT1, zT3toT1;
   float zPresetKeep, zPt;
   int impactPoly = -1;
   float zExtend, zExtendKeep;
   int outsideOfMesh;
   
   
   zPresetKeep = *zPreset;
   *impactFaceNum = -1;
   *outside = TRUE;
   
   
   // check that the x, y location is inside the bounds of the mesh
   if ((mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX]+mesh_TRANS[mesh_MESHNUM*TRSZ+BR] < xPast) ||
       (mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX]-mesh_TRANS[mesh_MESHNUM*TRSZ+BR] > xPast) ||
       (mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY]+mesh_TRANS[mesh_MESHNUM*TRSZ+BR] < yPast) ||
       (mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY]-mesh_TRANS[mesh_MESHNUM*TRSZ+BR] > yPast))
   return;
   
   
   // extend the line connecting the past and preset
   // points beyound the bounds box of the mesh to
   // insure it will go through a polygon this will
   // help determine if the point was inside or outside the mesh
   zExtend = zPast + mesh_TRANS[mesh_MESHNUM*TRSZ+BR] * 4;
   zExtendKeep = zExtend;
   
   
   for (i=mesh_QUADDATSZ[mesh_MESHNUM]/4*2; i < mesh_QUADDATSZ[mesh_MESHNUM+1]/4*2; i++)
   {
      // get a triangle
      t1 = mesh_QUAD[i/2*4+0]*3;
      t2 = mesh_QUAD[i/2*4+1]*3;
      t3 = mesh_QUAD[i/2*4+2]*3;
      
      // apply the mesh size
      xT1 = mesh_POINT[t1+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT1 = mesh_POINT[t1+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT1 = mesh_POINT[t1+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      xT2 = mesh_POINT[t2+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT2 = mesh_POINT[t2+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT2 = mesh_POINT[t2+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      xT3 = mesh_POINT[t3+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT3 = mesh_POINT[t3+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT3 = mesh_POINT[t3+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      
      // apply the mesh rotation
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT1, &yT1, &zT1);
      
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT2, &yT2, &zT2);
      
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT3, &yT3, &zT3);
      
      // apply the mesh location
      xT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      xT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      xT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      
      
      // extend or contract each edge of the triangle to the same y-plane as "yPast"
      xT1toT2 = xT1 - (yT1 - yPast) / (yT2 - yT1) * (xT2 - xT1);
      zT1toT2 = zT1 - (yT1 - yPast) / (yT2 - yT1) * (zT2 - zT1);
      
      xT2toT3 = xT2 - (yT2 - yPast) / (yT3 - yT2) * (xT3 - xT2);
      zT2toT3 = zT2 - (yT2 - yPast) / (yT3 - yT2) * (zT3 - zT2);
      
      xT3toT1 = xT3 - (yT3 - yPast) / (yT3 - yT1) * (xT3 - xT1);
      zT3toT1 = zT3 - (yT3 - yPast) / (yT3 - yT1) * (zT3 - zT1);
      
      
      outsideOfMesh = TRUE;
      
      if (((yPast <= yT1) && (yPast >= yT2)) || // is the point within the vertical area of a triangle edge
          ((yPast >= yT1) && (yPast <= yT2)))
      if (((yPast <= yT2) && (yPast >= yT3)) || // is the point within the vertical area of a triangle edge
          ((yPast >= yT2) && (yPast <= yT3)))
      if (((xPast <= xT1toT2) && (xPast >= xT2toT3)) || // is the point not too far to the left or right
          ((xPast >= xT1toT2) && (xPast <= xT2toT3)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT2toT3 != zT1toT2)
         zPt = zT1toT2 - (xT1toT2 - xPast) / (xT2toT3 - xT1toT2) * (zT2toT3 - zT1toT2);
         else
         zPt = zT1toT2;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT2)
         if ((xPast <= xT1toT2) && (xPast >= xT2toT3))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT2)
         if ((xPast >= xT1toT2) && (xPast <= xT2toT3))
         outsideOfMesh = FALSE;
      }
      
      if (((yPast <= yT2) && (yPast >= yT3)) ||
          ((yPast >= yT2) && (yPast <= yT3)))
      if (((yPast <= yT3) && (yPast >= yT1)) ||
          ((yPast >= yT3) && (yPast <= yT1)))
      if (((xPast <= xT2toT3) && (xPast >= xT3toT1)) ||
          ((xPast >= xT2toT3) && (xPast <= xT3toT1)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT3toT1 != zT2toT3)
         zPt = zT2toT3 - (xT2toT3 - xPast) / (xT3toT1 - xT2toT3) * (zT3toT1 - zT2toT3);
         else
         zPt = zT2toT3;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT3)
         if ((xPast <= xT2toT3) && (xPast >= xT3toT1))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT3)
         if ((xPast >= xT2toT3) && (xPast <= xT3toT1))
         outsideOfMesh = FALSE;
      }
      
      if (((yPast <= yT3) && (yPast >= yT1)) ||
          ((yPast >= yT3) && (yPast <= yT1)))
      if (((yPast <= yT1) && (yPast >= yT2)) ||
          ((yPast >= yT1) && (yPast <= yT2)))
      if (((xPast <= xT3toT1) && (xPast >= xT1toT2)) ||
          ((xPast >= xT3toT1) && (xPast <= xT1toT2)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT1toT2 != zT3toT1)
         zPt = zT3toT1 - (xT3toT1 - xPast) / (xT1toT2 - xT3toT1) * (zT1toT2 - zT3toT1);
         else
         zPt = zT3toT1;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT1)
         if ((xPast <= xT3toT1) && (xPast >= xT1toT2))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT1)
         if ((xPast >= xT3toT1) && (xPast <= xT1toT2))
         outsideOfMesh = FALSE;
      }
      
      if (impactPoly != -1)
      if (((zExtend <= zPt) && (zPast >= zPt)) || // is the polygon between the past and extended points
          ((zPast <= zPt) && (zExtend >= zPt)))
      if (fabs(zExtend-zPt) > fabs(zExtend-zExtendKeep))// closest polygon
      {
         zExtendKeep = zPt;
         *outside = outsideOfMesh;
      }
      
      if (impactPoly != -1)
      if (((*zPreset <= zPt) && (zPast >= zPt)) || // is the polygon between the past and preset points
          ((zPast <= zPt) && (*zPreset >= zPt)))
      if (fabs(*zPreset-zPt) > fabs(*zPreset-zPresetKeep))// closest polygon
      {
         zPresetKeep = zPt;
         *impactFaceNum = impactPoly;
      }
      
      
      
      // get a triangle
      t1 = mesh_QUAD[i/2*4+2]*3;
      t2 = mesh_QUAD[i/2*4+3]*3;
      t3 = mesh_QUAD[i/2*4+0]*3;
      
      // apply the mesh size
      xT1 = mesh_POINT[t1+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT1 = mesh_POINT[t1+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT1 = mesh_POINT[t1+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      xT2 = mesh_POINT[t2+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT2 = mesh_POINT[t2+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT2 = mesh_POINT[t2+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      xT3 = mesh_POINT[t3+0] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZX];
      yT3 = mesh_POINT[t3+1] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZY];
      zT3 = mesh_POINT[t3+2] * mesh_TRANS[mesh_MESHNUM*TRSZ+SZZ];
      
      // apply the mesh rotation
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT1, &yT1, &zT1);
      
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT2, &yT2, &zT2);
      
      applyXyzUcRotToPoint(mesh_TRANS[mesh_MESHNUM*TRSZ+9], mesh_TRANS[mesh_MESHNUM*TRSZ+10],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+11], mesh_TRANS[mesh_MESHNUM*TRSZ+12],
                           mesh_TRANS[mesh_MESHNUM*TRSZ+13], mesh_TRANS[mesh_MESHNUM*TRSZ+14],
                           &xT3, &yT3, &zT3);
      
      // apply the mesh location
      xT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT1 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      xT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT2 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      xT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCX];
      yT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCY];
      zT3 += mesh_TRANS[mesh_MESHNUM*TRSZ+LOCZ];
      
      
      // extend or contract each edge of the triangle to the same y-plane as "yPast"
      xT1toT2 = xT1 - (yT1 - yPast) / (yT2 - yT1) * (xT2 - xT1);
      zT1toT2 = zT1 - (yT1 - yPast) / (yT2 - yT1) * (zT2 - zT1);
      
      xT2toT3 = xT2 - (yT2 - yPast) / (yT3 - yT2) * (xT3 - xT2);
      zT2toT3 = zT2 - (yT2 - yPast) / (yT3 - yT2) * (zT3 - zT2);
      
      xT3toT1 = xT3 - (yT3 - yPast) / (yT3 - yT1) * (xT3 - xT1);
      zT3toT1 = zT3 - (yT3 - yPast) / (yT3 - yT1) * (zT3 - zT1);
      
      
      outsideOfMesh = TRUE;
      
      if (((yPast <= yT1) && (yPast >= yT2)) || // is the point within the vertical area of a triangle edge
          ((yPast >= yT1) && (yPast <= yT2)))
      if (((yPast <= yT2) && (yPast >= yT3)) || // is the point within the vertical area of a triangle edge
          ((yPast >= yT2) && (yPast <= yT3)))
      if (((xPast <= xT1toT2) && (xPast >= xT2toT3)) || // is the point not too far to the left or right
          ((xPast >= xT1toT2) && (xPast <= xT2toT3)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT2toT3 != zT1toT2)
         zPt = zT1toT2 - (xT1toT2 - xPast) / (xT2toT3 - xT1toT2) * (zT2toT3 - zT1toT2);
         else
         zPt = zT1toT2;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT2)
         if ((xPast <= xT1toT2) && (xPast >= xT2toT3))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT2)
         if ((xPast >= xT1toT2) && (xPast <= xT2toT3))
         outsideOfMesh = FALSE;
      }
      
      if (((yPast <= yT2) && (yPast >= yT3)) ||
          ((yPast >= yT2) && (yPast <= yT3)))
      if (((yPast <= yT3) && (yPast >= yT1)) ||
          ((yPast >= yT3) && (yPast <= yT1)))
      if (((xPast <= xT2toT3) && (xPast >= xT3toT1)) ||
          ((xPast >= xT2toT3) && (xPast <= xT3toT1)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT3toT1 != zT2toT3)
         zPt = zT2toT3 - (xT2toT3 - xPast) / (xT3toT1 - xT2toT3) * (zT3toT1 - zT2toT3);
         else
         zPt = zT2toT3;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT3)
         if ((xPast <= xT2toT3) && (xPast >= xT3toT1))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT3)
         if ((xPast >= xT2toT3) && (xPast <= xT3toT1))
         outsideOfMesh = FALSE;
      }
      
      if (((yPast <= yT3) && (yPast >= yT1)) ||
          ((yPast >= yT3) && (yPast <= yT1)))
      if (((yPast <= yT1) && (yPast >= yT2)) ||
          ((yPast >= yT1) && (yPast <= yT2)))
      if (((xPast <= xT3toT1) && (xPast >= xT1toT2)) ||
          ((xPast >= xT3toT1) && (xPast <= xT1toT2)))
      {
         // contract a horizontal line to the same x-plane as "xPast"
         if (zT1toT2 != zT3toT1)
         zPt = zT3toT1 - (xT3toT1 - xPast) / (xT1toT2 - xT3toT1) * (zT1toT2 - zT3toT1);
         else
         zPt = zT3toT1;
         
         impactPoly = i;
         
         // find which side of the triangle the collision occurred
         if (yPast <= yT1)
         if ((xPast <= xT3toT1) && (xPast >= xT1toT2))
         outsideOfMesh = FALSE;
         
         if (yPast >= yT1)
         if ((xPast >= xT3toT1) && (xPast <= xT1toT2))
         outsideOfMesh = FALSE;
      }
      
      if (impactPoly != -1)
      if (((zExtend <= zPt) && (zPast >= zPt)) || // is the polygon between the past and extended points
          ((zPast <= zPt) && (zExtend >= zPt)))
      if (fabs(zExtend-zPt) > fabs(zExtend-zExtendKeep))// closest polygon
      {
         zExtendKeep = zPt;
         *outside = outsideOfMesh;
      }
      
      if (impactPoly != -1)
      if (((*zPreset <= zPt) && (zPast >= zPt)) || // is the polygon between the past and preset points
          ((zPast <= zPt) && (*zPreset >= zPt)))
      if (fabs(*zPreset-zPt) > fabs(*zPreset-zPresetKeep))// closest polygon
      {
         zPresetKeep = zPt;
         *impactFaceNum = impactPoly;
      }
   }
   
   // return the collision point
   *zPreset = zPresetKeep;
}
