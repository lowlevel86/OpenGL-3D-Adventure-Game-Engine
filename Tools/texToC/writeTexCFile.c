#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>


void mixColors(char red1, char green1, char blue1, char alpha1,
               char red2, char green2, char blue2, char alpha2,
               char red3, char green3, char blue3, char alpha3,
               char red4, char green4, char blue4, char alpha4, char *r, char *g, char *b, char *a)
{
   *r = (char)round((float)(red1&0xFF) * 0.25 + (float)(red2&0xFF) * 0.25 + (float)(red3&0xFF) * 0.25 + (float)(red4&0xFF) * 0.25);
   //printf("r:%i ", *r);
   *g = (char)round((float)(green1&0xFF) * 0.25 + (float)(green2&0xFF) * 0.25 + (float)(green3&0xFF) * 0.25 + (float)(green4&0xFF) * 0.25);
   //printf("g:%i ", *g);
   *b = (char)round((float)(blue1&0xFF) * 0.25 + (float)(blue2&0xFF) * 0.25 + (float)(blue3&0xFF) * 0.25 + (float)(blue4&0xFF) * 0.25);
   //printf("b:%i ", *b);
   *a = (char)round((float)(alpha1&0xFF) * 0.25 + (float)(alpha2&0xFF) * 0.25 + (float)(alpha3&0xFF) * 0.25 + (float)(alpha4&0xFF) * 0.25);
   //printf("a:%i  ", *a);
}


