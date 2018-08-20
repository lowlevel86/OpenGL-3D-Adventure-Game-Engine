#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Uncompressed 16-bit PCM audio
// 8000  Hz
// 11025
// 16000
// 22050
// 32000
// 44100
// 48000
// 96000

void getWaveFormat16Bit(char *wavFileName, int *sampleRate, int *monoOrStereo)
{
   struct stat stat_p;
   FILE *wavFile;
   int i;
   
   // does the file exist
   if (-1 == stat(wavFileName, &stat_p))
   return;
   
   // open file for read
   wavFile = fopen(wavFileName,"rb");
   if (!wavFile)
   return;
   
   // search for the word "fmt "
   for (i=0; i < stat_p.st_size; i++)
   {
      // 0x66 0x6d 0x74 0x20 = "fmt "
      if (fgetc(wavFile) == 0x66)
      if (fgetc(wavFile) == 0x6d)
      if (fgetc(wavFile) == 0x74)
      if (fgetc(wavFile) == 0x20)
      {
         // 6 bytes after the string "fmt "
         fseek(wavFile, 6, SEEK_CUR);
         
         // 1 = mono; 2 = stereo
         *monoOrStereo = fgetc(wavFile);
         
         // 1 byte after the number of channels
         fseek(wavFile, 1, SEEK_CUR);
         
         // get the sample rate
         *sampleRate = fgetc(wavFile);
         *sampleRate = *sampleRate + (fgetc(wavFile) << 8);
         *sampleRate = *sampleRate + (fgetc(wavFile) << 16);
         *sampleRate = *sampleRate + (fgetc(wavFile) << 24);
      }
   }
   
   fclose(wavFile);
}


void readWavFileMono16Bit(char *wavFileName, float *rawSndData)
{
   struct stat stat_p;
   FILE *wavFile;
   char *wavData;
   int samples;
   int i;
   int startOfWavData;
   
   // does the file exist
   if (-1 == stat(wavFileName, &stat_p))
   return;
   
   // allocate memory for wav file
   wavData = (char *)malloc(stat_p.st_size);
   
   // open file for read
   wavFile = fopen(wavFileName,"rb");
   if (!wavFile)
   return;
   
   // read file data to buffer
   fread(wavData, sizeof(char), stat_p.st_size, wavFile);
   
   fclose(wavFile);
   
   // search for the word "data"
   for (i=0; i < stat_p.st_size; i++)
   {
      // 0x64 0x61 0x74 0x61 = "data"
      if ((wavData[i] == 0x64) && (wavData[i+1] == 0x61) &&
          (wavData[i+2] == 0x74) && (wavData[i+3] == 0x61))
      {
         // get the starting location of the wav sound data
         startOfWavData = i+4 + 4; // 4 bytes after the word "data"
         
         // end the for loop
         i = stat_p.st_size;
      }
   }
   
   // take the number of bytes and divide by 2 to get the number of samples
   samples = (stat_p.st_size - startOfWavData) / 2;
   
   // convert the 16-bit samples to floating point numbers
   for (i=0; i < samples; i++)
   rawSndData[i] = (float)((wavData[i*2+startOfWavData+1] << 8) |
                           (0x00FF & wavData[i*2+startOfWavData])) / 0x7FFF;// Not 0x8000;
   
   if (wavData)
   free(wavData);
}


void readWavFileStereo16Bit(char *wavFileName, float *rawSndDataLft, float *rawSndDataRght)
{
   struct stat stat_p;
   FILE *wavFile;
   char *wavData;
   int samples;
   int i;
   int startOfWavData;
   
   // does the file exist
   if (-1 == stat(wavFileName, &stat_p))
   return;
   
   // allocate memory for wav file
   wavData = (char *)malloc(stat_p.st_size);
   
   // open file for read
   wavFile = fopen(wavFileName,"rb");
   if (!wavFile)
   return;
   
   // read file data to buffer
   fread(wavData, sizeof(char), stat_p.st_size, wavFile);
   
   fclose(wavFile);
   
   // search for the word "data"
   for (i=0; i < stat_p.st_size; i++)
   {
      // 0x64 0x61 0x74 0x61 = "data"
      if ((wavData[i] == 0x64) && (wavData[i+1] == 0x61) &&
          (wavData[i+2] == 0x74) && (wavData[i+3] == 0x61))
      {
         // get the starting location of the wav sound data
         startOfWavData = i+4 + 4; // 4 bytes after the word "data"
         
         // end the for loop
         i = stat_p.st_size;
      }
   }
   
   // take the number of bytes and divide by 4 to get the number of samples
   samples = (stat_p.st_size - startOfWavData) / 4;
   
   // convert the 16-bit samples to floating point numbers
   for (i=0; i < samples; i++)
   {
      rawSndDataLft[i] = (float)((wavData[i*4+startOfWavData+1] << 8) |
                                 (0x00FF & wavData[i*4+startOfWavData])) / 0x7FFF;
      
      rawSndDataRght[i] = (float)((wavData[i*4+startOfWavData+3] << 8) |
                                  (0x00FF & wavData[i*4+startOfWavData+2])) / 0x7FFF;
   }
   
   if (wavData)
   free(wavData);
}


