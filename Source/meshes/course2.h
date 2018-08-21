extern float course2_TRANS[272];
extern float course2_POINT[3324];
extern short course2_QUAD[1108];
extern short course2_TRI[0];
extern char course2_VCOLOR[4432];
extern float course2_TEXCOORD[2216];

extern int course2_TEXLINKDAT[17];
extern int course2_TEXCNT;
int course2_TEX[2];

extern int course2_POINTDATSZ[18];
extern int course2_QUADDATSZ[18];
extern int course2_TRIDATSZ[18];
extern int course2_VCOLORDATSZ[18];
extern int course2_TEXCOORDDATSZ[18];

extern int course2_HIDE[17];

//unchanging transformation data
float course2_STATICTRANS[272];

//unchanging point data
float course2_STATICPOINT[3324];

extern int course2_MESHCNT;

//mesh names
#define course2_Cube 0
#define course2_Cube_001 1
#define course2_Cube_002 2
#define course2_Cube_003 3
#define course2_Cube_004 4
#define course2_Mesh_010 5
#define course2_Mesh_010_001 6
#define course2_Mesh_010_002 7
#define course2_finish 8
#define course2_obj1 9
#define course2_obj2 10
#define course2_obj3 11
#define course2_paddleAxis 12
#define course2_rotPaddle1 13
#define course2_rotPaddle2 14
#define course2_rotPaddle3 15
#define course2_start 16

//textures
#define course2_nonSlipSteel_bmp 0
#define course2_box_bmp 1
