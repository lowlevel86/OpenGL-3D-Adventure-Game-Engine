if (resetScene)
{
   cameraDistance = 100;
   
   // reset transformation data
   copyTransFromTo(&camera_STATICTRANS[0], &camera_TRANS[0], camera_MESHCNT);
   copyTransFromTo(&dome2_STATICTRANS[0], &dome2_TRANS[0], dome2_MESHCNT);
   copyTransFromTo(&course2_STATICTRANS[0], &course2_TRANS[0], course2_MESHCNT);
   copyTransFromTo(&character_STATICTRANS[0], &character_TRANS[0], character_MESHCNT);
   copyTransFromTo(&shadow_STATICTRANS[0], &shadow_TRANS[0], shadow_MESHCNT);

   // starting character location and rotation
   globalRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 0, 0, 180);
   globalMove(&character_TRANS[0], character_MESHCNT, 0, 0, 200);
   
   // starting rotation
   turnLeftRight = 0;
   
   // starting fall speed
   fallSpeed = 0;
   
   // reset animations
   animateRunCycle = 0;
   animateJumpInPlace = 0;
   moveOcean = 0;
   
   endAllSound();// stop sound
   
   // play sound in the background with looping and no concurrent playing
   mixPlaySound(oceanSndData, sizeof(oceanSndData), TRUE, FALSE);
   
   // keep the draw size relative to the window size
   contentRelativeToWindowSize = TRUE;
   changeWindow = TRUE;
   
   resetScene = FALSE;
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   return;
}


// reset mesh data for each frame
copyMeshFromTo(&camera_STATICPOINT[0], &camera_POINTDATSZ[0], 0,
               &camera_POINT[0], &camera_POINTDATSZ[0], 0, camera_MESHCNT);
copyMeshFromTo(&dome2_STATICPOINT[0], &dome2_POINTDATSZ[0], 0,
               &dome2_POINT[0], &dome2_POINTDATSZ[0], 0, dome2_MESHCNT);
copyMeshFromTo(&course2_STATICPOINT[0], &course2_POINTDATSZ[0], 0,
               &course2_POINT[0], &course2_POINTDATSZ[0], 0, course2_MESHCNT);
copyMeshFromTo(&character_STATICPOINT[0], &character_POINTDATSZ[0], 0,
               &character_POINT[0], &character_POINTDATSZ[0], 0, character_MESHCNT);
copyMeshFromTo(&shadow_STATICPOINT[0], &shadow_POINTDATSZ[0], 0,
               &shadow_POINT[0], &shadow_POINTDATSZ[0], 0, shadow_MESHCNT);


// turn the character toward the direction it is moving

// if moving forwards
if ((forward) && (!backward))
{
   // save the current location and rotation
   copyLocFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);
   
   // reset location and rotation
   copyLocFromTo(&character_STATICTRANS[0], &character_TRANS[0], character_MESHCNT);
   copyUcRotFromTo(&character_STATICTRANS[0], &character_TRANS[0], character_MESHCNT);

   // rotate the character to make it face forward
   globalRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 0, 0, turnLeftRight + 180);
   
   // rotate the character more if turning
   if ((turnLeft) && (!turnRight))
   globalRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 0, 0, 9);
   
   if ((turnRight) && (!turnLeft))
   globalRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 0, 0, -9);
   
   // move the character back where it was
   globalMove(&character_TRANS[0], character_MESHCNT, buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
}

// if moving backwards
if ((backward) && (!forward))
{
   // save the current location and rotation
   copyLocFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);
   
   // reset location and rotation
   copyLocFromTo(&character_STATICTRANS[0], &character_TRANS[0], character_MESHCNT);
   copyUcRotFromTo(&character_STATICTRANS[0], &character_TRANS[0], character_MESHCNT);

   // rotate the character to make it face forward
   globalRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 0, 0, turnLeftRight);
   
   // rotate the character more if turning
   if ((turnLeft) && (!turnRight))
   globalRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 0, 0, 9);
   
   if ((turnRight) && (!turnLeft))
   globalRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, 0, 0, -9);
   
   // move the character back where it was
   globalMove(&character_TRANS[0], character_MESHCNT, buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
}



