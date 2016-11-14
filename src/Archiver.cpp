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
    string metaData = getFilesMetaData();
    metaData = validateMeta(metaData);

    string nameArcFile = "arc";
    char byte [1];
    FILE* cf = fopen( (nameArcFile).c_str(), "wb"); // create new Arc File
    fputs(metaData.c_str(), cf); // writte meta in Arc


    for (int i = 0; i < files.size(); i++) {
        FILE* f = fopen(files[i].c_str(), "rb");
        if(!f){
            break;
        }
        while(!feof(f)) {
            if( fread(byte, 1, 1, f) ) {
                fwrite(byte, 1, 1, cf);
            }
        }
        cout<<files[i]<<" Добавлен в архив."<<endl;
        fclose(f);
    }
    fclose(cf);
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

        filesMetaData += strFileSize + " " + files[i] + "|";
        fclose(f);
    }
    return filesMetaData;
}


string Archiver::validateMeta(string metaData) {
    int sizeMetaData = metaData.length();
    string strSizeMeta = to_string( metaData.length() );
    if(strSizeMeta.length() > MAX_META) {
        cout << "Error" << endl;
    }

    while(strSizeMeta.length() < MAX_META) {
        strSizeMeta = "0" + strSizeMeta;
    }
    return strSizeMeta + "|" + metaData;
}


void Archiver::getFilesName() {
    for(vector<string>::const_iterator file = files.begin(); file != files.end(); ++file) {
        cout << *file << endl;
    }
}
