#include "Archiver.h"

#include <stdio.h>
#include <string.h>


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
    char byte[1];
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




void Archiver::Decompression(string nameArcFile) {
    FILE *arch = fopen(nameArcFile.c_str(),"rb"); // open Arch File
    char strSizeMeta[MAX_META];
    fread(strSizeMeta, 1, MAX_META, arch);
    int sizeMeta = atoi(strSizeMeta);

    char *metaData = new char[sizeMeta];
    fread(metaData, 1, sizeMeta + 1, arch);

    vector<string> tokens; // "file_name file_size"
    char *tok = strtok(metaData, "|");
    int toks = 0;

    while(tok) {
        if( !strlen(tok) ) break;
        tokens.push_back(tok);
        tok = strtok(NULL, "|");
        toks++;
    }

    char byte[1];

    for (int i = 0; i < tokens.size(); i++) {
        string fileName = tokens[i].substr(tokens[i].find(" ") + 1, tokens[i].length());
        int sizeFile = atoi( tokens[i].substr(0, tokens[i].find(" ")).c_str() );

        cout << fileName << endl;
        FILE* f = fopen(fileName.c_str(), "wb");

        while(sizeFile--) {
            if( fread(byte, 1, 1, arch) ) {
                fwrite(byte, 1, 1, f);
            }
        }

        fclose(f);
    }
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
