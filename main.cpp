#include <iostream>

#include "Archiver.h"


using namespace std;

int main()
{
    vector<string> files(3);

    files[0] = "aaa";
    files[1] = "bbb";
    files[2] = "ccc";

    Archiver *ar = new Archiver(files);
    ar->getFilesName();

    return 0;
}
