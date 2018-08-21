////////////////////////////////////////////////////////////////////
// Initialize Scenes //

// initializing variables for two or more scenes

int i;

static int sceneNumber = 0;
static int resetScene = TRUE;

float nullVar;
float buffer_TRANS[TRSZ];

float normalize_TRANS[TRSZ]={
0.000000, 0.000000, 0.000000,
0.000000, 0.000000, 0.000000,
1.000000, 1.000000, 1.000000,
1.000000, 0.000000,
1.000000, 0.000000,
1.000000, 0.000000,
1.732051};

#define gravity_force 5
#define fall_speed_limit 80
#define jump_force 160
#define jump_force_damper 20

static int upArrowKeyPressed = FALSE;
static int downArrowKeyPressed = FALSE;
static int upArrowKeyFirst = FALSE;
static int downArrowKeyFirst = FALSE;
static int forwardBackwardToggle;

static int leftArrowKeyPressed = FALSE;
static int rightArrowKeyPressed = FALSE;
static int leftArrowKeyFirst = FALSE;
static int rightArrowKeyFirst = FALSE;
static int leftRightToggle;

static float turnLeft = 0;
static float turnRight = 0;
static float turnLeftRight = 0;
static float forward = 0;
static float backward = 0;
static int moveCloser = FALSE;
static int moveAway = FALSE;
static int jumpUp = 0;

static int liftPutDownObj = FALSE;
static int holdObj = FALSE;
float yLiftArmMove;
float zLiftArmMove;

static int alreadyJumped = FALSE;

static float xCtrlForce, yCtrlForce, zCtrlForce;

static float fallSpeed;
static float jumpSpeed;

static int contact, impact;
static int meshNum;
static int boxImpactData;
static int boxContactData;
float xMove, yMove, zMove;

static int feetContact;
static int headContact;

static float travelDistance;
static float xArrow, yArrow, zArrow;
static float pathAngle, noAngle;
static float angleFrac;

static float zSlippageAngle = 45;
static float zSlippageAmt = 2.5;
static float xySlippageAngle = 10;
static float xySlippageAmt = 1.0;


static float animateJumpInPlace;
static float animateRunCycle;

static float sceneSz;
static float camLenseSz;
static float cameraDistance;

static int useFog = TRUE;
float fogColor[3];

static int useTexture = TRUE;


static int initializeScenes = TRUE;

if (initializeScenes)
{
   copyTransFromTo(&camera_TRANS[0], &camera_STATICTRANS[0], camera_MESHCNT);
   copyMeshFromTo(&camera_POINT[0], &camera_POINTDATSZ[0], 0,
                  &camera_STATICPOINT[0], &camera_POINTDATSZ[0], 0, camera_MESHCNT);
   
   copyTransFromTo(&character_TRANS[0], &character_STATICTRANS[0], character_MESHCNT);
   copyMeshFromTo(&character_POINT[0], &character_POINTDATSZ[0], 0,
                  &character_STATICPOINT[0], &character_POINTDATSZ[0], 0, character_MESHCNT);
   
   copyTransFromTo(&shadow_TRANS[0], &shadow_STATICTRANS[0], shadow_MESHCNT);
   copyMeshFromTo(&shadow_POINT[0], &shadow_POINTDATSZ[0], 0,
                  &shadow_STATICPOINT[0], &shadow_POINTDATSZ[0], 0, shadow_MESHCNT);
   
   character_HIDE[character_box] = TRUE;
   character_HIDE[character_feetBox] = TRUE;
   character_HIDE[character_frontBox] = TRUE;
   character_HIDE[character_headBox] = TRUE;
   
   initializeScenes = FALSE;
}

// Initialize Scenes //
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// Initialize Scene 0 //

static float winWdthPercentMult;
static float winHghtPercentMult;

static int viewMainMenu = TRUE;
static int viewControls = FALSE;
static int viewOptions = FALSE;

int menuHighlightOption;

static int optFullScreen = 0;
static char optFullScreenTxt[64] = "Full Screen: [ no ]";

static char optDisplayScrnResTxt[64];

static char optWindowSizeTxt[64];
static float optWinWidth, optWinHeight;

static int optFog = TRUE;
static char optFogTxt[64] = "Fog: [ yes ]";

static int optTexture = TRUE;
static char optTextureTxt[64] = "Texture: [ yes ]";

// polygon data for highlighter
GLushort polyVectorData[4] = {2, 1, 0, 3};
static float quadVertexData[12] = {
0.0, 10000, -0.1,
150.0, 10000, -0.1,
150.0, 10000, -0.1,
0.0, 10000, -0.1,};
static char polyVColorData[16] = {
0x7F, 0xAF, 0xAF, 0xFF,
0x7F, 0x7F, 0x7F, 0xFF,
0x7F, 0x7F, 0x7F, 0xFF,
0x7F, 0x7F, 0x7F, 0xFF};

