#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int height(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int get_balance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode* create_node(int value) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

AVLNode* insert(AVLNode* node, int value) {
    if (node == NULL)
        return create_node(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && value < node->left->value)
        return right_rotate(node);

    if (balance < -1 && value > node->right->value)
        return left_rotate(node);

    if (balance > 1 && value > node->left->value) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

AVLNode* find_min(AVLNode* node) {
    if (node == NULL)
        return NULL;

    while (node->left != NULL)
        node = node->left;
    return node;
}

AVLNode* find_max(AVLNode* node) {
    if (node == NULL)
        return NULL;
    
    while (node->right != NULL)
        node = node->right;
    return node;
}

bool search(AVLNode* node, int value) {
    if (node == NULL)
        return false;

    if (value < node->value)
        return search(node->left, value);
    else if (value > node->value)
        return search(node->right, value);
    else
        return true;
}

AVLNode* delete(AVLNode* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->value)
        root->left = delete(root->left, value);
    else if (value > root->value)
        root->right = delete(root->right, value);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            AVLNode* temp = find_min(root->right);

            root->value = temp->value;

            root->right = delete(root->right, temp->value);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0)
        return right_rotate(root);

    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0)
        return left_rotate(root);

    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void free_avl(AVLNode* node) {
    if (node != NULL) {
        free_avl(node->left);
        free_avl(node->right);
        free(node);
    }
}
