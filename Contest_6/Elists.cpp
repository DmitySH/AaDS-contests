#include <iostream>
#include <string>
#include <cmath>

template <typename T>
class Dimon {
    class SinglyLinkedList {
        struct Node {
        public:
            T value;
            Node *next;
        };

    private:
        int size_;
        Node *head_, *tail_;

    public:
        SinglyLinkedList *nextList;
        int sum;
        int xorr;

        static void copyLists(SinglyLinkedList *from, SinglyLinkedList *to, int max_len) {
            int j = 0;
            Node *cur_node = nullptr;
            SinglyLinkedList *to_head = to;
            if (from != nullptr) {
                cur_node = from->head_;
            }

            while (from != nullptr) {
                while (cur_node != nullptr) {
                    if (j == max_len) {
                        j = 0;
                        Dimon::addListAfter(to_head);
                        to_head = to_head->nextList;
                    }
                    to_head->append(cur_node->value);
                    ++j;
                    Node *removal_node = cur_node;
                    cur_node = cur_node->next;
                    delete removal_node;
                }
                SinglyLinkedList *removal = from;
                from = from->nextList;
                delete removal;
                if (from != nullptr) {
                    cur_node = from->head_;
                }
            }
        }

        SinglyLinkedList() {
            nextList = nullptr;
            head_ = nullptr;
            size_ = 0;
            sum = 0;
            tail_ = nullptr;
            xorr = 0;
        }

        ~SinglyLinkedList() {
            Node *cur = head_;
            while (cur != nullptr) {
                Node *next = cur->next;
                delete cur;
                cur = next;
            }
        }

        int getSize() const {
            return size_;
        }

        void append(T value) {
            Node *new_node = new Node{value, nullptr};
            if (head_ == nullptr) {
                head_ = new_node;
                tail_ = new_node;
            } else {
                tail_->next = new_node;
                tail_ = tail_->next;
            }
            sum += value;
            xorr ^= value;
            ++size_;
        }

        T &getElement(int index) {
            if (index >= size_ || index < 0) {
                throw std::out_of_range("Index error");
            }

            Node *cur = head_;
            for (int i = 0; i < index; ++i) {
                cur = cur->next;
            }
            return cur->value;
        }

        void changeElement(int index, T value) {
            if (index >= size_ || index < 0) {
                throw std::out_of_range("Index error");
            }

            Node *cur = head_;
            for (int i = 0; i < index; ++i) {
                cur = cur->next;
            }

            xorr ^= cur->value;
            xorr ^= value;
            sum -= cur->value;
            sum += value;
            cur->value = value;
        }

        void print() {
            Node *cur = head_;
            while (cur != nullptr) {
                std::cout << cur->value << ' ';
                cur = cur->next;
            }
        }

        void erase(int index) {
            if (index > size_ || index < 0) {
                throw std::out_of_range("Index error");
            }

            if (index == 0) {
                sum -= head_->value;
                xorr ^= head_->value;
                Node *removal = head_;
                head_ = head_->next;
                delete removal;
            } else {
                Node *cur = head_;
                for (int i = 0; i < index - 1; ++i) {
                    cur = cur->next;
                }
                if (cur->next == tail_) {
                    sum -= tail_->value;
                    xorr ^= tail_->value;
                    delete tail_;
                    tail_ = cur;
                    tail_->next = nullptr;
                } else {
                    xorr ^= cur->next->value;
                    sum -= cur->next->value;
                    Node *removal = cur->next;
                    cur->next = cur->next->next;
                    delete removal;
                }
            }
            --size_;
        }

        void insert(int index, T value) {
            if (index > size_ || index < 0) {
                throw std::out_of_range("Index error");
            }
            Node *new_node = new Node{value, nullptr};

            if (size_ == 0) {
                head_ = new_node;
                tail_ = new_node;
                ++size_;
                return;
            }

            if (size_ == index) {
                tail_->next = new_node;
                tail_ = new_node;
            } else if (index == 0) {
                new_node->next = head_;
                head_ = new_node;
            } else {
                Node *cur = head_;
                for (int i = 0; i < index - 1; ++i) {
                    cur = cur->next;
                }
                new_node->next = cur->next;
                cur->next = new_node;
            }
            sum += value;
            xorr ^= value;
            ++size_;
        }

        T &operator[](int index) {
            return getElement(index);
        }
    };

private:
    int size_;
    SinglyLinkedList *head_, *tail_;
    int max_list_size_;
    int operations_, operations_to_rebuild_;

public:
    Dimon() {
        head_ = nullptr;
        size_ = 0;
        tail_ = nullptr;
        operations_ = 0;
    }

    Dimon(T *arr, int arr_len) {
        head_ = nullptr;
        size_ = 0;
        tail_ = nullptr;
        operations_ = 0;
        max_list_size_ = ceil(sqrt(arr_len));
        int j = 0;
        head_ = new SinglyLinkedList;
        SinglyLinkedList *cur = head_;
        for (int i = 0; i < arr_len; ++i) {
            if (j == max_list_size_) {
                j = 0;
                addListAfter(cur);
                cur = cur->nextList;
            }
            cur->append(arr[i]);
            ++j;
        }
        size_ = arr_len;
        operations_to_rebuild_ = ceil(sqrt(arr_len));
        mod = 0;
    }