// data for polygon to create a background color
GLushort backgroundVector[4] = {0, 1, 2, 3};
static float backgroundVertex[12] = {
-100000.0, -100000.0, 0.0,
100000.0, -100000.0, 0.0,
100000.0, 100000.0, 0.0,
-100000.0, 100000, 0.0};
static char backgroundVColor[16] = {
0x7F, 0x7F, 0x7F, 0xFF,
0x7F, 0x7F, 0x7F, 0xFF,
0x7F, 0x7F, 0x7F, 0xFF,
0x7F, 0x7F, 0x7F, 0xFF};


static int initializeScene0 = TRUE;

if (initializeScene0)
{
   displayIndex = getCurrentDisplayRes(&xScrnRes, &yScrnRes, &colorDepth);
   originalDisplayIndex = displayIndex;
   
   sprintf(optDisplayScrnResTxt, "   Display: < %ix%i >", xScrnRes, yScrnRes);
   
   optWinWidth = staticViewPortWidth;
   optWinHeight = staticViewPortHeight;
   
   if ((optWinWidth >= xScrnRes) && (optWinHeight >= yScrnRes))
   sprintf(optWindowSizeTxt, "Window: < %ix%i > (Full Size)", (int)optWinWidth, (int)optWinHeight);
   else
   sprintf(optWindowSizeTxt, "Window: < %ix%i >", (int)optWinWidth, (int)optWinHeight);
   
   initializeScene0 = FALSE;
}

// Initialize Scene 0 //
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// Initialize Scene 1 //

static float animatePlatform;

float xPlatformNewloc;
float yPlatformNewloc;
float zPlatformNewloc;


static int initializeScene1 = TRUE;

if (initializeScene1)
{
   globalResize(&camera_STATICTRANS[0], camera_MESHCNT, 0, 0, 0, 1.0, 2.0, 1.0);
   // resize the dome
   globalResize(&dome1_TRANS[0], dome1_MESHCNT, 0, 0, 0, 300, 300, 300);
   
   // resize the course
   globalResize(&course1_TRANS[0], course1_MESHCNT, 0, 0, 0, 15, 15, 15);
   
   // copy the mesh data so you will always have the original data
   copyTransFromTo(&dome1_TRANS[0], &dome1_STATICTRANS[0], dome1_MESHCNT);
   copyMeshFromTo(&dome1_POINT[0], &dome1_POINTDATSZ[0], 0,
                  &dome1_STATICPOINT[0], &dome1_POINTDATSZ[0], 0, dome1_MESHCNT);
   
   copyTransFromTo(&course1_TRANS[0], &course1_STATICTRANS[0], course1_MESHCNT);
   copyMeshFromTo(&course1_POINT[0], &course1_POINTDATSZ[0], 0,
                  &course1_STATICPOINT[0], &course1_POINTDATSZ[0], 0, course1_MESHCNT);
   
   initializeScene1 = FALSE;
}

// Initialize Scene 1 //
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// Initialize Scene 2 //

// define where the box meshes are within the course2 meshes
#define first_obj course2_obj1
#define last_obj course2_obj3
#define total_objs 1 + (last_obj - first_obj)

static float objFallSpeed[total_objs] = {0, 0, 0};
static float xObjCtrlForce[total_objs] = {0, 0, 0};
static float yObjCtrlForce[total_objs] = {0, 0, 0};
static float zObjCtrlForce[total_objs] = {0, 0, 0};
static int lifted_obj;
int current_obj;
float xArmsReach, yArmsReach, zArmsReach;
int impactFace;
int outside;

static float moveOcean;
static float platformsRotSpeed = 0.3;

static float dome2_STATICTEXCOORD[sizeof(dome2_TEXCOORD)];// for animating the ocean


static int initializeScene2 = TRUE;

if (initializeScene2)
{
   // resize the dome
   globalResize(&dome2_TRANS[0], dome2_MESHCNT, 0, 0, 0, 300, 300, 300);
   
   // create extra texture coordinate data to animate the ocean
   copyTexCoordFromTo(&dome2_TEXCOORD[0], &dome2_TEXCOORDDATSZ[0], 0,
                      &dome2_STATICTEXCOORD[0], &dome2_TEXCOORDDATSZ[0], 0, dome2_MESHCNT);
   
   // resize the course
   globalResize(&course2_TRANS[0], course2_MESHCNT, 0, 0, 0, 15, 15, 15);
   
   // copy the mesh data so you will always have the original data
   copyTransFromTo(&dome2_TRANS[0], &dome2_STATICTRANS[0], dome2_MESHCNT);
   copyMeshFromTo(&dome2_POINT[0], &dome2_POINTDATSZ[0], 0,
                  &dome2_STATICPOINT[0], &dome2_POINTDATSZ[0], 0, dome2_MESHCNT);
   
   copyTransFromTo(&course2_TRANS[0], &course2_STATICTRANS[0], course2_MESHCNT);
   copyMeshFromTo(&course2_POINT[0], &course2_POINTDATSZ[0], 0,
                  &course2_STATICPOINT[0], &course2_POINTDATSZ[0], 0, course2_MESHCNT);
   
   initializeScene2 = FALSE;
}

