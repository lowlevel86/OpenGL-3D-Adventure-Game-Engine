#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// read a bmp file into an one integer per pixel double array
void readBmpFile(char *bmpFileName, int **rawImgData)
{
   struct stat stat_p;
   FILE *bmpFile;
   char *bmpData;
   int x, y, i, cntDown;
   int startOfBmpData = 0;
   
   int xSize = 0;
   int ySize = 0;
   int bitsPerPix = 0;
   
   int colorTable[256];
   
   // does the file exist
   if (-1 == stat(bmpFileName, &stat_p))
   return;
   
   // allocate memory for bmp file
   bmpData = (char *)malloc(stat_p.st_size);
   
   // open file for read
   bmpFile = fopen(bmpFileName,"rb");
   if (!bmpFile)
   return;
   
   // read file data to buffer
   fread(bmpData, sizeof(char), stat_p.st_size, bmpFile);
   
   fclose(bmpFile);
   
   
   // find where the image data begins
   if (10 < stat_p.st_size)
   startOfBmpData = startOfBmpData | (bmpData[10] & 0x000000FF);
   
   if (11 < stat_p.st_size)
   startOfBmpData = startOfBmpData | ((bmpData[11] & 0x000000FF) << 8);
   
   if (12 < stat_p.st_size)
   startOfBmpData = startOfBmpData | ((bmpData[12] & 0x000000FF) << 16);
   
   if (13 < stat_p.st_size)
   startOfBmpData = startOfBmpData | ((bmpData[13] & 0x000000FF) << 24);
   
   //printf("startOfBmpData %i\n", startOfBmpData);
   
   
   
   
   // get the width of the image
   if (18 < stat_p.st_size)
   xSize = xSize | (bmpData[18] & 0x000000FF);
   
   if (19 < stat_p.st_size)
   xSize = xSize | ((bmpData[19] & 0x000000FF) << 8);
   
   if (20 < stat_p.st_size)
   xSize = xSize | ((bmpData[20] & 0x000000FF) << 16);
   
   if (21 < stat_p.st_size)
   xSize = abs(xSize | ((bmpData[21] & 0x000000FF) << 24));
   
   //printf("xSize %i\n", xSize);
   
   // get the height of the image
   if (22 < stat_p.st_size)
   ySize = ySize | (bmpData[22] & 0x000000FF);
   
   if (23 < stat_p.st_size)
   ySize = ySize | ((bmpData[23] & 0x000000FF) << 8);
   
   if (24 < stat_p.st_size)
   ySize = ySize | ((bmpData[24] & 0x000000FF) << 16);
   
   if (25 < stat_p.st_size)
   ySize = abs(ySize | ((bmpData[25] & 0x000000FF) << 24));
   
   //printf("ySize %i\n", ySize);
   
   // get the number of bits per pixel
   if (28 < stat_p.st_size)
   bitsPerPix = bitsPerPix | (bmpData[28] & 0x000000FF);
   
   if (29 < stat_p.st_size)
   bitsPerPix = bitsPerPix | ((bmpData[29] & 0x000000FF) << 8);
   
   
   // to use for the count down
   // inside the memory array
   cntDown = stat_p.st_size - 1;
   
   int pix16bit;
   int colorTableCnt = 0;
   int bitShift;
   
   if (bitsPerPix >= 16)
   {
      // read 24 bpp image
      if (bitsPerPix == 24)
      for (y=0; y < ySize; y++)
      for (x=xSize-1; x >= 0; x--)
      {
         if (x == xSize-1)
         cntDown = cntDown - xSize % 4;// subtract offset
         
         rawImgData[x][y] = (0xFF & bmpData[cntDown-0]) << 16 |
                           ((0xFF & bmpData[cntDown-1]) << 8) |
                            (0xFF & bmpData[cntDown-2]);
         cntDown = cntDown - 3;
      }
      
      // read 16 bpp image
      if (bitsPerPix == 16)
      for (y=0; y < ySize; y++)
      for (x=xSize-1; x >= 0; x--)
      {
         if (x == xSize-1)
         cntDown = cntDown - (xSize % 2) * 2;// subtract offset
         
         pix16bit = ((0xFF & bmpData[cntDown-0]) << 8) |
                     (0xFF & bmpData[cntDown-1]);
         rawImgData[x][y] = ((pix16bit >> 10) & 0x1f) << (3+16) |
                           (((pix16bit >> 5) & 0x1f) << (3+8)) |
                            ((pix16bit & 0x1f) << 3);
         cntDown = cntDown - 2;
      }
   }
   //rawImgData[x][y] = (pix16bit >> 11) << (3+16) | (((pix16bit >> 5) & 0x3f) << (3+7)) | ((pix16bit & 0x1f) << 3);
   
   
   if (bitsPerPix <= 8)
   {
      // read 8 bpp image
      if (bitsPerPix == 8)
      {
         for (i=0; i < 256; i++)
         {
            colorTable[i] = (0xFF & bmpData[54+colorTableCnt+2]) << 16 |
                           ((0xFF & bmpData[54+colorTableCnt+1]) << 8) |
                            (0xFF & bmpData[54+colorTableCnt+0]);
            colorTableCnt = colorTableCnt + 4;
         }
         
         for (y=0; y < ySize; y++)
         for (x=xSize-1; x >= 0; x--)
         {
            // subtract offset
            if (x == xSize-1)
            cntDown = cntDown - (3-((xSize-1)%4));
            
            rawImgData[x][y] = colorTable[0xFF & bmpData[cntDown]];
            cntDown--;
         }
      }
      
      int flipFlop = 0;
      int offsetFlipFlop = 0;
      
      // read 4 bpp image
      if (bitsPerPix == 4)
      {
         for (i=0; i < 16; i++)
         {
            colorTable[i] = (0xFF & bmpData[54+colorTableCnt+2]) << 16 |
                           ((0xFF & bmpData[54+colorTableCnt+1]) << 8) |
                            (0xFF & bmpData[54+colorTableCnt+0]);
            colorTableCnt = colorTableCnt + 4;
         }
         
         
         for (y=0; y < ySize; y++)
         for (x=xSize-1; x >= 0; x--)
         {
            // add offset
            if (x == xSize-1)
            cntDown = cntDown - (3-(int)(((xSize-1)%8)/2));//1=2,2=3,3=3,4=0,5=0,6=1,7=1,8=2
            
            // add extra offset
            if (x == xSize-1)
            if (xSize % 2)// if odd
            offsetFlipFlop = !offsetFlipFlop;
            
            if (!flipFlop)
            {
               if (!offsetFlipFlop)
               rawImgData[x][y] = colorTable[bmpData[cntDown] & 0xF];
               else
               rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 4) & 0xF];
               
               if (offsetFlipFlop)
               cntDown--;
            }
            
            if (flipFlop)
            {
               if (offsetFlipFlop)
               rawImgData[x][y] = colorTable[bmpData[cntDown] & 0xF];
               else
               rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 4) & 0xF];
               
               if (!offsetFlipFlop)
               cntDown--;
            }
            
            flipFlop = !flipFlop;
         }
      }
      
      // read 1 bpp image
      if (bitsPerPix == 1)
      {
         for (i=0; i < 2; i++)
         {
            colorTable[i] = (0xFF & bmpData[54+colorTableCnt+2]) << 16 |
                           ((0xFF & bmpData[54+colorTableCnt+1]) << 8) |
                            (0xFF & bmpData[54+colorTableCnt+0]);
            colorTableCnt = colorTableCnt + 4;
         }
         
         i = 0;
         for (y=0; y < ySize; y++)
         for (x=xSize-1; x >= 0; x--)
         {
            // subtract offset
            if (x == xSize-1)
            {
               i = i + 31-(xSize-1)%32;
               
               if (31-(xSize-1)%32 >= 8)
               cntDown--;
               
               if (31-(xSize-1)%32 >= 16)
               cntDown--;
               
               if (31-(xSize-1)%32 >= 24)
               cntDown--;
            }
            
            bitShift = i % 8;
            
            if (bitShift < 4)
            {
               if (bitShift < 2)
               {
                  if (bitShift == 0)
                  rawImgData[x][y] = colorTable[bmpData[cntDown] & 1];
                  
                  if (bitShift == 1)
                  rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 1) & 1];
               }
               else
               {
                  if (bitShift == 2)
                  rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 2) & 1];
                  
                  if (bitShift == 3)
                  rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 3) & 1];
               }
            }
            else
            {
               if (bitShift < 6)
               {
                  if (bitShift == 4)
                  rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 4) & 1];
                  
                  if (bitShift == 5)
                  rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 5) & 1];
               }
               else
               {
                  if (bitShift == 6)
                  rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 6) & 1];
                  
                  if (bitShift == 7)
                  rawImgData[x][y] = colorTable[(bmpData[cntDown] >> 7) & 1];
                  
                  if (bitShift == 7)
                  cntDown--;
               }
            }
            i++;
         }
      }
   }
   
   if (bmpData)
   free(bmpData);
}


