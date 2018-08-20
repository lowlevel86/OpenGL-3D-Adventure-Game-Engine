extern float character_TRANS[240];
extern float character_POINT[3840];
extern short character_QUAD[1280];
extern short character_TRI[0];
extern char character_VCOLOR[5120];
extern float character_TEXCOORD[2560];

extern int character_TEXLINKDAT[15];
extern int character_TEXCNT;
int character_TEX[0];

extern int character_POINTDATSZ[16];
extern int character_QUADDATSZ[16];
extern int character_TRIDATSZ[16];
extern int character_VCOLORDATSZ[16];
extern int character_TEXCOORDDATSZ[16];

extern int character_HIDE[15];

//unchanging transformation data
float character_STATICTRANS[240];

//unchanging point data
float character_STATICPOINT[3840];

extern int character_MESHCNT;

//mesh names
#define character_box 0
#define character_feetBox 1
#define character_frontBox 2
#define character_head 3
#define character_headBox 4
#define character_lowerArmL 5
#define character_lowerArmR 6
#define character_lowerLegL 7
#define character_lowerLegR 8
#define character_midsection 9
#define character_neck 10
#define character_upperArmL 11
#define character_upperArmR 12
#define character_upperLegL 13
#define character_upperLegR 14

//textures
