#include <windows.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "3dEngine/3dEngine.h"
#include "world.h"

#define framesPerSec 16

float staticWinWidth = 1280;
float staticWinHeight = 720;
float startingWinWidth = 520;
float startingWinHeight = 360;

int xWinLoc, yWinLoc;
float winAndFrameWidth;
float winAndFrameHeight;
float staticViewPortWidth;
float staticViewPortHeight;

float xFrameOffset;
float yFrameOffset;
float scrnRatio;

int contentRelativeToWindowSize = TRUE;

int changeViewPortWindow = FALSE;
int changeWindow = FALSE;
   
int leftMouseDown = FALSE;
int rightMouseDown = FALSE;
int middleMouseDown = FALSE;
int leftMouseUp = FALSE;
int rightMouseUp = FALSE;
int middleMouseUp = FALSE;
int leftMouseClick = FALSE;
int rightMouseClick = FALSE;
int middleMouseClick = FALSE;
int dragMouse = FALSE;
float xDragLgth;
float yDragLgth;
float xMouseLoc;
float yMouseLoc;
float xMousePercent;
float yMousePercent;
float mouseWheelUp = 0;
float mouseWheelDown = 0;

int keyDown[256];
int keyUp[256];
int keyPress[256];

int exitMsg = FALSE;

void loopFunc(HWND);
void drawScene();


LRESULT CALLBACK mainWndProc(HWND, UINT, WPARAM, LPARAM);
HWND hwndMainWnd;

WNDCLASS wndclass;
BITMAPINFO pbmi[40];
HDC hdc;
HGLRC hrc;
RECT rect;
RENDRINFO rI;

SYSTEMTIME st;
float msecTS; //millisecond timestamp
float oldMsecTS = 0;
float ft; //frame time in milliseconds

unsigned int frameCnt = 0;
int msecSleep = 1000/framesPerSec;

int i;
float pv, zNear, zFar;
float xmin, xmax, ymin, ymax;
float camLenZ, camEndZ, fogBgnZ, fogEndZ, perspctv;
float overallNearClipping;
float overallFarClipping;

inline double round(double val)
{    
   return floor(val + 0.5);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
   MSG msg;

   wndclass.style = CS_HREDRAW | CS_VREDRAW;
   wndclass.lpfnWndProc = mainWndProc;
   wndclass.cbClsExtra = 0;
   wndclass.cbWndExtra = 0;
   wndclass.hInstance = hInstance;
   wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
   wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
   wndclass.hbrBackground = 0;
   wndclass.lpszMenuName = 0;
   wndclass.lpszClassName = TEXT("thisApp");

   if (!RegisterClass(&wndclass))
   return 0;

   xWinLoc = GetSystemMetrics(SM_CXSCREEN);
   yWinLoc = GetSystemMetrics(SM_CYSCREEN);
   xWinLoc = xWinLoc / 2 - startingWinWidth / 2;
   yWinLoc = yWinLoc / 2 - startingWinHeight / 2;

   hwndMainWnd = CreateWindowEx(WS_EX_APPWINDOW,//WS_EX_TOPMOST,
                                TEXT("thisApp"), TEXT("Mesh Loader"),
                                WS_OVERLAPPEDWINDOW,//WS_POPUPWINDOW//WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,
                                xWinLoc, yWinLoc,
                                startingWinWidth, startingWinHeight,
                                NULL, NULL, hInstance, NULL);


   PIXELFORMATDESCRIPTOR pfd;
   int iFormat;

   // get the device context (DC)
   hdc = GetDC(hwndMainWnd);

   // set the pixel format for the DC
   ZeroMemory(&pfd, sizeof(pfd));
   pfd.nSize = sizeof(pfd);
   pfd.nVersion = 1;
   pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
   pfd.iPixelType = PFD_TYPE_RGBA;
   pfd.cColorBits = 24;
   pfd.cDepthBits = 16;
   pfd.iLayerType = PFD_MAIN_PLANE;
   iFormat = ChoosePixelFormat(hdc, &pfd);
   SetPixelFormat(hdc, iFormat, &pfd);

   // create and enable the render context (RC)
   hrc = wglCreateContext(hdc);
   wglMakeCurrent(hdc, hrc);
   
   
   ShowWindow(hwndMainWnd, iCmdShow);
   UpdateWindow(hwndMainWnd);

   while (TRUE)
   {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
         if (msg.message == WM_QUIT)
         break;
         
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
      else
      loopFunc(hwndMainWnd);
   }
   
   wglMakeCurrent(NULL, NULL);
   wglDeleteContext(hrc);
   ReleaseDC(hwndMainWnd, hdc);
   DestroyWindow(hwndMainWnd);
   return msg.wParam;
}


