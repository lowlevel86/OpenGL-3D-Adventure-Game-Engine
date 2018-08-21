extern float ptToBoxCollision_TRANS[48];
extern float ptToBoxCollision_POINT[252];
extern short ptToBoxCollision_QUAD[24];
extern short ptToBoxCollision_TRI[60];
extern char ptToBoxCollision_VCOLOR[336];
extern float ptToBoxCollision_TEXCOORD[168];

extern int ptToBoxCollision_TEXLINKDAT[3];
extern int ptToBoxCollision_TEXCNT;
int ptToBoxCollision_TEX[0];

extern int ptToBoxCollision_POINTDATSZ[4];
extern int ptToBoxCollision_QUADDATSZ[4];
extern int ptToBoxCollision_TRIDATSZ[4];
extern int ptToBoxCollision_VCOLORDATSZ[4];
extern int ptToBoxCollision_TEXCOORDDATSZ[4];

extern int ptToBoxCollision_HIDE[3];

//unchanging transformation data
float ptToBoxCollision_STATICTRANS[48];

//unchanging point data
float ptToBoxCollision_STATICPOINT[252];

extern int ptToBoxCollision_MESHCNT;

//mesh names
#define ptToBoxCollision_Cube 0
#define ptToBoxCollision_Plane_004 1
#define ptToBoxCollision_Sphere 2

//textures
