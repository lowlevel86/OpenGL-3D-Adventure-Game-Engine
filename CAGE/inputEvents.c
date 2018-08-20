// move forwards or backwards
if ((keyDown[38]) || (keyPress[38]))
upArrowKeyPressed = TRUE;

if ((keyDown[40]) || (keyPress[40]))
downArrowKeyPressed = TRUE;

if ((keyUp[38]) && (!keyPress[38]))
upArrowKeyPressed = FALSE;

if ((keyUp[40]) && (!keyPress[40]))
downArrowKeyPressed = FALSE;


if ((upArrowKeyPressed) && (!downArrowKeyPressed))
{
   upArrowKeyFirst = TRUE;
   downArrowKeyFirst = FALSE;
}

if ((!upArrowKeyPressed) && (downArrowKeyPressed))
{
   upArrowKeyFirst = FALSE;
   downArrowKeyFirst = TRUE;
}

// toggle forwards or backwards depending on which was pressed first
forwardBackwardToggle = 0;
forward = 0;
backward = 0;

if ((upArrowKeyPressed) && (downArrowKeyPressed))
{
   if (upArrowKeyFirst)
   forwardBackwardToggle = 1;
   
   if (downArrowKeyFirst)
   forwardBackwardToggle = 2;
}

if (forwardBackwardToggle != 1)
if (upArrowKeyPressed)
{
   forward = 12.0;
   backward = 0;
}

if (forwardBackwardToggle != 2)
if (downArrowKeyPressed)
{
   forward = 0;
   backward = -12.0;
}


// turn left or right
if ((keyDown[37]) || (keyPress[37]))
leftArrowKeyPressed = TRUE;

if ((keyDown[39]) || (keyPress[39]))
rightArrowKeyPressed = TRUE;

if ((keyUp[37]) && (keyPress[37]))
leftArrowKeyPressed = FALSE;

if ((keyUp[39]) && (keyPress[39]))
rightArrowKeyPressed = FALSE;


if ((leftArrowKeyPressed) && (!rightArrowKeyPressed))
{
   leftArrowKeyFirst = TRUE;
   rightArrowKeyFirst = FALSE;
}

if ((!leftArrowKeyPressed) && (rightArrowKeyPressed))
{
   leftArrowKeyFirst = FALSE;
   rightArrowKeyFirst = TRUE;
}

// toggle left or right depending on which was pressed first
leftRightToggle = 0;
turnLeft = 0;
turnRight = 0;

if ((leftArrowKeyPressed) && (rightArrowKeyPressed))
{
   if (leftArrowKeyFirst)
   leftRightToggle = 1;
   
   if (rightArrowKeyFirst)
   leftRightToggle = 2;
}

if (forward)
{
   if (leftRightToggle != 1)
   if (leftArrowKeyPressed)
   turnLeft = 6;

   if (leftRightToggle != 2)
   if (rightArrowKeyPressed)
   turnRight = -6;
}

if (backward)
{
   if (leftRightToggle != 1)
   if (leftArrowKeyPressed)
   turnLeft = -6;

   if (leftRightToggle != 2)
   if (rightArrowKeyPressed)
   turnRight = 6;
}

if ((!forward) && (!backward))
{
   if (leftRightToggle != 1)
   if (leftArrowKeyPressed)
   turnLeft = 6;

   if (leftRightToggle != 2)
   if (rightArrowKeyPressed)
   turnRight = -6;
}

turnLeftRight += turnLeft + turnRight;

// jump
if ((keyDown[32]) || (keyPress[32]))// space key
jumpUp = TRUE;

// end jump
if ((keyUp[32]) && (!keyPress[32]))// space key
{
   alreadyJumped = FALSE;
   jumpUp = FALSE;
}

// lift up or put down object
if (keyPress[88])// x key
liftPutDownObj = TRUE;


// move camera
if (keyDown[33])// page up key
moveCloser = TRUE;
if (keyDown[34])// page down key
moveAway = TRUE;

if (!keyDown[33])// page up key
moveCloser = FALSE;
if (!keyDown[34])// page down key
moveAway = FALSE;

if (keyPress[27])// Esc
{
   // exit from the game scene first
   if ((viewMainMenu) && (sceneNumber == 0))
   {
      exitMsg = 1;
   }
   else
   {
      sceneNumber = 0;
      viewMainMenu = 1;
      viewControls = 0;
      viewOptions = 0;
      resetScene = TRUE;
   }
}
