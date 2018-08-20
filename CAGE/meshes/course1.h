extern float course1_TRANS[224];
extern float course1_POINT[4968];
extern short course1_QUAD[1584];
extern short course1_TRI[72];
extern char course1_VCOLOR[6624];
extern float course1_TEXCOORD[3312];

extern int course1_TEXLINKDAT[14];
extern int course1_TEXCNT;
int course1_TEX[1];

extern int course1_POINTDATSZ[15];
extern int course1_QUADDATSZ[15];
extern int course1_TRIDATSZ[15];
extern int course1_VCOLORDATSZ[15];
extern int course1_TEXCOORDDATSZ[15];

extern int course1_HIDE[14];

//unchanging transformation data
float course1_STATICTRANS[224];

//unchanging point data
float course1_STATICPOINT[4968];

extern int course1_MESHCNT;

//mesh names
#define course1_Mesh_004 0
#define course1_Mesh_005 1
#define course1_Mesh_006 2
#define course1_Mesh_007 3
#define course1_Mesh_008 4
#define course1_Mesh_010 5
#define course1_Mesh_011 6
#define course1_finish 7
#define course1_moving 8
#define course1_rail1 9
#define course1_rail2 10
#define course1_start 11
#define course1_stopperA 12
#define course1_stopperB 13

//textures
#define course1_nonSlipSteel_bmp 0
