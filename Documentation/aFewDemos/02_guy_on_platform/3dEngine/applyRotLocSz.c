#include <math.h>
#include <stdio.h>
#include "3dEngine.h"

void applyRotLocSz(float *mesh_TRANS, float *mesh_POINT, int *mesh_POINTDATSZ, int mesh_MESHNUM, int mesh_MESHCNT)
{
   int i, meshInc, transInc;
   int ptDatBgn, ptDatEnd;
   
   // apply the size from each transformation data block to the corresponding mesh
   for (meshInc=mesh_MESHNUM; meshInc < mesh_MESHNUM+mesh_MESHCNT; meshInc++)
   {
      transInc = meshInc * TRSZ;
      
      ptDatBgn = mesh_POINTDATSZ[meshInc];
      ptDatEnd = mesh_POINTDATSZ[meshInc+1];
      
      for (i=ptDatBgn; i < ptDatEnd; i=i+3)
      {
         mesh_POINT[i+0] = mesh_POINT[i+0] * mesh_TRANS[transInc+SZX];
         mesh_POINT[i+1] = mesh_POINT[i+1] * mesh_TRANS[transInc+SZY];
         mesh_POINT[i+2] = mesh_POINT[i+2] * mesh_TRANS[transInc+SZZ];
      }
   }
   
   // apply the rotation of the axises from each transformation data block to the corresponding mesh
   for (meshInc=mesh_MESHNUM; meshInc < mesh_MESHNUM+mesh_MESHCNT; meshInc++)
   {
      transInc = meshInc * TRSZ;
      
      ptDatBgn = mesh_POINTDATSZ[meshInc];
      ptDatEnd = mesh_POINTDATSZ[meshInc+1];
      
      for (i=ptDatBgn; i < ptDatEnd; i=i+3)
      applyXyzUcRotToPoint(mesh_TRANS[transInc+UCXH], mesh_TRANS[transInc+UCXV],
                           mesh_TRANS[transInc+UCYH], mesh_TRANS[transInc+UCYV],
                           mesh_TRANS[transInc+UCZH], mesh_TRANS[transInc+UCZV],
                           &mesh_POINT[i+0], &mesh_POINT[i+1], &mesh_POINT[i+2]);
   }
   
   // apply the location from each transformation data block to the corresponding mesh
   for (meshInc=mesh_MESHNUM; meshInc < mesh_MESHNUM+mesh_MESHCNT; meshInc++)
   {
      transInc = meshInc * TRSZ;
      
      ptDatBgn = mesh_POINTDATSZ[meshInc];
      ptDatEnd = mesh_POINTDATSZ[meshInc+1];
      
      for (i=ptDatBgn; i < ptDatEnd; i=i+3)
      {
         mesh_POINT[i+0] = mesh_POINT[i+0] + mesh_TRANS[transInc+LOCX];
         mesh_POINT[i+1] = mesh_POINT[i+1] + mesh_TRANS[transInc+LOCY];
         mesh_POINT[i+2] = mesh_POINT[i+2] + mesh_TRANS[transInc+LOCZ];
      }
   }
}

// apply a rotation, location and size to the view from a mesh
void applyMeshViewRotLocSz(float *mesh_POINT, int *mesh_POINTDATSZ, int mesh_MESHNUM, int mesh_MESHCNT,
                           float *meshView_TRANS, float camLenseSz, struct rendrInfo rI)
{
   int i;
   float yUc1, zUc1;
   float xUc2, zUc2;
   float xUc3, yUc3;
   float xLoc, yLoc, zLoc;
   float xSize, ySize, zSize;
   
   
   xLoc = -meshView_TRANS[LOCX];
   yLoc = -meshView_TRANS[LOCY];
   zLoc = -meshView_TRANS[LOCZ];
   
   // apply the view location
   for (i = mesh_POINTDATSZ[mesh_MESHNUM]; i < mesh_POINTDATSZ[mesh_MESHNUM+mesh_MESHCNT]; i=i+3)
   {
      mesh_POINT[i+0] = (mesh_POINT[i+0] + xLoc);
      mesh_POINT[i+1] = (mesh_POINT[i+1] + yLoc);
      mesh_POINT[i+2] = (mesh_POINT[i+2] + zLoc);
   }

   
   yUc1 = meshView_TRANS[UCXH];
   zUc1 = meshView_TRANS[UCXV];
   xUc2 = meshView_TRANS[UCYH];
   zUc2 = meshView_TRANS[UCYV];
   xUc3 = meshView_TRANS[UCZH];
   yUc3 = meshView_TRANS[UCZV];
   
   // apply a view rotation to each point within a mesh using unit circle coordinate data
   for (i = mesh_POINTDATSZ[mesh_MESHNUM]; i < mesh_POINTDATSZ[mesh_MESHNUM+mesh_MESHCNT]; i=i+3)
   reverseApplyXyzUcRotToPoint(yUc1, zUc1,
                               xUc2, zUc2,
                               xUc3, yUc3, &mesh_POINT[i+0], &mesh_POINT[i+1], &mesh_POINT[i+2]);
   
   if (camLenseSz)
   {
      xSize = 1.0 / camLenseSz * rI.viewRelativeSize;
      ySize = 1.0 / camLenseSz * rI.viewRelativeSize;
      zSize = 1.0 / camLenseSz * rI.viewRelativeSize;
   }
   else
   {
      xSize = 1.0 / meshView_TRANS[SZX] * rI.viewRelativeSize;
      ySize = 1.0 / meshView_TRANS[SZY] * rI.viewRelativeSize;
      zSize = 1.0 / meshView_TRANS[SZZ] * rI.viewRelativeSize;
   }
   
   // apply the view size
   for (i = mesh_POINTDATSZ[mesh_MESHNUM]; i < mesh_POINTDATSZ[mesh_MESHNUM+mesh_MESHCNT]; i=i+3)
   {
      mesh_POINT[i+0] *= xSize;
      mesh_POINT[i+1] *= ySize;
      mesh_POINT[i+2] *= zSize;
   }
}
