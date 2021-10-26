#include <iostream>
#include <string>

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

    void traverse(Node *cur, T value, int depth) {
        ++depth;
        if (value == cur->value) {
            return;
        }
        if (value < cur->value) {
            if (!cur->left) {
                cur->left = new Node{value, nullptr, nullptr};
            } else {
                traverse(cur->left, value, depth);
            }
        } else {
            if (!cur->right) {
                cur->right = new Node{value, nullptr, nullptr};
            } else {
                traverse(cur->right, value, depth);
            }
        }

        if (depth > depth_) {
            depth_ = depth;
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

    T max() {
        Node *cur = root_;
        while (cur->right != nullptr && cur->right->right != nullptr) {
            cur = cur->right;
        }
        Node *max = cur->right == nullptr ? cur : cur->right;
        if (max->left != nullptr) {
            cur = max->left;
            while (cur->right != nullptr) {
                cur = cur->right;
            }
            return cur->value;
        } else {
            if (cur->left != nullptr) {
                cur = cur->left;
            }
            while (cur->right != nullptr) {
                cur = cur->right;
            }
            return cur->value;
        }
    }

    void insert(T value) {
        ++size_;
        if (!root_) {
            ++depth_;
            root_ = new Node{value, nullptr, nullptr};
        } else {
            traverse(root_, value, 1);
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

    std::cout << tree.max();
    return 0;
}
