extern float dome1_TRANS[48];
extern float dome1_POINT[12096];
extern short dome1_QUAD[3840];
extern short dome1_TRI[192];
extern char dome1_VCOLOR[16128];
extern float dome1_TEXCOORD[8064];

extern int dome1_TEXLINKDAT[3];
extern int dome1_TEXCNT;
int dome1_TEX[1];

extern int dome1_POINTDATSZ[4];
extern int dome1_QUADDATSZ[4];
extern int dome1_TRIDATSZ[4];
extern int dome1_VCOLORDATSZ[4];
extern int dome1_TEXCOORDDATSZ[4];

extern int dome1_HIDE[3];

//unchanging transformation data
float dome1_STATICTRANS[48];

//unchanging point data
float dome1_STATICPOINT[12096];

extern int dome1_MESHCNT;

//mesh names
#define dome1_backGround 0
#define dome1_ground 1
#define dome1_sky 2

//textures
#define dome1_grass_bmp 0
