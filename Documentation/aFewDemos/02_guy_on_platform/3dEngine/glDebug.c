#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "3dEngine.h"

#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642

// print to screen
void printfScrn(float x, float y, float size, int color,
                struct rendrInfo rI, char *dbgString, ...)
{
   va_list arg;
   char dbgMsg[1024];
   float undoPerspctv = 1.0;
   float xSize, ySize, xLoc, yLoc, zLoc;
   float xScrnOffset, yScrnOffset;
   float xCharOffset, yCharOffset;
   float thickness;
   
   va_start(arg, dbgString);
   vsprintf(dbgMsg, dbgString, arg);
   va_end(arg);
   
   // keep the text the same size when close to the camera lens
   if (!rI.ortho)
   undoPerspctv = rI.perspctv / (rI.perspctv + (rI.camLenZ + 10));
   
   // move the text location from the middle to the upper left side
   xScrnOffset = rI.winWdth / 2.0;
   yScrnOffset = rI.winHght / 2.0;
   
   xSize = size / undoPerspctv * 2.0/3;
   ySize = size / undoPerspctv;
   xLoc = (x - xScrnOffset) / undoPerspctv;
   yLoc = (y + yScrnOffset) / undoPerspctv;
   zLoc = -(rI.camLenZ + 10) * rI.viewRelativeSize;
   xCharOffset = size / undoPerspctv * 2.0/3;
   yCharOffset = -size / undoPerspctv;
   thickness = size * 1.0/30;
   
   drawAscii(dbgMsg, xSize, ySize,
             xLoc + xCharOffset,
             yLoc + yCharOffset,
             zLoc, 0, 0, 0, thickness, color, 0);
}

void drawPt(float x, float y, float z, int color, float size)
{
   GLushort sequence[1] = {0};
   float coordinate[3];

   glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
   glPointSize(size);
   
   coordinate[0] = x;
   coordinate[1] = y;
   coordinate[2] = z;

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, coordinate);
   
   glDisableClientState(GL_COLOR_ARRAY);
   glColor4f((color&0xFF)/255.0, ((color&0xFF00)>>8)/255.0, ((color&0xFF0000)>>16)/255.0, 1.0);

   glDrawElements(GL_POINTS, 1, GL_UNSIGNED_SHORT, sequence);
}

void drawLine(float x1, float y1, float z1,
              float x2, float y2, float z2, int color, float size)
{
   GLushort sequence[2] = {0, 1};
   float coordinate[6];
   
   glLineWidth(size);
   
   coordinate[0] = x1;
   coordinate[1] = y1;
   coordinate[2] = z1;

   coordinate[3] = x2;
   coordinate[4] = y2;
   coordinate[5] = z2;

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, coordinate);
   
   glDisableClientState(GL_COLOR_ARRAY);
   glColor4f((color&0xFF)/255.0, ((color&0xFF00)>>8)/255.0, ((color&0xFF0000)>>16)/255.0, 1.0);

   glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, sequence);
}

void drawTransBox(float *mesh_TRANS,  int mesh_MESHCNT, float *meshView_TRANS,
                  float camLenseSz, float thickness, int color, struct rendrInfo rI)
{
   int i, transInc;

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
   
   
   // draw transformation box //
   int boxDataSize[2] = {0, 24};
   float box_POINT[24];
   float box_STATICPOINT[24]={
   1.0, 1.0, -1.0,
   1.0, -1.0, -1.0,
   -1.0, -1.0, -1.0,
   -1.0, 1.0, -1.0,
   1.0, 1.0, 1.0,
   1.0, -1.0, 1.0,
   -1.0, -1.0, 1.0,
   -1.0, 1.0, 1.0,
   };

   GLushort box_LINE[24]={
   0, 1,
   1, 2,
   2, 3,
   3, 0,
   4, 7,
   7, 6,
   6, 5,
   5, 4,
   0, 4,
   5, 1,
   6, 2,
   7, 3,
   };

   
   glLineWidth(thickness);

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, box_POINT);
   
   glDisableClientState(GL_COLOR_ARRAY);
   glColor4f((color&0xFF)/255.0, ((color&0xFF00)>>8)/255.0, ((color&0xFF0000)>>16)/255.0, 1.0);

   for (transInc=0; transInc < mesh_MESHCNT*TRSZ; transInc+=TRSZ)
   {
      for (i=0; i < 24; i+=3)
      {
         box_POINT[i+0] = box_STATICPOINT[i+0] * mesh_TRANS[transInc+SZX];
         box_POINT[i+1] = box_STATICPOINT[i+1] * mesh_TRANS[transInc+SZY];
         box_POINT[i+2] = box_STATICPOINT[i+2] * mesh_TRANS[transInc+SZZ];
         
         applyXyzUcRotToPoint(mesh_TRANS[transInc+UCXH], mesh_TRANS[transInc+UCXV],
                              mesh_TRANS[transInc+UCYH], mesh_TRANS[transInc+UCYV],
                              mesh_TRANS[transInc+UCZH], mesh_TRANS[transInc+UCZV],
                              &box_POINT[i+0], &box_POINT[i+1], &box_POINT[i+2]);
         
         box_POINT[i+0] = box_POINT[i+0] + mesh_TRANS[transInc+LOCX];
         box_POINT[i+1] = box_POINT[i+1] + mesh_TRANS[transInc+LOCY];
         box_POINT[i+2] = box_POINT[i+2] + mesh_TRANS[transInc+LOCZ];
      }
      
      applyMeshViewRotLocSz(box_POINT, boxDataSize, 0, 1, meshView_TRANS, camLenseSz, rI);
      
      glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, box_LINE);
   }
   // end of draw transformation box //
   
   glDisable(GL_CLIP_PLANE0);
   glDisable(GL_CLIP_PLANE1);
}

