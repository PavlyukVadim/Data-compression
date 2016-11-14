#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Archiver
{
    const int MAX_META = 3; // order
    vector<string> files;

    public:
        Archiver();
        Archiver(vector<string> const& filesName);
        virtual ~Archiver();

    string getFilesMetaData();
    void Compression();
    void Decompression(string);

    void getFilesName();
    string validateMeta(string);
};

