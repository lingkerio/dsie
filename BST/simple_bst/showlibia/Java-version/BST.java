package bst;

class BSTNode implements Comparable<BSTNode> {
    Integer data;
    BSTNode left;
    BSTNode right;

    public BSTNode() {
    }

    public BSTNode(BSTNode left, BSTNode right, Integer data) {
        this.left = left;
        this.right = right;
        this.data = data;
    }

    @Override
    public int compareTo(BSTNode other) {
        return this.data.compareTo(other.data);
    }
}

public class BST {
    private BSTNode root;

    public BST() {
        this.root = null;
    }

    public void makeEmpty() {
        this.root = null;
    }

    public boolean isEmpty() {
        return this.root == null;
    }

    public boolean contains(Integer x) {
        return contains(root, x);
    }

    private boolean contains(BSTNode node, Integer data) {
        if (node == null) {
            return false;
        }

        int compare = data.compareTo(node.data);
        if (compare < 0) {
            return contains(node.left, data);
        } else if (compare > 0) {
            return contains(node.right, data);
        }
        return true;
    }

    public BSTNode findMin() {
        return findMin(root);
    }

    private BSTNode findMin(BSTNode node) {
        if (node == null) {
            return null;
        }
        BSTNode cur = node;
        while (cur.left != null) {
            cur = cur.left;
        }
        return cur;
    }

    public BSTNode findMax() {
        return findMax(root);
    }

    private BSTNode findMax(BSTNode node) {
        if (node == null) {
            return null;
        }
        BSTNode cur = node;
        while (cur.right != null) {
            cur = cur.right;
        }
        return cur;
    }

    public void insert(Integer data) {
        root = insert(root, data);
    }

    private BSTNode insert(BSTNode node, Integer data) {
        if (node == null) {
            return new BSTNode(null, null, data);
        }

        int compare = data.compareTo(node.data);
        if (compare < 0) {
            node.left = insert(node.left, data);
        } else if (compare > 0) {
            node.right = insert(node.right, data);
        }

        return node;
    }

    public void remove(Integer data) {
        root = remove(root, data);
    }

    private BSTNode remove(BSTNode node, Integer data) {
        if (node == null) {
            return null;
        }

        int compare = data.compareTo(node.data);
        if (compare < 0) {
            node.left = remove(node.left, data);
        } else if (compare > 0) {
            node.right = remove(node.right, data);
        } else {
            if (node.left != null && node.right != null) {
                BSTNode minNode = findMin(node.right);
                node.data = minNode.data;
                node.right = remove(node.right, minNode.data);
            } else {
                node = (node.left != null) ? node.left : node.right;
            }
        }
        return node;
    }
}