    ~Dimon() {
        SinglyLinkedList *cur = head_;
        while (cur != nullptr) {
            SinglyLinkedList *next = cur->nextList;
            delete cur;
            cur = next;
        }
    }

    void rebuild() {
        max_list_size_ = ceil(sqrt(size_));
        operations_ = 0;
        operations_to_rebuild_ = ceil(sqrt(size_));
        SinglyLinkedList *new_head = new SinglyLinkedList;

        Dimon::SinglyLinkedList::copyLists(head_, new_head, max_list_size_);

        head_ = new_head;
    }

    int getSize() const {
        return size_;
    }

    static void addListAfter(SinglyLinkedList *list) {
        SinglyLinkedList *new_list = new SinglyLinkedList;
        new_list->nextList = list->nextList;
        list->nextList = new_list;
    }

    T getElement(int index) {
        --index;
        SinglyLinkedList *cur = head_;

        while (index - cur->getSize() >= 0) {
            index -= cur->getSize();
            cur = cur->nextList;
        }

        return cur->getElement(index);
    }

    void changeElement(int index, T value) {
        --index;
        SinglyLinkedList *cur = head_;

        while (index - cur->getSize() >= 0) {
            index -= cur->getSize();
            cur = cur->nextList;
        }

        cur->changeElement(index, value);
    }

    void insert(int index, T value) {
        if (operations_ >= operations_to_rebuild_) {
            rebuild();
        }
        ++operations_;
        --index;

        if (head_ == nullptr) {
            head_ = new SinglyLinkedList();
        }
        SinglyLinkedList *cur = head_;

        while (index - cur->getSize() > 0) {
            index -= cur->getSize();
            cur = cur->nextList;
        }

        cur->insert(index, value);
        ++size_;
    }

    void erase(int index) {
        if (operations_ >= operations_to_rebuild_) {
            rebuild();
        }
        ++operations_;
        --index;
        SinglyLinkedList *cur = head_;

        while (index - cur->getSize() >= 0) {
            index -= cur->getSize();
            cur = cur->nextList;
        }

        cur->erase(index);
        --size_;
    }

    T &operator[](int index) {
        return getElement(index);
    }

    void print() {
        SinglyLinkedList *cur = head_;
        while (cur != nullptr) {
            cur->print();
            std::cout << "!! \n";
            cur = cur->nextList;
        }
        std::cout << "all \n";
    }

    int sum(int l, int r) {
        --l;
        --r;
        int sum_l;
        int sum_r;

        sum_l = sumOnInterval(l - 1);
        sum_r = sumOnInterval(r);

        return (sum_r - sum_l) % mod;
    }

    int xxor(int l, int r) {
        --l;
        --r;
        int xor_l;
        int xor_r;

        xor_l = xorOnInterval(l - 1);
        xor_r = xorOnInterval(r);

        return xor_l ^ xor_r;
    }

    int xorOnInterval(int last) const {
        int xorr = 0;
        int count = 0;
        SinglyLinkedList *cur = head_;

        while (cur != nullptr && count + cur->getSize() <= last + 1) {
            xorr ^= cur->xorr;
            count += cur->getSize();
            cur = cur->nextList;
        }
        int j = 0;
        for (int i = count; i <= last; ++i) {
            xorr ^= cur->getElement(j);
            ++j;
        }
        return xorr;
    }

    int sumOnInterval(int last) const {
        int sum = 0;
        int count = 0;
        SinglyLinkedList *cur = head_;

        while (cur != nullptr && count + cur->getSize() <= last + 1) {
            sum += cur->sum;
            count += cur->getSize();
            cur = cur->nextList;
        }
        int j = 0;
        for (int i = count; i <= last; ++i) {
            sum += cur->getElement(j);
            ++j;
        }
        return sum;
    }

    int mod;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    char operation;
    int mod;
    std::cin >> operation;
    if (operation == '+') {
        std::cin >> mod;
    }
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int q;
    std::cin >> q;
    Dimon<int> dimon(arr, n);
    if (operation == '+') {
        dimon.mod = mod;
    }

    dimon.print();
    for (int i = 0; i < q; ++i) {
        std::string input;
        std::cin >> input;
        if (input == "insert") {
            int ind, x;
            std::cin >> ind >> x;
            dimon.insert(ind, x);
        } else if (input == "erase") {
            int ind;
            std::cin >> ind;
            dimon.erase(ind);
        } else if (input == "change") {
            int ind, x;
            std::cin >> ind >> x;
            dimon.changeElement(ind, x);
        } else if (input == "at") {
            int ind;
            std::cin >> ind;
            std::cout << dimon.getElement(ind) << '\n';
        } else if (input == "compute") {
            int l, r;
            std::cin >> l >> r;
            if (operation == '+') {
                std::cout << dimon.sum(l, r) << '\n';
            } else {
                std::cout << dimon.xxor(l, r) << '\n';
            }
        } else {
            std::cout << dimon.getSize() << '\n';
        }
    }

    return 0;
}