void writeTexCFile(char *CFileName, int **imgData, int imgWidth, int imgHeight,
                                    int **maskData, int maskWidth, int maskHeight)
{
   int i, x, y, h, w;
   FILE *CFile;
   char *NewName;
   char *NameDotC;
   char *NameDotH;
   
   
   NewName = malloc(strlen(CFileName)+9);
   sprintf(NewName, "%sTexData%c",CFileName, '\0');
   
   NameDotC = malloc(strlen(NewName)+4);
   sprintf(NameDotC, "%s.c%c",NewName, '\0');
   
   CFile = fopen(NameDotC, "wb");
   
   free(NameDotC);
   
   if (!CFile)
   return;
   
   int pow2Width, pow2Height;
   
   // find the next highest width
   // closest to the power of 2
   for (i=1; i < 32; i++)
   if (!((imgWidth-1) >> i))
   break;
   
   pow2Width = 1 << i;
   
   // find the next highest height
   // closest to the power of 2
   for (i=1; i < 32; i++)
   if (!((imgHeight-1) >> i))
   break;
   
   pow2Height = 1 << i;
   
   //printf("pow2Width %i\n", pow2Width);
   //printf("pow2Height %i\n", pow2Height);
   
   // used for scaling the size of the image
   float imgRelMultiplierX, imgRelMultiplierY;
   imgRelMultiplierX = (float)(imgWidth-1) / (float)(pow2Width-1);
   imgRelMultiplierY = (float)(imgHeight-1) / (float)(pow2Height-1);
   
   // used for scaling the size of the mask
   float maskRelMultiplierX, maskRelMultiplierY;
   maskRelMultiplierX = (float)(maskWidth-1) / (float)(pow2Width-1);
   maskRelMultiplierY = (float)(maskHeight-1) / (float)(pow2Height-1);
   
   
   // write the .c file
   fprintf(CFile, "#include <GL/gl.h>\n\n");
 
 
   // add texture sizes for MIP mapping
   
   w = pow2Width;
   h = pow2Height;
   
   // find the largest length
   int largestLgth;
   
   if (w > h)
   largestLgth = w;
   else
   largestLgth = h;
   
   // find the texture count for MIP mapping
   int textureCount = 0;
   for (i=1; i <= largestLgth; i=i*2)
   textureCount++;
 
   fprintf(CFile, "//Texture Count for MIP Mapping\n");
   fprintf(CFile, "int %sTexCount = %i;\n\n", CFileName, textureCount);
 
   
   fprintf(CFile, "//Texture Sizes for MIP Mapping\n");
   
   // print the texture sizes to file
   fprintf(CFile, "int %sTexWidth[%i]={\n", CFileName, textureCount);
   for (i=1; i <= largestLgth; i=i*2)
   {
      fprintf(CFile, "%i,\n", (int)w);
      w = round((float)w / 2.0);
   }
   fprintf(CFile, "};\n\n");
   
   fprintf(CFile, "int %sTexHeight[%i]={\n", CFileName, textureCount);
   for (i=1; i <= largestLgth; i=i*2)
   {
      fprintf(CFile, "%i,\n", (int)h);
      h = round((float)h / 2.0);
   }
   fprintf(CFile, "};\n\n");
   
   // find the texture data size for MIP mapping
   int textureDataSizeForMIP = 0;
   
   w = pow2Width;
   h = pow2Height;
   
   for (i=1; i <= largestLgth; i=i*2)
   {
      textureDataSizeForMIP += w * h;
      w = round((float)w / 2.0);
      h = round((float)h / 2.0);
   }
   textureDataSizeForMIP = textureDataSizeForMIP * 4;
   
   
   fprintf(CFile, "//Texture Data for MIP Mapping\n");
   fprintf(CFile, "GLubyte %s[%i]={\n", NewName, textureDataSizeForMIP);
   
   // move the image data into a buffer with a width
   // and height that is equated with the power of 2
   char **texDataPow2Red;
   char **texDataPow2Green;
   char **texDataPow2Blue;
   char **texDataPow2Alpha;
   
   texDataPow2Red = (char **)malloc(pow2Width * sizeof(char *));
   for (i = 0; i < pow2Width; i++)
   texDataPow2Red[i] = (char *)malloc(pow2Height * sizeof(char));
   
   texDataPow2Green = (char **)malloc(pow2Width * sizeof(char *));
   for (i = 0; i < pow2Width; i++)
   texDataPow2Green[i] = (char *)malloc(pow2Height * sizeof(char));
   
   texDataPow2Blue = (char **)malloc(pow2Width * sizeof(char *));
   for (i = 0; i < pow2Width; i++)
   texDataPow2Blue[i] = (char *)malloc(pow2Height * sizeof(char));
   
   texDataPow2Alpha = (char **)malloc(pow2Width * sizeof(char *));
   for (i = 0; i < pow2Width; i++)
   texDataPow2Alpha[i] = (char *)malloc(pow2Height * sizeof(char));
   
   
   for (y=0; y < pow2Height; y++)
   for (x=0; x < pow2Width; x++)
   {
      texDataPow2Red[x][y] = (char)((imgData[(int)round(x*imgRelMultiplierX)]
                           [(int)round(((pow2Height-1)-y)*imgRelMultiplierY)] & 0xFF0000) >> 16);
      texDataPow2Green[x][y] = (char)((imgData[(int)round(x*imgRelMultiplierX)]
                             [(int)round(((pow2Height-1)-y)*imgRelMultiplierY)] & 0x00FF00) >> 8);
      texDataPow2Blue[x][y] = (char)(imgData[(int)round(x*imgRelMultiplierX)]
                           [(int)round(((pow2Height-1)-y)*imgRelMultiplierY)] & 0x0000FF);
      
      if (maskWidth)
      texDataPow2Alpha[x][y] = (char)(maskData[(int)round(x*maskRelMultiplierX)]
                             [(int)round(((pow2Height-1)-y)*maskRelMultiplierY)] & 0x0000FF);
      else
      texDataPow2Alpha[x][y] = (char)0x0000FF;
   }
   
   /*
   //FOR DEBUGGING AND TESTING
   FILE *fp;
   fp = fopen("test.ppm", "wb");
   fprintf(fp, "P6\n");
   fprintf(fp, "%d %d\n",pow2Width,pow2Height);
   fprintf(fp, "%d\n",255);
   for (y = 0; y < pow2Height; y++)
   for (x = 0; x < pow2Width; x++)
   {
      fprintf(fp, "%c", texDataPow2Red[x][y]);
      fprintf(fp, "%c", texDataPow2Green[x][y]);
      fprintf(fp, "%c", texDataPow2Blue[x][y]);
   }
   fclose(fp);
   */
   
   // print the different size textures to file
   for (i=0; i < textureCount; i++)
   {
      for (y=0; y < pow2Height; y++)
      for (x=0; x < pow2Width; x++)
      {
         fprintf(CFile, "%i, ", (unsigned char)texDataPow2Red[x][y]);
         fprintf(CFile, "%i, ", (unsigned char)texDataPow2Green[x][y]);
         fprintf(CFile, "%i, ", (unsigned char)texDataPow2Blue[x][y]);
         
         if ((unsigned char)texDataPow2Alpha[x][y] > (unsigned char)0x7F)
         fprintf(CFile, "%i,\n", 0xFF);
         else
         fprintf(CFile, "%i,\n", 0x0);
      }
      
      pow2Width = round((float)pow2Width/2.0);
      pow2Height = round((float)pow2Height/2.0);
      
      for (y=0; y < pow2Height; y++)
      for (x=0; x < pow2Width; x++)
      mixColors(texDataPow2Red[x*2][y*2], texDataPow2Green[x*2][y*2], texDataPow2Blue[x*2][y*2], texDataPow2Alpha[x*2][y*2],
                texDataPow2Red[x*2+1][y*2], texDataPow2Green[x*2+1][y*2], texDataPow2Blue[x*2+1][y*2], texDataPow2Alpha[x*2+1][y*2],
                texDataPow2Red[x*2+1][y*2+1], texDataPow2Green[x*2+1][y*2+1], texDataPow2Blue[x*2+1][y*2+1], texDataPow2Alpha[x*2+1][y*2+1],
                texDataPow2Red[x*2][y*2+1], texDataPow2Green[x*2][y*2+1], texDataPow2Blue[x*2][y*2+1], texDataPow2Alpha[x*2][y*2+1],
                &texDataPow2Red[x][y], &texDataPow2Green[x][y], &texDataPow2Blue[x][y], &texDataPow2Alpha[x][y]);
      
      fprintf(CFile, "//end of texture %i\n\n", i);
   }

   for (i = 0; i < pow2Width; i++)
   free(texDataPow2Red[i]);
   free(texDataPow2Red);
   
   for (i = 0; i < pow2Width; i++)
   free(texDataPow2Green[i]);
   free(texDataPow2Green);
   
   for (i = 0; i < pow2Width; i++)
   free(texDataPow2Blue[i]);
   free(texDataPow2Blue);
   
   for (i = 0; i < pow2Width; i++)
   free(texDataPow2Alpha[i]);
   free(texDataPow2Alpha);
   
   fprintf(CFile, "};\n");
   
   fclose(CFile);
   
   
   // write the .h file
   NameDotH = malloc(strlen(NewName)+4);
   sprintf(NameDotH, "%s.h%c",NewName, '\0');
   
   CFile = fopen(NameDotH, "wb");
   
   free(NameDotH);
   
   if (!CFile)
   return;
   
   fprintf(CFile, "extern int %sTexCount;\n", CFileName);
   fprintf(CFile, "extern int %sTexWidth[%i];\n", CFileName, textureCount);
   fprintf(CFile, "extern int %sTexHeight[%i];\n", CFileName, textureCount);
   fprintf(CFile, "extern GLubyte %s[%i];\n", NewName, pow2Width * pow2Height * 4);
   fprintf(CFile, "GLuint %sTexPtrGL;\n", CFileName);
   
   fclose(CFile);
   
   free(NewName);
}
