#include <iostream>
#include <string>

template <typename T>
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
    SinglyLinkedList() {
        head_ = nullptr;
        size_ = 0;
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

    static SinglyLinkedList<int> reverse(const SinglyLinkedList<T> &list) {
        SinglyLinkedList<int> result;

        if (list.getSize() == 0) {
            return result;
        }

        result.head_ = new Node{list.getElement(0), nullptr};

        for (int i = 1; i < list.getSize(); ++i) {
            Node *new_node = new Node{list.getElement(i), nullptr};
            new_node->next = result.head_;
            result.head_ = new_node;
        }

        return result;
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
        ++size_;
    }

    T getElement(int index) const {
        if (index >= size_) {
            throw std::out_of_range("Index error");
        }
        Node *cur = head_;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->value;
    }

    void print() {
        Node *cur = head_;
        while (cur != nullptr) {
            std::cout << cur->value << ' ';
            cur = cur->next;
        }
    }

    void insertIn(int index, T value) {
        if (index > size_) {
            throw std::out_of_range("Index error");
        }

        Node *new_node = new Node{value, nullptr};
        if (index == 0) {
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
        ++size_;
    }

    int &operator[](const int index) {
        return getElement(index);
    }
};

void enterList(SinglyLinkedList<int> *list, int n) {
    for (int i = 0; i < n; ++i) {
        int elem;
        std::cin >> elem;
        list->append(elem);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n;

    SinglyLinkedList<int> first_list;

    enterList(&first_list, n);

    SinglyLinkedList<int> list_reversed = SinglyLinkedList<int>::reverse(first_list);
    list_reversed.print();
    return 0;
}
