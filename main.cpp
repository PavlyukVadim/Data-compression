#include <iostream>

#include "Archiver.h"
#include "BHuffman.h"

using namespace std;


int main()
{
    //vector<string> files(3);

    /*files[0] = "aaa.txt";
    files[1] = "bbb.txt";
    files[2] = "logo.png";


    Archiver *ar = new Archiver(files);
    ar->getFilesName();
    cout << ar->getFilesMetaData();
    ar->Compression();*/

    //ar->Decompression("arc");

    BHuffman* hf = new BHuffman();
    hf->Compression("data/video.mp4");
    hf->Decompression("data/huffmanCom.bin", "data/videodec.mp4");

    return 0;
}
