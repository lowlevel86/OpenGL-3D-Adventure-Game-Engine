CC = i686-w64-mingw32-gcc
WINDRES = i686-w64-mingw32-windres
RES =
OBJ = main.o $(RES)
LIBS = -mwindows -lopengl32
BIN = cube.exe
CFLAGS = -Wall
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)
