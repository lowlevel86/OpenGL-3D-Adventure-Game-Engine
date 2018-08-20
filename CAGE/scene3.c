if (resetScene)
{
   endAllSound();// stop sound
   
   // keep the draw size relative to the window size
   contentRelativeToWindowSize = TRUE;
   changeWindow = TRUE;
   
   resetScene = FALSE;
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   return;
}



// reset mesh data for each frame
copyMeshFromTo(&arena_STATICPOINT[0], &arena_POINTDATSZ[0], 0,
               &arena_POINT[0], &arena_POINTDATSZ[0], 0, arena_MESHCNT);


// switch camera modes
if (keyPress[9])// Tab
flyingCamMode = !flyingCamMode;

// if one of the tanks loose all health then switch to flying camera mode
if ((t1Health == 0) || (t2Health == 0))
flyingCamMode = TRUE;



if (flyingCamMode) // if in flying camera mode
{
   // normalize the arena_camera mesh
   copyTransFromTo(&arena_TRANS[arena_camera*TRSZ], &buffer_TRANS[0], 1);
   localMove(&arena_TRANS[0], arena_camera,
             -buffer_TRANS[LOCX], -buffer_TRANS[LOCY], -buffer_TRANS[LOCZ]);
   localRevRot(&arena_TRANS[0], arena_camera, 0, 0, 0,
               buffer_TRANS[ROTX], buffer_TRANS[ROTY], buffer_TRANS[ROTZ]);
   
   // move and rotate the arena_camera mesh
   if (keyDown[38])// Up
   buffer_TRANS[ROTX] += 5;
   if (keyDown[40])// Down
   buffer_TRANS[ROTX] -= 5;
   if (keyDown[37])// Left
   buffer_TRANS[ROTZ] += 5;
   if (keyDown[39])// Right
   buffer_TRANS[ROTZ] -= 5;

   if (keyDown[87])// W
   localMove(&arena_TRANS[0], arena_camera, 0, 0, -10);
   if (keyDown[83])// S
   localMove(&arena_TRANS[0], arena_camera, 0, 0, 10);
   if (keyDown[65])// A
   localMove(&arena_TRANS[0], arena_camera, -10, 0, 0);
   if (keyDown[68])// D
   localMove(&arena_TRANS[0], arena_camera, 10, 0, 0);

   // undo arena_camera mesh normalization
   localRot(&arena_TRANS[0], arena_camera, 0, 0, 0,
            buffer_TRANS[ROTX], buffer_TRANS[ROTY], buffer_TRANS[ROTZ]);
   localMove(&arena_TRANS[0], arena_camera,
             buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
}
else // if in tank camera mode
{
   // normalize tank mesh
   copyTransFromTo(&arena_TRANS[tankBodyNum*TRSZ], &buffer_TRANS[0], 1);
   globalMove(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt,
              -buffer_TRANS[LOCX], -buffer_TRANS[LOCY], -buffer_TRANS[LOCZ]);
   globalRevRot(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt, 0, 0, 0,
                buffer_TRANS[ROTX], buffer_TRANS[ROTY], buffer_TRANS[ROTZ]);

   // normalize tank barrel mesh
   localRevRot(&arena_TRANS[0], tankBarrelNum, 0, 0, 0,
               0, 0, arena_TRANS[tankTurretNum*TRSZ+ROTZ]);
   
	// move tank barrel
   if (keyDown[38])// Up
   {
      localRot(&arena_TRANS[0], tankBarrelNum,
               arena_TRANS[tankBarrelNum*TRSZ+LOCX],
               arena_TRANS[tankBarrelNum*TRSZ+LOCY],
               arena_TRANS[tankBarrelNum*TRSZ+LOCZ], 1.0, 0, 0);
      mixPlaySound(beepSndData, sizeof(beepSndData), FALSE, TRUE);
   }
   
   if (keyDown[40])// Down
   {
      localRot(&arena_TRANS[0], tankBarrelNum,
               arena_TRANS[tankBarrelNum*TRSZ+LOCX],
               arena_TRANS[tankBarrelNum*TRSZ+LOCY],
               arena_TRANS[tankBarrelNum*TRSZ+LOCZ], -1.0, 0, 0);
      mixPlaySound(beepSndData, sizeof(beepSndData), FALSE, TRUE);
   }
   
   if (keyDown[37])// Left
   {
      localRot(&arena_TRANS[0], tankTurretNum,
               arena_TRANS[tankTurretNum*TRSZ+LOCX],
               arena_TRANS[tankTurretNum*TRSZ+LOCY],
               arena_TRANS[tankTurretNum*TRSZ+LOCZ], 0, 0, 1.0);
      mixPlaySound(boopSndData, sizeof(boopSndData), FALSE, TRUE);
   }
   
   if (keyDown[39])// Right
   {
      localRot(&arena_TRANS[0], tankTurretNum,
               arena_TRANS[tankTurretNum*TRSZ+LOCX],
               arena_TRANS[tankTurretNum*TRSZ+LOCY],
               arena_TRANS[tankTurretNum*TRSZ+LOCZ], 0, 0, -1.0);
      mixPlaySound(boopSndData, sizeof(boopSndData), FALSE, TRUE);
   }
   
	// undo tank barrel mesh normalization
   localRot(&arena_TRANS[0], tankBarrelNum, 0, 0, 0,
            0, 0, arena_TRANS[tankTurretNum*TRSZ+ROTZ]);
   
   // move tank
   if (keyDown[87])// W
   if (tankFuel > 0)
   {
      animateLeftTrack = animateLeftTrack + 0.1;
      animateRightTrack = animateRightTrack + 0.1;
      globalMove(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt, 0, 2.0, 0);
      tankFuel = tankFuel - 2;
      mixPlaySound(smMachineSndData, sizeof(smMachineSndData), TRUE, FALSE);
   }

   if (keyDown[83])// S
   if (tankFuel > 0)
   {
      animateLeftTrack = animateLeftTrack - 0.1;
      animateRightTrack = animateRightTrack - 0.1;
      globalMove(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt, 0, -2.0, 0);
      tankFuel = tankFuel - 2;
      mixPlaySound(smMachineSndData, sizeof(smMachineSndData), TRUE, FALSE);
   }

   if (keyDown[65])// A
   if (tankFuel > 0)
   {
      animateLeftTrack = animateLeftTrack - 0.1;
      animateRightTrack = animateRightTrack + 0.1;
      globalRot(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt, 0, 0, 0, 0, 0, 5.0);
      tankFuel = tankFuel - 2;
      mixPlaySound(smMachineSndData, sizeof(smMachineSndData), TRUE, FALSE);
   }

   if (keyDown[68])// D
   if (tankFuel > 0)
   {
      animateLeftTrack = animateLeftTrack + 0.1;
      animateRightTrack = animateRightTrack - 0.1;
      globalRot(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt, 0, 0, 0, 0, 0, -5.0);
      tankFuel = tankFuel - 2;
      mixPlaySound(smMachineSndData, sizeof(smMachineSndData), TRUE, FALSE);
   }
   
   if (!keyDown[87])// W
   if (!keyDown[83])// S
   if (!keyDown[65])// A
   if (!keyDown[68])// D
   endSound(smMachineSndData);
   
   if (tankFuel == 0)
   endSound(smMachineSndData);
   
   // undo tank mesh normalization
   globalRot(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt, 0, 0, 0,
             buffer_TRANS[ROTX], buffer_TRANS[ROTY], buffer_TRANS[ROTZ]);
   globalMove(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt,
              buffer_TRANS[LOCX], buffer_TRANS[LOCY], buffer_TRANS[LOCZ]);
   
   
	// animate tank tracks
   animateMeshFromTo(&arena_STATICPOINT[0], &arena_POINTDATSZ[0], tankLeftTrackNum,
                     &arena_STATICPOINT[0], &arena_POINTDATSZ[0], tankRightTrackNum, 1,
                     &arena_POINT[0], &arena_POINTDATSZ[0], tankLeftTrackNum, &animateLeftTrack, 0, 1);

   animateMeshFromTo(&arena_STATICPOINT[0], &arena_POINTDATSZ[0], tankLeftTrackNum,
                     &arena_STATICPOINT[0], &arena_POINTDATSZ[0], tankRightTrackNum, 1,
                     &arena_POINT[0], &arena_POINTDATSZ[0], tankRightTrackNum, &animateRightTrack, 0, 1);


   // increase or decrease cannon power
   if ((keyDown[107]) || (keyDown[187]))// +
   if (cannonBallPower < 100)
   {
      if (playerTurn == 0)
      t1CannonBallPower += 1;
      else
      t2CannonBallPower += 1;
   }
   
   if ((keyDown[109]) || (keyDown[189]))// -
   if (cannonBallPower > 0)
   {
      if (playerTurn == 0)
      t1CannonBallPower -= 1;
      else
      t2CannonBallPower -= 1;
   }
   
   // fire
   if (keyPress[32])// spacebar
   if (moveCannonBall == FALSE)
   if (explodeCannonBall == FALSE)
   {
      arena_HIDE[arena_cannonBall] = FALSE;
      moveCannonBall = TRUE;
      
		// use the tank barrel to find the cannon ball velocity
		
      arena_TRANS[arena_cannonBall*TRSZ+LOCX] = arena_TRANS[tankBarrelNum*TRSZ+LOCX];
      arena_TRANS[arena_cannonBall*TRSZ+LOCY] = arena_TRANS[tankBarrelNum*TRSZ+LOCY];
      arena_TRANS[arena_cannonBall*TRSZ+LOCZ] = arena_TRANS[tankBarrelNum*TRSZ+LOCZ] + 1.0;
      
		// rotate the cannon ball in the same direction as the tank barrel
      localRot(&arena_TRANS[0], arena_cannonBall, arena_TRANS[tankBarrelNum*TRSZ+LOCX],
                                                  arena_TRANS[tankBarrelNum*TRSZ+LOCY],
                                                  arena_TRANS[tankBarrelNum*TRSZ+LOCZ],
                                                  arena_TRANS[tankBarrelNum*TRSZ+ROTX],
                                                  arena_TRANS[tankBarrelNum*TRSZ+ROTY],
                                                  arena_TRANS[tankBarrelNum*TRSZ+ROTZ]);
      
		// define initial velocity
      xCannonBallVelocity = (arena_TRANS[arena_cannonBall*TRSZ+LOCX] - arena_TRANS[tankBarrelNum*TRSZ+LOCX]) * 20;
      yCannonBallVelocity = (arena_TRANS[arena_cannonBall*TRSZ+LOCY] - arena_TRANS[tankBarrelNum*TRSZ+LOCY]) * 20;
      zCannonBallVelocity = (arena_TRANS[arena_cannonBall*TRSZ+LOCZ] - arena_TRANS[tankBarrelNum*TRSZ+LOCZ]) * 20;
      
      mixPlaySound(popSndData, sizeof(popSndData), FALSE, TRUE);
      
      cannonBallGravity = 0;
   }
}



// while cannon ball is moving
if (moveCannonBall)
{
   xCannonBallLoc = arena_TRANS[arena_cannonBall*TRSZ+LOCX];
   yCannonBallLoc = arena_TRANS[arena_cannonBall*TRSZ+LOCY];
   zCannonBallLoc = arena_TRANS[arena_cannonBall*TRSZ+LOCZ];
   
   // destination
   xCannonBallDest = xCannonBallLoc + xCannonBallVelocity;
   yCannonBallDest = yCannonBallLoc + yCannonBallVelocity;
   zCannonBallDest = zCannonBallLoc + zCannonBallVelocity;
   
   // travel length
   xCannonBallTravLgth = xCannonBallDest - xCannonBallLoc;
   yCannonBallTravLgth = yCannonBallDest - yCannonBallLoc;
   zCannonBallTravLgth = zCannonBallDest - zCannonBallLoc;
   
   
	// get the rotations to rotate the cannon ball travel length up right
	getUCRotPointToAxisZ(xCannonBallTravLgth, yCannonBallTravLgth, zCannonBallTravLgth,
								&buffer_TRANS[9], &buffer_TRANS[10],
								&buffer_TRANS[11], &buffer_TRANS[12],
								&buffer_TRANS[13], &buffer_TRANS[14]);

	// rotate cannon ball travel length up right
	applyXyzUcRotToPoint(buffer_TRANS[9], buffer_TRANS[10],
								buffer_TRANS[11], buffer_TRANS[12],
								buffer_TRANS[13], buffer_TRANS[14],
								&xCannonBallTravLgth, &yCannonBallTravLgth, &zCannonBallTravLgth);

	// add the starting location to the travel length
	zCannonBallTravLgth = zCannonBallTravLgth + zCannonBallLoc;


	// rotate the ground in the same way it takes to rotate the cannon ball travel length up right
	localUcRot(&arena_TRANS[0], arena_ground,
				  xCannonBallLoc, yCannonBallLoc, zCannonBallLoc, &buffer_TRANS[UC]);

	// find if the cannon ball collided with the ground and get the new travel length
	ptToTriMeshZCollision(&arena_TRANS[0], arena_ground, &arena_STATICPOINT[0],
								 &arena_TRI[0], &arena_TRIDATSZ[0],
								 xCannonBallLoc, yCannonBallLoc, zCannonBallLoc,
								 &zCannonBallTravLgth, &triFaceImpactNum, &outside);

	// rotate the ground back to where it was
	localRevUcRot(&arena_TRANS[0], arena_ground,
					  xCannonBallLoc, yCannonBallLoc, zCannonBallLoc, &buffer_TRANS[UC]);
 
 
	// subtract the starting location from the travel length
	zCannonBallTravLgth = zCannonBallTravLgth - zCannonBallLoc;

	// rotate cannon ball travel length back to where it was
	reverseApplyXyzUcRotToPoint(buffer_TRANS[9], buffer_TRANS[10],
							          buffer_TRANS[11], buffer_TRANS[12],
                               buffer_TRANS[13], buffer_TRANS[14],
                               &xCannonBallTravLgth, &yCannonBallTravLgth, &zCannonBallTravLgth);

   // get the new cannon ball destination
   xCannonBallDest = xCannonBallLoc + xCannonBallTravLgth;
   yCannonBallDest = yCannonBallLoc + yCannonBallTravLgth;
   zCannonBallDest = zCannonBallLoc + zCannonBallTravLgth;
   
 
   // find if the cannon ball collided with the sphere
   impactNum = -1;
   
   if (triFaceImpactNum != -1)
   impactNum = triFaceImpactNum;
   
   // find if the cannon ball collided with any of the trigons of the sphere
   ptToTriMeshCollision(&arena_TRANS[0], arena_sphere, &arena_STATICPOINT[0],
                        &arena_TRI[0], &arena_TRIDATSZ[0], &arena_TRITRANS[0],
                        arena_TRANS[arena_cannonBall*TRSZ+LOCX],
                        arena_TRANS[arena_cannonBall*TRSZ+LOCY],
                        arena_TRANS[arena_cannonBall*TRSZ+LOCZ],
                        &xCannonBallDest, &yCannonBallDest, &zCannonBallDest, 0.001, &triFaceImpactNum, &outside);
   
   if (triFaceImpactNum != -1)
   impactNum = triFaceImpactNum;
   
   // find if the cannon ball collided with any of the quads of the sphere
   ptToQuadMeshCollision(&arena_TRANS[0], arena_sphere, &arena_STATICPOINT[0],
                         &arena_QUAD[0], &arena_QUADDATSZ[0], &arena_QUADTRANS[0],
                         arena_TRANS[arena_cannonBall*TRSZ+LOCX],
                         arena_TRANS[arena_cannonBall*TRSZ+LOCY],
                         arena_TRANS[arena_cannonBall*TRSZ+LOCZ],
                         &xCannonBallDest, &yCannonBallDest, &zCannonBallDest, 0.001, &quadFaceImpactNum, &outside);
   
   if (quadFaceImpactNum != -1)
   impactNum = quadFaceImpactNum;
   
   
   if (impactNum != -1)
   {
      explodeCannonBall = TRUE;
      moveCannonBall = FALSE;
   }
   
   // find if the cannon ball collided with the cage
   ptToBoxCollision(&arena_TRANS[arena_cage*TRSZ], arena_TRANS[arena_cannonBall*TRSZ+LOCX],
                                                   arena_TRANS[arena_cannonBall*TRSZ+LOCY],
                                                   arena_TRANS[arena_cannonBall*TRSZ+LOCZ],
                                                   &xCannonBallDest, &yCannonBallDest, &zCannonBallDest, &impact, &outside);
   
   if (outside)// if the cannon ball collided from the outside
   {
      explodeCannonBall = TRUE;
      moveCannonBall = FALSE;
   }
   
   // make the cannon ball bounce off the cage if there was a collision
   if (impact != 0)
   {
      if ((impact == 1) || (impact == 2))
      xCannonBallVelocity = -xCannonBallVelocity;
      
      if ((impact == 3) || (impact == 4))
      yCannonBallVelocity = -yCannonBallVelocity;
      
      if ((impact == 5) || (impact == 6))
      zCannonBallVelocity = -zCannonBallVelocity;
      
      if (impact == 6)
      {
         explodeCannonBall = TRUE;
         moveCannonBall = FALSE;
      }
      
      mixPlaySound(popSndData, sizeof(popSndData), FALSE, TRUE);
   }
   else
   {
      localMove(&arena_TRANS[0], arena_cannonBall, xCannonBallDest - arena_TRANS[arena_cannonBall*TRSZ+LOCX],
                                                   yCannonBallDest - arena_TRANS[arena_cannonBall*TRSZ+LOCY],
                                                   zCannonBallDest - arena_TRANS[arena_cannonBall*TRSZ+LOCZ]);
   }
   
   // change velocity relative to cannon ball power
   cannonBallGravity += 1.0 - (float)cannonBallPower / 100;
   zCannonBallVelocity -= cannonBallGravity*0.2;
}



// after cannon ball has collided with the ground or sphere
if (explodeCannonBall)
{
   // begin sound play at the beginning of the explosion animation
   if (animateExplosionSize == 0)
   mixPlaySound(boomSndData, sizeof(boomSndData), FALSE, TRUE);
   
   // hide the cannon ball and make the explode mesh visible
   arena_HIDE[arena_cannonBall] = TRUE;
   arena_HIDE[arena_explode] = FALSE;
   
   // copy the explode mesh to the cannon ball location
   copyLocFromTo(&arena_TRANS[arena_cannonBall*TRSZ], &arena_TRANS[arena_explode*TRSZ], 1);
   
   
   // animate the size and color of the explode mesh
   animateExplosionColor += 0.2;
   animateExplosionSize += 0.1;
   
   animateColorFromTo(&arena_VCOLOR[0], &arena_VCOLORDATSZ[0], arena_explodeRed,
                      &arena_VCOLOR[0], &arena_VCOLORDATSZ[0], arena_explodeYellow, 1,
                      &arena_VCOLOR[0], &arena_VCOLORDATSZ[0], arena_explode, &animateExplosionColor, 0, 2);

   animateColorFromTo(&arena_VCOLOR[0], &arena_VCOLORDATSZ[0], arena_explodeYellow,
                      &arena_VCOLOR[0], &arena_VCOLORDATSZ[0], arena_explodeRed, 1,
                      &arena_VCOLOR[0], &arena_VCOLORDATSZ[0], arena_explode, &animateExplosionColor, 1, 2);
   
   animateSizeFromTo(&arena_TRANS[arena_explodeRed*TRSZ],
                    &arena_TRANS[arena_explodeYellow*TRSZ], 1,
                    &arena_TRANS[arena_explode*TRSZ], &animateExplosionSize, 0, 2);
   
   animateSizeFromTo(&arena_TRANS[arena_explodeYellow*TRSZ],
                    &arena_TRANS[arena_explodeRed*TRSZ], 1,
                    &arena_TRANS[arena_explode*TRSZ], &animateExplosionSize, 1, 2);
   
   
   // at the end of the explosion animation
   if (animateExplosionSize > 1.0)
   {
      // change the ground mesh to show effects from the explosion 
      for (i=arena_POINTDATSZ[arena_ground]; i < arena_POINTDATSZ[arena_ground+1]; i+=3)
      {
         // apply the size trasformation data
         // no need to apply rotation or location
         xGroundVertex = arena_STATICPOINT[i+0] * arena_TRANS[arena_ground*TRSZ+SZX];
         yGroundVertex = arena_STATICPOINT[i+1] * arena_TRANS[arena_ground*TRSZ+SZY];
         zGroundVertex = arena_STATICPOINT[i+2] * arena_TRANS[arena_ground*TRSZ+SZZ];
         
         // check if lines going from the bottom of the cage to each ground vertex
         // collided with the explode mesh and get the impact location
         ptToTriMeshZCollision(&arena_TRANS[0], arena_explode, &arena_STATICPOINT[0],
                               &arena_TRI[0], &arena_TRIDATSZ[0],
                               xGroundVertex, yGroundVertex, -arena_TRANS[arena_cage*TRSZ+SZZ],
                               &zGroundVertex, &impactNum, &outside);
         
         if (impactNum != -1)
         {
            // undo the applied size trasformation to change the position of a ground vertex
            arena_STATICPOINT[i+2] = zGroundVertex / arena_TRANS[arena_ground*TRSZ+SZZ];
            
            // change the color of the ground
            arena_VCOLOR[i/3*4 + 0] = 20;
            arena_VCOLOR[i/3*4 + 1] = 50;
            arena_VCOLOR[i/3*4 + 2] = 20;
         }
      }
      
      
      // if the explode mesh box touches the mesh box of one of the tanks
      // then reduce the health
      ptToBoxCollision(&arena_TRANS[arena_explode*TRSZ], 
                       arena_TRANS[arena_t1Body*TRSZ+LOCX],
                       arena_TRANS[arena_t1Body*TRSZ+LOCY],
                       arena_TRANS[arena_t1Body*TRSZ+LOCZ],
                       &arena_TRANS[arena_t1Body*TRSZ+LOCX],
                       &arena_TRANS[arena_t1Body*TRSZ+LOCY],
                       &arena_TRANS[arena_t1Body*TRSZ+LOCZ], &impact, &outside);
      
      if (outside == FALSE)
      t1Health = t1Health - 20;
      
      ptToBoxCollision(&arena_TRANS[arena_explode*TRSZ], 
                       arena_TRANS[arena_t2Body*TRSZ+LOCX],
                       arena_TRANS[arena_t2Body*TRSZ+LOCY],
                       arena_TRANS[arena_t2Body*TRSZ+LOCZ],
                       &arena_TRANS[arena_t2Body*TRSZ+LOCX],
                       &arena_TRANS[arena_t2Body*TRSZ+LOCY],
                       &arena_TRANS[arena_t2Body*TRSZ+LOCZ], &impact, &outside);
      
      if (outside == FALSE)
      t2Health = t2Health - 20;
      
      
      // reset explosion values
      arena_HIDE[arena_explode] = TRUE;
      animateExplosionColor = 0;
      animateExplosionSize = 0;
      
      explodeCannonBall = FALSE;
      
      // refuel and switch turns
      tankFuel = 100;
      playerTurn = !playerTurn;
   }
}



// get first tank location
xTankLoc = arena_TRANS[arena_t1Body*TRSZ+LOCX];
yTankLoc = arena_TRANS[arena_t1Body*TRSZ+LOCY];
zTankLoc = arena_TRANS[arena_t1Body*TRSZ+LOCZ] - arena_TRANS[arena_t1Body*TRSZ+SZZ];

// keep the tank within the cage
ptToBoxCollision(&arena_TRANS[arena_cage*TRSZ], 0, 0, 0,
                 &xTankLoc, &yTankLoc, &zTankLoc, &impact, &outside);

globalMove(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt,
           -arena_TRANS[arena_t1Body*TRSZ+LOCX] + xTankLoc,
           -arena_TRANS[arena_t1Body*TRSZ+LOCY] + yTankLoc, 0);

// keep the tank on top of the ground
zTankLoc = -arena_TRANS[arena_cage*TRSZ+SZZ]; // bottom of cage

ptToTriMeshZCollision(&arena_TRANS[0], arena_ground, &arena_STATICPOINT[0],
                      &arena_TRI[0], &arena_TRIDATSZ[0],
                      arena_TRANS[arena_t1Body*TRSZ+LOCX], // tank x position
                      arena_TRANS[arena_t1Body*TRSZ+LOCY], // tank y position
                      arena_TRANS[arena_cage*TRSZ+SZZ], // top of cage
                      &zTankLoc, // will return the new z location for the tank
                      &triFaceImpactNum, &outside);

globalMove(&arena_TRANS[tankFirstPartNum*TRSZ], tankPartCnt,
           0, 0, -arena_TRANS[arena_t1Body*TRSZ+LOCZ] + arena_TRANS[arena_t1Body*TRSZ+SZZ] + zTankLoc);


// get second tank location
xTankLoc = arena_TRANS[arena_t2Body*TRSZ+LOCX];
yTankLoc = arena_TRANS[arena_t2Body*TRSZ+LOCY];
zTankLoc = arena_TRANS[arena_t2Body*TRSZ+LOCZ] - arena_TRANS[arena_t2Body*TRSZ+SZZ];

// keep the tank within the cage
ptToBoxCollision(&arena_TRANS[arena_cage*TRSZ], 0, 0, 0,
                 &xTankLoc, &yTankLoc, &zTankLoc, &impact, &outside);

globalMove(&arena_TRANS[tank_t2FirstPartNum*TRSZ], tank_t2PartCnt,
           -arena_TRANS[arena_t2Body*TRSZ+LOCX] + xTankLoc,
           -arena_TRANS[arena_t2Body*TRSZ+LOCY] + yTankLoc, 0);

// keep the tank on top of the ground
zTankLoc = -arena_TRANS[arena_cage*TRSZ+SZZ]; // bottom of cage

ptToTriMeshZCollision(&arena_TRANS[0], arena_ground, &arena_STATICPOINT[0],
                      &arena_TRI[0], &arena_TRIDATSZ[0],
                      arena_TRANS[arena_t2Body*TRSZ+LOCX], // tank x position
                      arena_TRANS[arena_t2Body*TRSZ+LOCY], // tank y position
                      arena_TRANS[arena_cage*TRSZ+SZZ], // top of cage
                      &zTankLoc, // will return the new z location for the tank
                      &triFaceImpactNum, &outside);

globalMove(&arena_TRANS[tank_t2FirstPartNum*TRSZ], tank_t2PartCnt,
           0, 0, -arena_TRANS[arena_t2Body*TRSZ+LOCZ] + arena_TRANS[arena_t2Body*TRSZ+SZZ] + zTankLoc);



// normalize camera B
localMove(&arena_TRANS[0], arena_tank_CameraB, -arena_TRANS[arena_tank_CameraB*TRSZ+LOCX],
                                               -arena_TRANS[arena_tank_CameraB*TRSZ+LOCY],
                                               -arena_TRANS[arena_tank_CameraB*TRSZ+LOCZ]);
localRevRot(&arena_TRANS[0], arena_tank_CameraB, 0, 0, 0,
            0, 0, arena_TRANS[arena_tank_CameraB*TRSZ+ROTZ]);

// make camera B follow the current tank
localMove(&arena_TRANS[0], arena_tank_CameraB, arena_TRANS[tankBodyNum*TRSZ+LOCX],
                                               arena_TRANS[tankBodyNum*TRSZ+LOCY]-8.0*20,
                                               arena_TRANS[tankBodyNum*TRSZ+LOCZ]+6.0*20);
localRot(&arena_TRANS[0], arena_tank_CameraB, arena_TRANS[tankBodyNum*TRSZ+LOCX],
                                              arena_TRANS[tankBodyNum*TRSZ+LOCY],
                                              arena_TRANS[tankBodyNum*TRSZ+LOCZ],
                                              0, 0, arena_TRANS[tankBodyNum*TRSZ+ROTZ]);

// move and rotate "CameraA" to "CameraB" slowly 
animateLocFromTo(&arena_TRANS[arena_tank_CameraA*TRSZ],
                 &arena_TRANS[arena_tank_CameraB*TRSZ], 1,
                 &arena_TRANS[arena_tank_CameraA*TRSZ], &moveCamera, 0, 1);
animateUcRotFromTo(&arena_TRANS[arena_tank_CameraA*TRSZ],
                   &arena_TRANS[arena_tank_CameraB*TRSZ], 1,
                   &arena_TRANS[arena_tank_CameraA*TRSZ], &moveCamera, 0, 1);



// change the current tank when switching turns
if (playerTurn == 0)
{
   tankFirstPartNum = tank_t1FirstPartNum;
   tankPartCnt = tank_t1PartCnt;
   tankBodyNum = arena_t1Body;
   tankBarrelNum = arena_t1Barrel;
   tankTurretNum = arena_t1Turret;
   tankLeftTrackNum = arena_t1LeftTrack;
   tankRightTrackNum = arena_t1RightTrack;
   cannonBallPower = t1CannonBallPower;
}
else
{
   tankFirstPartNum = tank_t2FirstPartNum;
   tankPartCnt = tank_t2PartCnt;
   tankBodyNum = arena_t2Body;
   tankBarrelNum = arena_t2Barrel;
   tankTurretNum = arena_t2Turret;
   tankLeftTrackNum = arena_t2LeftTrack;
   tankRightTrackNum = arena_t2RightTrack;
   cannonBallPower = t2CannonBallPower;
}



////////////////////////////////////////////////////////////////////
// DRAW //

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

glDisable(GL_FOG);

// ADD TEXTURES

if (useTexture == TRUE)
{
   // add grass texture
   addTexture(&grassTexPtrGL, &grassTexData[0],
              &grassTexWidth[0], &grassTexHeight[0], grassTexCount, TRUE);
}

// END OF ADD TEXTURES


rI.camEndZ = 2000 * sceneSz;

// draw arena

// only use lines to draw the flying camera and cage
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
glLineWidth(1.0);

// apply transformation data to the meshes
applyRotLocSz(&arena_TRANS[0], &arena_POINT[0], &arena_POINTDATSZ[0], 0, arena_MESHCNT);

if (flyingCamMode)
applyMeshViewRotLocSz(&arena_POINT[0], &arena_POINTDATSZ[0], 0, arena_MESHCNT,
                      &arena_TRANS[arena_camera*TRSZ], camLenseSz, rI);
else
applyMeshViewRotLocSz(&arena_POINT[0], &arena_POINTDATSZ[0], 0, arena_MESHCNT,
                      &arena_TRANS[arena_tank_CameraA*TRSZ], camLenseSz, rI);

// draw mesh
drawMesh(&arena_POINT[0], &arena_QUAD[0], &arena_TRI[0], &arena_VCOLOR[0],
         &arena_TEX[0], &arena_TEXCOORD[0], &arena_TEXLINKDAT[0],
         &arena_QUADDATSZ[0], &arena_TRIDATSZ[0], &arena_HIDE[0], arena_cage, 1, rI);

if (flyingCamMode == FALSE)
drawMesh(&arena_POINT[0], &arena_QUAD[0], &arena_TRI[0], &arena_VCOLOR[0],
         &arena_TEX[0], &arena_TEXCOORD[0], &arena_TEXLINKDAT[0],
         &arena_QUADDATSZ[0], &arena_TRIDATSZ[0], &arena_HIDE[0], arena_camera, 1, rI);


// hide the flying camera and cage when drawing the other meshes
arena_HIDE[arena_camera] = TRUE;
arena_HIDE[arena_cage] = TRUE;

glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

// add textures to the mesh
arena_TEX[arena_grass_bmp] = grassTexPtrGL;

// draw mesh
drawMesh(&arena_POINT[0], &arena_QUAD[0], &arena_TRI[0], &arena_VCOLOR[0],
         &arena_TEX[0], &arena_TEXCOORD[0], &arena_TEXLINKDAT[0],
         &arena_QUADDATSZ[0], &arena_TRIDATSZ[0], &arena_HIDE[0], 0, arena_MESHCNT, rI);


arena_HIDE[arena_camera] = FALSE;
arena_HIDE[arena_cage] = FALSE;


// display status and usage text
if (flyingCamMode == FALSE)
{
   printfScrn(0, 0, 13, 0xCCCC88, rI, "Turret angle:%i  Barrel angle:%i",
                                      (int)round(arena_TRANS[tankTurretNum*TRSZ+ROTZ]),
                                      (int)round(90+arena_TRANS[tankBarrelNum*TRSZ+ROTX]));
   printfScrn(0, -2*13, 13, 0xCCCC88, rI, "Cannon power:%i%%  Fuel:%i%%", cannonBallPower, tankFuel);
   printfScrn(0, -4*13, 13, 0x444499, rI, "Camera/cannon angle: Arrow keys");
   printfScrn(0, -6*13, 13, 0x444499, rI, "Move around: W, A, S, D");
   printfScrn(0, -8*13, 13, 0x444499, rI, "Cannon power: +, -");
   printfScrn(0, -10*13, 13, 0x444499, rI, "Switch camera mode: Tab");
   printfScrn(0, -12*13, 13, 0x444499, rI, "Fire: Spacebar");
}
else
{
   if ((t1Health) && (t2Health))
   {
      printfScrn(0, 0, 13, 0x0000CC, rI, "Red health:%i%%", t1Health);
      printfScrn(0, -2*13, 13, 0xFF4444, rI, "Blue health:%i%%", t2Health);
   }
   
   if ((!t1Health) && (!t2Health))
   printfScrn(0, 0, 26, 0xCCCC88, rI, "It's a tie!");
   
   if ((t1Health) && (!t2Health))
   printfScrn(0, 0, 26, 0x0000CC, rI, "Red Wins!");
   
   if ((!t1Health) && (t2Health))
   printfScrn(0, 0, 26, 0xFF4444, rI, "Blue Wins!");

   printfScrn(0, -4*13, 13, 0x444499, rI, "Camera/cannon angle: Arrow keys");
   printfScrn(0, -6*13, 13, 0x444499, rI, "Move around: W, A, S, D");
   printfScrn(0, -8*13, 13, 0x444499, rI, "Cannon power: +, -");
   printfScrn(0, -10*13, 13, 0x444499, rI, "Switch camera mode: Tab");
   printfScrn(0, -12*13, 13, 0x444499, rI, "Fire: Spacebar");
}

deleteTextures();

// END OF DRAW //
////////////////////////////////////////////////////////////////////
