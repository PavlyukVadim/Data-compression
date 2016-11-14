#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Archiver
{
    vector<string> files;

    public:
        Archiver();
        virtual ~Archiver();

    void getInfo();
    void Compression();
    void Decompression();
};

