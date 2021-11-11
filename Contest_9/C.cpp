#include <iostream>

struct Node {
public:
    int key;
    Node *left;
    Node *right;
    Node *parent;

    ~Node() {
        delete right;
        delete left;
    }

    bool leftChild() {
        return this == this->parent->left;
    }

    bool rightChild() {
        return this == this->parent->right;
    }
};

class SplayTree {
public:
    SplayTree() {
        root_ = nullptr;
    }

    ~SplayTree() {
        delete root_;
    }

    void insert(int value) {
        if (!root_) {
            root_ = new Node{value, nullptr, nullptr, nullptr};
            return;
        }

        Node *cur = root_;
        while (cur) {
            if (cur->key < value) {
                if (!cur->right) {
                    cur->right = new Node{value, nullptr, nullptr, cur};
                    return;
                }
                cur = cur->right;
            } else if (value < cur->key) {
                if (!cur->left) {
                    cur->left = new Node{value, nullptr, nullptr, cur};
                    return;
                }
                cur = cur->left;
            } else {
                return;
            }
        }
    }

    Node *find(int value) const {
        Node *cur = root_;
        while (cur) {
            if (cur->key < value) {
                cur = cur->right;
            } else if (value < cur->key) {
                cur = cur->left;
            } else {
                return cur;
            }
        }

        return nullptr;
    }

    int splay(Node *node) {
        int rotates = 0;
        while (node != root_) {
            Node *parent = node->parent;

            if (!parent->parent) {
                ++rotates;
                if (node->leftChild()) {
                    zig(parent);
                } else {
                    zag(parent);
                }
            } else {
                ++rotates;
                if (node->leftChild() && parent->leftChild()) {
                    zig(parent->parent);
                    zig(parent);
                    ++rotates;
                } else if (node->rightChild() && parent->rightChild()) {
                    zag(parent->parent);
                    zag(parent);
                    ++rotates;
                } else if (node->rightChild() && parent->leftChild()) {
                    zag(parent);
                    zig(node->parent);
                } else {
                    zig(parent);
                    zag(node->parent);
                }
            }
        }

        return rotates;
    }

    int getHeight() const {
        int depth = traverse(root_) - 1;
        return depth < 0 ? 0 : depth;
    }

private:
    Node *root_;

    int traverse(Node *cur) const {
        int left;
        int right;
        int height = 0;

        if (cur) {
            left = traverse(cur->left);
            right = traverse(cur->right);
            height = ((left > right) ? left : right) + 1;
        }

        return height;
    }

    void zag(Node *pivot) {
        Node *temp = pivot->right;
        pivot->right = temp->left;

        if (temp->left) {
            temp->left->parent = pivot;
        }

        change(pivot, temp);
        temp->left = pivot;
        pivot->parent = temp;
    }

    void zig(Node *pivot) {
        Node *temp = pivot->left;
        pivot->left = temp->right;

        if (temp->right) {
            temp->right->parent = pivot;
        }

        change(pivot, temp);
        temp->right = pivot;
        pivot->parent = temp;
    }

    void change(Node *first, Node *second) {
        if (!first->parent) {
            root_ = second;
        } else if (first == first->parent->left) {
            first->parent->left = second;
        } else {
            first->parent->right = second;
        }
        second->parent = first->parent;
    }
};