void drawXyzAxis(float *mesh_TRANS,  int mesh_MESHCNT, float *meshView_TRANS,
                 float camLenseSz, float thickness, struct rendrInfo rI)
{
   int i, transInc;

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
   
   
   // draw xyz Axis //
   int triAxisDataSize[2] = {0, 18};
   float triAxis_POINT[18];
   float triAxis_STATICPOINT[18]={
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0,
   1.5, 0.0, 0.0,
   0.0, 1.5, 0.0,
   0.0, 0.0, 1.5,
   };
   
   GLushort triAxis_LINE[6]={
   0, 3,
   1, 4,
   2, 5,
   };
   
   char triAxisColorData[18] = {
   0xFF, 0x00, 0x00,
   0x00, 0xFF, 0x00,
   0x00, 0x00, 0xFF,
   0xFF, 0x00, 0x00,
   0x00, 0xFF, 0x00,
   0x00, 0x00, 0xFF,
   };
   
   
   glLineWidth(thickness);

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, triAxis_POINT);
   
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3, GL_UNSIGNED_BYTE, 0, triAxisColorData);
   
   for (transInc=0; transInc < mesh_MESHCNT*TRSZ; transInc+=TRSZ)
   {
      for (i=0; i < 18; i+=3)
      {
         triAxis_POINT[i+0] = triAxis_STATICPOINT[i+0] * mesh_TRANS[transInc+SZX];
         triAxis_POINT[i+1] = triAxis_STATICPOINT[i+1] * mesh_TRANS[transInc+SZY];
         triAxis_POINT[i+2] = triAxis_STATICPOINT[i+2] * mesh_TRANS[transInc+SZZ];
         
         applyXyzUcRotToPoint(mesh_TRANS[transInc+UCXH], mesh_TRANS[transInc+UCXV],
                              mesh_TRANS[transInc+UCYH], mesh_TRANS[transInc+UCYV],
                              mesh_TRANS[transInc+UCZH], mesh_TRANS[transInc+UCZV],
                              &triAxis_POINT[i+0], &triAxis_POINT[i+1], &triAxis_POINT[i+2]);
         
         triAxis_POINT[i+0] = triAxis_POINT[i+0] + mesh_TRANS[transInc+LOCX];
         triAxis_POINT[i+1] = triAxis_POINT[i+1] + mesh_TRANS[transInc+LOCY];
         triAxis_POINT[i+2] = triAxis_POINT[i+2] + mesh_TRANS[transInc+LOCZ];
      }
      
      applyMeshViewRotLocSz(triAxis_POINT, triAxisDataSize, 0, 1, meshView_TRANS, camLenseSz, rI);
      
      glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, triAxis_LINE);
   }
   // end of draw xyz Axis //
   
   glDisable(GL_CLIP_PLANE0);
   glDisable(GL_CLIP_PLANE1);
}

