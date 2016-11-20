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
    cout << huffmanTable << endl;
    string nameFile = "huffmanCom.bin";

    FILE* f = fopen( (nameFile).c_str(), "wb"); // create new File
    fputs(huffmanTable.c_str(), f); // writte meta

    char bite[1]; bite[0] = 0;
    int count_ = 0;
    for (int i = 0; i < data.length(); i++) {
        vector<bool> code = codes[data[i]];
        for (int n = 0; n < code.size(); n++) {
            bite[0] = bite[0] | code[n] << (7 - count_);
            count_++;
            if (count_ == 8) {
                fwrite(bite, 1, 1, f);
                bite[0] = 0;
                count_ = 0;
            }
        }
    }
    fclose(f);

}

void Huffman::Decompression(string cFileName, string dFileName) {
    FILE* cf = fopen( (cFileName).c_str(), "rb"); // open compressed file
    FILE* df = fopen( (dFileName).c_str(), "wb"); // create decompress file

    char strSizeMeta[MAX_META_H];
    fread(strSizeMeta, 1, MAX_META_H, cf);
    int sizeMeta = atoi(strSizeMeta);

    char *metaData = new char[sizeMeta];
    fread(metaData, 1, sizeMeta + 1, cf);
    metaData[sizeMeta] = '\0'; // delete last '|'

    vector<string> tokens; // "symbol symbol_code"
    char *tok = strtok(metaData, "|");
    int toks = 0;

    while(tok) {
        if( !strlen(tok) ) break;
        tokens.push_back(tok);
        tok = strtok(NULL, "|");
        toks++;
    }

    //create SymbolCodeMap ([symbol] = [binary_code])
    SymbolCodeMap codes;
    for (int i = 0; i < tokens.size(); i++) {
        //cout << tokens[i] << endl;
        char symbol = tokens[i][0];
        BinarySymbolCode code;
        string strCode = tokens[i].substr(tokens[i].find_last_of(" "), tokens[i].length());

        for (int n = 0; n < strCode.length(); n++) {
            if (strCode[n] == '1') {
                code.push_back(true);
            }
            else if (strCode[n] == '0') {
                code.push_back(false);
            }
        }
        codes[symbol] = code;
    }



    fclose(cf);
    fclose(df);

    //fputs(huffmanTable.c_str(), f); // writte meta
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
    // add string length meta data on begin
    string strTableSize = to_string( huffmanTable.length() );

    while(strTableSize.length() < MAX_META_H) {
        strTableSize = "0" + strTableSize;
    }

    return strTableSize + "|" + huffmanTable;
}
