if (resetScene)
{
   // control camera lense size relative to the scene
   sceneSz = 3.0; // used for opengl fog and clipping
   camLenseSz = 1.0 / sceneSz; // used for "applyMeshViewRotLocSz()"
   cameraDistance = 100;
   
   // reset transformation data
   copyTransFromTo(&camera_STATICTRANS[0], &camera_TRANS[0], camera_MESHCNT);
   copyTransFromTo(&dome1_STATICTRANS[0], &dome1_TRANS[0], dome1_MESHCNT);
   copyTransFromTo(&course1_STATICTRANS[0], &course1_TRANS[0], course1_MESHCNT);
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
   animatePlatform = 0;
   
   endAllSound();// stop sound
   
   // play sound in the background with looping and no concurrent playing
   mixPlaySound(windSndData, sizeof(windSndData), TRUE, FALSE);
   
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
copyMeshFromTo(&dome1_STATICPOINT[0], &dome1_POINTDATSZ[0], 0,
               &dome1_POINT[0], &dome1_POINTDATSZ[0], 0, dome1_MESHCNT);
copyMeshFromTo(&course1_STATICPOINT[0], &course1_POINTDATSZ[0], 0,
               &course1_POINT[0], &course1_POINTDATSZ[0], 0, course1_MESHCNT);
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
globalBoxKnockOut(&course1_TRANS[0], course1_MESHCNT,
                  &character_TRANS[character_box*TRSZ], 0.001,
                  &xMove, &yMove, &zMove, &contact);

globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);


// find if the character's feet is touching the floor for later use
globalBoxDetectAndMove(&course1_TRANS[0], course1_MESHCNT,
                       &character_TRANS[character_feetBox*TRSZ], 0.001,
                       0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &feetContact);


// find if the character hits his head for later use
globalBoxDetectAndMove(&course1_TRANS[0], course1_MESHCNT,
                       &character_TRANS[character_headBox*TRSZ], 0.001,
                       0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &headContact);



// get the control force that will be used to move the character in the x,y plane
xCtrlForce = 0;
yCtrlForce = forward + backward;
zCtrlForce = 0;
rotate(&xCtrlForce, &yCtrlForce, &zCtrlForce, 0, 0, turnLeftRight);


// find if the character collides with an object in the x,y plane
globalBoxCollision(&course1_TRANS[0], course1_MESHCNT,
                  &character_TRANS[character_box*TRSZ], 0.001,
                  xCtrlForce, yCtrlForce, zCtrlForce,
                  &xMove, &yMove, &zMove, &meshNum, &boxImpactData, &contact);

// move the character as much as possible
globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);