void getBmpFileDataSz(char *bmpFileName, int *xSize, int *ySize, int *bitsPerPix)
{
   struct stat stat_p;
   FILE *bmpFile;
   int c;
   
   *xSize = 0;
   *ySize = 0;
   *bitsPerPix = 0;
   
   // does the file exist
   if (-1 == stat(bmpFileName, &stat_p))
   return;
   
   // open file for read
   bmpFile = fopen(bmpFileName,"rb");
   
   if (!bmpFile)
   return;
   
   
   // get the width of the image
   fseek(bmpFile, 18, SEEK_CUR);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *xSize = *xSize | (c & 0x000000FF);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *xSize = *xSize | ((c & 0x000000FF) << 8);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *xSize = *xSize | ((c & 0x000000FF) << 16);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *xSize = abs(*xSize | ((c & 0x000000FF) << 24));

   
   // get the height of the image
   c = fgetc(bmpFile);
   if (c != EOF)
   *ySize = *ySize | (c & 0x000000FF);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *ySize = *ySize | ((c & 0x000000FF) << 8);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *ySize = *ySize | ((c & 0x000000FF) << 16);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *ySize = abs(*ySize | ((c & 0x000000FF) << 24));

   
   // get the number of bits per pixel
   fseek(bmpFile, 2, SEEK_CUR);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *bitsPerPix = *bitsPerPix | (c & 0x000000FF);
   
   c = fgetc(bmpFile);
   if (c != EOF)
   *bitsPerPix = *bitsPerPix | ((c & 0x000000FF) << 8);
   
   
   fclose(bmpFile);
}


