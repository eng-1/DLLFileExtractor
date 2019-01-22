#include <cstdio>
#include <string>
#include "FileWriter.h"
using namespace std;

FileWriter::FileWriter(const char *outputDirectoryPath) {
    this->outputDirectoryName = outputDirectoryPath;

}

void FileWriter::writeFile(const char *outputFileName, const uint8_t *outputFileContents, int fileSize) {
    string fullPath = string(outputDirectoryName) + "/" + outputFileName;
    FILE* fileWrite = fopen(fullPath.c_str(), "wb");

    int bytesWritten = fwrite(outputFileContents, 1, fileSize, fileWrite);
    printf("Wrote file '%s' with size: %d\n", outputFileName, bytesWritten);

    fclose(fileWrite);
}