void drawBounds(float *mesh_TRANS,  int mesh_MESHCNT, float *meshView_TRANS,
                float camLenseSz, float thickness, int color, struct rendrInfo rI)
{
   int i, transInc;

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
   
   
   // draw boundary box //
   int boxDataSize[2] = {0, 24};
   float box_POINT[24];
   float box_STATICPOINT[24]={
   1.0, 1.0, -1.0,
   1.0, -1.0, -1.0,
   -1.0, -1.0, -1.0,
   -1.0, 1.0, -1.0,
   1.0, 1.0, 1.0,
   1.0, -1.0, 1.0,
   -1.0, -1.0, 1.0,
   -1.0, 1.0, 1.0,
   };

   GLushort box_LINE[24]={
   0, 1,
   1, 2,
   2, 3,
   3, 0,
   4, 7,
   7, 6,
   6, 5,
   5, 4,
   0, 4,
   5, 1,
   6, 2,
   7, 3,
   };

   
   glLineWidth(thickness);

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, box_POINT);
   
   glDisableClientState(GL_COLOR_ARRAY);
   glColor4f((color&0xFF)/255.0, ((color&0xFF00)>>8)/255.0, ((color&0xFF0000)>>16)/255.0, 1.0);

   for (transInc=0; transInc < mesh_MESHCNT*TRSZ; transInc+=TRSZ)
   {
      for (i=0; i < 24; i+=3)
      {
         box_POINT[i+0] = box_STATICPOINT[i+0] * mesh_TRANS[transInc+BR] + mesh_TRANS[transInc+LOCX];
         box_POINT[i+1] = box_STATICPOINT[i+1] * mesh_TRANS[transInc+BR] + mesh_TRANS[transInc+LOCY];
         box_POINT[i+2] = box_STATICPOINT[i+2] * mesh_TRANS[transInc+BR] + mesh_TRANS[transInc+LOCZ];
      }
      
      applyMeshViewRotLocSz(box_POINT, boxDataSize, 0, 1, meshView_TRANS, camLenseSz, rI);
      
      glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, box_LINE);
   }
   // end of draw boundary box //
   
   glDisable(GL_CLIP_PLANE0);
   glDisable(GL_CLIP_PLANE1);
}

void screenShot(char *dirLoc, int numberOfShots)
{
   int x, y;
   static int frameCnt = 0;
   unsigned char *pix;
   char scrnShotFileName[2048];
   GLint viewPortFrameWH[4];
   int windowWdth, windowHght;

   if (frameCnt >= numberOfShots)
   return;

   glGetIntegerv(GL_VIEWPORT, viewPortFrameWH);
   
   windowWdth = viewPortFrameWH[2] + viewPortFrameWH[0]*2;
   windowHght = viewPortFrameWH[3] + viewPortFrameWH[1]*2;
   
   int rowSize = windowWdth * 3 + windowWdth % 4;
   
   pix = (unsigned char *)malloc(rowSize * windowHght);
   
   glReadPixels(0, 0, windowWdth, windowHght, GL_RGB, GL_UNSIGNED_BYTE, pix);
   
   FILE *fp;
   sprintf(scrnShotFileName, "%s%i.ppm", dirLoc, frameCnt);
   fp = fopen(scrnShotFileName, "wb");
   
   if (fp)
   {
      fprintf(fp, "P6\n");
      fprintf(fp, "%d %d\n", windowWdth, windowHght);
      fprintf(fp, "%d\n",255);
      
      for (y = windowHght-1; y >= 0; y--)
      for (x = 0; x < windowWdth; x++)
      {
         fprintf(fp, "%c", (char)pix[rowSize*y+x*3+0]);
         fprintf(fp, "%c", (char)pix[rowSize*y+x*3+1]);
         fprintf(fp, "%c", (char)pix[rowSize*y+x*3+2]);
      }
      
      fclose(fp);
   }
   
   free(pix);

   frameCnt++;
}

// use filePtr = fopen("file.dat", "w+b"); for *filePtr
// and fclose(filePtr); when done
void eventRecToFile(void **vars, int varCnt, FILE *filePtr)
{
   int i;
   char *varsBytes;
   
   if (!filePtr)
   return;
   
   varsBytes = (char *)vars;
   
   for (i=0; i < varCnt*sizeof(void *); i++)
   fputc(varsBytes[i], filePtr);
}

// use filePtr = fopen("file.dat", "r+b"); for *filePtr
// and fclose(filePtr); when done
void eventPlayFromFile(void **vars, int varCnt, FILE *filePtr)
{
   int i;
   char *varsBytes;
   
   if (!filePtr)
   return;
   
   if (feof(filePtr))// return if end of file
   return;
   
   varsBytes = (char *)vars;
   
   for (i=0; i < varCnt*sizeof(void *); i++)
   {
      varsBytes[i] = fgetc(filePtr);
      
      if (feof(filePtr))// break if end of file
      break;
   }
}