// find the direction the character will move after hitting an object
boxSkid(&course1_TRANS[meshNum*TRSZ], &character_TRANS[character_box*TRSZ],
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
   
   globalBoxCollision(&course1_TRANS[0], course1_MESHCNT,
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
globalBoxCollision(&course1_TRANS[0], course1_MESHCNT,
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
   
   globalBoxCollision(&course1_TRANS[0], course1_MESHCNT,
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
boxSkid(&course1_TRANS[meshNum*TRSZ], &character_TRANS[character_box*TRSZ],
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
   
   globalBoxCollision(&course1_TRANS[0], course1_MESHCNT,
                      &character_TRANS[character_box*TRSZ], 0.001,
                      xArrow*travelDistance, yArrow*travelDistance, zArrow*travelDistance,
                      &xMove, &yMove, &zMove, &meshNum, &boxImpactData, &contact);

   globalMove(&character_TRANS[0], character_MESHCNT, xMove, yMove, zMove);
}



// move the moving platform
animatePlatform = animatePlatform + 0.01;

animateLocFromTo(&course1_TRANS[course1_stopperA*TRSZ],
                 &course1_TRANS[course1_stopperB*TRSZ], 1, &buffer_TRANS[0], &animatePlatform, 0, 2);

animateLocFromTo(&course1_TRANS[course1_stopperB*TRSZ],
                 &course1_TRANS[course1_stopperA*TRSZ], 1, &buffer_TRANS[0], &animatePlatform, 1, 2);

xPlatformNewloc = buffer_TRANS[LOCX] - course1_TRANS[course1_moving*TRSZ+LOCX];
yPlatformNewloc = buffer_TRANS[LOCY] - course1_TRANS[course1_moving*TRSZ+LOCY];
zPlatformNewloc = buffer_TRANS[LOCZ] - course1_TRANS[course1_moving*TRSZ+LOCZ];

localMove(&course1_TRANS[0], course1_moving, xPlatformNewloc, yPlatformNewloc, zPlatformNewloc);


// move the character with the platform when standing on it
localBoxDetectAndMove(&course1_TRANS[course1_moving*TRSZ],
                      &character_TRANS[character_feetBox*TRSZ], 0.001,
                      0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &boxContactData, &contact);

if (contact)
globalMove(&character_TRANS[0], character_MESHCNT, xPlatformNewloc, yPlatformNewloc, zPlatformNewloc);



// if the character's feet contacts the finish platform then move to the next level
localBoxDetectAndMove(&course1_TRANS[course1_finish*TRSZ],
                      &character_TRANS[character_feetBox*TRSZ], 0.001,
                      0, 0, 0, FALSE, &nullVar, &nullVar, &nullVar, &boxContactData, &contact);

if (contact)
{
   resetScene = TRUE;
   sceneNumber = 2;
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



// move the character's shadow in position
copyLocFromTo(&character_TRANS[character_feetBox*TRSZ], shadow_TRANS, 1);

globalBoxCollision(&course1_TRANS[0], course1_MESHCNT,
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

fogColor[0] = 0.7;//r
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
   // add grass texture
   addTexture(&grassTexPtrGL, &grassTexData[0],
              &grassTexWidth[0], &grassTexHeight[0], grassTexCount, TRUE);

   // add nonSlipSteel texture
   addTexture(&nonSlipSteelTexPtrGL, &nonSlipSteelTexData[0],
              &nonSlipSteelTexWidth[0], &nonSlipSteelTexHeight[0], nonSlipSteelTexCount, TRUE);
}

// END OF ADD TEXTURES


rI.fogBgnZ = 5 * sceneSz;
rI.fogEndZ = 30000 * sceneSz;
rI.camEndZ = 100000 * sceneSz;

// draw dome1

// apply transformation data to the mesh
applyRotLocSz(&dome1_TRANS[0], &dome1_POINT[0], &dome1_POINTDATSZ[0], 0, dome1_MESHCNT);
applyMeshViewRotLocSz(&dome1_POINT[0], &dome1_POINTDATSZ[0], 0, dome1_MESHCNT,
                      &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);

// add textures to the mesh
dome1_TEX[dome1_grass_bmp] = grassTexPtrGL;

// draw mesh
drawMesh(&dome1_POINT[0], &dome1_QUAD[0], &dome1_TRI[0], &dome1_VCOLOR[0],
         &dome1_TEX[0], &dome1_TEXCOORD[0], &dome1_TEXLINKDAT[0],
         &dome1_QUADDATSZ[0], &dome1_TRIDATSZ[0], &dome1_HIDE[0], 0, dome1_MESHCNT, rI);


rI.fogBgnZ = 0 * sceneSz;
rI.fogEndZ = 550 * sceneSz;
rI.camEndZ = 550 * sceneSz;


// draw course1

// apply transformation data to the mesh
applyRotLocSz(&course1_TRANS[0], &course1_POINT[0], &course1_POINTDATSZ[0], 0, course1_MESHCNT);
applyMeshViewRotLocSz(&course1_POINT[0], &course1_POINTDATSZ[0], 0, course1_MESHCNT,
                      &camera_TRANS[camera_camera*TRSZ], camLenseSz, rI);

// add textures to the mesh
course1_TEX[course1_nonSlipSteel_bmp] = nonSlipSteelTexPtrGL;

// draw mesh
drawMesh(&course1_POINT[0], &course1_QUAD[0], &course1_TRI[0], &course1_VCOLOR[0],
         &course1_TEX[0], &course1_TEXCOORD[0], &course1_TEXLINKDAT[0],
         &course1_QUADDATSZ[0], &course1_TRIDATSZ[0], &course1_HIDE[0], 0, course1_MESHCNT, rI);


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
