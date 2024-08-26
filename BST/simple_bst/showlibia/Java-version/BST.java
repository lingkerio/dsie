package bst;

class BSTNode implements Comparable {
    Integer data;
    BSTNode left;
    BSTNode right;

    public BSTNode() {
    }

    public BSTNode(BSTNode right, BSTNode left, Integer data) {
        this.right = right;
        this.left = left;
        this.data = data;
    }

    @Override
    public int compareTo(Object o) {
        return this.data - (Integer) o;
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

        int compare = node.compareTo(data);
        if (compare < 0) {
            return contains(node.left, data);
        } else if (compare > 0) {
            return contains(node.right, data);
        }
        return true;
    }

    public BSTNode findMin(){
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

    public BSTNode findMax(){
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

    public void insert(Integer data){
        root = insert(root, data);
    }

    private BSTNode insert(BSTNode node, Integer data) {
        if (node == null) {
            return new BSTNode(null,null, data);
        }

        int compare = node.compareTo(data);
        if (compare < 0 ) {
            insert(node.left, data);
        } else if (compare > 0) {
            insert(node.right, data);
        }

        return node;
    }

    public void remove(Integer data){
        root = remove(root, data);
    }

    private BSTNode remove(BSTNode node, Integer data) {
        if (node == null) {
            return null;
        }

        int compare = node.compareTo(data);
        if (compare < 0 ) {
            return remove(node.left, data);
        } else if (compare > 0) {
            return remove(node.right, data);
        } else {
            if (node.left != null && node.right != null){
                node.data = findMin(node.right).data;
                node.right = remove(node.right, node.data);
            } else {
                node = (node.left != null) ? node.left : node.right;
            }

        }
        return node;
    }
}
