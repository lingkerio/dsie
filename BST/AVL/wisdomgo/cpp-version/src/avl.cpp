#include "avl.h"
#include <algorithm>
#include <stdexcept>

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    clear(root);
}

void AVL::clear(AVLnode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int height(AVLnode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLnode* node) {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

AVLnode* rightRotate(AVLnode* y) {
    AVLnode* x = y->left;
    AVLnode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLnode* leftRotate(AVLnode* x) {
    AVLnode* y = x->right;
    AVLnode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLnode* AVL::insert(AVLnode* node, int val) {
    if (!node) return new AVLnode(val);
    if (val < node->val)
        node->left = insert(node->left, val);
    else if (val > node->val)
        node->right = insert(node->right, val);
    else
        return node;
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && val < node->left->val) // LL型，右旋
        return rightRotate(node);
    if (balance < -1 && val > node->right->val)
        return leftRotate(node);  // RR型，左旋
    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);   //LR型，先左旋再右旋
    }
    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);  // RL型，先右旋再左旋
    }

    return node;
}
AVLnode* AVL::findmin(AVLnode* node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void AVL::insert(int val) {
    root = insert(root, val);
}

bool AVL::find(int val) {
    AVLnode* current = root;
    while (current) {
        if (val < current->val)
            current = current->left;
        else if (val > current->val)
            current = current->right;
        else
            return true; 
    }
    return false; 
}

int AVL::findmin() {
    AVLnode* current = root;
    if (!current) throw std::runtime_error("Tree is empty");
    while (current->left != nullptr)
        current = current->left;
    return current->val;
}

int AVL::findmax() {
    AVLnode* current = root;
    if (!current) throw std::runtime_error("Tree is empty");
    while (current->right != nullptr)
        current = current->right;
    return current->val;
}

AVLnode* AVL::remove(AVLnode* node, int val, bool& isDeleted) {
    if (node == nullptr) {
        isDeleted = false;
        return nullptr;
    }
    if (val < node->val) {
        node->left = remove(node->left, val, isDeleted);
    } else if (val > node->val) {
        node->right = remove(node->right, val, isDeleted);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            AVLnode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                delete node;
                node = nullptr;
            } else {
                *node = *temp; 
                delete temp;
            }
            isDeleted = true;
        } else {
            AVLnode* temp = findmin(node->right);
            node->val = temp->val;
            node->right = remove(node->right, temp->val, isDeleted);
        }
    }
    if (node == nullptr) return node;
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


bool AVL::remove(int val) {
    bool isDeleted = false;
    root = remove(root, val, isDeleted);
    return isDeleted;
}
