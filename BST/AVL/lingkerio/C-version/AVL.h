#ifndef AVL_H
#define AVL_H

#include <stdbool.h>

// Define the structure for an AVL tree node
typedef struct AVLNode {
    int height;
    int value;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

// Function to create a new AVL node
AVLNode* create_node(int value);

// Function to insert a value into the AVL tree
AVLNode* insert(AVLNode* node, int value);

// Function to check if a value exists in the AVL tree
bool search(AVLNode* node, int value);

// Function to find the minimum value in the AVL tree
AVLNode* find_min(AVLNode* node);

// Function to find the maximum value in the AVL tree
AVLNode* find_max(AVLNode* node);

// Function to delete a value from the AVL tree
AVLNode* delete(AVLNode* node, int value);

// Function to free the entire AVL tree
void free_avl(AVLNode* node);

#endif // AVL_H
