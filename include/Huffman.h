#include <iostream>
#include <queue>
#include <map>
#include <iterator>     // ostream_iterator
#include <algorithm>    // copy
#include <string.h>     // strtok


using namespace std;


typedef vector<bool> BinarySymbolCode;
typedef map<char, BinarySymbolCode> SymbolCodeMap;

const int UniqueSymbols = 256; // for char
class BasicNode;
const int MAX_META_H = 5; // order


class Huffman
{
    public:
        Huffman();
        virtual ~Huffman();

        BasicNode* BuildTree(int frequencies[]);
        void GenerateCodes(const BasicNode*, const BinarySymbolCode&, SymbolCodeMap&); // обхід дерева + запис в map
        string GetHuffmanTable(SymbolCodeMap&);
        void Compression(string);
        void Decompression(string, string);
        char findCodeInCodesMap(const BinarySymbolCode&, SymbolCodeMap&);
};

class BasicNode {
    public:
        int freq;
        BasicNode();
        BasicNode(int f) { freq = f;}
        virtual ~BasicNode() {};
};


class ParentNode : public BasicNode {
    public:
       BasicNode* left;
       BasicNode* right;

       ParentNode(BasicNode* l, BasicNode* r) : BasicNode(l->freq + r->freq), left(l), right(r) {}
       ~ParentNode() {
            delete left;
            delete right;
       }
};


class LeafNode : public BasicNode {
    public:
        const char c;
        LeafNode(int f, char c) : BasicNode(f), c(c) {}
};


class NodeComp {
    bool rev;
public:
    NodeComp(const bool& revpar = false) { rev = revpar;}
    bool operator()(const BasicNode* l, const BasicNode* r) {
        if (rev) {
            return l->freq < r->freq;
        }
        else
            return l->freq > r->freq;
    }
};
