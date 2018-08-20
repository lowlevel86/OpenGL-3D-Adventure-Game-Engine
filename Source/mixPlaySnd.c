#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>

HWAVEOUT hWaveOut;
PWAVEHDR pWaveHdr1, pWaveHdr2;

int soundBufferSize = 0;
char *pBuffer1;
char *pBuffer2;
char *outSndBuff;

char *sndPtrLRChann[8];
int sndSizeLRChann[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int sndSampLocLRChann[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int sndInALoopLRChann[8] = {FALSE, FALSE, FALSE, FALSE,
                            FALSE, FALSE, FALSE, FALSE};

int sndEndLRChann[8] = {FALSE, FALSE, FALSE, FALSE,
                        FALSE, FALSE, FALSE, FALSE};


void mixPlaySound(char *sndDataPt, int sndDataSize, int loopSnd, int concurrentSnd)
{
   int i;
   
   // if a sound was called to end by the
   // function endAllSound() or endSound()
   // then undo the end sound operation
   for (i=0; i < 8; i++)
   if (sndPtrLRChann[i] == sndDataPt)
   if (sndEndLRChann[i] == TRUE)
   sndEndLRChann[i] = FALSE;
   
   // if the sound pointer already exists within a left/right channel
   // and the sound had not already started or the new sound
   // was not set to play concurrently with its self then return
   for (i=0; i < 8; i++)
   if (sndPtrLRChann[i] == sndDataPt)
   if (sndSizeLRChann[i] != 0)
   if ((sndSampLocLRChann[i] == 0) || (!concurrentSnd))
   return;
   
   // find a channel that is not in use
   for (i=0; i < 8; i++)
   if (sndSizeLRChann[i] == 0)
   {
      sndPtrLRChann[i] = sndDataPt;
      sndSizeLRChann[i] = sndDataSize;
      
      if (loopSnd)
      sndInALoopLRChann[i] = TRUE;
      else
      sndInALoopLRChann[i] = FALSE;
      
      break;
   }
}

void endAllSound()
{
   int i;
   
   //stop all sound play
   for (i=0; i < 8; i++)
   {
      if (sndSizeLRChann[i])
      sndEndLRChann[i] = TRUE;
      else
      sndEndLRChann[i] = FALSE;
   }
}

void endSound(char *sndDataPt)
{
   int i;
   
   //find and stop sound play from pointer
   for (i=0; i < 8; i++)
   if (sndPtrLRChann[i] == sndDataPt)
   {
      if (sndSizeLRChann[i])
      sndEndLRChann[i] = TRUE;
      else
      sndEndLRChann[i] = FALSE;
   }
}

void mixSndTracks()
{
   int i, j;
   int leftSample, rightSample;
   int leftMixSample, rightMixSample;
   static int lastLeftSample[8] = {0, 0, 0, 0, 0, 0, 0, 0};
   static int lastRightSample[8] = {0, 0, 0, 0, 0, 0, 0, 0};
   static int muteLeftSnd[8] = {FALSE, FALSE, FALSE, FALSE,
                                FALSE, FALSE, FALSE, FALSE};
   static int muteRightSnd[8] = {FALSE, FALSE, FALSE, FALSE,
                                 FALSE, FALSE, FALSE, FALSE};
   
   
   // soundBufferSize = size in bytes
   for (i=0; i < soundBufferSize; i+=4)
   {
      leftMixSample = 0;
      rightMixSample = 0;
      
      for (j=0; j < 8; j++)
      {
         // if the sound is suppose to loop then keep resetting it
         if (sndInALoopLRChann[j] == TRUE)
         if (sndSampLocLRChann[j] >= sndSizeLRChann[j])
         sndSampLocLRChann[j] = 0;
         
         // mix sound channel
         if (sndSizeLRChann[j])
         if (sndSampLocLRChann[j] < sndSizeLRChann[j])
         {
            leftSample = 0;
            rightSample = 0;
            
            // if the sound is suppose to halt
            if (sndEndLRChann[j] == TRUE)
            {
               // wait until the sample crosses zero
               if ((leftSample >= 0) && (lastLeftSample[j] <= 0))
               muteLeftSnd[j] = TRUE;
               
               // wait until the sample crosses zero
               if ((rightSample >= 0) && (lastRightSample[j] <= 0))
               muteRightSnd[j] = TRUE;
            }
            
            if (muteLeftSnd[j] == FALSE)
            leftSample = ((sndPtrLRChann[j][sndSampLocLRChann[j]+1] << 8) |
                          (0x00FF & sndPtrLRChann[j][sndSampLocLRChann[j]]));
            
            if (muteRightSnd[j] == FALSE)
            rightSample = ((sndPtrLRChann[j][sndSampLocLRChann[j]+3] << 8) |
                           (0x00FF & sndPtrLRChann[j][sndSampLocLRChann[j]+2]));
            
            // save sample for later
            lastLeftSample[j] = leftSample;
            lastRightSample[j] = rightSample;
            
            leftMixSample += leftSample;
            rightMixSample += rightSample;
         }
         
         sndSampLocLRChann[j] += 4;
      }
      
      // move sound sample into "outSndBuff"
      outSndBuff[i] = (char)(leftMixSample & 0x00FF);
      outSndBuff[i+1] = (char)((leftMixSample & 0xFF00) >> 8);
      outSndBuff[i+2] = (char)(rightMixSample & 0x00FF);
      outSndBuff[i+3] = (char)((rightMixSample & 0xFF00) >> 8);
   }
   
   for (i=0; i < 8; i++)
   {
      // if a sound was called to end by the
      // function endAllSound() or endSound()
      // and both left and right channels are muted, reset it
      if ((muteLeftSnd[i]) && (muteRightSnd[i]))
      {
         lastLeftSample[i] = 0;
         lastRightSample[i] = 0;
         muteLeftSnd[i] = FALSE;
         muteRightSnd[i] = FALSE;
         
         sndSizeLRChann[i] = 0;
         sndSampLocLRChann[i] = 0;
         
         sndEndLRChann[i] = FALSE;
      }
      
      // if a sound is finished playing and is not looping, reset it
      if (sndInALoopLRChann[i] == FALSE)
      if (sndSampLocLRChann[i] >= sndSizeLRChann[i])
      {
         sndSizeLRChann[i] = 0;
         sndSampLocLRChann[i] = 0;
      }
   }
}

// 16 bit
void iniSndBuffs(HWND hwnd, int buffSize, int sampRate)
{
   WAVEFORMATEX waveformat;
   
   if (hWaveOut == NULL)
   {
      // Allocate memory for 2 headers and 2 buffers
      pWaveHdr1 = (PWAVEHDR)malloc(sizeof(WAVEHDR));
      pWaveHdr2 = (PWAVEHDR)malloc(sizeof(WAVEHDR));
      pBuffer1 = (char *)malloc(buffSize);
      pBuffer2 = (char *)malloc(buffSize);
      
      soundBufferSize = buffSize;
      
      // Allocate memory for sound buffer used for mixing
      outSndBuff = (char *)malloc(buffSize);
      
      
      // Open waveform audio for output
      
      waveformat.wFormatTag = WAVE_FORMAT_PCM;
      waveformat.nChannels = 2;
      waveformat.nSamplesPerSec = sampRate;
      waveformat.nAvgBytesPerSec = sampRate * 2 * 2; // sample rate * 2 bytes per sample * 2 channels
      waveformat.nBlockAlign = 4;
      waveformat.wBitsPerSample = 16;
      waveformat.cbSize = 0;
          
      if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveformat,
                     (DWORD) hwnd, 0, CALLBACK_WINDOW) != MMSYSERR_NOERROR)
      {
         free(pWaveHdr1);
         free(pWaveHdr2);
         free(pBuffer1);
         free(pBuffer2);
         
         hWaveOut = NULL;
         
         //error opening waveform audio device
         return;
      }
      
      // Set up headers and prepare them
      
      pWaveHdr1->lpData = (LPSTR)pBuffer1;
      pWaveHdr1->dwBufferLength = buffSize;
      pWaveHdr1->dwBytesRecorded = 0;
      pWaveHdr1->dwUser = 0;
      pWaveHdr1->dwFlags = 0;
      pWaveHdr1->dwLoops = 1;
      pWaveHdr1->lpNext = NULL;
      pWaveHdr1->reserved = 0;
      
      waveOutPrepareHeader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
      
      pWaveHdr2->lpData = (LPSTR)pBuffer2;
      pWaveHdr2->dwBufferLength = buffSize;
      pWaveHdr2->dwBytesRecorded = 0;
      pWaveHdr2->dwUser = 0;
      pWaveHdr2->dwFlags = 0;
      pWaveHdr2->dwLoops = 1;
      pWaveHdr2->lpNext = NULL;
      pWaveHdr2->reserved = 0;
      
      waveOutPrepareHeader(hWaveOut, pWaveHdr2, sizeof(WAVEHDR));
   }
}