// if the character is inside a course object then move it out
globalBoxKnockOut(&course2_TRANS[0], course2_MESHCNT,
                  &character_TRANS[character_box*TRSZ], 0.001,
                  &xMove, &yMove, &zMove, &contact);

if (contact)
globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);


// find if the character's feet is touching the floor for later use
globalBoxDetectAndMove(&course2_TRANS[0], course2_MESHCNT,
                       &character_TRANS[character_feetBox*TRSZ], 0.001,
                       0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &feetContact);


// find if the character hits his head for later use
globalBoxDetectAndMove(&course2_TRANS[0], course2_MESHCNT,
                       &character_TRANS[character_headBox*TRSZ], 0.001,
                       0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &headContact);



// get the control force that will be used to move the character in the x,y plane
xCtrlForce = 0;
yCtrlForce = forward + backward;
zCtrlForce = 0;
rotate(&xCtrlForce, &yCtrlForce, &zCtrlForce, 0, 0, turnLeftRight);



// lift or put down object
if (liftPutDownObj)
{
   if (holdObj)
   holdObj = FALSE;
   else
   for (i=0; i < total_objs; i++)
   {
      current_obj = first_obj + i;
      
      xArmsReach = character_TRANS[character_frontBox*TRSZ+LOCX];
      yArmsReach = character_TRANS[character_frontBox*TRSZ+LOCY];
      zArmsReach = character_TRANS[character_frontBox*TRSZ+LOCZ];
      
      ptToBoxCollision(&course2_TRANS[current_obj*TRSZ],
                       character_TRANS[character_box*TRSZ+LOCX],
                       character_TRANS[character_box*TRSZ+LOCY],
                       character_TRANS[character_box*TRSZ+LOCZ],
                       &xArmsReach, &yArmsReach, &zArmsReach, &impactFace, &outside);
      
      if (impactFace)
      {
         lifted_obj = current_obj;
         holdObj = TRUE;
      }
   }
   
   liftPutDownObj = FALSE;
}


// move the object the character is holding out of the way
// so that it does not interfere with anything else
if (holdObj)
localMove(&course2_TRANS[0], lifted_obj, 0, 0, 100000);

for (i=0; i < total_objs; i++)
{
   current_obj = first_obj+i;
   
   // calculate gravity for the movable object
   if (objFallSpeed[i] < fall_speed_limit)
   objFallSpeed[i] += gravity_force;
   
   zObjCtrlForce[i] = -objFallSpeed[i];

   
   // if the movable object is inside another object then move it out
   globalBoxKnockOut(&course2_TRANS[0], course2_MESHCNT,
                     &course2_TRANS[current_obj*TRSZ], 0.001,
                     &xMove, &yMove, &zMove, &contact);

   localMove(&course2_TRANS[0], current_obj, xMove, yMove, zMove);

   
   // if a movable object collides into a course object
   // then move it to the point before collision
   globalBoxCollision(&course2_TRANS[0], course2_MESHCNT,
                      &course2_TRANS[current_obj*TRSZ], 0.001,
                      xObjCtrlForce[i], yObjCtrlForce[i], zObjCtrlForce[i],
                      &xMove, &yMove, &zMove, &meshNum, &impact, &contact);

   if ((impact) || (contact))
   objFallSpeed[i] = 0;
   
   localMove(&course2_TRANS[0], current_obj, xMove, yMove, zMove);

   
   // allow the character to slide the movable object around
   globalBoxCollision(&course2_TRANS[current_obj*TRSZ], 1,
                      &character_TRANS[character_box*TRSZ], 0.001,
                      xCtrlForce, yCtrlForce, zCtrlForce,
                      &xMove, &yMove, &zMove, &meshNum, &impact, &contact);

   // divide by 2 for friction
   if (impact)
   localMove(&course2_TRANS[0], current_obj, xCtrlForce/2, yCtrlForce/2, zCtrlForce/2);
}



