#include <iostream>

template <typename T>
class BinarySearchTree {
    struct Node {
    public:
        T value;
        Node *right;
        Node *left;

        ~Node() {
            delete right;
            delete left;
        }
    };

private:
    Node *root_;
    int size_;
    int depth_;

    void insertValue(Node *cur, T value, int depth) {
        ++depth;
        if (value < cur->value) {
            if (!cur->left) {
                if (depth > depth_) {
                    depth_ = depth;
                }
                cur->left = new Node{value, nullptr, nullptr};
            } else {
                insertValue(cur->left, value, depth);
            }
        } else if (value > cur->value) {
            if (!cur->right) {
                if (depth > depth_) {
                    depth_ = depth;
                }
                cur->right = new Node{value, nullptr, nullptr};
            } else {
                insertValue(cur->right, value, depth);
            }
        }
    }

    void traverse(Node *cur) {
        if (cur != nullptr) {
            traverse(cur->left);
            if (cur->right == nullptr && cur->left == nullptr) {
                std::cout << cur->value << '\n';
            }
            traverse(cur->right);
        }
    }

public:
    BinarySearchTree() {
        size_ = 0;
        depth_ = 0;
        root_ = nullptr;
    }

    ~BinarySearchTree() {
        delete root_;
    }

    int getDepth() {
        return depth_;
    }

    int getSize() {
        return size_;
    }

    void bypass() {
        traverse(root_);
    }

    void insert(T value) {
        ++size_;
        if (!root_) {
            ++depth_;
            root_ = new Node{value, nullptr, nullptr};
        } else {
            insertValue(root_, value, 1);
        }
    }
};

void input(BinarySearchTree<int> *tree) {
    int inp;
    std::cin >> inp;
    while (inp != 0) {
        tree->insert(inp);
        std::cin >> inp;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BinarySearchTree<int> tree;
    input(&tree);

    tree.bypass();
    return 0;
}
