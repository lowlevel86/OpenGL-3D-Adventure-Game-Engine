#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLuint **texPtrArrayGL;
int texPtrArrayCount = 0;

void addTexture(GLuint *texPtrGL, GLubyte *texData,
                int *texWidth, int *texHeight, int texCount, int optimizeTex)
{
   int i;
   int textureDataSizeCount = 0;

   // get pointer to texture
   glGenTextures(1, &*texPtrGL);
   glBindTexture(GL_TEXTURE_2D, *texPtrGL);

   
   // allocate memory for automatic texture deletion
   if (texPtrArrayCount == 0)
   texPtrArrayGL = (GLuint **)malloc(1 * sizeof(GLuint));
   else
   texPtrArrayGL = (GLuint **)realloc(texPtrArrayGL, (texPtrArrayCount+1) * sizeof(GLuint));
   
   // add "texPtrGL" to "texPtrArrayGL" to be deleted later
   texPtrArrayGL[texPtrArrayCount] = &*texPtrGL;
   texPtrArrayCount++;
   
   
   // optimize texture mapping
   if (optimizeTex)
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   }
   else
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   }
   
   
   // add the different sized textures for use
   for (i=0; i < texCount; i++)
   {
      glTexImage2D(GL_TEXTURE_2D, i, GL_RGBA, texWidth[i], texHeight[i],
                   0, GL_RGBA, GL_UNSIGNED_BYTE, &texData[textureDataSizeCount]);
      
      textureDataSizeCount += texWidth[i] * texHeight[i] * 4;
   }
}

void deleteTextures()
{
   int i;
   
   for (i=0; i < texPtrArrayCount; i++)
   glDeleteTextures(1, &*texPtrArrayGL[i]);
   
   if (texPtrArrayCount)
   free(texPtrArrayGL);
   
   texPtrArrayCount = 0;
}