LRESULT CALLBACK mainWndProc(HWND hwndMainWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   if (WM_CREATE == message)
   {
      pbmi->bmiHeader.biSize = 40;
      pbmi->bmiHeader.biWidth = staticWinWidth;
      pbmi->bmiHeader.biHeight = staticWinHeight;
      pbmi->bmiHeader.biPlanes = 1;
      pbmi->bmiHeader.biBitCount = 24;
      pbmi->bmiHeader.biCompression = BI_RGB;
      pbmi->bmiHeader.biSizeImage = staticWinWidth * staticWinHeight;
      pbmi->bmiHeader.biXPelsPerMeter = 0;
      pbmi->bmiHeader.biYPelsPerMeter = 0;
      pbmi->bmiHeader.biClrUsed = 0;
      pbmi->bmiHeader.biClrImportant = 0;

      winAndFrameWidth = staticWinWidth;
      winAndFrameHeight = staticWinHeight;
      staticViewPortWidth = staticWinWidth;
      staticViewPortHeight = staticWinHeight;
      scrnRatio = staticWinHeight / staticWinWidth;
      
      rI.winWdth = staticWinWidth;
      rI.winHght = staticWinHeight;
      rI.camLenZ = -375;
      rI.camEndZ = 100000;
      rI.fogBgnZ = 50;
      rI.fogEndZ = 100000;
      rI.perspctv = 400;
      rI.ortho = FALSE;// TRUE = orthographic projection
      rI.viewRelativeSize = 1.0;
      
      overallNearClipping = rI.camLenZ;
      overallFarClipping = rI.camEndZ;
      
      for (i=0; i < 256; i++)
      keyDown[i] = FALSE;
      
      for (i=0; i < 256; i++)
      keyUp[i] = TRUE;
      
      for (i=0; i < 256; i++)
      keyPress[i] = FALSE;
   }
   
   if (WM_SIZE == message)
   changeWindow = TRUE;
   
   if (WM_SETFOCUS == message)
   changeWindow = TRUE;
   
   if (WM_MOVE == message)
   changeWindow = TRUE;
   
   if (WM_KEYDOWN == message)
   for (i=0; i < 256; i++)
   if (i == wParam)
   {
      keyDown[i] = TRUE;
      keyUp[i] = FALSE;
   }
   
   if (WM_KEYUP == message)
   for (i=0; i < 256; i++)
   if (i == wParam)
   {
      keyUp[i] = TRUE;
      
      if (keyDown[i])
      keyPress[i] = TRUE;
      
      keyDown[i] = FALSE;
   }
   
   if (WM_LBUTTONDOWN == message)
   {
      leftMouseDown = TRUE;
      leftMouseUp = FALSE;
   }
   if (WM_RBUTTONDOWN == message)
   {
      rightMouseDown = TRUE;
      rightMouseUp = FALSE;
   }
   if (WM_MBUTTONDOWN == message)
   {
      middleMouseDown = TRUE;
      middleMouseUp = FALSE;
   }
   
   if (WM_LBUTTONUP == message)
   {
      leftMouseUp = TRUE;
      
      if (leftMouseDown)
      leftMouseClick = TRUE;
      
      leftMouseDown = FALSE;
   }
   if (WM_RBUTTONUP == message)
   {
      rightMouseUp = TRUE;
      
      if (rightMouseDown)
      rightMouseClick = TRUE;
      
      rightMouseDown = FALSE;
   }
   if (WM_MBUTTONUP == message)
   {
      middleMouseUp = TRUE;
      
      if (middleMouseDown)
      middleMouseClick = TRUE;
      
      middleMouseDown = FALSE;
   }

   if (WM_MOUSEMOVE == message)
   {
      if ((leftMouseDown) || (rightMouseDown) || (middleMouseDown))
      {
         dragMouse = TRUE;
         xDragLgth = (LOWORD(lParam) - xMouseLoc);
         yDragLgth = -(HIWORD(lParam) - yMouseLoc);
      }
      
      // mouse position
      xMouseLoc = LOWORD(lParam);
      yMouseLoc = HIWORD(lParam);
      
      // get the mouse position in percentages within the window
      xMousePercent = (xMouseLoc - xFrameOffset) * (100.0 / rI.winWdth);
      yMousePercent = (yMouseLoc - yFrameOffset) * (100.0 / rI.winHght);
   }

   if (WM_MOUSEWHEEL == message)
   {
      if (HIWORD(wParam) == 120)
      mouseWheelUp++;
      
      if (HIWORD(wParam) == 65416)
      mouseWheelDown++;
   }
   
   if (WM_DESTROY == message)
   {
      PostQuitMessage(0);
   }
   
   return DefWindowProc(hwndMainWnd, message, wParam, lParam);
}


void loopFunc(HWND hwnd)
{
   if (changeWindow)
   {
      GetClientRect(hwnd, &rect);
      winAndFrameWidth = rect.right;
      winAndFrameHeight = rect.bottom;
      
      rI.winWdth = winAndFrameWidth;
      rI.winHght = winAndFrameHeight;
      
      changeViewPortWindow = TRUE;
      changeWindow = FALSE;
   }
   
   
   if (changeViewPortWindow)
   {
      pbmi->bmiHeader.biWidth = rI.winWdth;
      pbmi->bmiHeader.biHeight = rI.winHght;
      pbmi->bmiHeader.biSizeImage = rI.winWdth * rI.winHght;
      
      // get the frame sizes
      xFrameOffset = 0;
      yFrameOffset = 0;
      
      if (rI.winHght/rI.winWdth > scrnRatio)
      yFrameOffset = (rI.winHght - scrnRatio * rI.winWdth) / 2.0;
      else
      xFrameOffset = (rI.winWdth - 1.0 / scrnRatio * rI.winHght) / 2.0;
      
      // keep the view port no bigger than a fixed size
      if ((rI.winWdth >= staticViewPortWidth) && (rI.winHght >= staticViewPortHeight))
      {
         xFrameOffset = (rI.winWdth - staticViewPortWidth) / 2.0;
         yFrameOffset = (rI.winHght - staticViewPortHeight) / 2.0;
      }
      
      rI.winWdth = rI.winWdth - xFrameOffset * 2.0;
      rI.winHght = rI.winHght - yFrameOffset * 2.0;
      
      
      
      // Allow the 3d box in which objects are drawn in to
      // increase or decrease in size relative to the window
      if (contentRelativeToWindowSize == TRUE)
      rI.viewRelativeSize = rI.winWdth / staticWinWidth;
      else
      rI.viewRelativeSize = 1.0;
      
      camLenZ = overallNearClipping * rI.viewRelativeSize;
      camEndZ = overallFarClipping * rI.viewRelativeSize;
      fogBgnZ = rI.fogBgnZ * rI.viewRelativeSize;
      fogEndZ = rI.fogEndZ * rI.viewRelativeSize;
      perspctv = rI.perspctv * rI.viewRelativeSize;
      
      ////////////////////////////////////////////////////////////////////
      // set the view port and the perspective
      glViewport(winAndFrameWidth / 2.0 - rI.winWdth / 2.0,
                 winAndFrameHeight / 2.0 - rI.winHght / 2.0, rI.winWdth, rI.winHght);
      
      
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      
      pv = (rI.winWdth / 2.0) / perspctv;
      
      if ((!rI.ortho) && (camLenZ))
      zNear = (rI.winWdth / camLenZ / 2.0 + pv) * camLenZ;
      else
      zNear = rI.winWdth / 2.0;
      
      zFar = camEndZ * pv - ((camLenZ * pv) - zNear);
      
      ymax = zNear * pv;
      ymin = -ymax;
      xmin = ymin;
      xmax = ymax;
      
      if (!rI.ortho)
      glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
      else
      glOrtho(xmin, xmax, ymin, ymax, zNear, zFar);
      
      
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      
      glTranslatef(0.0, 0.0, ((camLenZ * pv) - zNear));
      glScalef(pv, pv * rI.winWdth/rI.winHght, pv);
      
      // end of set the view port and the perspective
      ////////////////////////////////////////////////////////////////////
      
      
      // allow the z buffer to determine if a
      // 3d object is above or below another
      glEnable(GL_DEPTH_TEST);
      
      // set how to blend objects
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
      // this will allow pixels within textures with
      // an alpha value greater than 0 to be drawn
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_NOTEQUAL, 0);
      
      changeViewPortWindow = FALSE;
   }
   
   // fine the frame time (the time in milliseconds each frame takes)
   GetSystemTime(&st);
   msecTS = (float)(st.wSecond * 1000 + st.wMilliseconds) / 1000;// get millisecond timestamp
   
   ft = msecTS - oldMsecTS;// get frame time in milliseconds
   if (ft < 0)// if millisecond timestamp is reseting
   ft += 60;
   oldMsecTS = msecTS;
   
   
   drawScene();
   
   
   // before drawing to screen add a delay to make sure
   // it is in sync with the amount of frames per second
   if (ft*1000 > 1000/framesPerSec)
   if (msecSleep > 0)
   msecSleep--;
   
   if (ft*1000 < 1000/framesPerSec)
   msecSleep++;
   
   Sleep(msecSleep);
   
   
   // draw to screen
   SwapBuffers(hdc);
   
   frameCnt++;
   
   // reset key and mouse event variables
   leftMouseClick = FALSE;
   rightMouseClick = FALSE;
   middleMouseClick = FALSE;
   mouseWheelUp = 0;
   mouseWheelDown = 0;
   
   dragMouse = FALSE;
   xDragLgth = 0;
   yDragLgth = 0;
   
   for (i=0; i < 256; i++)
   keyPress[i] = FALSE;
   
   
   if (exitMsg)
   {
      exitMsg = FALSE;
      PostQuitMessage(0);
   }
}


