#include <stdio.h>
#include <math.h>
#include "3dEngine.h"

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


void ptToPlaneSkid(float *mesh_TRANS, float xBgn, float yBgn, float zBgn,
                                      float xHit, float yHit, float zHit,
                                      float *xArrow, float *yArrow, float *zArrow)
{
   // move the "begin to hit" path in the same way it takes to normalize the plane
   xBgn -= mesh_TRANS[LOCX];
   yBgn -= mesh_TRANS[LOCY];
   zBgn -= mesh_TRANS[LOCZ];
   xHit -= mesh_TRANS[LOCX];
   yHit -= mesh_TRANS[LOCY];
   zHit -= mesh_TRANS[LOCZ];
   
   // rotate the "begin to hit" path in the same way it takes to normalize the plane
   reverseApplyXyzUcRotToPoint(mesh_TRANS[UCXH], mesh_TRANS[UCXV],
                               mesh_TRANS[UCYH], mesh_TRANS[UCYV],
                               mesh_TRANS[UCZH], mesh_TRANS[UCZV], &xBgn, &yBgn, &zBgn);
   reverseApplyXyzUcRotToPoint(mesh_TRANS[UCXH], mesh_TRANS[UCXV],
                               mesh_TRANS[UCYH], mesh_TRANS[UCYV],
                               mesh_TRANS[UCZH], mesh_TRANS[UCZV], &xHit, &yHit, &zHit);
   
   // find the slide path
   zPlaneSkidPath(xBgn, yBgn, zBgn, xHit, yHit, zHit,
                  &xHit, &yHit, &zHit, &*xArrow, &*yArrow, &*zArrow);
   
   // rotate the arrow as if undoing the normalization
   applyXyzUcRotToPoint(mesh_TRANS[UCXH], mesh_TRANS[UCXV],
                        mesh_TRANS[UCYH], mesh_TRANS[UCYV],
                        mesh_TRANS[UCZH], mesh_TRANS[UCZV], &*xArrow, &*yArrow, &*zArrow);
}