// Initialize Scene 2 //
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// Initialize Scene 3 //

static int flyingCamMode = FALSE;
static float moveCamera = 0.1;

static float animateLeftTrack = 0;
static float animateRightTrack = 0;
static float animateExplosionColor = 0;
static float animateExplosionSize = 0;

int impactNum;
int quadFaceImpactNum;
int triFaceImpactNum;

float xGroundVertex;
float yGroundVertex;
float zGroundVertex;


float xCannonBallLoc;
float yCannonBallLoc;
float zCannonBallLoc;

float xCannonBallDest;
float yCannonBallDest;
float zCannonBallDest;

float xCannonBallTravLgth;
float yCannonBallTravLgth;
float zCannonBallTravLgth;


static int moveCannonBall = FALSE;
static int explodeCannonBall = FALSE;
static float xCannonBallVelocity;
static float yCannonBallVelocity;
static float zCannonBallVelocity;
static float cannonBallGravity;


#define arena_numOfTriangles sizeof(arena_TRI)/3
static float arena_TRITRANS[TRSZ * arena_numOfTriangles];

#define arena_numOfQuadTriangles sizeof(arena_QUAD)/4 * 2
static float arena_QUADTRANS[TRSZ * arena_numOfQuadTriangles];


#define tank_t1FirstPartNum arena_t1Barrel
#define tank_t1LastPartNum arena_t1Turret
#define tank_t1PartCnt 1 + tank_t1LastPartNum - tank_t1FirstPartNum

#define tank_t2FirstPartNum arena_t2Barrel
#define tank_t2LastPartNum arena_t2Turret
#define tank_t2PartCnt 1 + tank_t2LastPartNum - tank_t2FirstPartNum

static int tankFirstPartNum = tank_t1FirstPartNum;
static int tankPartCnt = tank_t1PartCnt;
static int tankBodyNum = arena_t1Body;
static int tankBarrelNum = arena_t1Barrel;
static int tankTurretNum = arena_t1Turret;
static int tankLeftTrackNum = arena_t1LeftTrack;
static int tankRightTrackNum = arena_t1RightTrack;
float xTankLoc, yTankLoc, zTankLoc;

static int t1CannonBallPower = 75;
static int t2CannonBallPower = 75;
static int cannonBallPower = 75;
static int t1Health = 100;
static int t2Health = 100;
static int tankFuel = 100;
static int playerTurn = 0;


static int initializeScene3 = TRUE;

if (initializeScene3)
{
   // resize meshes
   globalResize(&arena_TRANS[0], arena_MESHCNT, 0, 0, 0, 20, 20, 20);

   // copy the mesh data so you will always have the original data
   copyTransFromTo(&arena_TRANS[0], &arena_STATICTRANS[0], arena_MESHCNT);
   copyMeshFromTo(&arena_POINT[0], &arena_POINTDATSZ[0], 0,
                  &arena_STATICPOINT[0], &arena_POINTDATSZ[0], 0, arena_MESHCNT);
   
   arena_HIDE[arena_tank_CameraA] = TRUE;
   arena_HIDE[arena_tank_CameraB] = TRUE;
   arena_HIDE[arena_explode] = TRUE;
   arena_HIDE[arena_explodeRed] = TRUE;
   arena_HIDE[arena_explodeYellow] = TRUE;
   arena_HIDE[arena_cannonBall] = TRUE;
   
   // create transformation data for each triangle
   makeTriTransData(0, arena_MESHCNT, &arena_POINT[0], &arena_POINTDATSZ[0],
                    &arena_TRI[0], &arena_TRIDATSZ[0], &arena_TRITRANS[0]);
   
   // create transformation data for each quad
   makeQuadTransData(0, arena_MESHCNT, &arena_POINT[0], &arena_POINTDATSZ[0],
                     &arena_QUAD[0], &arena_QUADDATSZ[0], &arena_QUADTRANS[0]);
   
   initializeScene3 = FALSE;
}

// Initialize Scene 3 //
////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// Initialize Scene 4 //

static int startNewGame = TRUE;
static int changePlaneColor = FALSE;
static int startCountDown = FALSE;
static int showGameScore = FALSE;
static int gameSpeedInc = 0;
static int scoreNumber = -1;
static int randomNumber;
static int timerCountDown;
unsigned char red, green, blue;


static int initializeScene4 = TRUE;

if (initializeScene4)
{
   // resize meshes
   globalResize(&cubes_TRANS[0], cubes_MESHCNT, 0, 0, 0, 30, 30, 30);
   
   // copy the mesh data so you will always have the original data
   copyTransFromTo(&cubes_TRANS[0], &cubes_STATICTRANS[0], cubes_MESHCNT);
   copyMeshFromTo(&cubes_POINT[0], &cubes_POINTDATSZ[0], 0,
                  &cubes_STATICPOINT[0], &cubes_POINTDATSZ[0], 0, cubes_MESHCNT);
   
   initializeScene4 = FALSE;
}

// Initialize Scene 4 //
////////////////////////////////////////////////////////////////////