void getWavFileSampSzMono16Bit(char *wavFileName, int *wavDataSize)
{
   struct stat stat_p;
   FILE *wavFile;
   int i;
   int startOfWavData;
   
   *wavDataSize = 0;
   
   // does the file exist
   if (-1 == stat(wavFileName, &stat_p))
   return;
   
   // open file for read
   wavFile = fopen(wavFileName,"rb");
   if (!wavFile)
   return;
   
   // search for the word "data"
   for (i=0; i < stat_p.st_size; i++)
   {
      // 0x64 0x61 0x74 0x61 = "data"
      if (fgetc(wavFile) == 0x64)
      if (fgetc(wavFile) == 0x61)
      if (fgetc(wavFile) == 0x74)
      if (fgetc(wavFile) == 0x61)
      // get the starting location of the wav sound data
      startOfWavData = i+4 + 4; // 4 bytes after the word "data"
   }
   
   // take the number of bytes and divide by 2 to get the number of samples
   *wavDataSize = (stat_p.st_size - startOfWavData) / 2;
   
   fclose(wavFile);
}


void getWavFileSampSzStereo16Bit(char *wavFileName, int *wavDataSize)
{
   struct stat stat_p;
   FILE *wavFile;
   int i;
   int startOfWavData;
   
   *wavDataSize = 0;
   
   // does the file exist
   if (-1 == stat(wavFileName, &stat_p))
   return;
   
   // open file for read
   wavFile = fopen(wavFileName,"rb");
   if (!wavFile)
   return;
   
   // search for the word "data"
   for (i=0; i < stat_p.st_size; i++)
   {
      // 0x64 0x61 0x74 0x61 = "data"
      if (fgetc(wavFile) == 0x64)
      if (fgetc(wavFile) == 0x61)
      if (fgetc(wavFile) == 0x74)
      if (fgetc(wavFile) == 0x61)
      // get the starting location of the wav sound data
      startOfWavData = i+4 + 4; // 4 bytes after the word "data"
   }
   
   // take the number of bytes and divide by 4 to get the number of samples
   *wavDataSize = (stat_p.st_size - startOfWavData) / 4;
   
   fclose(wavFile);
}


void writeWavFileMono16Bit(char *wavFileName, float *rawSndData, int wavDataSize, int sampleRate)
{
   int i;
   int sndSamp;
   FILE *wavFile;
   char waveFormatChunk[44]={0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
                             0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//sample rate and byte rate
                             0x02, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61, 0x00, 0x00, 0x00, 0x00};
   
   wavFile = fopen(wavFileName, "wb");
   if (!wavFile)
   return;
   
   fprintf(wavFile, "%s", "RIFF");
   
   fprintf(wavFile, "%c", (char)((wavDataSize * 2 + 44 - 8) & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 2 + 44 - 8) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 2 + 44 - 8) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 2 + 44 - 8) >> 24 & 0xFF));
   
   for (i = 8; i < 24; i++)
   fprintf(wavFile, "%c", waveFormatChunk[i]);
   
   // samples per second
   fprintf(wavFile, "%c", (char)((sampleRate) & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate) >> 24 & 0xFF));
   
   // bytes per second
   fprintf(wavFile, "%c", (char)((sampleRate * 2) & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate * 2) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate * 2) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate * 2) >> 24 & 0xFF));
   
   for (i = 32; i < 40; i++)
   fprintf(wavFile, "%c", waveFormatChunk[i]);
   
   fprintf(wavFile, "%c", (char)((wavDataSize * 2) & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 2) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 2) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 2) >> 24 & 0xFF));
   
   for (i = 0; i < wavDataSize; i++)
   {
      sndSamp = (int)(rawSndData[i] * 32767); //16 bits
      fprintf(wavFile, "%c", (char)(sndSamp & 0x0000FF));
      fprintf(wavFile, "%c", (char)((sndSamp & 0x00FF00) >> 8));
   }
   
   fclose(wavFile);
}


void writeWavFileStereo16Bit(char *wavFileName, float *rawSndDataLft, float *rawSndDataRght, int wavDataSize, int sampleRate)
{
   int i;
   int sndSamp;
   FILE *wavFile;
   char waveFormatChunk[44]={0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20,
                             0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61, 0x00, 0x00, 0x00, 0x00};
   
   wavFile = fopen(wavFileName, "wb");
   if (!wavFile)
   return;
   
   fprintf(wavFile, "%s", "RIFF");
   
   fprintf(wavFile, "%c", (char)((wavDataSize * 4 + 44 - 8) & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 4 + 44 - 8) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 4 + 44 - 8) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 4 + 44 - 8) >> 24 & 0xFF));
   
   for (i = 8; i < 24; i++)
   fprintf(wavFile, "%c", waveFormatChunk[i]);
   
   // samples per second
   fprintf(wavFile, "%c", (char)((sampleRate) & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate) >> 24 & 0xFF));
   
   // bytes per second
   fprintf(wavFile, "%c", (char)((sampleRate * 4) & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate * 4) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate * 4) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((sampleRate * 4) >> 24 & 0xFF));
   
   for (i = 32; i < 40; i++)
   fprintf(wavFile, "%c", waveFormatChunk[i]);
   
   fprintf(wavFile, "%c", (char)((wavDataSize * 4) & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 4) >> 8 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 4) >> 16 & 0xFF));
   fprintf(wavFile, "%c", (char)((wavDataSize * 4) >> 24 & 0xFF));
   
   for (i = 0; i < wavDataSize; i++)
   {
      sndSamp = (int)(rawSndDataLft[i] * 32767); // not 32768); //16 bits
      fprintf(wavFile, "%c", (char)(sndSamp & 0x0000FF));
      fprintf(wavFile, "%c", (char)((sndSamp & 0x00FF00) >> 8));
      
      sndSamp = (int)(rawSndDataRght[i] * 32767); //16 bits
      fprintf(wavFile, "%c", (char)(sndSamp & 0x0000FF));
      fprintf(wavFile, "%c", (char)((sndSamp & 0x00FF00) >> 8));
   }
   
   fclose(wavFile);
}
