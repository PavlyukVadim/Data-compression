#include "Huffman.h"


using namespace std;

Huffman::Huffman() {

}

Huffman::~Huffman() {

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


void Huffman::GenerateCodes(const BasicNode* node, const BinarySymbolCode& bsc, SymbolCodeMap& scm){
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
