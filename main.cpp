#include <iostream>

#include "Archiver.h"
#include "Huffman.h"

using namespace std;


int main()
{
    vector<string> files(3);

    /*files[0] = "aaa.txt";
    files[1] = "bbb.txt";
    files[2] = "logo.png";


    Archiver *ar = new Archiver(files);
    ar->getFilesName();
    cout << ar->getFilesMetaData();
    ar->Compression();*/
    //ar->Decompression("arc");
    //setlocale(LC_ALL, "Russian");
    Huffman* hf = new Huffman();
    string TestString = "aaa sdkjfj adsh fasfd sa;dfhudsioidjfhvdufd idaoisufh lasjdvhkjs sidfbdfh dajsb zlkxvj lksjzfzlkjcxlk";
    hf->Compression(TestString);
    hf->Decompression("huffmanCom.bin", "decompress.txt");

    return 0;
}
