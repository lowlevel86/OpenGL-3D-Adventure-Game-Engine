#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include "3dEngine.h"

#define TRUE 1
#define FALSE 0

void drawMesh(float *mesh_POINT, short *mesh_QUAD, short *mesh_TRI, char *mesh_VCOLOR,
              int *mesh_TEX, float *mesh_TEXCOORD, int *mesh_TEXLINKDAT,
              int *mesh_QUADDATSZ, int *mesh_TRIDATSZ, int *mesh_HIDE,
              int mesh_MESHNUM, int mesh_MESHCNT, struct rendrInfo rI)
{
   int i;
   int quadArraySize;
   int triArraySize;
   int quadArrayLoc;
   int triArrayLoc;

   float pv, zNear;
   float fogBgnZ, fogEndZ;
   GLdouble eqn[4];

   
   // calculate the fog position
   pv = (rI.winWdth / 2.0) / rI.perspctv;
   
   if ((!rI.ortho) && (rI.camLenZ))
   zNear = (rI.winWdth / rI.camLenZ / 2.0 + pv) * rI.camLenZ;
   else
   zNear = rI.winWdth / 2.0;
   
   fogBgnZ = (rI.fogBgnZ * pv) - ((rI.camLenZ * pv) - zNear);
   fogEndZ = (rI.fogEndZ * pv) - ((rI.camLenZ * pv) - zNear);
   
   glFogf(GL_FOG_START, fogBgnZ);
   glFogf(GL_FOG_END, fogEndZ);
   glFogi(GL_FOG_MODE, GL_LINEAR);

   // clips anything behind "rI.camLenZ"
   eqn[0] = 0.0;
   eqn[1] = 0.0;
   eqn[2] = -1.0;
   eqn[3] = -rI.camLenZ * rI.viewRelativeSize;
   glClipPlane(GL_CLIP_PLANE0, eqn);
   glEnable(GL_CLIP_PLANE0);
   
   // clips anything beyound "rI.camEndZ"
   eqn[0] = 0.0;
   eqn[1] = 0.0;
   eqn[2] = 1.0;
   eqn[3] = rI.camEndZ * rI.viewRelativeSize;
   glClipPlane(GL_CLIP_PLANE1, eqn);
   glEnable(GL_CLIP_PLANE1);
   
   
   // draw mesh //
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glTexCoordPointer(2, GL_FLOAT, 0, mesh_TEXCOORD);

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, mesh_POINT);

   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4, GL_UNSIGNED_BYTE, 0, mesh_VCOLOR);

   for (i=mesh_MESHNUM; i < mesh_MESHNUM+mesh_MESHCNT; i++)
   {
      quadArraySize = mesh_QUADDATSZ[i+1] - mesh_QUADDATSZ[i];
      triArraySize = mesh_TRIDATSZ[i+1] - mesh_TRIDATSZ[i];
      quadArrayLoc = mesh_QUADDATSZ[i];
      triArrayLoc = mesh_TRIDATSZ[i];
      
      if (mesh_HIDE[i] == FALSE)
      {
         if (mesh_TEXLINKDAT[i] != -1)
         {
            glBindTexture(GL_TEXTURE_2D, mesh_TEX[mesh_TEXLINKDAT[i]]);
            glEnable(GL_TEXTURE_2D);
         }
         else
         {
            glDisable(GL_TEXTURE_2D);
         }
         
         if (quadArraySize)
         glDrawElements(GL_QUADS, quadArraySize, GL_UNSIGNED_SHORT, &mesh_QUAD[quadArrayLoc]);
         
         if (triArraySize)
         glDrawElements(GL_TRIANGLES, triArraySize, GL_UNSIGNED_SHORT, &mesh_TRI[triArrayLoc]);
      }
   }
   // end of draw mesh //
   
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_CLIP_PLANE0);
   glDisable(GL_CLIP_PLANE1);
}