void drawScene()
{
   static int initializeScene = TRUE;
   static int resetScene = TRUE;

   if (initializeScene)
   {
      globalResize(&world_TRANS[0], world_MESHCNT, 0, 0, 0, 20, 20, 20);
      
      // copy the mesh data so you will always have the original data
      copyTransFromTo(&world_TRANS[0], &world_STATICTRANS[0], world_MESHCNT);
      copyMeshFromTo(&world_POINT[0], &world_POINTDATSZ[0], 0,
                     &world_STATICPOINT[0], &world_POINTDATSZ[0], 0, world_MESHCNT);
      
      initializeScene = FALSE;
   }

   if (resetScene)
   {
      // keep the draw size relative to the window size
      contentRelativeToWindowSize = FALSE;
      changeWindow = TRUE;
      
      resetScene = FALSE;
      return;
   }

   // reset mesh data for each frame
   copyMeshFromTo(&world_STATICPOINT[0], &world_POINTDATSZ[0], 0,
                  &world_POINT[0], &world_POINTDATSZ[0], 0, world_MESHCNT);


   // exit if press the Esc key
   if (keyPress[VK_ESCAPE])
   exitMsg = TRUE;
   
   globalRot(&world_TRANS[0], world_MESHCNT, 0, 0, 0, -yDragLgth, xDragLgth, 0);
   
   ////////////////////////////////////////////////////////////////////
   // DRAW //

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.35f, 0.35f, 0.65f, 1.0f);

   glDisable(GL_FOG);

   // apply transformation data to the meshes
   applyRotLocSz(&world_TRANS[0], &world_POINT[0], &world_POINTDATSZ[0], 0, world_MESHCNT);

   // draw mesh
   drawMesh(&world_POINT[0], &world_QUAD[0], &world_TRI[0], &world_VCOLOR[0],
            &world_TEX[0], &world_TEXCOORD[0], &world_TEXLINKDAT[0],
            &world_QUADDATSZ[0], &world_TRIDATSZ[0], &world_HIDE[0], 0, world_MESHCNT, rI);

   // END OF DRAW //
   ////////////////////////////////////////////////////////////////////
}
