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
    bool balanced_;

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

    int traverse(Node *cur) {
        if (cur != nullptr) {
            int left = traverse(cur->left);
            int right = traverse(cur->right);
            if (right - left > 1 || left - right > 1) {
                balanced_ = false;
            }
            if (left < right) {
                return right + 1;
            } else {
                return left + 1;
            }
        } else {
            return 0;
        }
    }

public:
    BinarySearchTree() {
        size_ = 0;
        root_ = nullptr;
        balanced_ = true;
        depth_ = 0;
    }

    ~BinarySearchTree() {
        delete root_;
    }

    bool isBalanced() {
        balanced_ = true;
        traverse(root_);
        return balanced_;
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

    if (tree.isBalanced()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}