// find if the character collides with an object in the x,y plane
globalBoxCollision(&course2_TRANS[0], course2_MESHCNT,
                  &character_TRANS[character_box*TRSZ], 0.001,
                  xCtrlForce, yCtrlForce, zCtrlForce,
                  &xMove, &yMove, &zMove, &meshNum, &boxImpactData, &contact);

// move the character as much as possible
globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);

// find the direction the character will move after hitting an object
boxSkid(&course2_TRANS[meshNum*TRSZ], &character_TRANS[character_box*TRSZ],
        xCtrlForce-xMove, yCtrlForce-yMove, zCtrlForce-zMove,
        boxImpactData, &xArrow, &yArrow, &zArrow);

// find the distance the character has left to travel after hitting an object
travelDistance = getTravelLength(xCtrlForce-xMove, yCtrlForce-yMove, zCtrlForce-zMove);

// find the angle of the path before and after hitting an object
noAngle = getDirectionChgAngle(xCtrlForce, yCtrlForce, zCtrlForce,
                               xArrow, yArrow, zArrow, &pathAngle);

// turn the angle (90 - 180 degrees) into a fraction (0.0 - 1.0)
angleFrac = (pathAngle-90) / 90;

// move the character in the direction of the slippage
if (noAngle == FALSE)
if (pathAngle-90 > xySlippageAngle)
{
   // find the amount of slippage
   travelDistance *= angleFrac * xySlippageAmt;
   
   globalBoxCollision(&course2_TRANS[0], course2_MESHCNT,
                      &character_TRANS[character_box*TRSZ], 0.001,
                      xArrow*travelDistance, yArrow*travelDistance, zArrow*travelDistance,
                      &xMove, &yMove, &zMove, &meshNum, &boxImpactData, &contact);

   globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);
}



// get the control force that will be used to move the character up and down the z axis
if (fallSpeed < fall_speed_limit)
fallSpeed += gravity_force;

zCtrlForce = -fallSpeed;

if (jumpSpeed > 0)
jumpSpeed -= jump_force_damper;

if (jumpSpeed < 0)
jumpSpeed = 0;

if (!jumpUp)
jumpSpeed = 0;

xCtrlForce = 0;
yCtrlForce = 0;
zCtrlForce += jumpSpeed;


// find if the character collides with an object along the z axis
globalBoxCollision(&course2_TRANS[0], course2_MESHCNT,
                  &character_TRANS[character_box*TRSZ], 0.001,
                  xCtrlForce, yCtrlForce, zCtrlForce,
                  &xMove, &yMove, &zMove, &meshNum, &boxImpactData, &contact);

// move the character as much as possible
globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);


// allow the character to jump if its feet is touching the floor
if (feetContact)
{
   zCtrlForce = -gravity_force;
   
   if (jumpUp)
   if (alreadyJumped == FALSE)// no double jumping
   {
      jumpSpeed = jump_force;
      zCtrlForce += jumpSpeed;
      
      mixPlaySound(jumpSndData, sizeof(jumpSndData), FALSE, TRUE);
      alreadyJumped = TRUE;
   }
   
   globalBoxCollision(&course2_TRANS[0], course2_MESHCNT,
                      &character_TRANS[character_box*TRSZ], 0.001,
                      xCtrlForce, yCtrlForce, zCtrlForce,
                      &xMove, &yMove, &zMove, &meshNum, &boxImpactData, &contact);

   globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);
   
   fallSpeed = 0;
   
   // reset animation
   animateJumpInPlace = 0;
}

// if the character bumps its head
if (headContact)
{
   zCtrlForce = -fallSpeed;
   jumpSpeed = 0;
}


// find the direction the character will move after hitting an object
boxSkid(&course2_TRANS[meshNum*TRSZ], &character_TRANS[character_box*TRSZ],
        xCtrlForce-xMove, yCtrlForce-yMove, zCtrlForce-zMove,
        boxImpactData, &xArrow, &yArrow, &zArrow);

// find the distance the character has left to travel after hitting an object
travelDistance = getTravelLength(xCtrlForce-xMove, yCtrlForce-yMove, zCtrlForce-zMove);

