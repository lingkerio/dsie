#ifndef SPLAY_H
#define SPLAY_H

#include <stdbool.h>

typedef struct SplayNode {
    int value;
    struct SplayNode *left;
    struct SplayNode *right;
} SplayNode;

SplayNode* create_node(int value);

SplayNode* insert(SplayNode* node, int value);

bool search(SplayNode** node, int value);

SplayNode* find_min(SplayNode* node);

SplayNode* find_max(SplayNode* node);

SplayNode* delete(SplayNode* node, int value);

void free_splay(SplayNode* node);

#endif // SPLAY_H