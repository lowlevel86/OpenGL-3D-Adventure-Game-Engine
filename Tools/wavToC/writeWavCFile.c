#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>


void writeWavCFileStereo16Bit(float *wavDataLft, float *wavDataRght, int wavDataSize, char *CFileName)
{
   int i;
   FILE *CFile;
   char *NameDotC;
   char *NameDotH;
   int sndSamp;
   int sampLoc = 0;
   char *NewName;
   
   NewName = malloc(strlen(CFileName)+9);
   sprintf(NewName, "%sSndData%c",CFileName, '\0');
   
   NameDotC = malloc(strlen(NewName)+4);
   sprintf(NameDotC, "%s.c%c",NewName, '\0');
   
   CFile = fopen(NameDotC, "wb");
   
   free(NameDotC);
   
   if (!CFile)
   return;
   
   
   fprintf(CFile, "char %s[%i]={\n", NewName, wavDataSize * 4);
   
   for (i = 0; i < wavDataSize*4; i=i+4)
   {
      // note: the sample is divided by 8
      //       this will allow the sound to mix with 7 other tracks
      
      // Left side
      sndSamp = round(wavDataLft[sampLoc] * 32767.0 / 8.0); // 32767 for 16 bits
      fprintf(CFile, "0x%x,\n", (sndSamp & 0x0000FF));
      fprintf(CFile, "0x%x,\n", ((sndSamp & 0x00FF00) >> 8));
      
      // Right side
      sndSamp = round(wavDataRght[sampLoc] * 32767.0 / 8.0); // 32767 for 16 bits
      fprintf(CFile, "0x%x,\n", (sndSamp & 0x0000FF));
      fprintf(CFile, "0x%x,\n", ((sndSamp & 0x00FF00) >> 8));
      
      sampLoc++;
   }
   
   fprintf(CFile, "};\n");
   
   fclose(CFile);
   
   
   NameDotH = malloc(strlen(NewName)+4);
   sprintf(NameDotH, "%s.h%c",NewName, '\0');
   
   CFile = fopen(NameDotH, "wb");
   
   free(NameDotH);
   
   if (!CFile)
   return;
   
   fprintf(CFile, "extern char %s[%i];\n", NewName, wavDataSize * 4);
   
   fclose(CFile);
   
   free(NewName);
}
