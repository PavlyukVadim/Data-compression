#include <iostream>
#include <queue>


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
