#include <iostream>
#include <string>
#include <cmath>

template <typename T>
class Dimon {
    struct Node {
    public:
        T *arr;
        Node *next;
        int size;
        int max_size;

        Node(int arr_size) {
            arr = new T[arr_size];
            next = nullptr;
            max_size = arr_size;
            size = 0;
        }

        Node(T *arr, int max_size, int cur_size) {
            this->arr = arr;
            next = nullptr;
            size = cur_size;
            this->max_size = max_size;
        }

        ~Node() {
            delete[] arr;
            arr = nullptr;
        }
    };

private:
    int64_t size_;
    Node *head_;
    int node_size;

public:
    Dimon() {
        head_ = nullptr;
        size_ = 0;
        node_size = 0;
    }

    ~Dimon() {
        //        throw "Destructor";
    }

    void insert(int index, T value) {
        Node *cur = head_;
        --index;
        while (index - cur->size > 0) {
            index -= cur->size;
            cur = cur->next;
        }
        if (cur->size == cur->max_size) {
            Node *new_node = new Node(node_size);
            for (int i = cur->max_size / 2; i < cur->max_size; ++i) {
                new_node->arr[i - cur->max_size / 2] = cur->arr[i];
            }
//            cur->arr[cur->max_size / 2] = TODO
        } else {
            for (int i = cur->size; i > index; --i) {
                cur->arr[i] = cur->arr[i - 1];
            }
            ++cur->size;
            cur->arr[index] = value;
        }
    }

    void appendArray(T *arr, int size, int max_size) {
        Node *cur = head_;
        if (cur == nullptr) {
            head_ = new Node(arr, max_size, size);
        } else {
            while (cur->next != nullptr) {
                cur = cur->next;
            }

            cur->next = new Node(arr, max_size, size);
        }
    }

    void print() {
        Node *cur = head_;
        while (cur != nullptr) {
            for (int i = 0; i < cur->size; ++i) {
                std::cout << cur->arr[i] << ' ';
            }
            cur = cur->next;

            std::cout << '\n';
        }
        std::cout << "Done \n";
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Dimon<int> dimon;
    dimon.appendArray(new int[2]{1, 2}, 2, 4);
    dimon.appendArray(new int[1]{3}, 1, 4);
    dimon.appendArray(new int[3]{5, 6, 7}, 3, 4);
    dimon.print();

    dimon.insert(6, 10);
    dimon.print();
    return 0;
}
