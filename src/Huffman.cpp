#include "Huffman.h"


using namespace std;

Huffman::Huffman() {

}

Huffman::~Huffman() {

}



void Huffman::Compression(string data) {

    int frequencies[UniqueSymbols] = {0};
    const char* ptr = data.c_str();
    while (*ptr != '\0') {
        ++frequencies[*ptr++];
    }

    BasicNode* root = BuildTree(frequencies);
    SymbolCodeMap codes;
    GenerateCodes(root, BinarySymbolCode(), codes);
    delete root;


    string huffmanTable = GetHuffmanTable(codes);
    string nameFile = "huffmanCom";

    char byte[1];
    FILE* f = fopen( (nameFile).c_str(), "wb"); // create new File
    fputs(huffmanTable.c_str(), f); // writte meta


    /*for (int i = 0; i < files.size(); i++) {
        FILE* f = fopen(files[i].c_str(), "rb");
        if(!f){
            break;
        }
        while(!feof(f)) {
            if( fread(byte, 1, 1, f) ) {
                fwrite(byte, 1, 1, cf);
            }
        }
        cout<<files[i]<<" Добавлен в архив."<<endl;
        fclose(f);
    }*/
    fclose(f);

}


BasicNode* Huffman::BuildTree(int frequencies[]) {
    priority_queue<BasicNode*, vector<BasicNode*>, NodeComp> trees;

    for (int i = 0; i < UniqueSymbols; ++i) {
        if(frequencies[i] != 0) {
            trees.push(new LeafNode(frequencies[i], (char)i));
        }
    }
    while (trees.size() > 1) {
        BasicNode* childR = trees.top();
        trees.pop();

        BasicNode* childL = trees.top();
        trees.pop();

        BasicNode* parent = new ParentNode(childR, childL);
        trees.push(parent);
    }
    return trees.top();
}


void Huffman::GenerateCodes(const BasicNode* node, const BinarySymbolCode& bsc, SymbolCodeMap& scm) {
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node)) { // перевірка чи вузол є екземпляром LeafNode
        scm[lf->c] = bsc;
    }
    else if (const ParentNode* pn = dynamic_cast<const ParentNode*>(node)) {
        BinarySymbolCode leftPrefix = bsc;
        leftPrefix.push_back(false);
        GenerateCodes(pn->left, leftPrefix, scm);

        BinarySymbolCode rightPrefix = bsc;
        rightPrefix.push_back(true);
        GenerateCodes(pn->right, rightPrefix, scm);
    }
}


string Huffman::GetHuffmanTable(SymbolCodeMap& scm) {
    string huffmanTable = "";
    for (SymbolCodeMap::const_iterator it = scm.begin(); it != scm.end(); ++it) {
        huffmanTable += it->first + '\0';
        huffmanTable += " ";

        string code = "";

        for (int i = 0; i < it->second.size(); i++) {
            code += it->second[i] ? "1" : "0";
        }
        huffmanTable += code + "|";
    }

    return huffmanTable;
}
