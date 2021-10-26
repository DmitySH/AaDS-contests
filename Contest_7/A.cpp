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
        if (value < cur->value) {
            if (!cur->left) {
                if (depth > depth_) {
                    depth_ = depth;
                }
                cur->left = new Node{value, nullptr, nullptr};
            } else {
                traverse(cur->left, value, depth);
            }
        } else if (value > cur->value) {
            if (!cur->right) {
                if (depth > depth_) {
                    depth_ = depth;
                }
                cur->right = new Node{value, nullptr, nullptr};
            } else {
                traverse(cur->right, value, depth);
            }
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

    std::cout << tree.getDepth();
    return 0;
}