// find the angle of the path before and after hitting an object
noAngle = getDirectionChgAngle(xCtrlForce, yCtrlForce, zCtrlForce,
                               xArrow, yArrow, zArrow, &pathAngle);

// turn the angle (90 - 180 degrees) into a fraction (0.0 - 1.0)
angleFrac = (pathAngle-90) / 90;

// move the character in the direction of the slippage
if (zArrow < 0)// only if moving down
if (noAngle == FALSE)
if (pathAngle-90 > zSlippageAngle)
{
   // find the amount of slippage
   travelDistance *= angleFrac * zSlippageAmt;
   
   globalBoxCollision(&course2_TRANS[0], course2_MESHCNT,
                      &character_TRANS[character_box*TRSZ], 0.001,
                      xArrow*travelDistance, yArrow*travelDistance, zArrow*travelDistance,
                      &xMove, &yMove, &zMove, &meshNum, &boxImpactData, &contact);

   globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);
}



// move the ocean
moveOcean = moveOcean + 0.01;

animateTexCoordFromTo(&dome2_STATICTEXCOORD[0], &dome2_TEXCOORDDATSZ[0], dome2_ocean1,
                      &dome2_STATICTEXCOORD[0], &dome2_TEXCOORDDATSZ[0], dome2_ocean2, 1,
                      &dome2_TEXCOORD[0], &dome2_TEXCOORDDATSZ[0], dome2_ocean1, &moveOcean, 0, 1);



// animate course platforms

// normalize
localMove(&course2_TRANS[0], course2_rotPaddle1, -course2_TRANS[course2_paddleAxis*TRSZ+LOCX],
                                                 -course2_TRANS[course2_paddleAxis*TRSZ+LOCY],
                                                 -course2_TRANS[course2_paddleAxis*TRSZ+LOCZ]);
localRevRot(&course2_TRANS[0], course2_rotPaddle1, 0, 0, 0, course2_TRANS[course2_paddleAxis*TRSZ+ROTX],
                                                            course2_TRANS[course2_paddleAxis*TRSZ+ROTY],
                                                            course2_TRANS[course2_paddleAxis*TRSZ+ROTZ]);

// add rotation
localRot(&course2_TRANS[0], course2_rotPaddle1, 0, 0, 0, platformsRotSpeed, 0, 0);

// undo normalization
localRot(&course2_TRANS[0], course2_rotPaddle1, 0, 0, 0, course2_TRANS[course2_paddleAxis*TRSZ+ROTX],
                                                         course2_TRANS[course2_paddleAxis*TRSZ+ROTY],
                                                         course2_TRANS[course2_paddleAxis*TRSZ+ROTZ]);
localMove(&course2_TRANS[0], course2_rotPaddle1, course2_TRANS[course2_paddleAxis*TRSZ+LOCX],
                                                 course2_TRANS[course2_paddleAxis*TRSZ+LOCY],
                                                 course2_TRANS[course2_paddleAxis*TRSZ+LOCZ]);


// normalize
localMove(&course2_TRANS[0], course2_rotPaddle2, -course2_TRANS[course2_paddleAxis*TRSZ+LOCX],
                                                 -course2_TRANS[course2_paddleAxis*TRSZ+LOCY],
                                                 -course2_TRANS[course2_paddleAxis*TRSZ+LOCZ]);
localRevRot(&course2_TRANS[0], course2_rotPaddle2, 0, 0, 0, course2_TRANS[course2_paddleAxis*TRSZ+ROTX],
                                                            course2_TRANS[course2_paddleAxis*TRSZ+ROTY],
                                                            course2_TRANS[course2_paddleAxis*TRSZ+ROTZ]);

// add rotation
localRot(&course2_TRANS[0], course2_rotPaddle2, 0, 0, 0, platformsRotSpeed, 0, 0);

// undo normalization
localRot(&course2_TRANS[0], course2_rotPaddle2, 0, 0, 0, course2_TRANS[course2_paddleAxis*TRSZ+ROTX],
                                                         course2_TRANS[course2_paddleAxis*TRSZ+ROTY],
                                                         course2_TRANS[course2_paddleAxis*TRSZ+ROTZ]);
