#ifndef DLLFILEEXTRACTOR_FILEWRITER_H
#define DLLFILEEXTRACTOR_FILEWRITER_H


class FileWriter {
    const char* outputDirectoryName;

public:
    FileWriter(const char* outputDirectoryPath);
    void writeFile(const char *outputFileName, const uint8_t *outputFileContents, int fileSize);
};


#endif //DLLFILEEXTRACTOR_FILEWRITER_H
