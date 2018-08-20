#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readWriteWavFile_16Bit.h"
#include "writeWavCFile.h"


// convert the old sound data to a different size
void convertSampleRate(float *oldSndData, float *newSndData, int oldSndDataSize, int newSndDataSize)
{
   int i;
   int sampleLoc;
   float relativeMultiplier;
   float oldSample;
   
   // find the size relationship between the two sound datas
   relativeMultiplier = (float)(oldSndDataSize-1) / (float)(newSndDataSize-1);
   
   oldSample = oldSndData[0];
   
   for (i=0; i < newSndDataSize; i++)
   {
      // find old sound data location, "i" = new sound data location
      sampleLoc = round(i * relativeMultiplier);
      
      // use the old data samples to find the new sample height
      newSndData[i] = (oldSample + oldSndData[sampleLoc]) / 2;
      
      // keep the old sample from the old data
      oldSample = oldSndData[sampleLoc];
   }
}


int main(int argc, char **argv)
{
   int i;
   int wavDataSize = 0;
   int sampleRate = 0;
   int monoOrStereo = 0;
   
   float *rawSndDataLft;
   int rawSndDataLftAllocated = 0;
   float *rawSndDataRght;
   int rawSndDataRghtAllocated = 0;
   
   int newSampleRate;
      
   float *newRawSndDataLft;
   float *newRawSndDataRght;
   int newWavDataSize;
   
   
   if ((argc <= 1) || (argc > 3))
   {
      printf("Usage: wavToC [16Bit Wav File] [Sample Rate]\n");
      return 0;
   }
   
   newSampleRate = 11025;
   
   if (argc == 3)
   newSampleRate = atoi(argv[2]);
   
   
   getWaveFormat16Bit(argv[1], &sampleRate, &monoOrStereo);
   
   if ((!sampleRate) || (!monoOrStereo))
   return 0;
   
   if (monoOrStereo == 1)
   {
      getWavFileSampSzMono16Bit(argv[1], &wavDataSize);
      
      if (!wavDataSize)
      return 0;
      
      rawSndDataLft = (float *)malloc(wavDataSize * sizeof(float));
      rawSndDataLftAllocated = 1;
      
      rawSndDataRght = (float *)malloc(wavDataSize * sizeof(float));
      rawSndDataRghtAllocated = 1;
      
      readWavFileMono16Bit(argv[1], rawSndDataLft);
      
      // convert to stereo
      for (i=0; i < wavDataSize; i++)
      rawSndDataRght[i] = rawSndDataLft[i];
   }
   
   if (monoOrStereo == 2)
   {
      getWavFileSampSzStereo16Bit(argv[1], &wavDataSize);
      
      if (!wavDataSize)
      return 0;
      
      rawSndDataLft = (float *)malloc(wavDataSize * sizeof(float));
      rawSndDataLftAllocated = 1;
      
      rawSndDataRght = (float *)malloc(wavDataSize * sizeof(float));
      rawSndDataRghtAllocated = 1;
      
      readWavFileStereo16Bit(argv[1], rawSndDataLft, rawSndDataRght);
   }
   

   // convert sample rate if needed
   if (sampleRate != newSampleRate)
   {
      // find the size of the new sound data
      newWavDataSize = round(wavDataSize * (float)newSampleRate / (float)sampleRate);
      
      // allocate memory for the new sound buffers
      newRawSndDataLft = malloc(newWavDataSize * sizeof(float));
      newRawSndDataRght = malloc(newWavDataSize * sizeof(float));
      
      
      // convert sample rate
      convertSampleRate(rawSndDataLft, newRawSndDataLft, wavDataSize, newWavDataSize);
      
      convertSampleRate(rawSndDataRght, newRawSndDataRght, wavDataSize, newWavDataSize);
      
      
      // remove ".wav"
      argv[1][strlen(argv[1])-4] = 0;
      
      // write to c file
      writeWavCFileStereo16Bit(newRawSndDataLft, newRawSndDataRght, newWavDataSize, argv[1]);
      
      
      free(newRawSndDataRght);
      free(newRawSndDataLft);
   }
   else
   {
      // remove ".wav"
      argv[1][strlen(argv[1])-4] = 0;
      
      // write to c file
      writeWavCFileStereo16Bit(rawSndDataLft, rawSndDataRght, wavDataSize, argv[1]);
   }
   
   
   if (rawSndDataLftAllocated)
   free(rawSndDataLft);
   if (rawSndDataRghtAllocated)
   free(rawSndDataRght);
   
   return 0;
}
