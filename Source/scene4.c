if (resetScene)
{
   // reset transformation data
   copyTransFromTo(&cubes_STATICTRANS[0], &cubes_TRANS[0], cubes_MESHCNT);
   
   endAllSound();// stop sound
   
   startNewGame = TRUE;
   changePlaneColor = FALSE;
   startCountDown = FALSE;
   showGameScore = FALSE;
   gameSpeedInc = 0;
   scoreNumber = -1;
   
   // keep the draw size relative to the window size
   contentRelativeToWindowSize = FALSE;// use with applyMeshViewRotLocSz() if TRUE
   changeWindow = TRUE;
   
   resetScene = FALSE;
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   return;
}


// reset mesh data for each frame
copyMeshFromTo(&cubes_STATICPOINT[0], &cubes_POINTDATSZ[0], 0,
               &cubes_POINT[0], &cubes_POINTDATSZ[0], 0, cubes_MESHCNT);


// control the rotation of the cubes by holding down the left mouse button and dragging
if (leftMouseDown)
{
   localConcurrentAxisRot(&cubes_TRANS[0], cubes_blue, 0, 0, 0, -yDragLgth, -xDragLgth, 0);
   localConcurrentAxisRot(&cubes_TRANS[0], cubes_cyan, 0, 0, 0, -yDragLgth, -xDragLgth, 0);
   localConcurrentAxisRot(&cubes_TRANS[0], cubes_green, 0, 0, 0, -yDragLgth, -xDragLgth, 0);
   localConcurrentAxisRot(&cubes_TRANS[0], cubes_magenta, 0, 0, 0, -yDragLgth, -xDragLgth, 0);
   localConcurrentAxisRot(&cubes_TRANS[0], cubes_red, 0, 0, 0, -yDragLgth, -xDragLgth, 0);
   localConcurrentAxisRot(&cubes_TRANS[0], cubes_yellow, 0, 0, 0, -yDragLgth, -xDragLgth, 0);
}


// right click to reset or start new game
if (rightMouseClick)
{
   if (startNewGame)
   {
      gameSpeedInc = 0;
      scoreNumber = -1;
      
      changePlaneColor = TRUE;
      startNewGame = FALSE;
   }
   
   if (showGameScore)
   {
      startNewGame = TRUE;
      showGameScore = FALSE;
      startCountDown = FALSE;
   }
}


// randomly change the color of the plane
if (changePlaneColor)
{
   randomNumber = round((float)rand() / RAND_MAX * 5);
   
   if (randomNumber == 0)
   {
      red = 255;
      green = 0;
      blue = 0;
   }
   
   if (randomNumber == 1)
   {
      red = 0;
      green = 255;
      blue = 0;
   }
   
   if (randomNumber == 2)
   {
      red = 0;
      green = 0;
      blue = 255;
   }
   
   if (randomNumber == 3)
   {
      red = 0;
      green = 255;
      blue = 255;
   }
   
   if (randomNumber == 4)
   {
      red = 255;
      green = 0;
      blue = 255;
   }
   
   if (randomNumber == 5)
   {
      red = 255;
      green = 255;
      blue = 0;
   }
   
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+0] = red;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+1] = green;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+2] = blue;
   
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+4] = red;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+5] = green;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+6] = blue;
   
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+8] = red;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+9] = green;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+10] = blue;
   
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+12] = red;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+13] = green;
   cubes_VCOLOR[cubes_VCOLORDATSZ[cubes_plane]+14] = blue;
   
   // reset count down and increase game speed for each color match
   timerCountDown = 100 - gameSpeedInc;
   gameSpeedInc++;
   
   // increase score for each color match
   scoreNumber++;
   
   startNewGame = FALSE;
   showGameScore = FALSE;
   startCountDown = TRUE;
   
   changePlaneColor = FALSE;
}


// while the game is in count down mode
if (startCountDown)
{
   // if the right colored cube is matching the plane
   // then go into "changePlaneColor" mode
   if (randomNumber == 0)
   if (cubes_TRANS[cubes_red*TRSZ+LOCZ] > cubes_TRANS[cubes_plane*TRSZ+LOCZ])
   changePlaneColor = TRUE;

   if (randomNumber == 1)
   if (cubes_TRANS[cubes_green*TRSZ+LOCZ] > cubes_TRANS[cubes_plane*TRSZ+LOCZ])
   changePlaneColor = TRUE;

   if (randomNumber == 2)
   if (cubes_TRANS[cubes_blue*TRSZ+LOCZ] > cubes_TRANS[cubes_plane*TRSZ+LOCZ])
   changePlaneColor = TRUE;

   if (randomNumber == 3)
   if (cubes_TRANS[cubes_cyan*TRSZ+LOCZ] > cubes_TRANS[cubes_plane*TRSZ+LOCZ])
   changePlaneColor = TRUE;

   if (randomNumber == 4)
   if (cubes_TRANS[cubes_magenta*TRSZ+LOCZ] > cubes_TRANS[cubes_plane*TRSZ+LOCZ])
   changePlaneColor = TRUE;

   if (randomNumber == 5)
   if (cubes_TRANS[cubes_yellow*TRSZ+LOCZ] > cubes_TRANS[cubes_plane*TRSZ+LOCZ])
   changePlaneColor = TRUE;

   // count down until zero
   timerCountDown--;

   if (timerCountDown == 0)
   {
      startNewGame = FALSE;
      showGameScore = TRUE;
      startCountDown = FALSE;
   }
}


////////////////////////////////////////////////////////////////////
// DRAW //

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.65f, 0.65f, 0.65f, 1.0f);

glDisable(GL_FOG);


// apply transformation data to the meshes
applyRotLocSz(&cubes_TRANS[0], &cubes_POINT[0], &cubes_POINTDATSZ[0], 0, cubes_MESHCNT);

cubes_HIDE[cubes_plane] = TRUE;

// draw mesh
drawMesh(&cubes_POINT[0], &cubes_QUAD[0], &cubes_TRI[0], &cubes_VCOLOR[0],
         &cubes_TEX[0], &cubes_TEXCOORD[0], &cubes_TEXLINKDAT[0],
         &cubes_QUADDATSZ[0], &cubes_TRIDATSZ[0], &cubes_HIDE[0], 0, cubes_MESHCNT, rI);

cubes_HIDE[cubes_plane] = FALSE;


// transparent meshes are best rendered at the end
glEnable(GL_BLEND); // make transparent
glDepthMask(GL_FALSE); // disable z buffering

// draw mesh
drawMesh(&cubes_POINT[0], &cubes_QUAD[0], &cubes_TRI[0], &cubes_VCOLOR[0],
         &cubes_TEX[0], &cubes_TEXCOORD[0], &cubes_TEXLINKDAT[0],
         &cubes_QUADDATSZ[0], &cubes_TRIDATSZ[0], &cubes_HIDE[0], cubes_plane, 1, rI);

glDepthMask(GL_TRUE);
glDisable(GL_BLEND);


// display status and usage text
if (startNewGame)
printfScrn(0, 0, 32, 0x0, rI, "Right click to play!");

if (startCountDown)
printfScrn(0, 0, 32, 0x0, rI, "Find color %i", timerCountDown);

if (showGameScore)
printfScrn(0, 0, 32, 0x0, rI, "Score:%i", scoreNumber);

// END OF DRAW //
////////////////////////////////////////////////////////////////////
