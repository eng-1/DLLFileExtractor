#include <iostream>
#include "FileFormats.h"
#include "PELocator.h"
#include "FileWriter.h"

using namespace std;

PELocator::PELocator(const char *memoryDumpFilePath, FileWriter *fileWriter, int dllFileSize) {
    dumpFile = fopen(memoryDumpFilePath, "rb");
    this->fileWriter = fileWriter;
    this->dllFileSize = dllFileSize;

}

PELocator::~PELocator() {
    fclose(dumpFile);
}

void PELocator::run() {
    for (;;) {
        int64_t positionInFile = ftello64(dumpFile);
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), dumpFile);
        if (bytesRead == 0) {
            break;
        }

        for (int i = 0; i < bytesRead - 1; i++) {
            int64_t offset = positionInFile + i;
            if (buffer[i] == 'M' && buffer[i + 1] == 'Z'
                //|| offset == 0x503cb914 || offset == 0x4b08bb54 //Forces the program to treat these offsets as a valid DLL file.
                ) {
                if (i < bytesRead - 0x300 && bytesRead > 0x300) {
                    checkIfValidPE(positionInFile, i);
                } else {
                    // MZ signature is too close to the end of the buffer.
                    // Adjusts file position so MZ will be at the beginning of the buffer on next loop iteration.
                    fseeko64(dumpFile, offset, SEEK_SET);
                }

            }
        }
    }
}

void PELocator::checkIfValidPE(int64_t positionOfBufferInFile, int positionInBuffer) {
    IMAGE_DOS_HEADER *mzHeader = reinterpret_cast<IMAGE_DOS_HEADER *>(&buffer[positionInBuffer]);

    uint32_t peOffset = mzHeader->e_lfanew;

    if (peOffset == 0) {
        peOffset = 0x80;
    }
    if (peOffset < 0x40 || peOffset > 0x100) {
        return;
    }

    IMAGE_NT_HEADERS *peHeader = reinterpret_cast<IMAGE_NT_HEADERS *>(&buffer[positionInBuffer + peOffset]);

    if (peHeader->Signature == 0x00004550) {
        int positionOfMzSignature = positionOfBufferInFile + positionInBuffer;
        printf("Located Valid PE File at: %010x\n", positionOfMzSignature);

        char name[36];
        sprintf(name, "pe%010x.dll", positionOfMzSignature);

        uint8_t* outputFileContents = new uint8_t[dllFileSize];

        uint64_t currentPositionOnBuffer = ftello64(dumpFile);
        fseeko64(dumpFile, positionOfMzSignature, SEEK_SET);
        int bytesRead = fread(outputFileContents, 1, dllFileSize, dumpFile);
        fseeko64(dumpFile, currentPositionOnBuffer, SEEK_SET);

        // Adds MZ header to DLL if it detects that it is missing
        IMAGE_DOS_HEADER *repairDosHeader = reinterpret_cast<IMAGE_DOS_HEADER *>(outputFileContents);
        if (repairDosHeader->e_magic == 0 ) {
            repairDosHeader->e_magic = 0x5a4d;
        }
        if (repairDosHeader->e_lfanew == 0 ) {
            repairDosHeader->e_lfanew = 0x80;
        }
        //

        fileWriter->writeFile(name, outputFileContents, bytesRead);
        delete[] outputFileContents;
    }
}
