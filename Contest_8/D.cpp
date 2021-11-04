#include <iostream>

template <class ValueType>
class RBTree {
    struct Node {
    public:
        ValueType value;
        char color;
        Node *left;
        Node *right;
        Node *parent;

        ~Node() {
            delete right;
            delete left;
        }

        bool isBlack() {
            return color == 'B';
        }

        bool isRed() {
            return color == 'R';
        };
    };

private:
    Node *root_;
    int size_;
    Node *nil_;

    void traverse(Node *cur) {
        if (cur != nullptr) {
            traverse(cur->left);
            std::cout << cur->value << '\n';
            traverse(cur->right);
        }
    }

    void rotateLeft(Node *pivot) {
        Node *temp = pivot->right;
        pivot->right = temp->left;

        if (temp->left != nil_) {
            temp->left->parent = pivot;
        }

        change(pivot, temp);
        temp->left = pivot;
        pivot->parent = temp;
    }

    void rotateRight(Node *pivot) {
        Node *temp = pivot->left;
        pivot->left = temp->right;

        if (temp->right != nil_) {
            temp->right->parent = pivot;
        }

        change(pivot, temp);
        temp->right = pivot;
        pivot->parent = temp;
    }

    void change(Node *first, Node *second) {
        if (first->parent == nullptr) {
            root_ = second;
        } else if (first == first->parent->left) {
            first->parent->left = second;
        } else {
            first->parent->right = second;
        }
        second->parent = first->parent;
    }

    void rotateBigRight(Node *pivot) {
        rotateLeft(pivot->left);
        rotateRight(pivot);
    }

    void rotateBigLeft(Node *pivot) {
        rotateRight(pivot->right);
        rotateLeft(pivot);
    }

    void insertToEnd(Node *cur, ValueType value) {
        if (value < cur->value) {
            if (cur->left == nil_) {
                cur->left = new Node{value, 'R', nil_, nil_, cur};
                fixAfterInsert(cur->left);
                //                insertFix(cur->left);
                return;
            }
            insertToEnd(cur->left, value);
        } else if (value > cur->value) {
            if (cur->right == nil_) {
                cur->right = new Node{value, 'R', nil_, nil_, cur};
                fixAfterInsert(cur->right);
                //                insertFix(cur->right);
                return;
            }
            insertToEnd(cur->right, value);
        }
    }

    void insertFix(Node *k) {
        Node *u;
        while (k->parent->color == 'R') {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 'R') {
                    u->color = 'B';
                    k->parent->color = 'B';
                    k->parent->parent->color = 'R';
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(k);
                    }
                    k->parent->color = 'B';
                    k->parent->parent->color = 'R';
                    rotateLeft(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;

                if (u->color == 'R') {
                    u->color = 'B';
                    k->parent->color = 'B';
                    k->parent->parent->color = 'R';
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        rotateLeft(k);
                    }
                    k->parent->color = 'B';
                    k->parent->parent->color = 'R';
                    rotateRight(k->parent->parent);
                }
            }
            if (k == root_) {
                break;
            }
        }
        root_->color = 'B';
    }

    void fixAfterInsert(Node *new_node) {
        while (new_node != root_ && new_node->parent->isRed()) {
            Node *parent = new_node->parent;
            Node *grand_parent = parent->parent;
            if (parent == grand_parent->right) {
                if (grand_parent->left->isRed()) {
                    grand_parent->left->color = 'B';
                    parent->color = 'B';
                    grand_parent->color = 'R';
                    new_node = grand_parent;
                } else {
                    if (new_node == parent->left) {
                        new_node = parent;
                        rotateRight(new_node);
                    }
                    new_node->parent->color = 'B';
                    new_node->parent->parent->color = 'R';
                    rotateLeft(new_node->parent->parent);
                }
            } else {
                if (grand_parent->right->isRed()) {
                    grand_parent->right->color = 'B';
                    parent->color = 'B';
                    grand_parent->color = 'R';
                    new_node = grand_parent;
                } else {
                    if (new_node == parent->right) {
                        new_node = parent;
                        rotateLeft(new_node);
                    }
                    new_node->parent->color = 'B';
                    new_node->parent->parent->color = 'R';
                    rotateRight(new_node->parent->parent);
                }
            }
        }
        root_->color = 'B';
    }

    void fixAfterErase(Node *new_node) {  // TODO
        while (new_node->isBlack() && new_node != root_) {
        }
    }

    Node *findByValue(Node *cur, ValueType value) {
        if (!cur) {
            return nullptr;
        }

        if (value == cur->value) {
            return cur;
        }

        if (value < cur->value) {
            return findByValue(cur->left, value);
        } else {
            return findByValue(cur->right, value);
        }
    }

    Node *subMin(Node *node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node *subMax(Node *node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

public:
    //    void insert(ValueType key) {
    //        Node *node = new Node;
    //        node->parent = nullptr;
    //        node->value = key;
    //        node->left = nil_;
    //        node->right = nil_;
    //        node->color = 'R';
    //
    //        Node *y = nullptr;
    //        Node *x = this->root_;
    //
    //        while (x != nil_) {
    //            y = x;
    //            if (node->value < x->value) {
    //                x = x->left;
    //            } else {
    //                x = x->right;
    //            }
    //        }
    //
    //        node->parent = y;
    //        if (y == nullptr) {
    //            root_ = node;
    //        } else if (node->value < y->value) {
    //            y->left = node;
    //        } else {
    //            y->right = node;
    //        }
    //
    //        if (node->parent == nullptr) {
    //            node->color = 'B';
    //            return;
    //        }
    //
    //        if (node->parent->parent == nullptr) {
    //            return;
    //        }
    //
    //        insertFix(node);
    //    }

    RBTree() {
        size_ = 0;
        nil_ = new Node{0, 'B', nullptr, nullptr, nullptr};
        root_ = nil_;
    }

    ~RBTree() {
        delete root_;
    }

    void bypass() {
        traverse(root_);
    }

    bool isEmpty() {
        return root_ == nullptr;
    }

    int getSize() {
        return size_;
    }

    void printTree() {
        if (root_) {
            printHelper(this->root_, "", true);
        }
    }

    void printHelper(Node *root, std::string indent, bool last) {
        if (root != nil_) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "   ";
            } else {
                std::cout << "L----";
                indent += "|  ";
            }

            std::string s_color = root->color == 'R' ? "RED" : "BLACK";
            std::cout << root->value << "(" << s_color << ")" << std ::endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }
    void erase(ValueType value) {
        Node *excluded = findByValue(root_, value);
        char color = excluded->color;

        Node *temp;
        if (!excluded->left) {
            temp = excluded->right;
            change(excluded, temp);
        } else if (!excluded->right) {
            temp = excluded->left;
            change(excluded, temp);
        } else {
            Node *sub_min = subMin(excluded);
            color = sub_min->color;
            temp = sub_min->right;
            if (sub_min == excluded->right || sub_min == excluded->left) {
                temp->parent = sub_min;
            } else {
                change(sub_min, sub_min->right);
            }
            change(excluded, sub_min);
            sub_min->color = color;
        }
        if (color == 'B') {
            fixAfterInsert(temp);
        }
    }

    void insert(ValueType value) {
        ++size_;
        if (root_ == nil_) {
            root_ = new Node{value, 'B', nil_, nil_, nullptr};
        } else {
            insertToEnd(root_, value);
        }
    }
};

void input(RBTree<int> *tree) {
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

    RBTree<int> tree;
    input(&tree);
    //    tree.bypass();
    //    tree.erase(38);
    tree.printTree();
    return 0;
}
