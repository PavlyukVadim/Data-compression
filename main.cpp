#include <iostream>

#include "Archiver.h"


using namespace std;

int main()
{
    vector<string> files(3);

    files[0] = "aaa.txt";
    files[1] = "bbb.txt";
    files[2] = "bird.avi";

    Archiver *ar = new Archiver(files);
    //ar->getFilesName();
    //cout << ar->getFilesMetaData();
    //ar->Compression();
    ar->Decompression("arc");

    return 0;
}
