// reset
if (resetScene)
{
   endAllSound();
   contentRelativeToWindowSize = TRUE;
   changeWindow = TRUE;
   
   resetScene = FALSE;
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   return;
}

// clear buffers and color screen
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

float fogColor[3] = {0.7, 0.7, 0.7};
glFogfv(GL_FOG_COLOR, fogColor);
glDisable(GL_FOG);

// disable z buffering
glDepthMask(GL_FALSE);

// make the window fit into a 100x100 area
winWdthPercentMult = (rI.winWdth / 100.0) / (rI.winWdth / staticWinWidth);
winHghtPercentMult = (rI.winHght / 100.0) / (rI.winHght / staticWinHeight);
glScalef(winWdthPercentMult, winHghtPercentMult, 1.0);

// make drawn objects relative to window size
glScalef(rI.winWdth / staticWinWidth, rI.winWdth / staticWinWidth, rI.winWdth / staticWinWidth);

// use a polygon to create a background color
glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3, GL_FLOAT, 0, backgroundVertex);
glEnableClientState(GL_COLOR_ARRAY);
glColorPointer(4, GL_UNSIGNED_BYTE, 0, backgroundVColor);
glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, backgroundVector);

menuHighlightOption = 0;

if (viewMainMenu)
{
   // clickable area for entering game
   if ((xMousePercent >= 50-5) &&
       (yMousePercent >= 50+0) &&
       (yMousePercent <= 50+10))
   menuHighlightOption = 1;

   // clickable area for entering options menu
   if ((xMousePercent >= 50-5) &&
       (yMousePercent >= 50+10) &&
       (yMousePercent <= 50+20))
   menuHighlightOption = 2;

   // clickable area for entering view controls menu
   if ((xMousePercent >= 50-5) &&
       (yMousePercent >= 50+20) &&
       (yMousePercent <= 50+30))
   menuHighlightOption = 3;

   // clickable area for exit
   if ((xMousePercent >= 50-5) &&
       (yMousePercent >= 50+30) &&
       (yMousePercent <= 50+40))
   menuHighlightOption = 4;
}

if (viewControls)
{
   // clickable area for back to menu option
   if ((xMousePercent <= 50) &&
       (yMousePercent >= 50-10) &&
       (yMousePercent <= 50-0))
   menuHighlightOption = 1;
}

if (viewOptions)
{
   // clickable area for full screen option
   if ((xMousePercent >= 14*2) &&
       (xMousePercent <= 23*2) &&
       (yMousePercent >= 50-50) &&
       (yMousePercent <= 50-40))
   menuHighlightOption = 1;
   
   // clickable area for display option
   if ((xMousePercent >= 13*2) &&
       (xMousePercent <= 16*2) &&
       (yMousePercent >= 50-40) &&
       (yMousePercent <= 50-30))
   menuHighlightOption = 2;
   if ((xMousePercent >= (23 + (int)strlen(optDisplayScrnResTxt)-23)*2) &&
       (xMousePercent <= (26 + (int)strlen(optDisplayScrnResTxt)-23)*2) &&
       (yMousePercent >= 50-40) &&
       (yMousePercent <= 50-30))
   menuHighlightOption = 3;
   
   // clickable area for window size option
   if ((xMousePercent >= 9*2) &&
       (xMousePercent <= 12*2) &&
       (yMousePercent >= 50-30) &&
       (yMousePercent <= 50-20))
   menuHighlightOption = 4;
   if ((xMousePercent >= (19 + (int)strlen(optWindowSizeTxt)-19)*2) &&
       (xMousePercent <= (22 + (int)strlen(optWindowSizeTxt)-19)*2) &&
       (yMousePercent >= 50-30) &&
       (yMousePercent <= 50-20))
   menuHighlightOption = 5;
   
   // clickable area for fog option
   if ((xMousePercent >= 6*2) &&
       (xMousePercent <= 15*2) &&
       (yMousePercent >= 50-20) &&
       (yMousePercent <= 50-10))
   menuHighlightOption = 6;
   
   // clickable area for texture option
   if ((xMousePercent >= 10*2) &&
       (xMousePercent <= 19*2) &&
       (yMousePercent >= 50-10) &&
       (yMousePercent <= 50-0))
   menuHighlightOption = 7;
   
   // clickable area for apply graphics option
   if ((xMousePercent <= 50) &&
       (yMousePercent >= 50+10) &&
       (yMousePercent <= 50+20))
   menuHighlightOption = 8;
   
   // clickable area for back to menu option
   if ((xMousePercent <= 50) &&
       (yMousePercent >= 50+20) &&
       (yMousePercent <= 50+30))
   menuHighlightOption = 9;
}

