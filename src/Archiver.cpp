#include "Archiver.h"

#include <stdio.h>

Archiver::Archiver() {
}

Archiver::Archiver(vector<string> const& filesName) {
    files = filesName;
}

Archiver::~Archiver() {

}

void Archiver::Compression() {

}

void Archiver::getFilesMetaData() {
    for(vector<string>::const_iterator file = files.begin()+1; file != files.end(); ++file) {
        //cout << file << endl;
    }
}



void Archiver::getFilesName() {
    for(int i = 0; i < files.size(); i++) {
        cout << files[i] << endl;
    }
}
