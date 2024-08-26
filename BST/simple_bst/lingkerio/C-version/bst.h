#ifndef BST_H
#define BST_H

#include <stdbool.h>

// Define the structure for a BST node
typedef struct BSTNode {
    int value;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// Function to create a new BST node
BSTNode* create_node(int value);

// Function to insert a value into the BST
BSTNode* insert(BSTNode* root, int value);

// Function to check if a value exists in the BST
bool search(BSTNode* root, int value);

// Function to find the minimum value in the BST
BSTNode* find_min(BSTNode* root);

// Function to find the maximum value in the BST
BSTNode* find_max(BSTNode* root);

// Function to delete a value from the BST
BSTNode* delete(BSTNode* root, int value);

// Function to free the entire BST
void free_bst(BSTNode* root);

#endif // BST_H
