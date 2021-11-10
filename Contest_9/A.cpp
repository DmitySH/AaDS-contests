#include <iostream>
#include <string>

template <typename T>
class BinarySearchTree {
    struct Pair {
        T max, min;
    };

    struct Node {
    public:
        T value;
        Node *right;
        Node *left;
        char color;
        int left_number, right_number;

        ~Node() {
            delete right;
            delete left;
        }

        Node(T value, char color, int left_num, int right_num) {
            this->color = color;
            this->value = value;
            this->left_number = left_num;
            this->right_number = right_num;
        }
    };

private:
    Node *root_;
    bool is_rb_;
    int blacks_;
    Node **node_array_;

    int myMax(int num_left, int num_right) {
        if (num_left > num_right) {
            return num_left;
        } else {
            return num_right;
        }
    }
    int myMin(int num_left, int num_right) {
        if (num_left > num_right) {
            return num_right;
        } else {
            return num_left;
        }
    }

    void createTree(Node *cur) {
        if (cur) {
            if (cur->right_number == -1) {
                cur->right = nullptr;
            } else {
                cur->right = node_array_[cur->right_number];
            }

            if (cur->left_number == -1) {
                cur->left = nullptr;
            } else {
                cur->left = node_array_[cur->left_number];
            }
            createTree(cur->right);
            createTree(cur->left);
        }
    }

    Pair checkRB(Node *cur, int black_before) {
        if (cur != nullptr) {
            if (cur->color == 'B') {
                ++black_before;
            }

            Pair values_left = checkRB(cur->left, black_before);
            Pair values_right = checkRB(cur->right, black_before);

            if (cur->right != nullptr) {
                if (values_right.min <= cur->value ||
                    cur->right->color == 'R' && cur->color != 'B') {
                    is_rb_ = false;
                }
            }

            if (cur->color != 'R' && cur->color != 'B') {
                is_rb_ = false;
            }

            if (cur->left != nullptr) {
                if (values_left.max >= cur->value || cur->left->color == 'R' && cur->color != 'B') {
                    is_rb_ = false;
                }
            }

            return Pair{myMax(myMax(values_right.max, cur->value), values_left.max),
                        myMin(myMin(values_right.min, cur->value), values_left.min)};

        } else {
            if (blacks_ == 0) {
                blacks_ = black_before;
            } else if (blacks_ != black_before) {
                is_rb_ = false;
            }
            return Pair{INT32_MIN, INT32_MAX};
        }
    }

public:
    BinarySearchTree() {
        root_ = nullptr;
        is_rb_ = true;
        blacks_ = 0;
    }

    ~BinarySearchTree() {
        delete root_;
        delete[] node_array_;
    }

    bool isRBtree() {
        is_rb_ = true;
        if (root_->color != 'B') {
            return false;
        }
        blacks_ = 0;
        checkRB(root_, blacks_);
        return is_rb_;
    }

    void traverse(Node *cur) {
        if (cur != nullptr) {
            traverse(cur->left);
            std::cout << cur->value << '\n';
            traverse(cur->right);
        }
    }

    void bypass() {
        traverse(root_);
    }

    void createFromInput(int number_of_nodes) {
        int root;
        std::cin >> root;
        node_array_ = new Node *[number_of_nodes];
        --root;

        for (int i = 0; i < number_of_nodes; ++i) {
            node_array_[i] = nullptr;
        }

        for (int i = 0; i < number_of_nodes; ++i) {
            int number;
            T key;
            std::string left, right;
            char color;
            std::cin >> number >> key >> left >> right >> color;

            int left_number = left == "null" ? -1 : std::stoi(left) - 1;
            int right_number = right == "null" ? -1 : std::stoi(right) - 1;

            node_array_[number - 1] = new Node(key, color, left_number, right_number);
        }
        createTree(node_array_[root]);
        root_ = node_array_[root];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_nodes;
    std::cin >> number_of_nodes;
    if (number_of_nodes == 0) {
        std::cout << "YES";
        return 0;
    }
    BinarySearchTree<int> tree;
    tree.createFromInput(number_of_nodes);
    if (tree.isRBtree()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}
