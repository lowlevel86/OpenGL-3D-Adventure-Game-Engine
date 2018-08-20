CC = i686-w64-mingw32-gcc
OBJ = main.o readWriteWavFile_16Bit.o writeWavCFile.o
LIBS = -mwindows
BIN = wavToC.exe
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

readWriteWavFile_16Bit.o: readWriteWavFile_16Bit.c
	$(CC) -c readWriteWavFile_16Bit.c -o readWriteWavFile_16Bit.o $(CFLAGS)

writeWavCFile.o: writeWavCFile.c
	$(CC) -c writeWavCFile.c -o writeWavCFile.o $(CFLAGS)
