extern float arena_TRANS[320];
extern float arena_POINT[13050];
extern short arena_QUAD[1536];
extern short arena_TRI[2814];
extern char arena_VCOLOR[17400];
extern float arena_TEXCOORD[8700];

extern int arena_TEXLINKDAT[20];
extern int arena_TEXCNT;
int arena_TEX[1];

extern int arena_POINTDATSZ[21];
extern int arena_QUADDATSZ[21];
extern int arena_TRIDATSZ[21];
extern int arena_VCOLORDATSZ[21];
extern int arena_TEXCOORDDATSZ[21];

extern int arena_HIDE[20];

//unchanging transformation data
float arena_STATICTRANS[320];

//unchanging point data
float arena_STATICPOINT[13050];

extern int arena_MESHCNT;

//mesh names
#define arena_cage 0
#define arena_camera 1
#define arena_cannonBall 2
#define arena_explode 3
#define arena_explodeRed 4
#define arena_explodeYellow 5
#define arena_ground 6
#define arena_sphere 7
#define arena_t1Barrel 8
#define arena_t1Body 9
#define arena_t1LeftTrack 10
#define arena_t1RightTrack 11
#define arena_t1Turret 12
#define arena_t2Barrel 13
#define arena_t2Body 14
#define arena_t2LeftTrack 15
#define arena_t2RightTrack 16
#define arena_t2Turret 17
#define arena_tank_CameraA 18
#define arena_tank_CameraB 19

//textures
#define arena_grass_bmp 0
