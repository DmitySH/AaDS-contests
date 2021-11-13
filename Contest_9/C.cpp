#include <iostream>

struct Node {
public:
    int key;
    Node *left;
    Node *right;
    Node *parent;
    int height;

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
            root_ = new Node{value, nullptr, nullptr, nullptr, 0};
            return;
        }

        Node *cur = root_;
        while (cur) {
            if (cur->key < value) {
                if (!cur->right) {
                    cur->right = new Node{value, nullptr, nullptr, cur, 0};
                    reDepth(cur);
                    return;
                }
                cur = cur->right;
            } else if (value < cur->key) {
                if (!cur->left) {
                    cur->left = new Node{value, nullptr, nullptr, cur, 0};
                    reDepth(cur);
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
        return root_->height;
    }

private:
    Node *root_;

    void zag(Node *pivot) {
        Node *temp = pivot->right;
        pivot->right = temp->left;

        if (temp->left) {
            temp->left->parent = pivot;
        }

        change(pivot, temp);
        temp->left = pivot;
        pivot->parent = temp;

        depth(pivot);
        depth(temp);
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

        depth(pivot);
        depth(temp);
    }

    void depth(Node *cur) {
        if (!cur->left && !cur->right) {
            cur->height = 0;
            return;
        }
        if (!cur->left) {
            cur->height = cur->right->height + 1;
            return;
        }
        if (!cur->right) {
            cur->height = cur->left->height + 1;
            return;
        }
        if (cur->left->height > cur->right->height) {
            cur->height = cur->left->height + 1;
        } else {
            cur->height = cur->right->height + 1;
        }
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

    void reDepth(Node *cur) {
        while (cur) {
            depth(cur);
            cur = cur->parent;
        }
    }
};
