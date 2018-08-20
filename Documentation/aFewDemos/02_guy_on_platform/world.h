extern float world_TRANS[48];
extern float world_POINT[1920];
extern short world_QUAD[484];
extern short world_TRI[156];
extern char world_VCOLOR[2560];
extern float world_TEXCOORD[1280];

extern int world_TEXLINKDAT[3];
extern int world_TEXCNT;
int world_TEX[0];

extern int world_POINTDATSZ[4];
extern int world_QUADDATSZ[4];
extern int world_TRIDATSZ[4];
extern int world_VCOLORDATSZ[4];
extern int world_TEXCOORDDATSZ[4];

extern int world_HIDE[3];

//unchanging transformation data
float world_STATICTRANS[48];

//unchanging point data
float world_STATICPOINT[1920];

extern int world_MESHCNT;

//mesh names
#define world_camera 0
#define world_guy 1
#define world_platform 2

//textures
