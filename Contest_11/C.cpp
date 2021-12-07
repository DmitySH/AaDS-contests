#include <iostream>
#include <string>

template <class ValueType>
class RBTree {
    struct Node {
    public:
        ValueType value;
        char color;
        Node *left;
        Node *right;
        Node *parent;

        Node() {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            color = 'B';
        }

        Node(ValueType value, char color, Node *left, Node *right, Node *parent) {
            this->left = left;
            this->color = color;
            this->value = value;
            this->right = right;
            this->parent = parent;
        }

        bool isBlack() {
            return color == 'B';
        }

        bool isRed() {
            return !isBlack();
        }

        bool isNil() {
            return color == 'B' && parent == nullptr && right == nullptr && left == nullptr;
        }
    };

public:
    RBTree() {
        size_ = 0;
        nil_ = new Node();
        root_ = nil_;
    }

    RBTree(const RBTree &other) {
        size_ = other.size_;
        nil_ = new Node();
        root_ = nil_;
        root_ = travelAndCopy(other.root_);
    }

    RBTree &operator=(const RBTree &other) {
        if (this == &other) {
            return *this;
        }

        size_ = other.size_;

        deleter(root_);
        delete nil_;

        nil_ = new Node();

        root_ = nil_;

        Node *new_root = travelAndCopy(other.root_);

        root_ = new_root;
        return *this;
    }

