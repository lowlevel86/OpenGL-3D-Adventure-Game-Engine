CC = i686-w64-mingw32-gcc
OBJ = main.o readWriteBmpFile.o writeTexCFile.o
LIBS = -mwindows
BIN = texToC.exe
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

readWriteBmpFile.o: readWriteBmpFile.c
	$(CC) -c readWriteBmpFile.c -o readWriteBmpFile.o $(CFLAGS)

writeTexCFile.o: writeTexCFile.c
	$(CC) -c writeTexCFile.c -o writeTexCFile.o $(CFLAGS)

