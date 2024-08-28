#ifndef AVL_H
#define AVL_H

struct AVLnode {
    int val;
    AVLnode* left;
    AVLnode* right;
    int height;
    AVLnode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    AVLnode* root;
    AVLnode* insert(AVLnode* node, int val);
    AVLnode* remove(AVLnode* node, int val, bool& isDeleted);
    AVLnode* findmin(AVLnode* node);
    AVLnode* findmax(AVLnode* node);
    void clear(AVLnode* node);

public:
    AVL();
    ~AVL();
    void insert(int val);
    bool remove(int val);
    bool find(int val);
    int findmin();
    int findmax();
};

#endif // AVL_H
