#include <windows.h>
#include <stdio.h>

int getNextDisplayResUp(int *xScrnRes, int *yScrnRes, int colorDepth)
{
	DEVMODE dm;
	int i;
   int displayFound = 0;
   int xScrnResHold, yScrnResHold, colorDepthHold;
   
	i = 0;
	while (EnumDisplaySettings(NULL, i++, &dm)) 
   {
      if (dm.dmBitsPerPel == colorDepth)
      if ((dm.dmPelsWidth == *xScrnRes) && (dm.dmPelsHeight == *yScrnRes))
      {
         displayFound = 1;
         break;
      }
   }
   
   if (!displayFound)
   return -1;
   
   if (i < 2)
   return -1;
   
   i = i - 2;
   EnumDisplaySettings(NULL, i, &dm);
   
   if (i == 0)
   {
      if (dm.dmBitsPerPel == colorDepth)
      if ((dm.dmPelsWidth > *xScrnRes) || (dm.dmPelsHeight > *yScrnRes))
      {
         *xScrnRes = dm.dmPelsWidth;
         *yScrnRes = dm.dmPelsHeight;
      }
      
      return i;
   }
   
   while (i)
   {
      xScrnResHold = dm.dmPelsWidth;
      yScrnResHold = dm.dmPelsHeight;
      colorDepthHold = dm.dmBitsPerPel;
      
      i--;
      EnumDisplaySettings(NULL, i, &dm);
      
      if (dm.dmBitsPerPel == colorDepth)
      if ((colorDepthHold != dm.dmBitsPerPel) ||
          (xScrnResHold != dm.dmPelsWidth) || (yScrnResHold != dm.dmPelsHeight))
      break;
   }
   
   *xScrnRes = xScrnResHold;
   *yScrnRes = yScrnResHold;
   i++;
   
	return i;
}

int getNextDisplayResDown(int *xScrnRes, int *yScrnRes, int colorDepth)
{
	DEVMODE dm;
   int displayFound = 0;
	int i;
   
	i = 0;
	while (EnumDisplaySettings(NULL, i++, &dm)) 
   {
      if (dm.dmBitsPerPel == colorDepth)
      if ((dm.dmPelsWidth == *xScrnRes) && (dm.dmPelsHeight == *yScrnRes))
      {
         displayFound = 1;
         break;
      }
   }
   
   if (!displayFound)
   return -1;
   
   while (EnumDisplaySettings(NULL, i++, &dm)) 
   {
      if (dm.dmBitsPerPel == colorDepth)
      if ((dm.dmPelsWidth < *xScrnRes) || (dm.dmPelsHeight < *yScrnRes))
      break;
   }
   
   if ((dm.dmBitsPerPel != colorDepth) ||
      ((dm.dmPelsWidth >= *xScrnRes) && (dm.dmPelsHeight >= *yScrnRes)))
   return -1;
   
   *xScrnRes = dm.dmPelsWidth;
   *yScrnRes = dm.dmPelsHeight;
   i--;
   
	return i;
}

void changeDisplayRes(int displayIndex)
{
	DEVMODE dm;
   
   EnumDisplaySettings(NULL, displayIndex, &dm);
   
   if (ChangeDisplaySettings(&dm, CDS_TEST) != DISP_CHANGE_SUCCESSFUL)
   return;
   
   ChangeDisplaySettings(&dm, 0);
}

int getCurrentDisplayRes(int *xScrnRes, int *yScrnRes, int *colorDepth)
{
   DISPLAY_DEVICE dd;
   DEVMODE dm;
   int i;
   
   *xScrnRes = GetSystemMetrics(SM_CXSCREEN);
   *yScrnRes = GetSystemMetrics(SM_CYSCREEN);
   *colorDepth = 0;

   if (!EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
   return -1;

   *xScrnRes = dm.dmPelsWidth;
   *yScrnRes = dm.dmPelsHeight;
   *colorDepth = dm.dmBitsPerPel;
   
   i = 0;
	while (EnumDisplaySettings(NULL, i++, &dm)) 
   {
      if (dm.dmBitsPerPel == *colorDepth)
      if ((dm.dmPelsWidth == *xScrnRes) && (dm.dmPelsHeight == *yScrnRes))
      {
         i--;
         return i;
      }
   }
   
   return -1;
}
