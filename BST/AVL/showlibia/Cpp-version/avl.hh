#include <memory>
struct AVLNode {
  int data;
  int height;
  std::unique_ptr<AVLNode> left;
  std::unique_ptr<AVLNode> right;

  AVLNode(int data) : data(data), height(0), left(nullptr), right(nullptr) {}
};

using Node = std::unique_ptr<AVLNode>;

class AVLTree {
private:
  Node root_;
  int height(const Node &node) const;
  void updateHeight(Node &node);
  int balanceFactor(const Node &node) const;

  void rightRotate(Node &node);
  void leftRotate(Node &node);
  void reBalance(Node &node);

  void insert(Node &node, int data);
  void remove(Node &node, int data);
  bool search(const Node &node, int data) const;
  AVLNode *findMin(const Node &node) const;
  AVLNode *findMax(const Node &node) const;

public:
  AVLTree() = default;
  ~AVLTree() = default;
  
  AVLNode *findMin() const;
  AVLNode *findMax() const;
  void insert(int data);
  void remove(int data);
  bool search(int data) const;
};