if (leftMouseClick)
{
   if (viewMainMenu)
   {
      // click on Play Game and go to next scene
      if (menuHighlightOption == 1)
      {
         resetScene = 1;
         sceneNumber = 1;
      }
      // go to Options menu after click
      if (menuHighlightOption == 2)
      {
         viewMainMenu = 0;
         viewOptions = 1;
         menuHighlightOption = 0;
      }
      // go to View Controls after click
      if (menuHighlightOption == 3)
      {
         viewMainMenu = 0;
         viewControls = 1;
         menuHighlightOption = 0;
      }
      // click on Exit and exit program
      if (menuHighlightOption == 4)
      {
         exitMsg = 1;
         return;
      }
   }
   
   if (viewControls)
   {  
      // exit View Controls if "BACK TO MENU" is clicked
      if (menuHighlightOption == 1)
      {
         viewMainMenu = 1;
         viewControls = 0;
         menuHighlightOption = 0;
      }
   }
   
   if (viewOptions)
   {
      // change full screen option if clicked
      if (menuHighlightOption == 1)
      {
         optFullScreen = !optFullScreen;
         if (optFullScreen)
         sprintf(optFullScreenTxt, "%s", "Full Screen: [ yes ]");
         else
         sprintf(optFullScreenTxt, "%s", "Full Screen: [ no ]");
      }
      
      // change display option if clicked
      if (menuHighlightOption == 2)
      {
         i = displayIndex;
         displayIndex = getNextDisplayResDown(&xScrnRes, &yScrnRes, colorDepth);
         if (displayIndex == -1)
         displayIndex = i;
         sprintf(optDisplayScrnResTxt, "   Display: < %ix%i >", xScrnRes, yScrnRes);
      }
      // change display option if clicked
      if (menuHighlightOption == 3)
      {
         i = displayIndex;
         displayIndex = getNextDisplayResUp(&xScrnRes, &yScrnRes, colorDepth);
         if (displayIndex == -1)
         displayIndex = i;
         sprintf(optDisplayScrnResTxt, "   Display: < %ix%i >", xScrnRes, yScrnRes);
      }
      
      // change window size option if clicked
      if (menuHighlightOption == 4)
      {
         if ((optWinWidth > 200) && (optWinHeight > 200))
         {
            // increase the view port by 1/8 the window size
            optWinWidth = optWinWidth - staticWinWidth/8;
            optWinHeight = optWinHeight - staticWinHeight/8;
            
            if (optWinWidth*scrnRatio >= yScrnRes)
            sprintf(optWindowSizeTxt, "Window: < %ix%i > (Full Size)", (int)optWinWidth, (int)optWinHeight);
            else
            sprintf(optWindowSizeTxt, "Window: < %ix%i >", (int)optWinWidth, (int)optWinHeight);
         }
      }
      // change window size option if clicked
      if (menuHighlightOption == 5)
      {
         if (optWinWidth*scrnRatio < yScrnRes)
         {
            // decrease the view port by 1/8 the window size
            optWinWidth = optWinWidth + staticWinWidth/8;
            optWinHeight = optWinHeight + staticWinHeight/8;
            
            if (optWinWidth*scrnRatio >= yScrnRes)
            sprintf(optWindowSizeTxt, "Window: < %ix%i > (Full Size)", (int)optWinWidth, (int)optWinHeight);
            else
            sprintf(optWindowSizeTxt, "Window: < %ix%i >", (int)optWinWidth, (int)optWinHeight);
         }
      }
      
      // change fog option if clicked
      if (menuHighlightOption == 6)
      {
         optFog = !optFog;
         if (optFog)
         sprintf(optFogTxt, "%s", "Fog: [ yes ]");
         else
         sprintf(optFogTxt, "%s", "Fog: [ no ]");
      }
      
      // change texture option if clicked
      if (menuHighlightOption == 7)
      {
         optTexture = !optTexture;
         if (optTexture)
         sprintf(optTextureTxt, "%s", "Texture: [ yes ]");
         else
         sprintf(optTextureTxt, "%s", "Texture: [ no ]");
      }
      
      // apply graphics settings
      if (menuHighlightOption == 8)
      {
         // change into full screen mode
         if ((optFullScreen) && (!fullScreenMode))
         {
            changefullScreenMode = 1;
            winWdthSave = rI.winWdth + xFrameOffset * 2;
            winHghtSave = rI.winHght + yFrameOffset * 2;
         }
         // change out of full screen mode
         if ((!optFullScreen) && (fullScreenMode))
         changefullScreenMode = 1;
         
         // change display resolution
         if (optFullScreen)
         {
            changeDisplayMode = 1;
            
            if (fullScreenMode)
            changeDisplayRes(displayIndex);
         }
         
         // change the view port size
         if (staticViewPortHeight != optWinHeight)
         {
            staticViewPortWidth = optWinWidth;
            staticViewPortHeight = optWinHeight;
            
            if (staticViewPortWidth > xScrnRes)
            staticViewPortWidth = xScrnRes;
            
            if (staticViewPortHeight > yScrnRes)
            staticViewPortHeight = yScrnRes;
            
            changeWindow = 1;
         }
         
         // set the "useFog" variable true or false
         if (optFog)
         useFog = TRUE;
         else
         useFog = FALSE;
         
         // set the "useTexture" variable true or false
         if (optTexture)
         useTexture = TRUE;
         else
         useTexture = FALSE;
      }
      
      // exit the options menu if clicked
      if (menuHighlightOption == 9)
      {
         viewMainMenu = 1;
         viewOptions = 0;
         menuHighlightOption = 0;
      }
   }
}