void boxSkid(float *fixed_TRANS, float *moving_TRANS,
             float xTravel, float yTravel, float zTravel, int faceHitData,
             float *xArrow, float *yArrow, float *zArrow)
{
   #define FACE_CONTACT 1
   #define EDGE_CONTACT 2
   #define POINT_CONTACT 3
   
   float plane_TRANS[TRSZ];
   float plane_POINT[9];
   int plane_POINTDATSZ[2]={0, 9};
   short plane_TRI[3]={0, 1, 2};
   int plane_TRIDATSZ[2] = {0, 3};
   int fixedBoxContactType = 0;
   
   *xArrow = xTravel;
   *yArrow = yTravel;
   *zArrow = zTravel;
   
   if ((FIXED_POS_X & faceHitData) || (FIXED_NEG_X & faceHitData))
   fixedBoxContactType++;
   
   if ((FIXED_POS_Y & faceHitData) || (FIXED_NEG_Y & faceHitData))
   fixedBoxContactType++;
   
   if ((FIXED_POS_Z & faceHitData) || (FIXED_NEG_Z & faceHitData))
   fixedBoxContactType++;
   
   
   if (fixedBoxContactType == FACE_CONTACT)
   {
      copyLocFromTo(&fixed_TRANS[0], &plane_TRANS[0], 1);
      
      if ((FIXED_POS_X & faceHitData) || (FIXED_NEG_X & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = 0.0; plane_TRANS[UCYV] = 1.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
      }
      
      if ((FIXED_POS_Y & faceHitData) || (FIXED_NEG_Y & faceHitData))
      {
         plane_TRANS[UCXH] = 0.0; plane_TRANS[UCXV] = 1.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
      }
      
      if ((FIXED_POS_Z & faceHitData) || (FIXED_NEG_Z & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
      }
      
      // apply the fixed box rotation to the plane
      applyXyzUcRot(&plane_TRANS[UCXH], &plane_TRANS[UCXV],
                    &plane_TRANS[UCYH], &plane_TRANS[UCYV],
                    &plane_TRANS[UCZH], &plane_TRANS[UCZV],
                    fixed_TRANS[UCXH], fixed_TRANS[UCXV],
                    fixed_TRANS[UCYH], fixed_TRANS[UCYV],
                    fixed_TRANS[UCZH], fixed_TRANS[UCZV]);
      
      ptToPlaneSkid(plane_TRANS, moving_TRANS[LOCX], moving_TRANS[LOCY], moving_TRANS[LOCZ],
                    moving_TRANS[LOCX] + xTravel,
                    moving_TRANS[LOCY] + yTravel,
                    moving_TRANS[LOCZ] + zTravel, &*xArrow, &*yArrow, &*zArrow);
   }
   
   
   if (fixedBoxContactType == EDGE_CONTACT)
   {
      plane_POINT[0] = 0;
      plane_POINT[1] = 0;
      plane_POINT[2] = 0;
      
      // fixed box top
      if ((FIXED_POS_X & faceHitData) && (FIXED_POS_Z & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = M_SQRT1_2; plane_TRANS[UCYV] = M_SQRT1_2;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 1.0;
         plane_POINT[5] = 0.0;
      }
      if ((FIXED_NEG_X & faceHitData) && (FIXED_POS_Z & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = M_SQRT1_2; plane_TRANS[UCYV] = -M_SQRT1_2;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 1.0;
         plane_POINT[5] = 0.0;
      }
      if ((FIXED_POS_Y & faceHitData) && (FIXED_POS_Z & faceHitData))
      {
         plane_TRANS[UCXH] = M_SQRT1_2; plane_TRANS[UCXV] = -M_SQRT1_2;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 1.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 0.0;
      }
      if ((FIXED_NEG_Y & faceHitData) && (FIXED_POS_Z & faceHitData))
      {
         plane_TRANS[UCXH] = M_SQRT1_2; plane_TRANS[UCXV] = M_SQRT1_2;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 1.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 0.0;
      }
      
      // fixed box sides
      if ((FIXED_POS_X & faceHitData) && (FIXED_POS_Y & faceHitData))
      {
         plane_TRANS[UCXH] = 0.0; plane_TRANS[UCXV] = -1.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = M_SQRT1_2; plane_TRANS[UCZV] = -M_SQRT1_2;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 1.0;
      }
      if ((FIXED_NEG_X & faceHitData) && (FIXED_NEG_Y & faceHitData))
      {
         plane_TRANS[UCXH] = 0.0; plane_TRANS[UCXV] = -1.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = M_SQRT1_2; plane_TRANS[UCZV] = -M_SQRT1_2;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 1.0;
      }
      if ((FIXED_POS_X & faceHitData) && (FIXED_NEG_Y & faceHitData))
      {
         plane_TRANS[UCXH] = 0.0; plane_TRANS[UCXV] = -1.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = M_SQRT1_2; plane_TRANS[UCZV] = M_SQRT1_2;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 1.0;
      }
      if ((FIXED_NEG_X & faceHitData) && (FIXED_POS_Y & faceHitData))
      {
         plane_TRANS[UCXH] = 0.0; plane_TRANS[UCXV] = -1.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = M_SQRT1_2; plane_TRANS[UCZV] = M_SQRT1_2;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 1.0;
      }
      
      // fixed box bottom
      if ((FIXED_NEG_X & faceHitData) && (FIXED_NEG_Z & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = M_SQRT1_2; plane_TRANS[UCYV] = M_SQRT1_2;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 1.0;
         plane_POINT[5] = 0.0;
      }
      if ((FIXED_POS_X & faceHitData) && (FIXED_NEG_Z & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = M_SQRT1_2; plane_TRANS[UCYV] = -M_SQRT1_2;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 0.0;
         plane_POINT[4] = 1.0;
         plane_POINT[5] = 0.0;
      }
      if ((FIXED_NEG_Y & faceHitData) && (FIXED_NEG_Z & faceHitData))
      {
         plane_TRANS[UCXH] = M_SQRT1_2; plane_TRANS[UCXV] = -M_SQRT1_2;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 1.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 0.0;
      }
      if ((FIXED_POS_Y & faceHitData) && (FIXED_NEG_Z & faceHitData))
      {
         plane_TRANS[UCXH] = M_SQRT1_2; plane_TRANS[UCXV] = M_SQRT1_2;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
         plane_POINT[3] = 1.0;
         plane_POINT[4] = 0.0;
         plane_POINT[5] = 0.0;
      }
      
      // apply the moving box rotation to the trigon point
      applyXyzUcRotToPoint(fixed_TRANS[UCXH], fixed_TRANS[UCXV],
                           fixed_TRANS[UCYH], fixed_TRANS[UCYV],
                           fixed_TRANS[UCZH], fixed_TRANS[UCZV],
                           &plane_POINT[3], &plane_POINT[4], &plane_POINT[5]);
      
      
      // moving box top
      if ((MOVING_POS_X & faceHitData) && (MOVING_POS_Z & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 1.0;
         plane_POINT[8] = 0.0;
      }
      if ((MOVING_NEG_X & faceHitData) && (MOVING_POS_Z & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 1.0;
         plane_POINT[8] = 0.0;
      }
      if ((MOVING_POS_Y & faceHitData) && (MOVING_POS_Z & faceHitData))
      {
         plane_POINT[6] = 1.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 0.0;
      }
      if ((MOVING_NEG_Y & faceHitData) && (MOVING_POS_Z & faceHitData))
      {
         plane_POINT[6] = 1.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 0.0;
      }
      
      // moving box sides
      if ((MOVING_POS_X & faceHitData) && (MOVING_POS_Y & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 1.0;
      }
      if ((MOVING_NEG_X & faceHitData) && (MOVING_NEG_Y & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 1.0;
      }
      if ((MOVING_POS_X & faceHitData) && (MOVING_NEG_Y & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 1.0;
      }
      if ((MOVING_NEG_X & faceHitData) && (MOVING_POS_Y & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 1.0;
      }
      
      // moving box bottom
      if ((MOVING_NEG_X & faceHitData) && (MOVING_NEG_Z & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 1.0;
         plane_POINT[8] = 0.0;
      }
      if ((MOVING_POS_X & faceHitData) && (MOVING_NEG_Z & faceHitData))
      {
         plane_POINT[6] = 0.0;
         plane_POINT[7] = 1.0;
         plane_POINT[8] = 0.0;
      }
      if ((MOVING_NEG_Y & faceHitData) && (MOVING_NEG_Z & faceHitData))
      {
         plane_POINT[6] = 1.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 0.0;
      }
      if ((MOVING_POS_Y & faceHitData) && (MOVING_NEG_Z & faceHitData))
      {
         plane_POINT[6] = 1.0;
         plane_POINT[7] = 0.0;
         plane_POINT[8] = 0.0;
      }
      
      // apply the moving box rotation to the trigon point
      applyXyzUcRotToPoint(moving_TRANS[UCXH], moving_TRANS[UCXV],
                           moving_TRANS[UCYH], moving_TRANS[UCYV],
                           moving_TRANS[UCZH], moving_TRANS[UCZV],
                           &plane_POINT[6], &plane_POINT[7], &plane_POINT[8]);
      
      
      // if both edges are the same
      if ((plane_POINT[3] == plane_POINT[6]) &&
          (plane_POINT[4] == plane_POINT[7]) &&
          (plane_POINT[5] == plane_POINT[8]))
      applyXyzUcRot(&plane_TRANS[UCXH], &plane_TRANS[UCXV],
                    &plane_TRANS[UCYH], &plane_TRANS[UCYV],
                    &plane_TRANS[UCZH], &plane_TRANS[UCZV],
                    fixed_TRANS[UCXH], fixed_TRANS[UCXV],
                    fixed_TRANS[UCYH], fixed_TRANS[UCYV],
                    fixed_TRANS[UCZH], fixed_TRANS[UCZV]);
      else
      // create transformation data for a plane from the two contacting box edges
      makeTriTransData(0, 1, &plane_POINT[0], &plane_POINTDATSZ[0],
                       &plane_TRI[0], &plane_TRIDATSZ[0], &plane_TRANS[0]);
      
      
      copyLocFromTo(&fixed_TRANS[0], &plane_TRANS[0], 1);
      
      ptToPlaneSkid(plane_TRANS, moving_TRANS[LOCX], moving_TRANS[LOCY], moving_TRANS[LOCZ],
                    moving_TRANS[LOCX] + xTravel,
                    moving_TRANS[LOCY] + yTravel,
                    moving_TRANS[LOCZ] + zTravel, &*xArrow, &*yArrow, &*zArrow);
   }
   
   
   if (fixedBoxContactType == POINT_CONTACT)
   {
      copyLocFromTo(&moving_TRANS[0], &plane_TRANS[0], 1);
      
      if ((MOVING_POS_X & faceHitData) || (MOVING_NEG_X & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = 0.0; plane_TRANS[UCYV] = 1.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
      }
      
      if ((MOVING_POS_Y & faceHitData) || (MOVING_NEG_Y & faceHitData))
      {
         plane_TRANS[UCXH] = 0.0; plane_TRANS[UCXV] = 1.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
      }
      
      if ((MOVING_POS_Z & faceHitData) || (MOVING_NEG_Z & faceHitData))
      {
         plane_TRANS[UCXH] = 1.0; plane_TRANS[UCXV] = 0.0;
         plane_TRANS[UCYH] = 1.0; plane_TRANS[UCYV] = 0.0;
         plane_TRANS[UCZH] = 1.0; plane_TRANS[UCZV] = 0.0;
      }
      
      // apply the moving box rotation to the plane
      applyXyzUcRot(&plane_TRANS[UCXH], &plane_TRANS[UCXV],
                    &plane_TRANS[UCYH], &plane_TRANS[UCYV],
                    &plane_TRANS[UCZH], &plane_TRANS[UCZV],
                    moving_TRANS[UCXH], moving_TRANS[UCXV],
                    moving_TRANS[UCYH], moving_TRANS[UCYV],
                    moving_TRANS[UCZH], moving_TRANS[UCZV]);
      
      ptToPlaneSkid(plane_TRANS, moving_TRANS[LOCX] + xTravel,
                                 moving_TRANS[LOCY] + yTravel,
                                 moving_TRANS[LOCZ] + zTravel,
                                 moving_TRANS[LOCX], moving_TRANS[LOCY], moving_TRANS[LOCZ],
                                 &*xArrow, &*yArrow, &*zArrow);
      
      *xArrow = -*xArrow;
      *yArrow = -*yArrow;
      *zArrow = -*zArrow;
   }
}