void loadPlaySnd(UINT message, LPARAM lParam, char *sndBuffer)
{
   int i;
   static int loadBuffer = 1;
   
   // Message generated from waveOutOpen call
   if (MM_WOM_OPEN == message)
   {
      // Send two buffers to waveform output device
      
      if (loadBuffer == 1)
      {
         for (i=0; i < soundBufferSize; i++)
         sndBuffer[i] = outSndBuff[i];
         
         waveOutWrite(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
         
         loadBuffer = 2;
         return;
      }
      
      if (loadBuffer == 2)
      {
         for (i=0; i < soundBufferSize; i++)
         sndBuffer[i] = outSndBuff[i];
         
         waveOutWrite(hWaveOut, pWaveHdr2, sizeof(WAVEHDR));
         
         loadBuffer = 1;
         return;
      }
   }
   
   // Message generated when a buffer is finished
   if (MM_WOM_DONE == message)
   {
      if (hWaveOut != NULL)
      {
         for (i=0; i < soundBufferSize; i++)
         sndBuffer[i] = outSndBuff[i];
         
         waveOutWrite(hWaveOut, (PWAVEHDR)lParam, sizeof(WAVEHDR));
      }
   }
}

void closeSndBuffs()
{
   if (hWaveOut != NULL)
   {
      soundBufferSize = 0;
      
      waveOutReset(hWaveOut);
      waveOutClose(hWaveOut);
      
      waveOutUnprepareHeader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
      waveOutUnprepareHeader(hWaveOut, pWaveHdr2, sizeof(WAVEHDR));
      
      free(outSndBuff);
      free(pWaveHdr1);
      free(pWaveHdr2);
      free(pBuffer1);
      free(pBuffer2);
      
      hWaveOut = NULL;
   }
}

void soundToDevice(int message, int lParam)
{
   if (MM_WOM_OPEN == message)// load and play the first two sound segments
   {
      mixSndTracks();
      
      loadPlaySnd(message, lParam, pBuffer1);
      
      
      mixSndTracks();
      
      loadPlaySnd(message, lParam, pBuffer2);
   }

   if (MM_WOM_DONE == message)// load next sound segment after one is finished
   {
      mixSndTracks();
      
      loadPlaySnd(message, lParam, (char *)((PWAVEHDR) lParam)->lpData);
   }
}
