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
            return !isBlack();
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
                return;
            }
            insertToEnd(cur->left, value);
        } else if (value > cur->value) {
            if (cur->right == nil_) {
                cur->right = new Node{value, 'R', nil_, nil_, cur};
                fixAfterInsert(cur->right);
                return;
            }
            insertToEnd(cur->right, value);
        }
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

    void fixAfterErase(Node *new_node) {
        while (new_node != root_ && new_node->isBlack()) {
            Node *parent = new_node->parent;
            if (new_node == parent->left) {
                //                s = x->parent->right;
                if (parent->right->isRed()) {
                    parent->right->color = 'B';
                    parent->color = 'R';
                    rotateLeft(new_node->parent);
                    //                    s = x->parent->right;
                    parent = new_node->parent;
                }

                if (parent->right->left->isBlack() && (parent->right->right->isBlack())) {
                    parent->right->color = 'R';
                    new_node = new_node->parent;
                } else {
                    if (parent->right->right->isBlack()) {
                        parent->right->left->color = 'B';
                        parent->right->color = 'R';
                        rotateRight(parent->right);
                        //                        s = x->parent->right;
                        parent = new_node->parent;
                    }

                    parent->right->color = parent->color;
                    parent->color = 'B';
                    parent->right->right->color = 'B';
                    rotateLeft(new_node->parent);
                    new_node = root_;
                }
            } else {
                //                s = x->parent->left;
                if (parent->left->isRed()) {
                    parent->left->color = 'B';
                    parent->color = 'R';
                    rotateRight(new_node->parent);
                    //                    s = x->parent->left;
                    parent = new_node->parent;
                }

                if (parent->left->right->isBlack() && parent->left->right->isBlack()) {
                    parent->left->color = 'R';
                    new_node = parent;
                } else {
                    if (parent->left->left->isBlack()) {
                        parent->left->right->color = 'B';
                        parent->left->color = 'R';
                        rotateLeft(parent->left);
                        //                        s = x->parent->left;
                        parent = new_node->parent;
                    }

                    parent->left->color = parent->color;
                    parent->color = 'B';
                    parent->left->left->color = 'B';
                    rotateRight(new_node->parent);
                    new_node = root_;
                }
            }
        }
        new_node->color = 'B';
    }

    Node *findByValue(Node *cur, ValueType value) {
        while (cur != nil_) {
            if (cur->value == value) {
                return cur;
            }
            if (value >= cur->value) {
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }
        return nil_;
    }

    Node *subMin(Node *node) {
        while (node->left != nil_) {
            node = node->left;
        }
        return node;
    }

    Node *subMax(Node *node) {
        while (node->right != nil_) {
            node = node->right;
        }
        return node;
    }

public:
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
        return root_ == nil_;
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
        //        std::cout << excluded->value << "Fdsfsdf \n";
        if (excluded == nil_) {
            std::cout << "NO no no";
            return;
        }

        Node *temp = excluded;
        char color = excluded->color;

        Node *sub;

        if (excluded->left == nil_) {
            sub = excluded->right;
            change(excluded, excluded->right);
        } else if (excluded->right == nil_) {
            sub = excluded->left;
            change(excluded, excluded->left);
        } else {
            temp = subMin(excluded->right);
            color = temp->color;
            sub = temp->right;
            if (temp->parent == excluded) {
                sub->parent = temp;
            } else {
                change(temp, temp->right);
                temp->right = excluded->right;
                temp->right->parent = temp;
            }

            change(excluded, temp);
            temp->left = excluded->left;
            temp->left->parent = temp;
            temp->color = excluded->color;
        }
        //        delete z;
        if (color == 'B') {
            fixAfterErase(sub);
        }
        //        Node *temp;
        //        if (!excluded->left) {
        //            temp = excluded->right;
        //            change(excluded, temp);
        //        } else if (!excluded->right) {
        //            temp = excluded->left;
        //            change(excluded, temp);
        //        } else {
        //            Node *sub_min = subMin(excluded);
        //            color = sub_min->color;
        //            temp = sub_min->right;
        //            if (sub_min == excluded->right || sub_min == excluded->left) {
        //                temp->parent = sub_min;
        //            } else {
        //                change(sub_min, sub_min->right);
        //            }
        //            change(excluded, sub_min);
        //            sub_min->color = color;
        //        }
    }

    void insert(ValueType value) {
        ++size_;
        if (root_ == nil_) {
            root_ = new Node{value, 'B', nil_, nil_, nullptr};
        } else {
            insertToEnd(root_, value);
        }
    }

    void deleteNodeHelper(Node *node, ValueType key) {
        Node *z = nil_;
        Node *x, *y;
        while (node != nil_) {
            if (node->value == key) {
                z = node;
            }

            if (node->value <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == nil_) {
            std::cout << "Key not found in the tree" << std::endl;
            return;
        }

        y = z;
        char y_original_color = y->color;
        if (z->left == nil_) {
            x = z->right;
            change(z, z->right);
        } else if (z->right == nil_) {
            x = z->left;
            change(z, z->left);
        } else {
            y = subMin(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                change(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            change(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        //        delete z;
        if (y_original_color == 'B') {
            fixAfterErase(x);
        }
    }

    //    void deleteFix(Node* x) {
    //        Node* s;
    //        while (x != root_ && x->color == 'B') {
    //            if (x == x->parent->left) {
    //                s = x->parent->right;
    //                if (s->color == 'R') {
    //                    s->color = 'B';
    //                    x->parent->color = 'R';
    //                    rotateLeft(x->parent);
    //                    s = x->parent->right;
    //                }
    //
    //                if (s->left->color == 'B' && s->right->color == 'B') {
    //                    s->color = 'R';
    //                    x = x->parent;
    //                } else {
    //                    if (s->right->color == 'B') {
    //                        s->left->color = 'B';
    //                        s->color = 'R';
    //                        rotateRight(s);
    //                        s = x->parent->right;
    //                    }
    //
    //                    s->color = x->parent->color;
    //                    x->parent->color = 'B';
    //                    s->right->color = 'B';
    //                    rotateLeft(x->parent);
    //                    x = root_;
    //                }
    //            } else {
    //                s = x->parent->left;
    //                if (s->color == 'R') {
    //                    s->color = 'B';
    //                    x->parent->color = 'R';
    //                    rotateRight(x->parent);
    //                    s = x->parent->left;
    //                }
    //
    //                if (s->right->color == 'B' && s->right->color == 'B') {
    //                    s->color = 'R';
    //                    x = x->parent;
    //                } else {
    //                    if (s->left->color == 'B') {
    //                        s->right->color = 'B';
    //                        s->color = 'R';
    //                        rotateLeft(s);
    //                        s = x->parent->left;
    //                    }
    //
    //                    s->color = x->parent->color;
    //                    x->parent->color = 'B';
    //                    s->left->color = 'B';
    //                    rotateRight(x->parent);
    //                    x = root_;
    //                }
    //            }
    //        }
    //        x->color = 'B';
    //    }

    void deleteNode(ValueType data) {
        deleteNodeHelper(this->root_, data);
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

void eraser(RBTree<int> *tree) {
    int inp;
    std::cin >> inp;
    while (inp != 0) {
        tree->erase(inp);
        tree->printTree();
        std::cin >> inp;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    RBTree<int> tree;
    input(&tree);
    tree.printTree();

    //    tree.bypass();
    //    tree.erase(38);
    eraser(&tree);
    tree.printTree();
    return 0;
}
