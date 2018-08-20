@echo off

echo This batch file will use tcc to compile c code.
echo To use just type 'tmake' within a terminal.
echo Use 'tmake clean' to prepare for remaking all c files.

SET BIN=cube.exe
SET OBJ=main.o

if "%1" == "clean" GOTO clean

..\..\tccAndTools\tcc\tcc.exe -c main.c -o main.o

..\..\tccAndTools\tcc\tcc.exe %OBJ% -mwindows -lopengl32 -o %BIN%

GOTO end

:clean

del %BIN% %OBJ%

:end
