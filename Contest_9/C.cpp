struct Node {
public:
    int key;
    Node *left;
    Node *right;
    Node *parent;

    ~Node() {
        delete right;
        delete left;
    }

private:
    // your code
};

class SplayTree {
public:
    SplayTree() {
        root_ = nullptr;
    }

    ~SplayTree() {
        delete root_;
    }

    void insert(int value) {
        if (!root_) {
            root_ = new Node{value, nullptr, nullptr, nullptr};
            return;
        }

        Node *cur = root_;
        while (cur) {
            if (cur->key < value) {
                if (!cur->right) {
                    cur->right = new Node{value, nullptr, nullptr, cur};
                    return;
                }
                cur = cur->right;
            } else if (value < cur->key) {
                if (!cur->left) {
                    cur->left = new Node{value, nullptr, nullptr, cur};
                    return;
                }
                cur = cur->left;
            } else {
                return;
            }
        }
    }

    Node *find(int value) const {
        Node *cur = root_;
        while (cur) {
            if (cur->key < value) {
                cur = cur->right;
            } else if (value < cur->key) {
                cur = cur->left;
            } else {
                return cur;
            }
        }
        return nullptr;
    }

    int splay(Node *) {
    }

    int getHeight() const {
    }

private:
    Node *root_;
};
//
// int main() {
//    SplayTree st;
//    st.insert(1);
//    st.insert(3);
//    st.insert(2);
//    st.insert(7);
//    st.insert(3);
//    st.insert(6);
//
//    int k = 5;
//    return 0;
//}
