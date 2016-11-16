#include <iostream>

#include "Archiver.h"
#include "Huffman.h"

using namespace std;

const char* TestString = "test string ssss aaaaaa";

int main()
{
    vector<string> files(3);

    files[0] = "aaa.txt";
    files[1] = "bbb.txt";
    files[2] = "bird.avi";

    //Archiver *ar = new Archiver(files);
    //ar->getFilesName();
    //cout << ar->getFilesMetaData();
    //ar->Compression();
    //ar->Decompression("arc");

    Huffman* hf = new Huffman();

    int frequencies[UniqueSymbols] = {0};
    const char* ptr = TestString;
    while (*ptr != '\0') {
        ++frequencies[*ptr++];
    }

    BasicNode* root = hf->BuildTree(frequencies);

    SymbolCodeMap codes;
    hf->GenerateCodes(root, BinarySymbolCode(), codes);
    delete root;

    for (SymbolCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it) {
        cout << it->first << " ";
        copy(it->second.begin(), it->second.end(), ostream_iterator<bool>(cout));
        cout << endl;
    }

    return 0;
}
