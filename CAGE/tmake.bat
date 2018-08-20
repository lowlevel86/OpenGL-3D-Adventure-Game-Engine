@echo off

echo This batch file will use tcc to compile c code.
echo To use just type 'tmake' within a terminal.
echo Use 'tmake clean' to prepare for remaking all c files.
echo To remake fileLoc\thisFile.c use 'tmake fileLoc\thisFile'.

SET BIN=game.exe
SET OBJ=main.o setDisplay.o mixPlaySnd.o sounds\jumpSndData.o sounds\footStepsSndData.o sounds\windSndData.o sounds\oceanSndData.o sounds\smMachineSndData.o sounds\boopSndData.o sounds\beepSndData.o sounds\popSndData.o sounds\boomSndData.o meshes\texture\grassTexData.o meshes\texture\oceanTexData.o meshes\texture\nonSlipSteelTexData.o meshes\texture\boxTexData.o meshes\character.o meshes\shadow.o meshes\run1.o meshes\run2.o meshes\run3.o meshes\run4.o meshes\jump.o meshes\liftUp.o meshes\course1.o meshes\course2.o meshes\dome1.o meshes\dome2.o meshes\arena.o meshes\camera.o meshes\cubes.o 3dEngine\rotate.o 3dEngine\rotate2.o 3dEngine\applyRotLocSz.o 3dEngine\transform.o 3dEngine\drawMeshGL.o 3dEngine\textureGL.o 3dEngine\asciiOpenGL.o 3dEngine\collisionDetect.o 3dEngine\collisionDetect2.o 3dEngine\path.o 3dEngine\glDebug.o 3dEngine\animate.o 3dEngine\polyTransData.o

if "%1" == "clean" GOTO clean

if exist %1.o echo deleting and remaking %1.o
if exist %1.o del %1.o

copy main.c mainWithRSRC.c
echo int dummy __attribute__ ((section(".rsrc"))); >> mainWithRSRC.c
..\..\tccAndTools\tcc\tcc.exe -c mainWithRSRC.c -o main.o
del mainWithRSRC.c

if NOT exist setDisplay.o ..\..\tccAndTools\tcc\tcc.exe -c setDisplay.c -o setDisplay.o
if NOT exist mixPlaySnd.o ..\..\tccAndTools\tcc\tcc.exe -c mixPlaySnd.c -o mixPlaySnd.o

if NOT exist sounds\jumpSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\jumpSndData.c -o sounds\jumpSndData.o
if NOT exist sounds\footStepsSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\footStepsSndData.c -o sounds\footStepsSndData.o
if NOT exist sounds\windSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\windSndData.c -o sounds\windSndData.o
if NOT exist sounds\oceanSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\oceanSndData.c -o sounds\oceanSndData.o
if NOT exist sounds\smMachineSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\smMachineSndData.c -o sounds\smMachineSndData.o
if NOT exist sounds\boopSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\boopSndData.c -o sounds\boopSndData.o
if NOT exist sounds\beepSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\beepSndData.c -o sounds\beepSndData.o
if NOT exist sounds\popSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\popSndData.c -o sounds\popSndData.o
if NOT exist sounds\boomSndData.o ..\..\tccAndTools\tcc\tcc.exe -c sounds\boomSndData.c -o sounds\boomSndData.o

if NOT exist meshes\texture\grassTexData.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\texture\grassTexData.c -o meshes\texture\grassTexData.o
if NOT exist meshes\texture\oceanTexData.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\texture\oceanTexData.c -o meshes\texture\oceanTexData.o
if NOT exist meshes\texture\nonSlipSteelTexData.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\texture\nonSlipSteelTexData.c -o meshes\texture\nonSlipSteelTexData.o
if NOT exist meshes\texture\boxTexData.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\texture\boxTexData.c -o meshes\texture\boxTexData.o

if NOT exist meshes\character.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\character.c -o meshes\character.o
if NOT exist meshes\shadow.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\shadow.c -o meshes\shadow.o
if NOT exist meshes\run1.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\run1.c -o meshes\run1.o
if NOT exist meshes\run2.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\run2.c -o meshes\run2.o
if NOT exist meshes\run3.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\run3.c -o meshes\run3.o
if NOT exist meshes\run4.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\run4.c -o meshes\run4.o
if NOT exist meshes\jump.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\jump.c -o meshes\jump.o
if NOT exist meshes\liftUp.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\liftUp.c -o meshes\liftUp.o
if NOT exist meshes\course1.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\course1.c -o meshes\course1.o
if NOT exist meshes\course2.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\course2.c -o meshes\course2.o
if NOT exist meshes\dome1.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\dome1.c -o meshes\dome1.o
if NOT exist meshes\dome2.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\dome2.c -o meshes\dome2.o
if NOT exist meshes\arena.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\arena.c -o meshes\arena.o
if NOT exist meshes\camera.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\camera.c -o meshes\camera.o
if NOT exist meshes\cubes.o ..\..\tccAndTools\tcc\tcc.exe -c meshes\cubes.c -o meshes\cubes.o

if NOT exist 3dEngine\rotate.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\rotate.c -o 3dEngine\rotate.o
if NOT exist 3dEngine\rotate2.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\rotate2.c -o 3dEngine\rotate2.o
if NOT exist 3dEngine\applyRotLocSz.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\applyRotLocSz.c -o 3dEngine\applyRotLocSz.o
if NOT exist 3dEngine\transform.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\transform.c -o 3dEngine\transform.o
if NOT exist 3dEngine\drawMeshGL.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\drawMeshGL.c -o 3dEngine\drawMeshGL.o
if NOT exist 3dEngine\textureGL.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\textureGL.c -o 3dEngine\textureGL.o
if NOT exist 3dEngine\asciiOpenGL.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\asciiOpenGL.c -o 3dEngine\asciiOpenGL.o
if NOT exist 3dEngine\collisionDetect.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\collisionDetect.c -o 3dEngine\collisionDetect.o
if NOT exist 3dEngine\collisionDetect2.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\collisionDetect2.c -o 3dEngine\collisionDetect2.o
if NOT exist 3dEngine\path.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\path.c -o 3dEngine\path.o
if NOT exist 3dEngine\glDebug.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\glDebug.c -o 3dEngine\glDebug.o
if NOT exist 3dEngine\animate.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\animate.c -o 3dEngine\animate.o
if NOT exist 3dEngine\polyTransData.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\polyTransData.c -o 3dEngine\polyTransData.o

if NOT exist rsrc.res ..\..\tccAndTools\Gorc\Gorc.exe /r rsrc.rc

..\..\tccAndTools\tcc\tcc.exe %OBJ% -mwindows -lopengl32 -lwinmm -o %BIN%
..\..\tccAndTools\LinkRes2Exe.exe rsrc.res %BIN%

GOTO end

:clean

del %BIN% %OBJ% rsrc.res

:end
