#define TRSZ 16 //transformation data size
#define ROTX 0  //rotataion
#define ROTY 1
#define ROTZ 2
#define LOCX 3  //location
#define LOCY 4
#define LOCZ 5
#define SZX  6  //size
#define SZY  7
#define SZZ  8
#define UC   9  //unit circle data
#define UCXH 9  //unit circle X rotation, horizontal coordinate
#define UCXV 10 //unit circle X rotation, vertical coordinate
#define UCYH 11 //unit circle Y rotation
#define UCYV 12 //unit circle Y rotation
#define UCZH 13 //unit circle Z rotation
#define UCZV 14 //unit circle Z rotation
#define BR   15 //bounds radius

struct rendrInfo
{
   float winWdth;
   float winHght;
   float camLenZ;
   float camEndZ;
   float fogBgnZ;
   float fogEndZ;
   float perspctv;
   int ortho;
   float viewRelativeSize;
};
typedef struct rendrInfo RENDRINFO;

// in rotate.c
void relativeRot(float *, float *, float *,
                 float, float, float, float, float, float);
void rotate(float *, float *, float *, float, float, float);
void degRot(float *, float *, float);
void ucRot(float, float, float *, float *);

// in rotate2.c
void addRotToXyzUcRot(float *, float *,
                      float *, float *,
                      float *, float *, float, float, float);
void subtractRotFromXyzUcRot(float *, float *,
                             float *, float *,
                             float *, float *, float, float, float);

void addXyzUcRot(float *, float *,
                 float *, float *,
                 float *, float *,
                 float, float, float, float, float, float);
void subtractXyzUcRot(float *, float *,
                      float *, float *,
                      float *, float *,
                      float, float, float, float, float, float);

void applyXyzUcRot(float *, float *,
                   float *, float *,
                   float *, float *,
                   float, float, float, float, float, float);
void reverseApplyXyzUcRot(float *, float *,
                          float *, float *,
                          float *, float *,
                          float, float, float, float, float, float);

void applyXyzUcRotToPoint(float, float,
                          float, float,
                          float, float, float *, float *, float *);
void reverseApplyXyzUcRotToPoint(float, float,
                                 float, float,
                                 float, float, float *, float *, float *);

void convertRotToXyzUcRot(float *, float *,
                          float *, float *,
                          float *, float *, float, float, float);
void convertXyzUcRotToRot(float, float,
                          float, float,
                          float, float, float *, float *, float *);

void getUCRotPointToAxisX(float, float, float,
                          float *, float *, float *, float *, float *, float *);
void getUCRotPointToAxisY(float, float, float,
                          float *, float *, float *, float *, float *, float *);
void getUCRotPointToAxisZ(float, float, float,
                          float *, float *, float *, float *, float *, float *);

// in applyRotLocSz.c
void applyRotLocSz(float *, float *, int *, int, int);
void applyMeshViewRotLocSz(float *, int *, int, int, float *, float, struct rendrInfo);

// in transform.c
void globalRot(float *, int, float, float, float, float, float, float);
void localRot(float *, int, float, float, float, float, float, float);
void globalRevRot(float *, int, float, float, float, float, float, float);
void localRevRot(float *, int, float, float, float, float, float, float);
void globalConcurrentAxisRot(float *, int, float, float, float, float, float, float);
void localConcurrentAxisRot(float *, int, float, float, float, float, float, float);
void globalMove(float *, int, float, float, float);
void localMove(float *, int, float, float, float);
void globalResize(float *, int, float, float, float, float, float, float);
void localResize(float *, int, float, float, float, float, float, float);
void globalUcRot(float *, int, float, float, float, float *);
void localUcRot(float *, int, float, float, float, float *);
void globalRevUcRot(float *, int, float, float, float, float *);
void localRevUcRot(float *, int, float, float, float, float *);
void copyTransFromTo(float *, float *, int);
void copyRotFromTo(float *, float *, int);
void copyLocFromTo(float *, float *, int);
void copySizeFromTo(float *, float *, int);
void copyUcRotFromTo(float *, float *, int);
void copyMeshFromTo(float *, int *, int,
                    float *, int *, int, int);
void copyColorFromTo(char *, int *, int,
                     char *, int *, int, int);
void copyTexCoordFromTo(float *, int *, int,
                        float *, int *, int, int);

// in collisionDetect.c
int parallQuadToNormBoxContact(float *, float *, float *,
                                        float *, float *);
int boundsContact(float *, float *);
int nonOrientBoxContact(float *, float *);
void ptToBoundsCollision(float *, float, float, float,
                         float *, float *, float *, int *, int *);
void ptToBoxCollision(float *, float, float, float,
                      float *, float *, float *, int *, int *);
void globalBoxKnockOut(float *, int,
                       float *, float,
                       float *, float *, float *, int *);
