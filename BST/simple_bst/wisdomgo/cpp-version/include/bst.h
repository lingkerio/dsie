#ifndef BST_H
#define BST_H

struct BSTnode {
    int val;
    BSTnode* left;
    BSTnode* right;
    BSTnode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTnode* root;
    BSTnode* insert(BSTnode* node, int val);
    BSTnode* remove(BSTnode* node, int val, bool& isDeleted);
    BSTnode* findmin(BSTnode* node);
    BSTnode* findmax(BSTnode* node);
    void destroyTree(BSTnode* node);

public:
    BST();
    ~BST();
    void insert(int val);
    bool remove(int val);
    bool find(int val);
    int findmin();
    int findmax();
};

#endif
