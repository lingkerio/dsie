#include "bst.h"
#include <stdexcept>
#include <iostream>

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    destroyTree(root);
}

void BST::insert(int val) {
    root = insert(root, val);
}

bool BST::remove(int val) { 
    bool isDeleted = false;
    root = remove(root, val, isDeleted);
    return isDeleted; 
}

bool BST::find(int val) {
    BSTnode* node = root;
    while (node != nullptr) {
        if (val < node->val) {
            node = node->left;
        } else if (val > node->val) {
            node = node->right;
        } else {
            return true;
        }
    }
    return false;
}

int BST::findmin() {
    BSTnode* node = findmin(root);
    if (node == nullptr) {
        throw std::runtime_error("Error: It is an empty tree");
    }
    return node->val;
}

int BST::findmax() {
    BSTnode* node = findmax(root);
    if (node == nullptr) {
        throw std::runtime_error("Error: It is an empty tree");
    }
    return node->val;
}

BSTnode* BST::insert(BSTnode* node, int val) {
    if (node == nullptr) {
        return new BSTnode(val);
    } else if (val < node->val) {
        node->left = insert(node->left, val);
    } else if (val > node->val) {
        node->right = insert(node->right, val);
    }
    return node;
}

BSTnode* BST::remove(BSTnode* node, int val, bool& isDeleted) {
    if (node == nullptr) {
        isDeleted = false;
        return nullptr;
    } else if (val < node->val) {
        node->left = remove(node->left, val, isDeleted);
    } else if (val > node->val) {
        node->right = remove(node->right, val, isDeleted);
    } else {
        isDeleted = true;
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            BSTnode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BSTnode* temp = node->left;
            delete node;
            return temp;
        } else {
            BSTnode* temp = findmin(node->right);
            node->val = temp->val;
            node->right = remove(node->right, temp->val, isDeleted);
        }
    }
    return node;
}

BSTnode* BST::findmin(BSTnode* node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->left == nullptr) {
        return node;
    } else {
        return findmin(node->left);
    }
}

BSTnode* BST::findmax(BSTnode* node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->right == nullptr) {
        return node;
    } else {
        return findmax(node->right);
    }
}

void BST::destroyTree(BSTnode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
