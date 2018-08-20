extern float camera_TRANS[16];
extern float camera_POINT[1110];
extern short camera_QUAD[172];
extern short camera_TRI[198];
extern char camera_VCOLOR[1480];
extern float camera_TEXCOORD[740];

extern int camera_TEXLINKDAT[1];
extern int camera_TEXCNT;
int camera_TEX[0];

extern int camera_POINTDATSZ[2];
extern int camera_QUADDATSZ[2];
extern int camera_TRIDATSZ[2];
extern int camera_VCOLORDATSZ[2];
extern int camera_TEXCOORDDATSZ[2];

extern int camera_HIDE[1];

//unchanging transformation data
float camera_STATICTRANS[16];

//unchanging point data
float camera_STATICPOINT[1110];

extern int camera_MESHCNT;

//mesh names
#define camera_camera 0

//textures
