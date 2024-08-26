#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a BST node
typedef struct BSTNode {
    int value;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// Function to create a new BST node
BSTNode* create_node(int value) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a value into the BST
BSTNode* insert(BSTNode* root, int value) {
    if (root == NULL) {
        return create_node(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to check if a value exists in the BST
bool search(BSTNode* root, int value) {
    if (root == NULL) {
        return false;
    }

    if (value < root->value) {
        return search(root->left, value);
    } else if (value > root->value) {
        return search(root->right, value);
    } else {
        return true;
    }
}

// Function to find the minimum value in the BST
BSTNode* find_min(BSTNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to find the maximum value in the BST
BSTNode* find_max(BSTNode* root) {
    while (root && root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Function to delete a value from the BST
BSTNode* delete(BSTNode* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->value) {
        root->left = delete(root->left, value);
    } else if (value > root->value) {
        root->right = delete(root->right, value);
    } else {
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        BSTNode* temp = find_min(root->right);
        root->value = temp->value;
        root->right = delete(root->right, temp->value);
    }

    return root;
}

// Function to free the entire BST
void free_bst(BSTNode* root) {
    if (root != NULL) {
        free_bst(root->left);
        free_bst(root->right);
        free(root);
    }
}
