#include "SParch.h"

#include<vector>
#include <iostream>


using namespace std;

SParch::SParch() {
    ar = new Archiver();
    bH = new BHuffman();
}

SParch::~SParch() { }

void SParch::Compression(vector<string> files, string pathArch) {

    vector<string> compressedFiles;
    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
         compressedFiles.push_back(bH->Compression(*(it)));
    }
    ar->Compression(compressedFiles, pathArch);
    DeleteFiles(compressedFiles);
}

void SParch::DeleteFiles(vector<string> files) {
    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
        string fileName = *(it);
        remove(fileName.c_str());
    }
}

void SParch::Decompression(string cFilePath, string dFilePath) {
    vector<string> cFiles;
    cFiles = ar->Decompression(cFilePath, dFilePath);
    for (vector<string>::iterator it = cFiles.begin(); it != cFiles.end(); ++it) {
        string filePath = *(it);
        cout << "Compressed files: " << endl;
        cout << filePath << endl;
        int l_pos = filePath.rfind("/");
        int d_pos = filePath.rfind(".");
        string fileName = filePath.substr(l_pos + 1, (d_pos - l_pos - 1));
        string dFileName = dFilePath + fileName;
        cout << "Decompressed files: " << endl;
        cout << dFileName << endl;

        bH->Decompression(filePath, dFilePath + fileName);
    }
    DeleteFiles(cFiles);
}


