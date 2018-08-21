void getWaveFormat16Bit(char *, int *, int *);

void readWavFileMono16Bit(char *, float *);
void readWavFileStereo16Bit(char *, float *, float *);

void getWavFileSampSzMono16Bit(char *, int *);
void getWavFileSampSzStereo16Bit(char *, int *);

void writeWavFileMono16Bit(char *, float *, int, int);
void writeWavFileStereo16Bit(char *, float *, float *, int, int);
