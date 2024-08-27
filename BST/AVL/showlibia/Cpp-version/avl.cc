#include "avl.hh"
#include <memory>
#include <utility>

// public function
void AVLTree::insert(int data)
{
    insert(root_, data);
}

void AVLTree::remove(int data)
{
    remove(root_, data);
}

bool AVLTree::search(int data) const
{
    return search(root_, data);
}

AVLNode *AVLTree::findMin() const
{
    return findMin(root_);
}

AVLNode *AVLTree::findMax() const
{
    return findMax(root_);
}

// private function

int inline AVLTree::height(const Node&node) const
{
    return node ? node->height:-1;
}

void inline AVLTree::updateHeight(Node &node)
{
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

int inline AVLTree::balanceFactor(const Node &node) const
{
    return node ? height(node->left) - height(node->right):0;
}

void AVLTree::rightRotate(Node &node)
{
    Node child = std::move(node->left);
    node->left = std::move(child->right);
    child->right = std::move(node);
    updateHeight(child);
    updateHeight(child->right);
    node = std::move(child);
}

void AVLTree::leftRotate(Node &node)
{
    Node child = std::move(node->right);
    node->right = std::move(child->left);
    child->left = std::move(node);
    updateHeight(child);
    updateHeight(child->left);
    node = std::move(child);
}

void AVLTree::reBalance(Node &node)
{
    if (!node)
        return;

    updateHeight(node);

    int balance = balanceFactor(node);

    if (balance > 1)
    {
        if (balanceFactor(node->left) < 0)
        {
            leftRotate(node->left);
        }
        rightRotate(node);
    }
    else if (balance < -1)
    {
        if (balanceFactor(node->right) > 0)
        {
            rightRotate(node->right);
        }
        leftRotate(node);
    }
}

AVLNode *AVLTree::findMin(const Node &node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    AVLNode *cur = node.get();
    while (cur->left)
    {
        cur = cur->left.get();
    }
    return cur;
}

AVLNode *AVLTree::findMax(const Node &node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    AVLNode *cur = node.get();
    while (cur->right)
    {
        cur = cur->right.get();
    }
    return cur;
}

void AVLTree::insert(Node &node, int data)
{
    if (node == nullptr) {
        node = std::make_unique<AVLNode>(data);
        return;
    }
    if (data < node->data) {
        insert(node->left, data);
    } else if (data > node->data) {
        insert(node->right, data);
    }

    reBalance(node);
}

void AVLTree::remove(Node &node, int data)
{
    if (node == nullptr) {
        return;
    }
    if (data < node->data) {
        remove(node->left, data);
    } else if (data > node->data) {
        remove(node->right, data);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            node = std::move(node->left ? node->left : node->right);
        } else {
            AVLNode *minNode = findMin(node->right);
            node->data = minNode->data;
            remove(node->right, node->data);
        }
    }

    reBalance(node);
}

bool AVLTree::search(const Node &node, int data) const
{
    if (node == nullptr) {
        return false;
    }
    if (data < node->data) {
        return search(node->left, data);
    }
    else if (data > node->data) {
        return search(node->right, data);
    }

    return true;
}