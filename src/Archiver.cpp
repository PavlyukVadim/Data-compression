#include "Archiver.h"

#include <stdio.h>
#include <string.h>


Archiver::Archiver() { }
Archiver::~Archiver() { }


void Archiver::Compression(vector<string> const& filesPath, string archName) {
    //cout << "aaaaaaa";
    string metaData = getFilesMetaData(filesPath);
    //cout << metaData;
    metaData = validateMeta(metaData);

    char byte[1];
    FILE* cf = fopen( (archName).c_str(), "wb"); // create new Arc File
    fputs(metaData.c_str(), cf); // writte meta in Arc


    for (int i = 0; i < filesPath.size(); i++) {
        FILE* f = fopen(filesPath[i].c_str(), "rb");
        if(!f){
            break;
        }
        while(!feof(f)) {
            if( fread(byte, 1, 1, f) ) {
                fwrite(byte, 1, 1, cf);
                //cout << byte[0];
            }
        }
        cout << filesPath[i]<<" Добавлен в архив."<<endl;
        fclose(f);
    }
    fclose(cf);
}




string Archiver::getFilesMetaData(vector<string> const& filesPath) {

    string filesMetaData = "";

    for(int i = 0; i < filesPath.size(); i++) {
        FILE *f = fopen( (filesPath[i]).c_str(), "rb"); // c_str - string to char *
        if(!f) {
            break;
            //
        }

        fseek(f, 0, SEEK_END);
        int fileSize = ftell(f); // count bite from begin

        string strFileSize = to_string(fileSize);
        int l_pos = filesPath[i].rfind("/");
        string fileName = filesPath[i].substr(l_pos + 1, filesPath[i].length());
        //cout << "file_name : " << fileName << endl;

        filesMetaData += strFileSize + " " + fileName + "|";
        fclose(f);
    }
    return filesMetaData;
}


void Archiver::Decompression(string nameArcFile, string pathFile) {
    FILE *arch = fopen(nameArcFile.c_str(),"rb"); // open Arch File
    char strSizeMeta[MAX_META];
    fread(strSizeMeta, 1, MAX_META, arch);
    int sizeMeta = atoi(strSizeMeta);
    cout << "sizeMeta: " << sizeMeta << endl;

    char *metaData = new char[sizeMeta];
    fread(metaData, 1, sizeMeta, arch);
    cout << "MetaData: " << metaData << endl;

    fread(metaData, 1, 1, arch);
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

        cout << pathFile << fileName << endl;
        FILE* f = fopen((pathFile + fileName + "2").c_str(), "wb");

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
    cout << "W meta: " << metaData << endl;
    cout << "W meta size: " << strSizeMeta << endl;
    return strSizeMeta + "|" + metaData;
}


void Archiver::getFilesName() {
    for(vector<string>::const_iterator file = files.begin(); file != files.end(); ++file) {
        cout << *file << endl;
    }
}
