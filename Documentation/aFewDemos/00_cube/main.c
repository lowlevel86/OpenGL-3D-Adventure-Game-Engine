#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>

#define winWidth 400
#define winHeight 400

int xWinPos, yWinPos;
int width = winWidth, height = winHeight;
float xCenter = winWidth / 2, yCenter = winHeight / 2;

GLfloat vertexData[12*2] = {
// BACK
-100.0,  100.0, -100.0,
100.0,  100.0, -100.0,
-100.0, -100.0, -100.0,
100.0, -100.0, -100.0,

// FRONT
-100.0,  100.0,  100.0,
100.0,  100.0,  100.0,
-100.0, -100.0,  100.0,
100.0, -100.0,  100.0,
};

GLushort vectorData[3*4+8] = {0, 1, 3, 0, 2, 3, 4, 5, 7, 4, 6, 7, 0, 4, 1, 5, 3, 7, 2, 6};

GLfloat colorData[16*2] = {
1.0, 0.0, 0.0, 1.0,
0.0, 1.0, 0.0, 1.0,
0.0, 0.0, 1.0, 1.0,
0.0, 0.0, 0.0, 1.0,

1.0, 0.0, 0.0, 1.0,
0.0, 1.0, 0.0, 1.0,
0.0, 0.0, 1.0, 1.0,
0.0, 0.0, 0.0, 1.0,
};

float xP[8] = {-100, 100,-100, 100,-100, 100,-100, 100};
float yP[8] = { 100, 100,-100,-100, 100, 100,-100,-100};
float zP[8] = {-100,-100,-100,-100, 100, 100, 100, 100};

void drawScene();
void degRot(float *, float *, float);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR szAppName[] = TEXT("thisApp");