void writeBmpFile(char *bmpFileName, int **rawImgData, int xSize, int ySize, int bitsPerPix)
{
   int i, x, y;
   int bmpDataSize;
   FILE *bmpFile;
   int colorTable[256];
   int colorTableCnt;
   
   
   bmpFile = fopen(bmpFileName, "wb");
   if (!bmpFile)
   return;
   
   
   fprintf(bmpFile, "%s", "BM");
   
   bmpDataSize = xSize * ySize * ((float)bitsPerPix / 8);
   
   
   // write 24 bits per pixel bmp file
   if (bitsPerPix == 24)
   {
      // file size
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) >> 24 & 0xFF));
      
      // reserved1 and 2
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // file offset to pixel array
      fprintf(bmpFile, "%c", 0x36);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      
      // dib header size
      fprintf(bmpFile, "%c", 0x28);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      
      // image width
      fprintf(bmpFile, "%c", (char)(xSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 24 & 0xFF));
      
      // image height
      fprintf(bmpFile, "%c", (char)(ySize & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 24 & 0xFF));
      
      // number of planes
      fprintf(bmpFile, "%c", 1);
      fprintf(bmpFile, "%c", 0);
      
      // number of bits per pixel
      fprintf(bmpFile, "%c", 24);
      fprintf(bmpFile, "%c", 0);
      
      // compression
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // image size
      fprintf(bmpFile, "%c", (char)(bmpDataSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 24 & 0xFF));
      
      // x pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // y pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // colors in color table
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // important color count
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // image data
      for (y = ySize-1; y >= 0; y--)
      for (x = 0; x < xSize; x++)
      {
         fprintf(bmpFile, "%c", (char)rawImgData[x][y] & 0x0000FF);
         fprintf(bmpFile, "%c", (char)((rawImgData[x][y] & 0x00FF00) >> 8));
         fprintf(bmpFile, "%c", (char)((rawImgData[x][y] & 0xFF0000) >> 16));
         
         // print offset bytes
         if (x == xSize-1)
         for (i=0; i < xSize % 4; i++)
         fprintf(bmpFile, "%c", (char)0);
      }
   }
   
   
   // write 16 bits per pixel bmp file
   if (bitsPerPix == 16)
   {
      // file size
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36) >> 24 & 0xFF));
      
      // reserved1 and 2
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // file offset to pixel array
      fprintf(bmpFile, "%c", 0x36);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      
      // dib header size
      fprintf(bmpFile, "%c", 0x28);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      
      // image width
      fprintf(bmpFile, "%c", (char)(xSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 24 & 0xFF));
      
      // image height
      fprintf(bmpFile, "%c", (char)(ySize & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 24 & 0xFF));
      
      // number of planes
      fprintf(bmpFile, "%c", 1);
      fprintf(bmpFile, "%c", 0);
      
      // number of bits per pixel
      fprintf(bmpFile, "%c", 16);
      fprintf(bmpFile, "%c", 0);
      
      // compression
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // image size
      fprintf(bmpFile, "%c", (char)(bmpDataSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 24 & 0xFF));
      
      // x pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // y pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // colors in color table
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // important color count
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      int r, g, b;
      int pix16bit;
      
      
      // image data
      for (y=ySize-1; y >= 0; y--)
      for (x=0; x < xSize; x++)
      {
         r = (rawImgData[x][y] & 0xFF0000) >> 16;
         g = (rawImgData[x][y] & 0x00FF00) >> 8;
         b = rawImgData[x][y] & 0x0000FF;
         
         pix16bit = (r >> 3 << 10) + (g >> 3 << 5) + (b >> 3);
         
         fprintf(bmpFile, "%c", (char)(pix16bit & 0x0000FF));
         fprintf(bmpFile, "%c", (char)((pix16bit & 0x00FF00) >> 8));
         
         if (x == xSize-1)
         for (i=0; i < (xSize % 2) * 2; i++)
         fprintf(bmpFile, "%c", (char)0x0);// add offset
      }
   }


   // write 8 bits per pixel bmp file
   if (bitsPerPix == 8)
   {
      // file size
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 256 * 4) & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 256 * 4) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 256 * 4) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 256 * 4) >> 24 & 0xFF));
      
      // reserved1 and 2
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // file offset to pixel array
      fprintf(bmpFile, "%c", (char)((0x36 + 256 * 4) & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 256 * 4) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 256 * 4) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 256 * 4) >> 24 & 0xFF));
      
      // dib header size
      fprintf(bmpFile, "%c", 0x28);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      
      // image width
      fprintf(bmpFile, "%c", (char)(xSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 24 & 0xFF));
      
      // image height
      fprintf(bmpFile, "%c", (char)(ySize & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 24 & 0xFF));
      
      // number of planes
      fprintf(bmpFile, "%c", 1);
      fprintf(bmpFile, "%c", 0);
      
      // number of bits per pixel
      fprintf(bmpFile, "%c", 8);
      fprintf(bmpFile, "%c", 0);
      
      // compression
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // image size
      fprintf(bmpFile, "%c", (char)(bmpDataSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 24 & 0xFF));
      
      // x pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // y pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // colors in color table
      fprintf(bmpFile, "%c", (char)(256 & 0xFF));
      fprintf(bmpFile, "%c", (char)(256 >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(256 >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(256 >> 24 & 0xFF));
      
      // important color count
      fprintf(bmpFile, "%c", (char)(256 & 0xFF));
      fprintf(bmpFile, "%c", (char)(256 >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(256 >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(256 >> 24 & 0xFF));
      
      colorTableCnt = 0;
      
      // used for pointing to the color table for each color on an image
      int **colorImgData;
      colorImgData = (int **)malloc(xSize * sizeof(int *));
      for (i = 0; i < xSize; i++)
      colorImgData[i] = (int *)malloc(ySize * sizeof(int));
      
      // create color table
      for (y=ySize-1; y >= 0; y--)
      for (x=0; x < xSize; x++)
      {
         for (i=0; i < 256; i++)
         {
            if (i > colorTableCnt)
            break;
            
            if (i < colorTableCnt)
            if (colorTable[i] == rawImgData[x][y])
            break;
            
            if (i == colorTableCnt)
            {
               colorTable[i] = rawImgData[x][y];
               colorTableCnt++;
               break;
            }
         }
         
         colorImgData[x][y] = i;
      }
      
      // color table
      for (i=0; i < 256; i++)
      {
         fprintf(bmpFile, "%c", (char)colorTable[i] & 0x0000FF);
         fprintf(bmpFile, "%c", (char)((colorTable[i] & 0x00FF00) >> 8));
         fprintf(bmpFile, "%c", (char)((colorTable[i] & 0xFF0000) >> 16));
         fprintf(bmpFile, "%c", 0);
      }
      
      // image data
      for (y=ySize-1; y >= 0; y--)
      for (x=0; x < xSize; x++)
      {
         fprintf(bmpFile, "%c", (char)colorImgData[x][y]);
         
         if (x == xSize-1)
         for (i=0; i < 3-((xSize-1)%4); i++)
         fprintf(bmpFile, "%c", (char)0x0);// add offset
      }
      
      for (i = 0; i < xSize; i++)
      free(colorImgData[i]);
      free(colorImgData);
   }

   
   // write 4 bits per pixel bmp file
   if (bitsPerPix == 4)
   {
      // file size
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 16 * 4) & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 16 * 4) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 16 * 4) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 16 * 4) >> 24 & 0xFF));
      
      // reserved1 and 2
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // file offset to pixel array
      fprintf(bmpFile, "%c", (char)((0x36 + 16 * 4) & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 16 * 4) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 16 * 4) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 16 * 4) >> 24 & 0xFF));
      
      // dib header size
      fprintf(bmpFile, "%c", 0x28);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      
      // image width
      fprintf(bmpFile, "%c", (char)(xSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 24 & 0xFF));
      
      // image height
      fprintf(bmpFile, "%c", (char)(ySize & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 24 & 0xFF));
      
      // number of planes
      fprintf(bmpFile, "%c", 1);
      fprintf(bmpFile, "%c", 0);
      
      // number of bits per pixel
      fprintf(bmpFile, "%c", 4);
      fprintf(bmpFile, "%c", 0);
      
      // compression
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // image size
      fprintf(bmpFile, "%c", (char)(bmpDataSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 24 & 0xFF));
      
      // x pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // y pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // colors in color table
      fprintf(bmpFile, "%c", (char)(16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(16 >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(16 >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(16 >> 24 & 0xFF));
      
      // important color count
      fprintf(bmpFile, "%c", (char)(16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(16 >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(16 >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(16 >> 24 & 0xFF));
      
      colorTableCnt = 0;
      
      // create color table
      for (y=ySize-1; y >= 0; y--)
      for (x=0; x < xSize; x++)
      {
         for (i=0; i < 16; i++)
         {
            if (i > colorTableCnt)
            break;
            
            if (i < colorTableCnt)
            if (colorTable[i] == rawImgData[x][y])
            break;
            
            if (i == colorTableCnt)
            {
               colorTable[i] = rawImgData[x][y];
               colorTableCnt++;
               break;
            }
         }
      }
      
      // color table
      for (i=0; i < 16; i++)
      {
         fprintf(bmpFile, "%c", (char)colorTable[i] & 0x0000FF);
         fprintf(bmpFile, "%c", (char)((colorTable[i] & 0x00FF00) >> 8));
         fprintf(bmpFile, "%c", (char)((colorTable[i] & 0xFF0000) >> 16));
         fprintf(bmpFile, "%c", 0);
      }
      
      int pix4bpp1, pix4bpp2;
      int flipFlop = 1;
      int offsetFlipFlop = 0;
      int color;
      
      // image data
      for (y=ySize-1; y >= 0; y--)
      for (x=0; x < xSize; x++)
      {
         color = 0;
         for (i=0; i < 16; i++)
         if (rawImgData[x][y] == colorTable[i])
         color = i;
         
         // add offset
         if (x == xSize-1)
         if (xSize % 2)// if odd
         for (i=0; i < 3-(int)(((xSize-1)%8)/2); i++)//1=2,2=3,3=3,4=0,5=0,6=1,7=1,8=2
         fprintf(bmpFile, "%c", (char)color<<4);
         
         // add extra offset
         if (x == xSize-1)
         if (xSize % 2)// if odd
         {
            pix4bpp1 = 0;// load 0
            pix4bpp2 = 0;
            offsetFlipFlop = !offsetFlipFlop;
         }
         
         
         if (!flipFlop)
         {
            pix4bpp1 = color;
            
            if (!offsetFlipFlop)
            fprintf(bmpFile, "%c", (char)(pix4bpp1 | (pix4bpp2 << 4)));
         }
         
         
         // add offset
         if (x == xSize-1)
         if (!(xSize % 2))// if even
         for (i=0; i < 3-(int)(((xSize-1)%8)/2); i++)//1=2,2=3,3=3,4=0,5=0,6=1,7=1,8=2
         fprintf(bmpFile, "%c", (char)color<<4);
         
         
         if (flipFlop)
         {
            pix4bpp2 = color;
            
            if (offsetFlipFlop)
            fprintf(bmpFile, "%c", (char)(pix4bpp2 | (pix4bpp1 << 4)));
         }
         
         
         flipFlop = !flipFlop;
      }
   }
   
   
   // write 1 bit per pixel bmp file
   if (bitsPerPix == 1)
   {
      // file size
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 2 * 4) & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 2 * 4) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 2 * 4) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((bmpDataSize + 0x36 + 2 * 4) >> 24 & 0xFF));
      
      // reserved1 and 2
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // file offset to pixel array
      fprintf(bmpFile, "%c", (char)((0x36 + 2 * 4) & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 2 * 4) >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 2 * 4) >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)((0x36 + 2 * 4) >> 24 & 0xFF));
      
      // dib header size
      fprintf(bmpFile, "%c", 0x28);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      fprintf(bmpFile, "%c", 0);
      
      // image width
      fprintf(bmpFile, "%c", (char)(xSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(xSize >> 24 & 0xFF));
      
      // image height
      fprintf(bmpFile, "%c", (char)(ySize & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(ySize >> 24 & 0xFF));
      
      // number of planes
      fprintf(bmpFile, "%c", 1);
      fprintf(bmpFile, "%c", 0);
      
      // number of bits per pixel
      fprintf(bmpFile, "%c", 1);
      fprintf(bmpFile, "%c", 0);
      
      // compression
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // image size
      fprintf(bmpFile, "%c", (char)(bmpDataSize & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(bmpDataSize >> 24 & 0xFF));
      
      // x pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // y pixels per meter
      for (i=0; i < 4; i++)
      fprintf(bmpFile, "%c", 0);
      
      // colors in color table
      fprintf(bmpFile, "%c", (char)(2 & 0xFF));
      fprintf(bmpFile, "%c", (char)(2 >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(2 >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(2 >> 24 & 0xFF));
      
      // important color count
      fprintf(bmpFile, "%c", (char)(2 & 0xFF));
      fprintf(bmpFile, "%c", (char)(2 >> 8 & 0xFF));
      fprintf(bmpFile, "%c", (char)(2 >> 16 & 0xFF));
      fprintf(bmpFile, "%c", (char)(2 >> 24 & 0xFF));
      
      colorTableCnt = 0;
      
      // create color table
      for (y=ySize-1; y >= 0; y--)
      for (x=0; x < xSize; x++)
      {
         for (i=0; i < 2; i++)
         {
            if (i > colorTableCnt)
            break;
            
            if (i < colorTableCnt)
            if (colorTable[i] == rawImgData[x][y])
            break;
            
            if (i == colorTableCnt)
            {
               colorTable[i] = rawImgData[x][y];
               colorTableCnt++;
               break;
            }
         }
      }
      
      // color table
      for (i=0; i < 2; i++)
      {
         fprintf(bmpFile, "%c", (char)colorTable[i] & 0x0000FF);
         fprintf(bmpFile, "%c", (char)((colorTable[i] & 0x00FF00) >> 8));
         fprintf(bmpFile, "%c", (char)((colorTable[i] & 0xFF0000) >> 16));
         fprintf(bmpFile, "%c", 0);
      }
      
      int pix1bpp = 0;
      int bitShift;
      int color;
      i = 0;
      
      // image data
      for (y=ySize-1; y >= 0; y--)
      for (x=0; x < xSize; x++)
      {
         color = 0;
         
         if (rawImgData[x][y] == colorTable[0])
         color = 0;
         
         if (rawImgData[x][y] == colorTable[1])
         color = 1;
         
         // add offset
         if (x == xSize-1)
         {
            i = i + 31-(xSize-1)%32;
            
            pix1bpp = pix1bpp | (color << (31-(xSize-1)%32) % 8);
            
            if (31-(xSize-1)%32 >= 8)
            fprintf(bmpFile, "%c", (char)pix1bpp);
            
            if (31-(xSize-1)%32 >= 16)
            fprintf(bmpFile, "%c", (char)0);
            
            if (31-(xSize-1)%32 >= 24)
            fprintf(bmpFile, "%c", (char)0);
         }
         
         bitShift = i % 8;
         
         
         if (bitShift < 4)
         {
            if (bitShift < 2)
            {
               if (bitShift == 0)
               pix1bpp = pix1bpp | (color << 7);
               
               if (bitShift == 1)
               pix1bpp = pix1bpp | (color << 6);
            }
            else
            {
               if (bitShift == 2)
               pix1bpp = pix1bpp | (color << 5);
               
               if (bitShift == 3)
               pix1bpp = pix1bpp | (color << 4);
            }
         }
         else
         {
            if (bitShift < 6)
            {
               if (bitShift == 4)
               pix1bpp = pix1bpp | (color << 3);
               
               if (bitShift == 5)
               pix1bpp = pix1bpp | (color << 2);
            }
            else
            {
               if (bitShift == 6)
               pix1bpp = pix1bpp | (color << 1);
               
               if (bitShift == 7)
               pix1bpp = pix1bpp | color;
               
               if (bitShift == 7)
               {
                  fprintf(bmpFile, "%c", (char)pix1bpp);
                  pix1bpp = 0;
               }
            }
         }
         
         i++;
      }
   }
   
   fclose(bmpFile);
}
