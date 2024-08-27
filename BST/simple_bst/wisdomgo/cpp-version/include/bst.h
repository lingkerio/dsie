#pragma once

#include <iostream>

struct BSTnode{
    int val;
    BSTnode* left;
    BSTnode* right;
    BSTnode(int val): val(val), left(nullptr), right(nullptr){}
};


class BST{
public:
    BST();
    ~BST();
    void insert(int val);
    void remove(int val);
    bool find(int val);
    int findmin();
    int findmax();

private:
    BSTnode* root;
    BSTnode* insert(BSTnode* node,int val);
    BSTnode* remove(BSTnode* node,int val);
    BSTnode* findmin(BSTnode* node);
    BSTnode* findmax(BSTnode* node);
    void destroyTree(BSTnode* node);
};