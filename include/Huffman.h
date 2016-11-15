

const int UniqueSymbols = 256;

class BasicNode;


class Huffman
{
    public:
        Huffman();
        virtual ~Huffman();

        BasicNode* BuildTree(int frequencies[]);

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
    //конструктор по умолчанию
    NodeComp(const bool& revpar = false) { rev = revpar;}
    bool operator()(const BasicNode* l, const BasicNode* r) {
        if (rev) {
            return l->freq > r->freq;
        }
        else
            return l->freq < r->freq;
    }
};


