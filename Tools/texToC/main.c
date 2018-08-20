#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readWriteBmpFile.h"
#include "writeTexCFile.h"

int main(int argc, char **argv)
{
   int i;
   int bpp;
   int **imgData;
   int imgDataAllocated = 0;
   int imgWidth = 0, imgHeight = 0;
   int **maskData;
   int maskDataAllocated = 0;
   int maskWidth = 0, maskHeight = 0;
   
   if ((argc <= 1) || (argc > 3))
   {
      printf("Usage: texToC [Texture Bmp File] [Mask Bmp File]\n");
      return 0;
   }
   
   // get image size
   getBmpFileDataSz(argv[1], &imgWidth, &imgHeight, &bpp);
   
   // allocate memory for the image
   if (bpp)
   {
      imgData = (int **)malloc(imgWidth * sizeof(int *));
      for (i = 0; i < imgWidth; i++)
      imgData[i] = (int *)malloc(imgHeight * sizeof(int));
      imgDataAllocated = 1;
   }
   
   // read the image
   readBmpFile(argv[1], imgData);
   
   
   if (argc == 3)
   {
      // get mask size
      getBmpFileDataSz(argv[2], &maskWidth, &maskHeight, &bpp);
      
      // allocate memory for the mask
      if (bpp)
      {
         maskData = (int **)malloc(maskWidth * sizeof(int *));
         for (i = 0; i < maskWidth; i++)
         maskData[i] = (int *)malloc(maskHeight * sizeof(int));
         maskDataAllocated = 1;
      }
      
      // read the image mask
      readBmpFile(argv[2], maskData);
   }
   
   
   if (imgWidth)
   {
      // remove ".bmp"
      argv[1][strlen(argv[1])-4] = 0;
      
      // write .c file
      writeTexCFile(argv[1], imgData, imgWidth, imgHeight, maskData, maskWidth, maskHeight);
   }

   /*
   //for testing
   // make pics with different widths
   char nameText[256];
   
   for (i=0; i < 6; i++)
   {
      sprintf(nameText, "%i.bmp", i); 
      writeBmpFile(nameText, imgData, imgWidth-i, imgHeight, 16);
   }
   */
/*
//for testing
   FILE *fp;
   fp = fopen("0.ppm", "wb");
   fprintf(fp, "P6\n");
   fprintf(fp, "%d %d\n",imgWidth,imgHeight);
   fprintf(fp, "%d\n",255);
   int x, y;
   for (y = 0; y < imgHeight; y++)
   for (x = 0; x < imgWidth; x++)
   {
      fprintf(fp, "%c", (char)((imgData[x][y] & 0xFF0000) >> 16));
      fprintf(fp, "%c", (char)((imgData[x][y] & 0x00FF00) >> 8));
      fprintf(fp, "%c", (char)imgData[x][y] & 0x0000FF);
   }
   fclose(fp);
   */
   if (imgDataAllocated)
   {
      for (i = 0; i < imgWidth; i++)
      free(imgData[i]);
      free(imgData);
   }

   if (maskDataAllocated)
   {
      for (i = 0; i < maskWidth; i++)
      free(maskData[i]);
      free(maskData);
   }

   return 0;
}
