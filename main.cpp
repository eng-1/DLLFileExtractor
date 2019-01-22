#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "PELocator.h"
#include "FileWriter.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 4) {
        cout << "Usage: DLLFileExtractor <Memory_dump_path> <Output_directory> <Size_of_largest_DLL>" << endl;
        return 1;
    }
    char* dumpFileName = argv[1];
    char* outputDir = argv[2];
    int fileSize = atoi(argv[3]);

    if (fileSize < 1) {
        cout << "Wrong file size" << endl;
        return 2;
    }
    FileWriter fWriter(outputDir);
    PELocator locator(dumpFileName, &fWriter, fileSize);

    locator.run();

    return 0;
}