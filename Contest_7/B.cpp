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

    // Понятно, что можно поиск макс сделать за O(1), если его как и глубину искать при
    // добавлении, но тут это уже совсем не круто.
    // Кроме того, куча конечно круто, да, но на семинарах мы обсуждали обычное BST,
    // поэтому писать тут кучу кажется не очень своевременно.
    T max() {
        Node *cur = root_;
        Node *second_max;

        if (cur->right != nullptr) {
            while (cur->right->right != nullptr) {
                cur = cur->right;
            }

            if (cur->right->left != nullptr) {
                cur = cur->right->left;
                while (cur->right != nullptr) {
                    cur = cur->right;
                }
                second_max = cur;
            } else {
                second_max = cur;
            }
        } else {
            cur = cur->left;
            while (cur->right != nullptr) {
                cur = cur->right;
            }
            second_max = cur;
        }

        return second_max->value;
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

    std::cout << tree.max();
    return 0;
}
