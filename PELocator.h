#ifndef DLLFILEEXTRACTOR_PELOCATOR_H
#define DLLFILEEXTRACTOR_PELOCATOR_H


#include <cstdio>
#include "FileWriter.h"

class PELocator {
    FILE *dumpFile;
    uint8_t buffer[0x10000];
    FileWriter *fileWriter;
    int dllFileSize;

public:

    PELocator(const char *memoryDumpFilePath, FileWriter *fileWriter, int dllFileSize);

   ~PELocator();

    void run();

    void checkIfValidPE(int64_t positionOfBufferInFile, int positionInBuffer);
};


#endif //DLLFILEEXTRACTOR_PELOCATOR_H
