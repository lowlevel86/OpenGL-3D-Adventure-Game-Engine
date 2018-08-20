CC = i686-w64-mingw32-gcc
WINDRES = i686-w64-mingw32-windres
RES = 
OBJ = main.o world.o 3dEngine/rotate.o 3dEngine/rotate2.o 3dEngine/applyRotLocSz.o 3dEngine/transform.o 3dEngine/drawMeshGL.o $(RES)
LIBS = -mwindows -lopengl32 -lwinmm
BIN = loader.exe
CFLAGS = -Wall
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

main.o: .FORCE
	$(CC) -c main.c -o main.o $(CFLAGS)

.FORCE:

