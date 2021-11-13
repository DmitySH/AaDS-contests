#include <iostream>

struct Node {
    int *values;
    int step;
    Node **children;
    int size;
    bool leaf;
    int fact_size;

    Node(int value, int step, bool leaf) : Node(step, leaf) {
        size = 1;
        values[0] = value;
    }

    ~Node() {
        for (int i = 0; i < fact_size; ++i) {
            delete children[i];
        }
        delete[] values;
        delete[] children;
    }

    Node(int step, bool leaf) {
        fact_size = 0;
        size = 0;
        this->step = step;
        this->leaf = leaf;
        values = new int[2 * step - 1];
        children = new Node *[2 * step];

        for (int i = 0; i < 2 * step; ++i) {
            children[i] = nullptr;
        }
    }

    bool full() {
        return size == 2 * step - 1;
    }

    int64_t summer() const {
        int counter;
        int64_t sum = 0;
        for (counter = 0; counter < size; ++counter) {
            if (!leaf) {
                sum += children[counter]->summer();
            } else {
                sum += values[counter];
            }
        }
        if (!leaf) {
            sum += children[counter]->summer();
        }

        return sum;
    }
};

class BTree {
public:
    explicit BTree(int step) {
        size_ = 0;
        root_ = nullptr;
        t_ = step;
    }

    ~BTree() {
        delete root_;
    }

    void insert(int value) {
        if (!root_) {
            ++size_;
            root_ = new Node(value, t_, true);
        } else {
            if (search(root_, value)) {
                return;
            }
            if (root_->full()) {
                ++size_;
                Node *upper_node = new Node(t_, false);
                upper_node->children[0] = root_;

                split(upper_node, root_, 0);

                ++upper_node->fact_size;

                int index = upper_node->values[0] < value ? 1 : 0;

                deepInsert(upper_node->children[index], value);
                root_ = upper_node;
            } else {
                deepInsert(root_, value);
            }
        }
    }

    size_t size() const {
        return size_;
    }

    int64_t sum() const {
        if (root_) {
            return root_->summer();
        }
        return 0;
    }

private:
    int t_;
    size_t size_;
    Node *root_;

    bool search(Node *node, int value) {
        int index;
        if (!node) {
            return false;
        }
        for (index = 0; index < node->size; ++index) {
            if (value < node->values[index]) {
                break;
            }
            if (value == node->values[index]) {
                return true;
            }
        }
        if (node->leaf) {
            return false;
        } else {
            return search(node->children[index], value);
        }
    }

    void deepInsert(Node *node, int value) {
        int counter = node->size - 1;

        if (!node->leaf) {
            while (counter >= 0 && value < node->values[counter]) {
                --counter;
            }
            ++counter;

            Node *tmp = node->children[counter];
            if (tmp->full()) {
                split(node, tmp, counter);
                if (node->values[counter] < value) {
                    ++counter;
                }
            }
            deepInsert(node->children[counter], value);
        } else {
            for (counter = node->size - 1; counter >= 0; --counter) {
                if (value > node->values[counter]) {
                    break;
                }
                node->values[counter + 1] = node->values[counter];
            }
            node->values[counter + 1] = value;
            ++node->size;
        }
    }

    void split(Node *parent, Node *child, int child_index) {
        ++size_;

        Node *right = new Node(child->step, child->leaf);

        int step = parent->step;
        right->size = step - 1;
        child->size = step - 1;

        right->fact_size = step;
        child->fact_size = step;
        ++parent->fact_size;

        for (int j = 0; j < parent->step - 1; ++j) {
            right->values[j] = child->values[j + parent->step];
        }

        if (!child->leaf) {
            for (int j = 0; j < parent->step; ++j) {
                right->children[j] = child->children[j + parent->step];
            }
        }

        for (int j = parent->size; j >= child_index + 1; --j) {
            parent->children[j + 1] = parent->children[j];
        }

        parent->children[child_index + 1] = right;

        for (int j = parent->size - 1; j >= child_index; --j) {
            parent->values[j + 1] = parent->values[j];
        }

        parent->values[child_index] = child->values[parent->step - 1];
        parent->size++;
    }
};
