extern float dome2_TRANS[48];
extern float dome2_POINT[18144];
extern short dome2_QUAD[5760];
extern short dome2_TRI[288];
extern char dome2_VCOLOR[24192];
extern float dome2_TEXCOORD[12096];

extern int dome2_TEXLINKDAT[3];
extern int dome2_TEXCNT;
int dome2_TEX[1];

extern int dome2_POINTDATSZ[4];
extern int dome2_QUADDATSZ[4];
extern int dome2_TRIDATSZ[4];
extern int dome2_VCOLORDATSZ[4];
extern int dome2_TEXCOORDDATSZ[4];

extern int dome2_HIDE[3];

//unchanging transformation data
float dome2_STATICTRANS[48];

//unchanging point data
float dome2_STATICPOINT[18144];

extern int dome2_MESHCNT;

//mesh names
#define dome2_ocean1 0
#define dome2_ocean2 1
#define dome2_sky 2

//textures
#define dome2_ocean_bmp 0
