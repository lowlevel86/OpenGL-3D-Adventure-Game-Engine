extern float shadow_TRANS[16];
extern float shadow_POINT[108];
extern short shadow_QUAD[0];
extern short shadow_TRI[36];
extern char shadow_VCOLOR[144];
extern float shadow_TEXCOORD[96];

extern int shadow_TEXLINKDAT[1];
extern int shadow_TEXCNT;
int shadow_TEX[0];

extern int shadow_POINTDATSZ[2];
extern int shadow_QUADDATSZ[2];
extern int shadow_TRIDATSZ[2];
extern int shadow_VCOLORDATSZ[2];
extern int shadow_TEXCOORDDATSZ[2];

extern int shadow_HIDE[1];

//unchanging transformation data
float shadow_STATICTRANS[16];

//unchanging point data
float shadow_STATICPOINT[108];

extern int shadow_MESHCNT;

//mesh names
#define shadow_shadow 0

//textures
