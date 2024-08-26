#include "bst.h"
#include <asm-generic/errno.h>
#include <cstddef>
#include <memory>
#include <utility>

BST::BST(int data)
{
   root_ = std::make_unique<BSTNode>(data);
}

//public function
bool BST::isEmpty() const
{
    return root_ == nullptr;
}

bool BST::search(int data) const
{
    return search(root_, data);
}

BSTNode* BST::findMin() const
{
    return findMin(root_);
}

BSTNode* BST::findMax() const
{
    return findMax(root_);
}

void BST::insert(int data)
{
    insert(root_, data);
}

void BST::remove(int data)
{
    remove(root_, data);
}

// private function
void BST::insert(Node& node, int data)
{
    if (node == nullptr) {
        node = std::make_unique<BSTNode>(data);
    } else if (data < node->data) {
        insert(node->left, data);
    } else if (data > node->data) {
        insert(node->right, data);
    }
}

void BST::remove(Node& node, int data)
{
    if (node == nullptr) {
        return;
    }

    if (data < node->data) {
        remove(node->left, data);
    } else if (data > node->data) {
        remove(node->right,data);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            node.reset();
        } else if (node->left == nullptr) {
            node = std::move(node->right);
        } else if (node->right == nullptr) {
            node = std::move(node->left);
        } else {
            BSTNode* minNode = findMin(node->right);
            node->data = minNode->data;
            remove(node->right, minNode->data);
        }
    }
}

BSTNode* BST::findMin(const Node& node) const
{
    if (node == nullptr) {
        return nullptr;
    }

    BSTNode* cur = node.get();

    while (cur->left) {
        cur = cur->left.get();
    }

    return cur;
}

BSTNode* BST::findMax(const Node& node) const
{
    if (node == nullptr) {
        return nullptr;
    }

    BSTNode* cur = node.get();

    while (cur->right) {
        cur = cur->right.get();
    }
    return cur;
}

bool BST::search(const Node& node, int data) const
{
    if (node == nullptr) {
        return false;
    }
    if (data < node->data) {
        return search(node->left, data);
    }
    if (data > node->data) {
        return search(node, data);
    }

    return true;
}