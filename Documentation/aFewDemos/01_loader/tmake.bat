@echo off

echo This batch file will use tcc to compile c code.
echo To use just type 'tmake' within a terminal.
echo Use 'tmake clean' to prepare for remaking all c files.
echo To remake fileLoc\thisFile.c use 'tmake fileLoc\thisFile'.

SET BIN=loader.exe
SET OBJ=main.o world.o 3dEngine\rotate.o 3dEngine\rotate2.o 3dEngine\applyRotLocSz.o 3dEngine\transform.o 3dEngine\drawMeshGL.o

if "%1" == "clean" GOTO clean

if exist %1.o echo deleting and remaking %1.o
if exist %1.o del %1.o

..\..\tccAndTools\tcc\tcc.exe -c main.c -o main.o

if NOT exist world.o ..\..\tccAndTools\tcc\tcc.exe -c world.c -o world.o

if NOT exist 3dEngine\rotate.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\rotate.c -o 3dEngine\rotate.o
if NOT exist 3dEngine\rotate2.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\rotate2.c -o 3dEngine\rotate2.o
if NOT exist 3dEngine\applyRotLocSz.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\applyRotLocSz.c -o 3dEngine\applyRotLocSz.o
if NOT exist 3dEngine\transform.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\transform.c -o 3dEngine\transform.o
if NOT exist 3dEngine\drawMeshGL.o ..\..\tccAndTools\tcc\tcc.exe -c 3dEngine\drawMeshGL.c -o 3dEngine\drawMeshGL.o

..\..\tccAndTools\tcc\tcc.exe %OBJ% -mwindows -lopengl32 -o %BIN%

GOTO end

:clean

del %BIN% %OBJ%

:end
