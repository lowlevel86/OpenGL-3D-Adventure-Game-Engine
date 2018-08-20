#include <stdio.h>
#include <math.h>
#include "3dEngine.h"

#define TRUE 1
#define FALSE 0


void animateTransFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT,
                        float *result_TRANS, float *position, int sequenceNum, int reset)
{
   animateRotFromTo(mesh_TRANS1, mesh_TRANS2, mesh_MESHCNT, result_TRANS, position, sequenceNum, reset);
   animateLocFromTo(mesh_TRANS1, mesh_TRANS2, mesh_MESHCNT, result_TRANS, position, sequenceNum, reset);
   animateSizeFromTo(mesh_TRANS1, mesh_TRANS2, mesh_MESHCNT, result_TRANS, position, sequenceNum, reset);
}

void animateRotFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT,
                      float *result_TRANS, float *position, int sequenceNum, int reset)
{
   int i;
   float cyclicPos;
   float percent;
   
   cyclicPos = *position;
   
   // reset the position to make it cycle
   if (fabs(cyclicPos) >= reset)
   cyclicPos = fmod(cyclicPos, reset);

   if (cyclicPos < 0.0)
   cyclicPos = reset + cyclicPos;
   
   // this if statement is here because of a rounding error:
   // 1.0 - 0.0000000000003 >= 1.0
   if (cyclicPos >= reset)
   cyclicPos = 0;
   
   // if wrong sequence number then return
   if ((cyclicPos < sequenceNum) || (cyclicPos >= sequenceNum+1))
   return;
   
   // update the position
   *position = cyclicPos;
   
   // amount to morph
   percent = cyclicPos - (int)cyclicPos;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      result_TRANS[i+ROTX] = (mesh_TRANS2[i+ROTX] - mesh_TRANS1[i+ROTX]) * percent + mesh_TRANS1[i+ROTX];
      result_TRANS[i+ROTY] = (mesh_TRANS2[i+ROTY] - mesh_TRANS1[i+ROTY]) * percent + mesh_TRANS1[i+ROTY];
      result_TRANS[i+ROTZ] = (mesh_TRANS2[i+ROTZ] - mesh_TRANS1[i+ROTZ]) * percent + mesh_TRANS1[i+ROTZ];
      
      convertRotToXyzUcRot(&result_TRANS[i+UCXH], &result_TRANS[i+UCXV],
                           &result_TRANS[i+UCYH], &result_TRANS[i+UCYV],
                           &result_TRANS[i+UCZH], &result_TRANS[i+UCZV],
                           result_TRANS[i+ROTX], result_TRANS[i+ROTY], result_TRANS[i+ROTZ]);
   }
}

void animateLocFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT,
                      float *result_TRANS, float *position, int sequenceNum, int reset)
{
   int i;
   float cyclicPos;
   float percent;
   
   cyclicPos = *position;
   
   // reset the position to make it cycle
   if (fabs(cyclicPos) >= reset)
   cyclicPos = fmod(cyclicPos, reset);

   if (cyclicPos < 0.0)
   cyclicPos = reset + cyclicPos;
   
   if (cyclicPos >= reset)
   cyclicPos = 0;
   
   // if wrong sequence number then return
   if ((cyclicPos < sequenceNum) || (cyclicPos >= sequenceNum+1))
   return;
   
   // update the position
   *position = cyclicPos;
   
   // amount to morph
   percent = cyclicPos - (int)cyclicPos;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      result_TRANS[i+LOCX] = (mesh_TRANS2[i+LOCX] - mesh_TRANS1[i+LOCX]) * percent + mesh_TRANS1[i+LOCX];
      result_TRANS[i+LOCY] = (mesh_TRANS2[i+LOCY] - mesh_TRANS1[i+LOCY]) * percent + mesh_TRANS1[i+LOCY];
      result_TRANS[i+LOCZ] = (mesh_TRANS2[i+LOCZ] - mesh_TRANS1[i+LOCZ]) * percent + mesh_TRANS1[i+LOCZ];
   }
}

void animateSizeFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT,
                       float *result_TRANS, float *position, int sequenceNum, int reset)
{
   int i;
   float cyclicPos;
   float percent;
   
   cyclicPos = *position;
   
   // reset the position to make it cycle
   if (fabs(cyclicPos) >= reset)
   cyclicPos = fmod(cyclicPos, reset);

   if (cyclicPos < 0.0)
   cyclicPos = reset + cyclicPos;
   
   if (cyclicPos >= reset)
   cyclicPos = 0;
   
   // if wrong sequence number then return
   if ((cyclicPos < sequenceNum) || (cyclicPos >= sequenceNum+1))
   return;
   
   // update the position
   *position = cyclicPos;
   
   // amount to morph
   percent = cyclicPos - (int)cyclicPos;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      result_TRANS[i+SZX] = (mesh_TRANS2[i+SZX] - mesh_TRANS1[i+SZX]) * percent + mesh_TRANS1[i+SZX];
      result_TRANS[i+SZY] = (mesh_TRANS2[i+SZY] - mesh_TRANS1[i+SZY]) * percent + mesh_TRANS1[i+SZY];
      result_TRANS[i+SZZ] = (mesh_TRANS2[i+SZZ] - mesh_TRANS1[i+SZZ]) * percent + mesh_TRANS1[i+SZZ];
      result_TRANS[i+BR] = (mesh_TRANS2[i+BR] - mesh_TRANS1[i+BR]) * percent + mesh_TRANS1[i+BR];
   }
}

void animateUcRotFromTo(float *mesh_TRANS1, float *mesh_TRANS2, int mesh_MESHCNT,
                        float *result_TRANS, float *position, int sequenceNum, int reset)
{
   int i;
   float cyclicPos;
   float percent;
   float xRot1, yRot1, zRot1;
   float xRot2, yRot2, zRot2;
   float xRot, yRot, zRot;
   float xRotResult, yRotResult, zRotResult;
   
   cyclicPos = *position;
   
   // reset the position to make it cycle
   if (fabs(cyclicPos) >= reset)
   cyclicPos = fmod(cyclicPos, reset);

   if (cyclicPos < 0.0)
   cyclicPos = reset + cyclicPos;
   
   if (cyclicPos >= reset)
   cyclicPos = 0;
   
   // if wrong sequence number then return
   if ((cyclicPos < sequenceNum) || (cyclicPos >= sequenceNum+1))
   return;
   
   // update the position
   *position = cyclicPos;
   
   // amount to morph
   percent = cyclicPos - (int)cyclicPos;
   
   for (i = 0; i < mesh_MESHCNT*TRSZ; i=i+TRSZ)
   {
      convertXyzUcRotToRot(mesh_TRANS1[i+UCXH], mesh_TRANS1[i+UCXV],
                           mesh_TRANS1[i+UCYH], mesh_TRANS1[i+UCYV],
                           mesh_TRANS1[i+UCZH], mesh_TRANS1[i+UCZV], &xRot1, &yRot1, &zRot1);
      
      convertXyzUcRotToRot(mesh_TRANS2[i+UCXH], mesh_TRANS2[i+UCXV],
                           mesh_TRANS2[i+UCYH], mesh_TRANS2[i+UCYV],
                           mesh_TRANS2[i+UCZH], mesh_TRANS2[i+UCZV], &xRot2, &yRot2, &zRot2);
      
      xRot = xRot2 - xRot1;
      yRot = yRot2 - yRot1;
      zRot = zRot2 - zRot1;
      
      
      // find the shortest travel distance around the circle
      if (xRot > 180)
      xRot = xRot - 360;
      
      if (xRot < -180)
      xRot = 360 + xRot;
      
      xRotResult = xRot * percent + xRot1;
      
      // find the shortest travel distance around the circle
      if (yRot > 180)
      yRot = yRot - 360;
      
      if (yRot < -180)
      yRot = 360 + yRot;
      
      yRotResult = yRot * percent + yRot1;
      
      // find the shortest travel distance around the circle
      if (zRot > 180)
      zRot = zRot - 360;
      
      if (zRot < -180)
      zRot = 360 + zRot;
      
      zRotResult = zRot * percent + zRot1;
      
      
      convertRotToXyzUcRot(&result_TRANS[i+UCXH], &result_TRANS[i+UCXV],
                           &result_TRANS[i+UCYH], &result_TRANS[i+UCYV],
                           &result_TRANS[i+UCZH], &result_TRANS[i+UCZV], xRotResult, yRotResult, zRotResult);
   }
}


void animateMeshFromTo(float *mesh_POINT1, int *mesh_POINTDATSZ1, int mesh_start1,
                       float *mesh_POINT2, int *mesh_POINTDATSZ2, int mesh_start2, int mesh_MESHCNT,
                       float *result_POINT, int *result_POINTDATSZ, int result_start,
                       float *position, int sequenceNum, int reset)
{
   int i;
   float cyclicPos;
   float percent;
   float *input_POINT1;
   float *input_POINT2;
   float *output_POINT;
   
   cyclicPos = *position;
   
   // reset the position to make it cycle
   if (fabs(cyclicPos) >= reset)
   cyclicPos = fmod(cyclicPos, reset);

   if (cyclicPos < 0.0)
   cyclicPos = reset + cyclicPos;
   
   if (cyclicPos >= reset)
   cyclicPos = 0;
   
   // if wrong sequence number then return
   if ((cyclicPos < sequenceNum) || (cyclicPos >= sequenceNum+1))
   return;
   
   // update the position
   *position = cyclicPos;
   
   // amount to morph
   percent = cyclicPos - (int)cyclicPos;
   
   input_POINT1 = &mesh_POINT1[mesh_POINTDATSZ1[mesh_start1]];
   input_POINT2 = &mesh_POINT2[mesh_POINTDATSZ2[mesh_start2]];
   output_POINT = &result_POINT[result_POINTDATSZ[result_start]];
   
   for (i=0; i < result_POINTDATSZ[result_start+mesh_MESHCNT]-result_POINTDATSZ[result_start]; i++)
   output_POINT[i] = (input_POINT2[i] - input_POINT1[i]) * percent + input_POINT1[i];
}