void globalBoxDetectAndMove(float *, int,
                            float *, float,
                            float, float, float, int,
                            float *, float *, float *, int *);
void globalBoxCollision(float *, int,
                        float *, float,
                        float, float, float,
                        float *, float *, float *, int *, int *, int *);
void localBoxKnockOut(float *, float *, float,
                      float *, float *, float *, int *, int *);
void localBoxDetectAndMove(float *, float *, float,
                           float, float, float, int,
                           float *, float *, float *, int *, int *);
void localBoxCollision(float *, float *, float,
                       float, float, float,
                       float *, float *, float *, int *, int *);

// in collisionDetect2.c
void ptToTriMeshCollision(float *, int, float *,
                          short *, int *, float *,
                          float, float, float,
                          float *, float *, float *, float, int *, int *);
void ptToQuadMeshCollision(float *, int, float *,
                           short *, int *, float *,
                           float, float, float,
                           float *, float *, float *, float, int *, int *);
void ptToTriCollision(float, float, float, float, float, float,
                      float, float, float, float, float, float, float, float, float,
                      float, float, float, float, float, float, float,
                      int *, int *, float *, float *, float *);
void ptToTriMeshZCollision(float *, int, float *, short *, int *,
                           float, float, float, float *, int *, int *);
void ptToQuadMeshZCollision(float *, int, float *, short *, int *,
                            float, float, float, float *, int *, int *);

// in path.c
void resizeLineToPlaneX(float, float, float,
                        float *, float *, float *, float, int *, int *);
void resizeLineToPlaneY(float, float, float,
                        float *, float *, float *, float, int *, int *);
void resizeLineToPlaneZ(float, float, float,
                        float *, float *, float *, float, int *, int *);
void travelParallelToAxisX(float, float,
                           float, float,
                           float, float,
                           float, float, float, float *, float *, float *);
void travelParallelToAxisY(float, float,
                           float, float,
                           float, float,
                           float, float, float, float *, float *, float *);
void travelParallelToAxisZ(float, float,
                           float, float,
                           float, float,
                           float, float, float, float *, float *, float *);
void xPlaneSkidPath(float, float, float, float, float, float,
                    float *, float *, float *, float *, float *, float *);
void yPlaneSkidPath(float, float, float, float, float, float,
                    float *, float *, float *, float *, float *, float *);
void zPlaneSkidPath(float, float, float, float, float, float,
                    float *, float *, float *, float *, float *, float *);
int getDirectionChgAngle(float, float, float,
                         float, float, float, float *);
float getTravelLength(float, float, float);

// physics.c
void ptToPlaneSkid(float *, float, float, float,
                            float, float, float, float *, float *, float *);
void boxSkid(float *, float *,
             float, float, float, int,
             float *, float *, float *);

// in animate.c
void animateTransFromTo(float *, float *, int, float *, float *, int, int);
void animateRotFromTo(float *, float *, int, float *, float *, int, int);
void animateLocFromTo(float *, float *, int, float *, float *, int, int);
void animateSizeFromTo(float *, float *, int, float *, float *, int, int);
void animateUcRotFromTo(float *, float *, int, float *, float *, int, int);
void animateMeshFromTo(float *, int *, int,
                       float *, int *, int, int,
                       float *, int *, int, float *, int, int);
void animateColorFromTo(char *, int *, int,
                        char *, int *, int, int,
                        char *, int *, int, float *, int, int);
void animateTexCoordFromTo(float *, int *, int,
                           float *, int *, int, int,
                           float *, int *, int, float *, int, int);

// in polyTransData.c
void makeTriTransData(int, int, float *, int *, short *, int *, float *);
void makeQuadTransData(int, int, float *, int *, short *, int *, float *);

#include <GL/gl.h>

// in drawMeshGL.c
void drawMesh(float *, short *, short *, char *,
              int *, float *, int *, int *, int *, int *, int, int, struct rendrInfo);

// in textureGL.c
void addTexture(GLuint *, GLubyte *, int *, int *, int, int);
void deleteTextures();

// in asciiOpenGL.c
void drawAsciiChar(int, float, float,
                   float, float, float,
                   float, float, float, float, int);
void drawAscii(char *, float, float,
               float, float, float,
               float, float, float, float, int, int);

// glDebug.c
void printfScrn(float, float, float, int, struct rendrInfo, char *, ...);
void drawPt(float, float, float, int, float);
void drawLine(float, float, float, float, float, float, int, float);
void drawTransBox(float *, int, float *, float, float, int, struct rendrInfo);
void drawXyzAxis(float *, int, float *, float, float, struct rendrInfo);
void drawBounds(float *, int, float *, float, float, int, struct rendrInfo);
void screenShot(char *, int);
void eventRecToFile(void **, int, FILE *);
void eventPlayFromFile(void **, int, FILE *);