localMove(&course2_TRANS[0], course2_rotPaddle2, course2_TRANS[course2_paddleAxis*TRSZ+LOCX],
                                                 course2_TRANS[course2_paddleAxis*TRSZ+LOCY],
                                                 course2_TRANS[course2_paddleAxis*TRSZ+LOCZ]);


// normalize
localMove(&course2_TRANS[0], course2_rotPaddle3, -course2_TRANS[course2_paddleAxis*TRSZ+LOCX],
                                                 -course2_TRANS[course2_paddleAxis*TRSZ+LOCY],
                                                 -course2_TRANS[course2_paddleAxis*TRSZ+LOCZ]);
localRevRot(&course2_TRANS[0], course2_rotPaddle3, 0, 0, 0, course2_TRANS[course2_paddleAxis*TRSZ+ROTX],
                                                            course2_TRANS[course2_paddleAxis*TRSZ+ROTY],
                                                            course2_TRANS[course2_paddleAxis*TRSZ+ROTZ]);

// add rotation
localRot(&course2_TRANS[0], course2_rotPaddle3, 0, 0, 0, platformsRotSpeed, 0, 0);

// undo normalization
localRot(&course2_TRANS[0], course2_rotPaddle3, 0, 0, 0, course2_TRANS[course2_paddleAxis*TRSZ+ROTX],
                                                         course2_TRANS[course2_paddleAxis*TRSZ+ROTY],
                                                         course2_TRANS[course2_paddleAxis*TRSZ+ROTZ]);
localMove(&course2_TRANS[0], course2_rotPaddle3, course2_TRANS[course2_paddleAxis*TRSZ+LOCX],
                                                 course2_TRANS[course2_paddleAxis*TRSZ+LOCY],
                                                 course2_TRANS[course2_paddleAxis*TRSZ+LOCZ]);


   
// if the character's feet contacts the finish platform then move to the next level
localBoxDetectAndMove(&course2_TRANS[course2_finish*TRSZ],
                      &character_TRANS[character_feetBox*TRSZ], 0.001,
                      0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &boxContactData, &contact);

if (contact)
{
   resetScene = TRUE;
   sceneNumber = 3;
}


// if the character falls past a certain point then reset
if (character_TRANS[character_box*TRSZ+LOCZ] < -200)
resetScene = TRUE;



// show standing if not moving

// save the current location and rotation
copyLocFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);
copyUcRotFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);

// reset location and rotation
copyLocFromTo(&character_STATICTRANS[0], &character_TRANS[0], character_MESHCNT);
copyUcRotFromTo(&character_STATICTRANS[0], &character_TRANS[0], character_MESHCNT);

// move the character back to position
globalUcRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, &buffer_TRANS[UC]);
globalMove(&character_TRANS[0], character_MESHCNT, buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);

endSound(footStepsSndData);


// if not in the air and moving forwards or backwards
if ((forward) || (backward)) 
if (!fallSpeed)
{
   // save the current location and rotation
   copyLocFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);
   copyUcRotFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);

   // animate run cycle
   animateRunCycle = animateRunCycle + 0.31;

   animateTransFromTo(&run1_TRANS[0], &run2_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 0, 4);
   animateTransFromTo(&run2_TRANS[0], &run3_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 1, 4);
   animateTransFromTo(&run3_TRANS[0], &run4_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 2, 4);
   animateTransFromTo(&run4_TRANS[0], &run1_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 3, 4);

   // rotate and move the character back to position
   globalUcRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, &buffer_TRANS[UC]);
   globalMove(&character_TRANS[0], character_MESHCNT, buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
   
   mixPlaySound(footStepsSndData, sizeof(footStepsSndData), FALSE, FALSE);
}


