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

SinglyLinkedList<int> mergeLists(const SinglyLinkedList<int> &first_list,
                                 const SinglyLinkedList<int> &second_list) {
    int first_index = 0, second_index = 0;
    SinglyLinkedList<int> result;

    while (first_index < first_list.getSize() && second_index < second_list.getSize()) {
        int elem_in_first = first_list.getElement(first_index);
        int elem_in_second = second_list.getElement(second_index);

        if (elem_in_first <= elem_in_second) {
            result.append(elem_in_first);
            ++first_index;
        } else {
            result.append(elem_in_second);
            ++second_index;
        }
    }
    if (first_index != first_list.getSize()) {
        for (int i = first_index; i < first_list.getSize(); ++i) {
            result.append(first_list.getElement(i));
        }
    } else {
        for (int i = second_index; i < second_list.getSize(); ++i) {
            result.append(second_list.getElement(i));
        }
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    SinglyLinkedList<int> first_list;
    SinglyLinkedList<int> second_list;

    enterList(&first_list, n);
    enterList(&second_list, m);

    SinglyLinkedList<int> merged_list = mergeLists(first_list, second_list);
    merged_list.print();
    return 0;
}