HDC hDC;
HGLRC hRC;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
   WNDCLASS wndclass;
   HWND hwnd;      
   MSG msg;

   wndclass.style = CS_HREDRAW | CS_VREDRAW;
   wndclass.lpfnWndProc = WndProc;
   wndclass.cbClsExtra = 0;
   wndclass.cbWndExtra = 0;
   wndclass.hInstance = hInstance;
   wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
   wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
   wndclass.hbrBackground = 0;
   wndclass.lpszMenuName = szAppName;
   wndclass.lpszClassName = szAppName;

   if (!RegisterClass(&wndclass))
   return 0;

   xWinPos = GetSystemMetrics(SM_CXSCREEN);
   yWinPos = GetSystemMetrics(SM_CYSCREEN);
   xWinPos = xWinPos / 2 - winWidth / 2;
   yWinPos = yWinPos / 2 - winHeight / 2;

   hwnd = CreateWindow(szAppName, TEXT("cube"),
                       WS_OVERLAPPEDWINDOW,//WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,
                       xWinPos, yWinPos,
                       winWidth+6, winHeight+25, 
                       NULL, NULL, hInstance, NULL);

   
   PIXELFORMATDESCRIPTOR pfd;
   int iFormat;

   // get the device context (DC)
   hDC = GetDC(hwnd);

   // set the pixel format for the DC
   ZeroMemory(&pfd, sizeof(pfd));
   pfd.nSize = sizeof(pfd);
   pfd.nVersion = 1;
   pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
   pfd.iPixelType = PFD_TYPE_RGBA;
   pfd.cColorBits = 24;
   pfd.cDepthBits = 16;
   pfd.iLayerType = PFD_MAIN_PLANE;
   iFormat = ChoosePixelFormat(hDC, &pfd);
   SetPixelFormat(hDC, iFormat, &pfd);

   // create and enable the render context (RC)
   hRC = wglCreateContext(hDC);
   wglMakeCurrent(hDC, hRC);
   
   glEnable(GL_DEPTH_TEST);
   
   
   ShowWindow(hwnd, iCmdShow);
   UpdateWindow(hwnd);


   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   wglMakeCurrent(NULL, NULL);
   wglDeleteContext(hRC);
   ReleaseDC(hwnd, hDC);
   DestroyWindow(hwnd);
   return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   int i;
   static int exitMsg = 0;
   float xRot = 0;
   float yRot = 0;
   float zRot = 0;
   int changeCamera = 0;

   float canvasSize = 1200.0;// larger than computer screen
   
   float pv, zNear, zFar;
   float xmin, xmax, ymin, ymax;
   
   static float camLenZ = 300.0;
   static float camEndZ = -300.0;
   static float perspctv = 400.0;
   static float ortho = 0;// 1 = orthographic projection
   
   
   if (WM_CREATE == message)
   changeCamera = 1;
   
   if (WM_SIZE == message)
   {
      width = LOWORD(lParam);
      height = HIWORD(lParam);
      
      xCenter = width / 2;
      yCenter = height / 2;
      
      changeCamera = 1;
   }
   
   if (WM_KEYDOWN == message)
   {
      if (38 == wParam)//Rotate Up
      xRot = -5.0;

      if (40 == wParam)//Rotate Down
      xRot = 5.0;
      
      if (37 == wParam)//Rotate Left
      yRot = 5.0;

      if (39 == wParam)//Rotate Right
      yRot = -5.0;

      if (82 == wParam)//"R" Rotate Counterclockwise
      zRot = 5.0;

      if (76 == wParam)//"L" Rotate Clockwise
      zRot = -5.0;
      
      for(i = 0; i < 24; i=i+3)
      degRot(&vertexData[i+1], &vertexData[i+2], xRot);
      
      for(i = 0; i < 24; i=i+3)
      degRot(&vertexData[i+0], &vertexData[i+2], yRot);
      
      for(i = 0; i < 24; i=i+3)
      degRot(&vertexData[i+0], &vertexData[i+1], zRot);
      
      drawScene();
      
      if (27 == wParam)
      exitMsg = 1;
      
      changeCamera = 1;
   }

   if (changeCamera == 1)
   {
      glViewport(xCenter-canvasSize/2, yCenter-canvasSize/2, canvasSize, canvasSize);
      
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      
      
      pv = (canvasSize / 2) / perspctv;
      
      if (!ortho)
      zNear = (canvasSize / camLenZ / 2.0 - pv) * camLenZ;
      else
      zNear = canvasSize / 2;
      
      zFar = -camEndZ * pv - (-zNear - (camLenZ * pv));
      
      ymax = zNear * pv;
      ymin = -ymax;
      xmin = ymin;
      xmax = ymax;
      
      if (!ortho)
      glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
      else
      glOrtho(xmin, xmax, ymin, ymax, zNear, zFar);
      
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      
      
      glTranslatef(0.0, 0.0, (-zNear - (camLenZ * pv)));
      glScalef(pv, pv, pv);
      
      drawScene();
   }
   
   if (WM_PAINT == message)
   drawScene();
   
   if ((WM_DESTROY == message) || (exitMsg))
   {
      PostQuitMessage(0);
      return 0;
   }

   return DefWindowProc(hwnd, message, wParam, lParam);
}

void drawScene()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(1.0, 1.0, 1.0, 0.0);
   
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, vertexData);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4, GL_FLOAT, 0, colorData);
   
   // draw planes
   glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_SHORT, vectorData);
   glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_SHORT, vectorData+3);
   glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_SHORT, vectorData+6);
   glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_SHORT, vectorData+9);

   // draw vectors
   glLineWidth(2.0);
   glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_SHORT, vectorData+12);
   glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_SHORT, vectorData+14);
   glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_SHORT, vectorData+16);
   glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_SHORT, vectorData+18);
   
   SwapBuffers(hDC);
}

// rotate using degrees
void degRot(float *horiP, float *vertP, float degrees)
{
   float h, v;
   float hUc;
   float vUc;
   float hLine1, vLine1;
   float hLine2, vLine2;
   
   if (degrees != degrees) // check if NaN
   return;
   
   hUc = cos(degrees * (M_PI * 2.0 / 360.0));
   vUc = sin(degrees * (M_PI * 2.0 / 360.0));
   
   hLine1 = hUc;
   vLine1 = vUc;
   hLine2 = -vUc;
   vLine2 = hUc;

   h = *vertP * hLine2 + *horiP * vLine2;
   v = *horiP * vLine1 + *vertP * hLine1;
   *horiP = h;
   *vertP = v;
}
