#include <iostream>

#include "Archiver.h"
#include "BHuffman.h"

using namespace std;


int main()
{
    vector<string> files(2);

    files[0] = "data/lol.jpg";
    files[1] = "data/test.bmp";


    Archiver *ar = new Archiver();
    //ar->getFilesName();
    ar->Compression(files, "arc1");
    ar->Decompression("arc1", "data/");

    /*BHuffman* hf = new BHuffman();
    hf->Compression("data/video.mp4");
    hf->Decompression("data/huffmanCom.bin", "data/videodec.mp4");*/

    return 0;
}
