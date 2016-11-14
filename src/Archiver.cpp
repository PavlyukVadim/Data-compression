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

string Archiver::getFilesMetaData() {

    string filesMetaData = "";

    for(int i = 0; i < files.size(); i++) {
        FILE *f = fopen( (files[i]).c_str(), "rb"); // c_str - string to char *
        if(!f) {
            break;
            //
        }

        fseek(f, 0, SEEK_END);
        int fileSize = ftell(f); // count bite from begin

        string strFileSize = to_string(fileSize);

        filesMetaData += strFileSize + " " + files[i] + "\n";
        fclose(f);
    }
    return filesMetaData ;
}



void Archiver::getFilesName() {
    for(vector<string>::const_iterator file = files.begin(); file != files.end(); ++file) {
        cout << *file << endl;
    }
}
