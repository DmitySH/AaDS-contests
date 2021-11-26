#include <iostream>

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

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable() {
        size_ = 0;
        capacity_ = 100;
        fullness_ = 0.5;
        hasher_ = Func();
        values_ = new Node<KeyType, ValueType> *[capacity_];

        for (int i = 0; i < capacity_; ++i) {
            values_[i] = nullptr;
        }
    }

    explicit HashTable(Func hasher) : HashTable() {
        hasher_ = hasher;
    }

    HashTable(size_t capacity, double fullness, Func hasher = std::hash<KeyType>()) {
        capacity_ = capacity;
        hasher_ = hasher;
        size_ = 0;
        if (fullness <= 0 || fullness > 1) {
            fullness_ = 0.5;
        } else {
            fullness_ = fullness;
        }

        values_ = new Node<KeyType, ValueType> *[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            values_[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < capacity_; ++i) {
            if (values_[i]) {
                values_[i]->deleteList();
                delete values_[i];
            }
        }

        delete[] values_;
    }

    void insert(KeyType key, ValueType value) {
        size_t hash = hasher_(key) % capacity_;

        if (!values_[hash]) {
            values_[hash] = new Node<KeyType, ValueType>(key, value);
            ++size_;
        } else {
            Node<KeyType, ValueType> *cur = values_[hash];
            while (cur->next_) {
                if (cur->key_ == key) {
                    cur->value_ = value;
                    return;
                }
                cur = cur->next_;
            }

            if (cur->key_ == key) {
                cur->value_ = value;
                return;
            }

            ++size_;
            cur->next_ = new Node<KeyType, ValueType>(key, value);
        }

        if (size_ > capacity_ * fullness_) {
            reHash();
        }
    }

    ValueType *find(KeyType key) {
        size_t hash = hasher_(key) % capacity_;
        Node<KeyType, ValueType> *cur = values_[hash];
        while (cur) {
            if (cur->key_ == key) {
                return &(cur->value_);
            }
            cur = cur->next_;
        }
        return nullptr;
    }

    void erase(KeyType key) {
        size_t hash = hasher_(key) % capacity_;

        Node<KeyType, ValueType> *cur = values_[hash];

        if (!cur) {
            return;
        }

        if (cur->key_ == key) {
            Node<KeyType, ValueType> *to_del = values_[hash];
            values_[hash] = values_[hash]->next_;
            delete to_del;
            --size_;
        } else {
            while (cur->next_) {
                if (cur->next_->key_ == key) {
                    Node<KeyType, ValueType> *to_del = cur->next_;
                    cur->next_ = cur->next_->next_;
                    delete to_del;
                    --size_;
                    return;
                }
                cur = cur->next_;
            }
        }
    }

    Node<KeyType, ValueType> &operator[](uint64_t hash) {
        if (hash < 0 || hash >= capacity_) {
            throw std::out_of_range("Error");
        }

        if (!values_[hash]) {
            throw std::runtime_error("Error");
        }

        return *(values_[hash]);
    }

    Node<KeyType, ValueType> at(uint64_t hash) {
        return operator[](hash);
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

private:
    size_t size_;
    size_t capacity_;
    double fullness_;
    Func hasher_;
    Node<KeyType, ValueType> **values_;

    void reHash() {
        size_t prev_capacity = capacity_;
        capacity_ = capacity_ + capacity_;
        Node<KeyType, ValueType> **prev_table = values_;
        values_ = new Node<KeyType, ValueType> *[capacity_];

        for (int i = 0; i < capacity_; ++i) {
            values_[i] = nullptr;
        }

        for (int index = 0; index < prev_capacity; ++index) {
            Node<KeyType, ValueType> *prev = prev_table[index];

            if (prev) {
                Node<KeyType, ValueType> *to_del = prev;
                while (prev) {
                    size_t hash = hasher_(prev->key_) % capacity_;

                    Node<KeyType, ValueType> *new_place = values_[hash];
                    if (!values_[hash]) {
                        values_[hash] = new Node<KeyType, ValueType>(prev->key_, prev->value_);
                    } else {
                        while (new_place->next_) {
                            new_place = new_place->next_;
                        }
                        new_place->next_ = new Node<KeyType, ValueType>(prev->key_, prev->value_);
                    }

                    prev = prev->next_;
                }
                to_del->deleteList();
                delete to_del;
            }
        }

        delete[] prev_table;
    }
};