    ~RBTree() {
        deleter(root_);
        delete nil_;
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    void insert(const ValueType &value) {
        if (root_ == nil_) {
            ++size_;
            root_ = new Node{value, 'B', nil_, nil_, nullptr};
        } else {
            insertToEnd(root_, value);
        }
    }

    void erase(const ValueType &value) {
        Node *excluded = findByValue(root_, value);
        if (excluded == nil_) {
            return;
        }
        --size_;

        Node *s_min;
        char color = excluded->color;

        Node *sub;

        if (excluded->left == nil_) {
            sub = excluded->right;
            change(excluded, excluded->right);
        } else if (excluded->right == nil_) {
            sub = excluded->left;
            change(excluded, excluded->left);
        } else {
            s_min = subMin(excluded->right);
            color = s_min->color;
            sub = s_min->right;
            if (s_min->parent == excluded) {
                sub->parent = s_min;
            } else {
                change(s_min, s_min->right);
                s_min->right = excluded->right;
                s_min->right->parent = s_min;
            }

            change(excluded, s_min);
            s_min->left = excluded->left;
            s_min->left->parent = s_min;
            s_min->color = excluded->color;
        }
        excluded->left = nullptr;
        excluded->right = nullptr;
        delete excluded;
        if (color == 'B') {
            fixAfterErase(sub);
        }
    }

    ValueType *lower_bound(const ValueType &value) const {  // NOLINT
        Node *cur = root_;
        Node *prev = nullptr;

        while (cur != nil_) {
            prev = cur;
            if (value < cur->value) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }

        while (prev && prev->value < value) {
            prev = prev->parent;
        }
        return prev == nullptr ? nullptr : &(prev->value);
    }

    ValueType *find(const ValueType &value) const {
        Node *node = findByValue(root_, value);
        if (node == nil_) {
            return nullptr;
        } else {
            return &(node->value);
        }
    }

    ValueType *traversal() const {
        ValueType *ar = new ValueType[size_];
        int *index = new int(0);
        traveller(root_, ar, index);
        delete index;
        return ar;
    }

private:
    void deleter(Node *cur) {
        if (cur != nil_) {
            deleter(cur->right);
            deleter(cur->left);
            delete cur;
        }
    }

    Node *root_;
    size_t size_;
    Node *nil_;

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
        } else if (cur->value < value) {
            if (cur->right == nil_) {
                cur->right = new Node{value, 'R', nil_, nil_, cur};
                fixAfterInsert(cur->right);
                return;
            }
            insertToEnd(cur->right, value);
        }
    }

    void fixAfterInsert(Node *new_node) {
        ++size_;
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
                if (parent->right->isRed()) {
                    parent->right->color = 'B';
                    parent->color = 'R';
                    rotateLeft(new_node->parent);
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
                        parent = new_node->parent;
                    }

                    parent->right->color = parent->color;
                    parent->color = 'B';
                    parent->right->right->color = 'B';
                    rotateLeft(new_node->parent);
                    new_node = root_;
                }
            } else {
                if (parent->left->isRed()) {
                    parent->left->color = 'B';
                    parent->color = 'R';
                    rotateRight(new_node->parent);
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

    Node *findByValue(Node *cur, ValueType value) const {
        while (cur != nil_) {
            if (cur->value < value) {
                cur = cur->right;
            } else if (value < cur->value) {
                cur = cur->left;
            } else {
                return cur;
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

    void traveller(Node *cur, ValueType *ar, int *index) const {
        if (cur != nullptr && cur != nil_) {
            traveller(cur->left, ar, index);
            ar[*index] = cur->value;
            *index += 1;
            traveller(cur->right, ar, index);
        }
    }

    Node *travelAndCopy(Node *other_cur) {
        if (other_cur != nullptr && !other_cur->isNil()) {
            Node *cur = new Node{other_cur->value, other_cur->color, nil_, nil_, nullptr};

            Node *temp = travelAndCopy(other_cur->left);
            cur->left = temp;

            temp = travelAndCopy(other_cur->right);

            cur->right = temp;

            if (!cur->right->isNil()) {
                cur->right->parent = cur;
            }

            if (!cur->left->isNil()) {
                cur->left->parent = cur;
            }

            return cur;
        }
        return nil_;
    }
};

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node(KeyType key, ValueType value) {
        key_ = key;
        value_ = value;
        next_ = nullptr;
    }

    ~Node() = default;

    void deleteList() {
        Node *cur = this->next_;
        while (cur) {
            Node *to_del = cur;
            cur = cur->next_;
            delete to_del;
        }
    }
};

// основной класс фильтра
class BloomFilter {
public:
    BloomFilter(size_t hashes, size_t bits) {
        hashes_count_ = hashes;
        bits_ = bits;
        byte_ar_ = new bool[bits_];
        fp_ = 0;
        total_queries_ = 0;

        for (int i = 0; i < bits_; ++i) {
            byte_ar_[i] = false;
        }
    }

    ~BloomFilter() {
        delete[] byte_ar_;
    }

    // вставка информации об объекте
    void add(const std::string &obj) {
        strings_.insert(obj);

        if (test(obj)) {
            return;
        }

        byte_ar_[std::hash<std::string>{}(obj) % bits_] = true;
        for (int i = 1; i < hashes_count_; ++i) {
            byte_ar_[std::hash<std::string>{}(obj + std::to_string(i)) % bits_] = true;
        }
    }

    // проверка принадлежности объекта
    bool verify(const std::string &obj) {
        ++total_queries_;
        bool in_filter = test(obj);
        if (in_filter && !strings_.find(obj)) {
            ++fp_;
        }

        return in_filter;
    }

    // считаем относительную величину false positive rate по запросам тестирования
    // принадлежности
    double getFPRate() const {
        if (total_queries_ == 0) {
            return 0;
        }

        return static_cast<double>(fp_) / total_queries_;
    }

    size_t numberOfHashFunctions() const {
        return hashes_count_;
    }

    size_t numberOfBits() const {
        return bits_;
    }

private:
    bool test(std::string str) {
        if (!byte_ar_[std::hash<std::string>{}(str) % bits_]) {
            return false;
        }
        for (int i = 1; i < hashes_count_; ++i) {
            if (!byte_ar_[std::hash<std::string>{}(str + std::to_string(i)) % bits_]) {
                return false;
            }
        }

        return true;
    }

    RBTree<std::string> strings_;
    size_t hashes_count_;
    size_t bits_;
    bool *byte_ar_;
    int fp_;
    int total_queries_;
};
