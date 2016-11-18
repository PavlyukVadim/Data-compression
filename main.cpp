#include <iostream>

#include "Archiver.h"
#include "Huffman.h"

using namespace std;


int main()
{
    vector<string> files(3);

    files[0] = "aaa.txt";
    files[1] = "bbb.txt";
    files[2] = "logo.png";


    Archiver *ar = new Archiver(files);
    ar->getFilesName();
    cout << ar->getFilesMetaData();
    ar->Compression();
    //ar->Decompression("arc");

    /*Huffman* hf = new Huffman();
    string TestString = "test string ssss aaaaaa";
    hf->Compression(TestString);*/

    return 0;
}
