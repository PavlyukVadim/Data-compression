#include <iostream>

#include "SParch.h"

using namespace std;


int main()
{

    vector<string> files(1);

    files[0] = "data/img.bmp";
    /*files[1] = "data/test.bmp";
    files[2] = "data/rtx.txt";
    files[3] = "data/aaa.txt";*/



    SParch* arch = new SParch();
    arch->Compression(files, "data/arch/arch.sp");
    arch->Decompression("data/arch/arch.sp", "data/decom/");

    return 0;
}
