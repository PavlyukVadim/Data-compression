#include <iostream>

#include "Archiver.h"


using namespace std;

int main()
{
    vector<string> files(3);

    files[0] = "aaa.txt";
    files[1] = "bbb.txt";
    files[2] = "ccc.txt";

    Archiver *ar = new Archiver(files);
    //ar->getFilesName();
    //cout << ar->getFilesMetaData();
    ar->Compression();

    return 0;
}
