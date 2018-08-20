extern float lightCycle_TRANS[144];
extern float lightCycle_POINT[21324];
extern short lightCycle_QUAD[6904];
extern short lightCycle_TRI[204];
extern char lightCycle_VCOLOR[28432];
extern float lightCycle_TEXCOORD[14216];

extern int lightCycle_TEXLINKDAT[9];
extern int lightCycle_TEXCNT;
int lightCycle_TEX[1];

extern int lightCycle_POINTDATSZ[10];
extern int lightCycle_QUADDATSZ[10];
extern int lightCycle_TRIDATSZ[10];
extern int lightCycle_VCOLORDATSZ[10];
extern int lightCycle_TEXCOORDDATSZ[10];

extern int lightCycle_HIDE[9];

//unchanging transformation data
float lightCycle_STATICTRANS[144];

//unchanging point data
float lightCycle_STATICPOINT[21324];

extern int lightCycle_MESHCNT;

//mesh names
#define lightCycle_backWheel 0
#define lightCycle_body 1
#define lightCycle_frame 2
#define lightCycle_frontWheel 3
#define lightCycle_sign 4
#define lightCycle_sign_001 5
#define lightCycle_sign_002 6
#define lightCycle_sign_003 7
#define lightCycle_sign_004 8

//textures
#define lightCycle_lightCycle_bmp 0
