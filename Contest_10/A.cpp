#include <iostream>

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

    ~Node() {
    }

    void deleteList() {
        Node *cur = cur->next_;
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
        hasher_ = std::hash<KeyType>();
        values_ = new Node<KeyType, ValueType> *[capacity_];
    }

    HashTable(Func hasher) : HashTable() {
        hasher_ = hasher;
    }

    HashTable(size_t capacity, double fullness, Func hashser = std::hash<KeyType>()) {
        capacity_ = capacity;
        hasher_ = hashser;

        if (fullness <= 0 || fullness > 1) {
            fullness_ = 0.5;
        } else {
            fullness_ = fullness;
        }

        values_ = new Node<KeyType, ValueType> *[capacity_];
    };

    ~HashTable() {
        for (int i = 0; i < size_; ++i) {
            values_[i]->deleteList();
            delete values_[i];
        }

        delete[] values_;
    }

    void insert(KeyType key, ValueType value) {
        size_t hash = hasher_(key) % capacity_;

        if (!values_[hash]) {
            values_[hash] = new Node<KeyType, ValueType>(key, value);
        } else {
            Node<KeyType, ValueType> *cur = values_[hash];
            while (cur->next_) {
                if (cur->key_ == key) {
                    cur->value_ = value;
                    return;
                }
                cur = cur->next_;
            }

            cur->next_ = new Node<KeyType, ValueType>(key, value);
        }

        ++size_;

        if (size_ > capacity_ * fullness_) {
            reHash();
        }
    }

    ValueType *find(KeyType key) {
        size_t hash = hasher_(key) % capacity_;
        Node<KeyType, ValueType> *cur = values_[hash];
        while (cur && cur->key_ != key) {
            cur = cur->next_;
        }

        if (cur) {
            return &(cur->value_);
        }

        return nullptr;
    }

    void erase(KeyType key) {
        size_t hash = hasher_(key) % capacity_;
        Node<KeyType, ValueType> *cur = values_[hash];

        if (cur->key_ == key) {
            values_[hash] = cur->next_;
            --size_;
        } else {
            while (cur->next_ && cur->next_->key_ != key) {
                cur = cur->next_;
            }

            if (cur->next_) {
                cur->next_ = cur->next_->next_;
                --size_;
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
        return (*this)[hash];
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
        capacity_ = capacity_ * 2;
        Node<KeyType, ValueType> **prev_table = values_;
        values_ = new Node<KeyType, ValueType> *[capacity_];

        for (int i = 0; i < capacity_ / 2; ++i) {
            if (prev_table[i]) {
                Node<KeyType, ValueType> *cur = values_[i];
                while (cur) {
                    this->insert(cur->key_, cur->value_);
                    cur = cur->next_;
                }
            }
        }

        delete[] prev_table;
    }
};

int main() {
    HashTable<std::string, int> table;

    std::cout << table.capacity() << std::endl;
    std::cout << table.size() << std::endl;

    table.insert("hello", 5);

    return 0;
}
