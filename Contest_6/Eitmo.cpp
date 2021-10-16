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
        int sum;

        SinglyLinkedList() {
            head_ = nullptr;
            size_ = 0;
            sum = 0;
            tail_ = nullptr;
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
                    delete tail_;
                    tail_ = cur;
                    tail_->next = nullptr;
                } else {
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

            ++size_;
        }

        T &operator[](int index) {
            return getElement(index);
        }
    };
private:
    SinglyLinkedList sums_;
    SinglyLinkedList xors_;
    SinglyLinkedList left_indexes_;
    SinglyLinkedList right_indexes_;
    SinglyLinkedList order_;
    SinglyLinkedList init_array_;

public:
    Dimon(T *arr, int arr_size) {
        int size = ceil(sqrt(arr_size));

        for (int i = 0; i < arr_size / size; ++i) {
            sums_.append(0);
            xors_.append(0);
        }

        for (int i = 0; i < arr_size / size; ++i) {
            left_indexes_.append(i * size);
            right_indexes_.append(size * i + size - 1);
        }

        int j = 0;
        for (int i = 0; i < arr_size; ++i) {
            if(i % size == 0) {
                ++j;
            }
            init_array_.append(arr[i]);
            order_.append(i);
            sums_[j] += arr[i];
            xors_[j] ^= arr[i];
        }
    }

    void cutFrom(int left, int right) {
        int sum = 0;
        int xorr = 0;

        for (int i = left; i <= right; ++i) {
            sum += init_array_[i];
            xorr ^= init_array_[i];
            left_indexes_.append(left);
            right_indexes_.append(right);
        }
    }

    ~Dimon(){

    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    //    std::cin >> n;

    return 0;
}