// if in the air and moving forwards or backwards
if ((forward) || (backward))
if (fallSpeed)
{
   // save the current location and rotation
   copyLocFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);
   copyUcRotFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);

   // animate forwards or in reverse to move the legs apart
   if (animateRunCycle < 1.0)// key frame 0
   animateRunCycle = animateRunCycle - 0.1;
   
   if ((animateRunCycle >= 1.0) && (animateRunCycle < 2.0))// key frame 1
   animateRunCycle = animateRunCycle + 0.1;
   
   if ((animateRunCycle >= 2.0) && (animateRunCycle < 3.0))// key frame 2
   animateRunCycle = animateRunCycle - 0.1;
   
   if ((animateRunCycle >= 3.0) || (animateRunCycle < 0.0))// key frame 3
   animateRunCycle = animateRunCycle + 0.1;
   
   animateTransFromTo(&run1_TRANS[0], &run2_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 0, 4);
   animateTransFromTo(&run2_TRANS[0], &run3_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 1, 4);
   animateTransFromTo(&run3_TRANS[0], &run4_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 2, 4);
   animateTransFromTo(&run4_TRANS[0], &run1_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateRunCycle, 3, 4);

   // rotate and move the character back to position
   globalUcRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, &buffer_TRANS[UC]);
   globalMove(&character_TRANS[0], character_MESHCNT, buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
}


// if in the air and not moving forwards or backwards
if (animateJumpInPlace < 0.9)
animateJumpInPlace = animateJumpInPlace + 0.1;

if ((!forward) && (!backward))
if (fallSpeed)
{
   // save the current location and rotation
   copyLocFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);
   copyUcRotFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);

   // animate to "jump in place" pose
   animateTransFromTo(&character_STATICTRANS[0], &jump_TRANS[0], character_MESHCNT, &character_TRANS[0], &animateJumpInPlace, 0, 1);
   
   // rotate and move the character back to position
   globalUcRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, &buffer_TRANS[UC]);
   globalMove(&character_TRANS[0], character_MESHCNT, buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
}



