#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "splay.h"

// Function to create a new splay node
SplayNode* create_node(int value) {
    SplayNode* node = (SplayNode*)malloc(sizeof(SplayNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

SplayNode* splay(SplayNode* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->value) {
        assert(root->left != NULL);

        if (value < root->left->value) {
            SplayNode* temp = splay(root->left->left, value);
            assert(temp != NULL);

            root->left->left = temp->right;
            temp->right = root->left;
            root->left = root->left->right;
            temp->right->right = root;

            return temp;
            
        } else if (value > root->left->value) {
            SplayNode* temp = splay(root->left->right, value);
            assert(temp != NULL);

            root->left->right = temp->left;
            temp->left = root->left;
            root->left = temp->right;
            temp->right = root;

            return temp;

        } else {
            SplayNode* temp = root->left;
            root->left = temp->right;
            temp->right = root;

            return temp;

        }
    } else if (value > root->value) {
        assert(root->right != NULL);

        if (value < root->right->value) {
            SplayNode* temp = splay(root->right->left, value);
            assert(temp != NULL);

            root->right->left = temp->right;
            temp->right = root->right;
            root->right = temp->left;
            temp->left = root;

            return temp;

        } else if (value > root->right->value) {
            SplayNode* temp = splay(root->right->right, value);
            assert(temp != NULL);

            root->right->right = temp->left;
            temp->left = root->right;
            root->right = root->right->left;
            temp->left->left = root;

            return temp;

        } else {
            SplayNode* temp = root->right;
            root->right = temp->left;
            temp->left = root;

            return temp;

        }
    } else {
            return root;

    }
}

SplayNode* insert(SplayNode* root, int value) {
    if (root == NULL) {
        return create_node(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);

    } else if (value > root->value) {
        root->right = insert(root->right, value);

    } else {
        return root;

    }

    return splay(root, value);
}

SplayNode* delete(SplayNode* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (search(&root, value)) {
        SplayNode* temp = root;

        if (temp->left == NULL) {
            root = temp->right;

        } else if (temp->right == NULL) {
            root = temp->left;

        } else {
            temp->right = find_min(temp->right);
            temp->right->left = temp->left;
            root = temp->right;
        }

        free(temp);

        return root;
    } else {
        return root;
    }
}

bool search_aux(SplayNode* root, int value) {
    if (root == NULL) {
        return false;
    }

    SplayNode* temp = root;

    while (temp) {
        if (value < temp->value) {
            temp = temp->left;

        } else if (value > temp->value) {
            temp = temp->right;

        } else {
            return true;

        }
    }

    return false;
}

bool search(SplayNode** root, int value) {
    bool found = search_aux(*root, value);

    if (found) {
        *root = splay(*root, value);
    }

    return found;
}


SplayNode* find_min(SplayNode* root) {
    if (root == NULL) {
        return NULL;
    }

    SplayNode* temp = root;

    while (temp->left) {
        temp = temp->left;
    }

    return splay(root, temp->value);
}

SplayNode* find_max(SplayNode* root) {
    if (root == NULL) {
        return NULL;
    }

    SplayNode* temp = root;

    while (temp->right) {
        temp = temp->right;
    }

    return splay(root, temp->value);
}

void free_splay(SplayNode* root) {
    if (root == NULL) {
        return;
    }

    free_splay(root->left);
    free_splay(root->right);
    free(root);
}
