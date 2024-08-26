#ifndef BST_H
#define BST_H

#include <memory>
struct BSTNode{
    int data;
    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;

    BSTNode(int val)
        : data(val)
        , left(nullptr)
        , right(nullptr)
    {}
};

using Node = std::unique_ptr<BSTNode>;

class BST {
private:
    Node root_;

public:
    BST() = default;
    BST(int data);
    ~BST() = default;
    bool isEmpty() const;
    void insert(int data);
    void remove(int data);
    BSTNode* findMin() const;
    BSTNode* findMax() const;
    bool search(int data) const;

private:
    void insert(Node& node, int data);
    void remove(Node& node, int data);
    BSTNode* findMin(const Node& node) const;
    BSTNode* findMax(const Node& node) const;
    bool search(const Node& node, int data) const;
};
#endif