void animateColorFromTo(char *mesh_VCOLOR1, int *mesh_VCOLORDATSZ1, int mesh_start1,
                        char *mesh_VCOLOR2, int *mesh_VCOLORDATSZ2, int mesh_start2, int mesh_MESHCNT,
                        char *result_VCOLOR, int *result_VCOLORDATSZ, int result_start,
                        float *position, int sequenceNum, int reset)
{
   int i;
   float cyclicPos;
   float percent;
   char *input_VCOLOR1;
   char *input_VCOLOR2;
   char *output_VCOLOR;
   
   cyclicPos = *position;
   
   // reset the position to make it cycle
   if (fabs(cyclicPos) >= reset)
   cyclicPos = fmod(cyclicPos, reset);

   if (cyclicPos < 0.0)
   cyclicPos = reset + cyclicPos;
   
   if (cyclicPos >= reset)
   cyclicPos = 0;
   
   // if wrong sequence number then return
   if ((cyclicPos < sequenceNum) || (cyclicPos >= sequenceNum+1))
   return;
   
   // update the position
   *position = cyclicPos;
   
   // amount to morph
   percent = cyclicPos - (int)cyclicPos;
   
   input_VCOLOR1 = &mesh_VCOLOR1[mesh_VCOLORDATSZ1[mesh_start1]];
   input_VCOLOR2 = &mesh_VCOLOR2[mesh_VCOLORDATSZ2[mesh_start2]];
   output_VCOLOR = &result_VCOLOR[result_VCOLORDATSZ[result_start]];
   
   for (i=0; i < result_VCOLORDATSZ[result_start+mesh_MESHCNT]-result_VCOLORDATSZ[result_start]; i++)
   output_VCOLOR[i] = (char)(((float)(input_VCOLOR2[i] & 0xFF) - (float)(input_VCOLOR1[i] & 0xFF)) *
                      percent + (float)(input_VCOLOR1[i] & 0xFF));
}

void animateTexCoordFromTo(float *mesh_TEXCOORD1, int *mesh_TEXCOORDDATSZ1, int mesh_start1,
                           float *mesh_TEXCOORD2, int *mesh_TEXCOORDDATSZ2, int mesh_start2, int mesh_MESHCNT,
                           float *result_TEXCOORD, int *result_TEXCOORDDATSZ, int result_start,
                           float *position, int sequenceNum, int reset)
{
   int i;
   float cyclicPos;
   float percent;
   float *input_TEXCOORD1;
   float *input_TEXCOORD2;
   float *output_TEXCOORD;
   
   cyclicPos = *position;
   
   // reset the position to make it cycle
   if (fabs(cyclicPos) >= reset)
   cyclicPos = fmod(cyclicPos, reset);

   if (cyclicPos < 0.0)
   cyclicPos = reset + cyclicPos;
   
   if (cyclicPos >= reset)
   cyclicPos = 0;
   
   // if wrong sequence number then return
   if ((cyclicPos < sequenceNum) || (cyclicPos >= sequenceNum+1))
   return;
   
   // update the position
   *position = cyclicPos;
   
   // amount to morph
   percent = cyclicPos - (int)cyclicPos;
   
   input_TEXCOORD1 = &mesh_TEXCOORD1[mesh_TEXCOORDDATSZ1[mesh_start1]];
   input_TEXCOORD2 = &mesh_TEXCOORD2[mesh_TEXCOORDDATSZ2[mesh_start2]];
   output_TEXCOORD = &result_TEXCOORD[result_TEXCOORDDATSZ[result_start]];
   
   for (i=0; i < result_TEXCOORDDATSZ[result_start+mesh_MESHCNT]-result_TEXCOORDDATSZ[result_start]; i++)
   output_TEXCOORD[i] = (input_TEXCOORD2[i] - input_TEXCOORD1[i]) * percent + input_TEXCOORD1[i];
}