if (viewMainMenu)
{
   // initial x location of highlighter polygon
   quadVertexData[0] = -5;
   quadVertexData[3] = 50;
   quadVertexData[6] = 50;
   quadVertexData[9] = -5;
   
   // initial y location of highlighter polygon
   quadVertexData[1] = 10000;
   quadVertexData[4] = 10000;
   quadVertexData[7] = 10000;
   quadVertexData[10] = 10000;
   
   // highlight "PLAY GAME" menu item
   if (menuHighlightOption == 1)
   {
      quadVertexData[1] = 0;
      quadVertexData[4] = 0;
      quadVertexData[7] = -10;
      quadVertexData[10] = -10;
   }
   
   // highlight "OPTIONS" menu item
   if (menuHighlightOption == 2)
   {
      quadVertexData[1] = 0 - 10;
      quadVertexData[4] = 0 - 10;
      quadVertexData[7] = -10 - 10;
      quadVertexData[10] = -10 - 10;
   }
   
   // highlight "VIEW CONTROLS" menu item
   if (menuHighlightOption == 3)
   {
      quadVertexData[1] = 0 - 20;
      quadVertexData[4] = 0 - 20;
      quadVertexData[7] = -10 - 20;
      quadVertexData[10] = -10 - 20;
   }
   
   // highlight "EXIT" menu item
   if (menuHighlightOption == 4)
   {
      quadVertexData[1] = 0 - 30;
      quadVertexData[4] = 0 - 30;
      quadVertexData[7] = -10 - 30;
      quadVertexData[10] = -10 - 30;
   }
   
   // draw highlighter polygon
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, quadVertexData);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4, GL_UNSIGNED_BYTE, 0, polyVColorData);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, polyVectorData);
   
   // draw main menu text
   drawAscii("PLAY GAME", 3, 3, 0, -5, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("OPTIONS", 3, 3, 0, -15, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("VIEW CONTROLS", 3, 3, 0, -25, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("EXIT", 3, 3, 0, -35, 0, 0, 0, 0, 1, 0x0, 1);
}

if (viewControls)
{
   // initial y location of highlighter polygon
   quadVertexData[1] = 10000;
   quadVertexData[4] = 10000;
   quadVertexData[7] = 10000;
   quadVertexData[10] = 10000;
   
   // highlight "BACK TO MENU" menu item
   if (menuHighlightOption == 1)
   {
      quadVertexData[0] = -48;
      quadVertexData[3] = 0;
      quadVertexData[6] = 0;
      quadVertexData[9] = -48;
      
      quadVertexData[1] = 10;
      quadVertexData[4] = 10;
      quadVertexData[7] = 0;
      quadVertexData[10] = 0;
   }
   
   // draw highlighter polygon
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, quadVertexData);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4, GL_UNSIGNED_BYTE, 0, polyVColorData);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, polyVectorData);
   
   // draw the view controls screen text
   drawAscii("MOVE = ARROW KEYS", 2, 3,
             -45, 45, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("JUMP = SPACE BAR", 2, 3,
             -45, 35, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("ZOOM CAMERA = PAGEUP/PAGEDOWN", 2, 3,
             -45, 25, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("BACK TO MENU", 2, 3,
             -45, 5, 0, 0, 0, 0, 1, 0x0, 1);
}

if (viewOptions)
{
   // keep refreshing the view port window
   // if the monitor size changes, this will allow
   // the view port to adjust correctly afterwards
   changeWindow = 1;
   
   // initial y location of highlighter polygon
   quadVertexData[1] = 10000;
   quadVertexData[4] = 10000;
   quadVertexData[7] = 10000;
   quadVertexData[10] = 10000;
   
   // highlighter for full screen option
   if (menuHighlightOption == 1)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -50 + 14 * 2;
      quadVertexData[3] = -50 + 23 * 2;
      quadVertexData[6] = -50 + 23 * 2;
      quadVertexData[9] = -50 + 14 * 2;
      
      // change the y position of the highlighter
      quadVertexData[1] = 50;
      quadVertexData[4] = 50;
      quadVertexData[7] = 40;
      quadVertexData[10] = 40;
   }
   
   // highlighter for display option
   if (menuHighlightOption == 2)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -50 + 13 * 2;
      quadVertexData[3] = -50 + 16 * 2;
      quadVertexData[6] = -50 + 16 * 2;
      quadVertexData[9] = -50 + 13 * 2;
      
      // change the y position of the highlighter
      quadVertexData[1] = 40;
      quadVertexData[4] = 40;
      quadVertexData[7] = 30;
      quadVertexData[10] = 30;
   }
   if (menuHighlightOption == 3)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -50 + (23 + (int)strlen(optDisplayScrnResTxt)-23) * 2;
      quadVertexData[3] = -50 + (26 + (int)strlen(optDisplayScrnResTxt)-23) * 2;
      quadVertexData[6] = -50 + (26 + (int)strlen(optDisplayScrnResTxt)-23) * 2;
      quadVertexData[9] = -50 + (23 + (int)strlen(optDisplayScrnResTxt)-23) * 2;
      
      // change the y position of the highlighter
      quadVertexData[1] = 40;
      quadVertexData[4] = 40;
      quadVertexData[7] = 30;
      quadVertexData[10] = 30;
   }
   
   // highlighter for window size option
   if (menuHighlightOption == 4)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -50 + 9 * 2;
      quadVertexData[3] = -50 + 12 * 2;
      quadVertexData[6] = -50 + 12 * 2;
      quadVertexData[9] = -50 + 9 * 2;
      
      // change the y position of the highlighter
      quadVertexData[1] = 30;
      quadVertexData[4] = 30;
      quadVertexData[7] = 20;
      quadVertexData[10] = 20;
   }
   // if window is not bigger than screen
   if ((optWinWidth < xScrnRes) || (optWinHeight < yScrnRes))
   if (menuHighlightOption == 5)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -50 + (19 + (int)strlen(optWindowSizeTxt)-19) * 2;
      quadVertexData[3] = -50 + (22 + (int)strlen(optWindowSizeTxt)-19) * 2;
      quadVertexData[6] = -50 + (22 + (int)strlen(optWindowSizeTxt)-19) * 2;
      quadVertexData[9] = -50 + (19 + (int)strlen(optWindowSizeTxt)-19) * 2;
      
      // change the y position of the highlighter
      quadVertexData[1] = 30;
      quadVertexData[4] = 30;
      quadVertexData[7] = 20;
      quadVertexData[10] = 20;
   }
   
   // highlighter for fog option
   if (menuHighlightOption == 6)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -50 + 6 * 2;
      quadVertexData[3] = -50 + 15 * 2;
      quadVertexData[6] = -50 + 15 * 2;
      quadVertexData[9] = -50 + 6 * 2;
      
      // change the y position of the highlighter
      quadVertexData[1] = 20;
      quadVertexData[4] = 20;
      quadVertexData[7] = 10;
      quadVertexData[10] = 10;
   }
   
   // highlighter for Texture option
   if (menuHighlightOption == 7)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -50 + 10 * 2;
      quadVertexData[3] = -50 + 19 * 2;
      quadVertexData[6] = -50 + 19 * 2;
      quadVertexData[9] = -50 + 10 * 2;
      
      // change the y position of the highlighter
      quadVertexData[1] = 10;
      quadVertexData[4] = 10;
      quadVertexData[7] = 0;
      quadVertexData[10] = 0;
   }
   
   // highlighter for apply settings option
   if (menuHighlightOption == 8)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -48;
      quadVertexData[3] = 0;
      quadVertexData[6] = 0;
      quadVertexData[9] = -48;
      
      // change the y position of the highlighter
      quadVertexData[1] = -10;
      quadVertexData[4] = -10;
      quadVertexData[7] = -20;
      quadVertexData[10] = -20;
   }
   
   // highlighter for back to menu option
   if (menuHighlightOption == 9)
   {
      // change the x position of the highlighter
      quadVertexData[0] = -48;
      quadVertexData[3] = 0;
      quadVertexData[6] = 0;
      quadVertexData[9] = -48;
      
      // change the y position of the highlighter
      quadVertexData[1] = -20;
      quadVertexData[4] = -20;
      quadVertexData[7] = -30;
      quadVertexData[10] = -30;
   }
   
   // draw highlighter polygon
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, quadVertexData);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(4, GL_UNSIGNED_BYTE, 0, polyVColorData);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, polyVectorData);
   
   
   // draw options menu text
   drawAscii(optFullScreenTxt, 2, 3,
             -45, 45, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii(optDisplayScrnResTxt, 2, 3,
             -45, 35, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii(optWindowSizeTxt, 2, 3,
             -45, 25, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii(optFogTxt, 2, 3,
             -45, 15, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii(optTextureTxt, 2, 3,
             -45, 5, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("APPLY SETTINGS", 2, 3,
             -45, -15, 0, 0, 0, 0, 1, 0x0, 1);
   drawAscii("BACK TO MENU", 2, 3,
             -45, -25, 0, 0, 0, 0, 1, 0x0, 1);
}

// return the matrix back to its original size
glScalef(staticWinWidth / rI.winWdth, staticWinWidth / rI.winWdth, staticWinWidth / rI.winWdth);

// undo make the window fit into a 100x100 area
winWdthPercentMult = (rI.winWdth / staticWinWidth) / (rI.winWdth / 100.0);
winHghtPercentMult = (rI.winHght / staticWinHeight) / (rI.winHght / 100.0);
glScalef(winWdthPercentMult, winHghtPercentMult, 1.0);

// enable z buffering
glDepthMask(GL_TRUE);