// lift and carry object
if (holdObj)
{
   // normalize the character
   copyTransFromTo(&character_TRANS[character_box*TRSZ], &buffer_TRANS[0], 1);
   globalMove(&character_TRANS[0], character_MESHCNT,
              -buffer_TRANS[LOCX], -buffer_TRANS[LOCY], -buffer_TRANS[LOCZ]);
   globalRevUcRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0,&buffer_TRANS[UC]);

   
   // find the upper arm position relative to the lift up pose position
   // the character's arms change position as the character is animated
   yLiftArmMove = character_TRANS[character_upperArmL*TRSZ+LOCY] - liftUp_TRANS[liftUp_upperArmL*TRSZ+LOCY];
   zLiftArmMove = character_TRANS[character_upperArmL*TRSZ+LOCZ] - liftUp_TRANS[liftUp_upperArmL*TRSZ+LOCZ];
   
   // copy the lift up pose of the arms to the character data
   copyTransFromTo(&liftUp_TRANS[liftUp_upperArmL*TRSZ], &character_TRANS[character_upperArmL*TRSZ], 1);
   copyTransFromTo(&liftUp_TRANS[liftUp_lowerArmL*TRSZ], &character_TRANS[character_lowerArmL*TRSZ], 1);
   copyTransFromTo(&liftUp_TRANS[liftUp_upperArmR*TRSZ], &character_TRANS[character_upperArmR*TRSZ], 1);
   copyTransFromTo(&liftUp_TRANS[liftUp_lowerArmR*TRSZ], &character_TRANS[character_lowerArmR*TRSZ], 1);
   
   // move the arms into position as the character is animated
   localMove(&character_TRANS[0], character_upperArmL, 0, yLiftArmMove, zLiftArmMove);
   localMove(&character_TRANS[0], character_lowerArmL, 0, yLiftArmMove, zLiftArmMove);
   localMove(&character_TRANS[0], character_upperArmR, 0, yLiftArmMove, zLiftArmMove);
   localMove(&character_TRANS[0], character_lowerArmR, 0, yLiftArmMove, zLiftArmMove);
   
   
   // undo normalization
   globalUcRot(&character_TRANS[0], character_MESHCNT, 0, 0, 0, &buffer_TRANS[UC]);
   globalMove(&character_TRANS[0], character_MESHCNT,
              buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
   
   
   // move object on top of arms
   
   // normalize the lifted object
   copyUcRotFromTo(&normalize_TRANS[0], &course2_TRANS[lifted_obj*TRSZ], 1);
   copyLocFromTo(&normalize_TRANS[0], &course2_TRANS[lifted_obj*TRSZ], 1);
   
   
   localMove(&course2_TRANS[0], lifted_obj, 0,
             -character_TRANS[character_box*TRSZ+SZY] +
             -course2_TRANS[lifted_obj*TRSZ+SZY] + yLiftArmMove, 0);
   
   localMove(&course2_TRANS[0], lifted_obj, 0, 0,
             liftUp_TRANS[liftUp_lowerArmL*TRSZ+LOCZ] +
             course2_TRANS[lifted_obj*TRSZ+SZZ] + zLiftArmMove);
   
   
   // rotate and move the object the same way the character was reversed normalized
   localUcRot(&course2_TRANS[0], lifted_obj, 0, 0, 0, &buffer_TRANS[UC]);
   localMove(&course2_TRANS[0], lifted_obj,
             buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
  
   // reset fall speed
   objFallSpeed[lifted_obj-first_obj] = 0.0;
}



// move the character's shadow in position
copyLocFromTo(&character_TRANS[character_feetBox*TRSZ], shadow_TRANS, 1);

globalBoxCollision(&course2_TRANS[0], course2_MESHCNT,
                   &character_TRANS[character_feetBox*TRSZ], 0.001,
                   0.0, 0.0, -1000.0, &xMove, &yMove, &zMove, &meshNum, &impact, &contact);

globalMove(&shadow_TRANS[0], shadow_MESHCNT, xMove, yMove, zMove);

// hide shadow if not contacting anything
if (contact == FALSE)
shadow_HIDE[shadow_shadow] = TRUE;
else
shadow_HIDE[shadow_shadow] = FALSE;



// move camera where the character is located
copyLocFromTo(&character_TRANS[character_box*TRSZ], &camera_TRANS[camera_camera*TRSZ], 1);

// move camera closer or further from the character
if (moveCloser)
cameraDistance -= 10.0;

if (moveAway)
cameraDistance += 10.0;

globalMove(&camera_TRANS[0], camera_MESHCNT, 0, 0, cameraDistance);


// reset camera rotation
copyUcRotFromTo(&camera_STATICTRANS[0], &camera_TRANS[0], camera_MESHCNT);

// rotate camera at a slanted angle
globalRot(&camera_TRANS[0], camera_MESHCNT,
          character_TRANS[character_box*TRSZ+LOCX],
          character_TRANS[character_box*TRSZ+LOCY],
          character_TRANS[character_box*TRSZ+LOCZ], 72.0, 0, 0);

// rotate camera in position
globalRot(&camera_TRANS[0], camera_MESHCNT,
          character_TRANS[character_box*TRSZ+LOCX],
          character_TRANS[character_box*TRSZ+LOCY],
          character_TRANS[character_box*TRSZ+LOCZ], 0, 0, turnLeftRight);



////////////////////////////////////////////////////////////////////
// DRAW //

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

fogColor[0] = 1.0;//r
fogColor[1] = 0.7;//g
fogColor[2] = 0.7;//b
glFogfv(GL_FOG_COLOR, fogColor);

if (useFog == TRUE)
glEnable(GL_FOG);
else
glDisable(GL_FOG);


// ADD TEXTURES

if (useTexture == TRUE)
{
   // add ocean texture
   addTexture(&oceanTexPtrGL, &oceanTexData[0],
              &oceanTexWidth[0], &oceanTexHeight[0], oceanTexCount, TRUE);

   // add nonSlipSteel texture
   addTexture(&nonSlipSteelTexPtrGL, &nonSlipSteelTexData[0],
              &nonSlipSteelTexWidth[0], &nonSlipSteelTexHeight[0], nonSlipSteelTexCount, TRUE);

   // add box texture
   addTexture(&boxTexPtrGL, &boxTexData[0],
              &boxTexWidth[0], &boxTexHeight[0], boxTexCount, TRUE);
}

// END OF ADD TEXTURES


rI.fogBgnZ = 5 * sceneSz;
rI.fogEndZ = 30000 * sceneSz;
rI.camEndZ = 100000 * sceneSz;

// draw dome2

// apply transformation data to the meshes
applyRotLocSz(&dome2_TRANS[0], &dome2_POINT[0], &dome2_POINTDATSZ[0], 0, dome2_MESHCNT);
applyMeshViewRotLocSz(&dome2_POINT[0], &dome2_POINTDATSZ[0], 0, dome2_MESHCNT,
                      &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);

// add textures to the mesh
dome2_TEX[dome2_ocean_bmp] = oceanTexPtrGL;

// draw mesh
drawMesh(&dome2_POINT[0], &dome2_QUAD[0], &dome2_TRI[0], &dome2_VCOLOR[0],
         &dome2_TEX[0], &dome2_TEXCOORD[0], &dome2_TEXLINKDAT[0],
         &dome2_QUADDATSZ[0], &dome2_TRIDATSZ[0], &dome2_HIDE[0], 0, dome2_MESHCNT, rI);


rI.fogBgnZ = 0 * sceneSz;
rI.fogEndZ = 1050 * sceneSz;
rI.camEndZ = 1050 * sceneSz;


// draw course2

// apply transformation data to the meshes
applyRotLocSz(&course2_TRANS[0], &course2_POINT[0], &course2_POINTDATSZ[0], 0, course2_MESHCNT);
applyMeshViewRotLocSz(&course2_POINT[0], &course2_POINTDATSZ[0], 0, course2_MESHCNT,
                      &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);

// add textures to the mesh
course2_TEX[course2_nonSlipSteel_bmp] = nonSlipSteelTexPtrGL;
course2_TEX[course2_box_bmp] = boxTexPtrGL;

// draw mesh
drawMesh(&course2_POINT[0], &course2_QUAD[0], &course2_TRI[0], &course2_VCOLOR[0],
         &course2_TEX[0], &course2_TEXCOORD[0], &course2_TEXLINKDAT[0],
         &course2_QUADDATSZ[0], &course2_TRIDATSZ[0], &course2_HIDE[0], 0, course2_MESHCNT, rI);


// draw character

// apply transformation data to the mesh
applyRotLocSz(&character_TRANS[0], &character_POINT[0], &character_POINTDATSZ[0], 0, character_MESHCNT);
applyMeshViewRotLocSz(&character_POINT[0], &character_POINTDATSZ[0], 0, character_MESHCNT,
                      &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);

// draw mesh
drawMesh(&character_POINT[0], &character_QUAD[0], &character_TRI[0], &character_VCOLOR[0],
         &character_TEX[0], &character_TEXCOORD[0], &character_TEXLINKDAT[0],
         &character_QUADDATSZ[0], &character_TRIDATSZ[0], &character_HIDE[0], 0, character_MESHCNT, rI);


// transparent meshes are best rendered at the end
glEnable(GL_BLEND); // make transparent
glDepthMask(GL_FALSE); // disable z buffering


// draw shadow

// apply transformation data to the mesh
applyRotLocSz(&shadow_TRANS[0], &shadow_POINT[0], &shadow_POINTDATSZ[0], 0, shadow_MESHCNT);
applyMeshViewRotLocSz(&shadow_POINT[0], &shadow_POINTDATSZ[0], 0, shadow_MESHCNT,
                      &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);

// draw mesh
drawMesh(&shadow_POINT[0], &shadow_QUAD[0], &shadow_TRI[0], &shadow_VCOLOR[0],
         &shadow_TEX[0], &shadow_TEXCOORD[0], &shadow_TEXLINKDAT[0],
         &shadow_QUADDATSZ[0], &shadow_TRIDATSZ[0], &shadow_HIDE[0], 0, shadow_MESHCNT, rI);

glDepthMask(GL_TRUE);
glDisable(GL_BLEND);


deleteTextures();

// END OF DRAW //
////////////////////////////////////////////////////////////////////
