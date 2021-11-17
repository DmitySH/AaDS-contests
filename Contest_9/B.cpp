#include <iostream>

struct Node {
    int *values;
    int step;
    Node **children;
    int size;
    bool leaf;
    Node *right;
    Node *parent;

    Node(int value, int step, bool leaf) : Node(step, leaf) {
        size = 1;
        values[0] = value;
    }

    ~Node() {
        for (int i = 0; i <= size; ++i) {
            delete children[i];
        }
        delete[] values;
        delete[] children;
    }

    Node(int step, bool leaf) {
        size = 0;
        this->step = step;
        this->leaf = leaf;
        values = new int[2 * step - 1];
        children = new Node *[2 * step];

        for (int i = 0; i < 2 * step; ++i) {
            children[i] = nullptr;
        }

        right = nullptr;
    }

    bool full() {
        return size == 2 * step - 1;
    }

    bool contains(int value) {
        for (int i = 0; i < 2 * step - 1; ++i) {
            if (values[i] == value) {
                return true;
            }
        }

        return false;
    }
};

class BPlusTree {
public:
    explicit BPlusTree(int step) {
        t_ = step;
        root_ = nullptr;
    }

    ~BPlusTree() {
        delete root_;
    }

    void insert(int value) {
        Node *cur;
        if (!root_) {
            root_ = new Node(value, t_, true);
        } else {
            cur = findLeaf(value, root_);

            if (cur->full()) {
                split(cur);
            }

            cur = findLeaf(value, root_);

            if (cur->contains(value)) {
                return;
            }

            int index = 0;
            while (index < cur->size && cur->values[index] < value) {
                ++index;
            }

            for (int i = cur->size; i > index; --i) {
                cur->values[i] = cur->values[i - 1];
            }
            cur->values[index] = value;
            ++cur->size;
        }
    }
    Node *findLeaf(int value, Node *cur) const {
        while (!cur->leaf) {
            int index = 0;
            while (index < cur->size && cur->values[index] < value) {
                ++index;
            }

            cur = cur->children[index];
        }
        return cur;
    }

    void printLeaves() const {
        Node *cur = root_;
        while (!cur->leaf) {
            cur = cur->children[0];
        }
        while (cur) {
            for (int i = 0; i < cur->size; ++i) {
                std::cout << cur->values[i] << ' ';
            }
            cur = cur->right;
            std::cout << '\n';
        }
    }

private:
    int t_;
    Node *root_;

    void split(Node *cur) {
        Node *right = new Node(t_, false);

        right->right = cur->right;
        cur->right = right;

        int mid = cur->values[t_ - 1];
        right->size = t_ - 1;
        cur->size = t_ - 1;

        for (int i = 0; i < t_ - 1; ++i) {
            right->values[i] = cur->values[i + t_];
            right->children[i] = cur->children[i + t_];
            if (right->children[i]) {
                right->children[i]->parent = right;
            }
        }

        right->children[t_ - 1] = cur->children[2 * t_ - 1];
        if (right->children[t_ - 1]) {
            right->children[t_ - 1]->parent = right;
        }

        if (cur->leaf) {
            right->leaf = true;

            for (int i = right->size; i > 0; --i) {
                right->values[i] = right->values[i - 1];
            }

            right->values[0] = mid;
            ++right->size;
        }

        if (cur == root_) {
            newRoot(cur, right, mid);
        } else {
            right->parent = cur->parent;

            int index = 0;
            while (index < cur->parent->size && cur->parent->values[index] < mid) {
                ++index;
            }

            cur->parent->children[cur->parent->size + 1] = cur->parent->children[cur->parent->size];
            for (int i = cur->parent->size; i > index; --i) {
                cur->parent->values[i] = cur->parent->values[i - 1];
                cur->parent->children[i] = cur->parent->children[i - 1];
            }
            cur->parent->values[index] = mid;
            ++cur->parent->size;
            cur->parent->children[index] = cur;
            cur->parent->children[index + 1] = right;

            if (cur->parent->full()) {
                split(cur->parent);
            }
        }
    }

    void newRoot(Node *cur, Node *right, int mid) {
        root_ = new Node(mid, t_, false);
        root_->children[0] = cur;
        root_->children[1] = right;

        cur->parent = root_;
        right->parent = root_;
    }
};
