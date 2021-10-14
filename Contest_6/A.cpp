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

    bool need_to_delete_;
    // Надо проверить, вызывать ли десутруктор, ибо если он смерженный,
    // то удаление будет удалять узлы двух дургих листов и будет хаос,
    // поэтому если лист учавствовал в мерже, то он удалится лишь удалением
    // смерженного листа.

    void appendNode(Node *next_node) {
        if (size_ == 0) {
            head_ = next_node;
            tail_ = next_node;
        } else {
            tail_->next = next_node;
            tail_ = next_node;
        }

        ++size_;
    }

public:
    static SinglyLinkedList<int> mergeLists(SinglyLinkedList<int> *first_list,
                                            SinglyLinkedList<int> *second_list) {
        SinglyLinkedList<int> result;

        Node *first_node = first_list->head_;
        Node *second_node = second_list->head_;

        while (second_node != nullptr && first_node != nullptr) {
            int elem_in_first = first_node->value;
            int elem_in_second = second_node->value;

            if (elem_in_first <= elem_in_second) {
                result.appendNode(first_node);
                first_node = first_node->next;
            } else {
                result.appendNode(second_node);
                second_node = second_node->next;
            }
        }
        while (first_node != nullptr) {
            result.appendNode(first_node);
            first_node = first_node->next;
        }

        while (second_node != nullptr) {
            result.appendNode(second_node);
            second_node = second_node->next;
        }

        first_list->need_to_delete_ = false;
        second_list->need_to_delete_ = false;

        result.tail_->next = nullptr;
        return result;
    }

    SinglyLinkedList() {
        head_ = nullptr;
        size_ = 0;
        tail_ = nullptr;
        need_to_delete_ = true;
    }

    ~SinglyLinkedList() {
        if (!need_to_delete_) {
            return;
        }

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    SinglyLinkedList<int> first_list;
    SinglyLinkedList<int> second_list;

    enterList(&first_list, n);
    enterList(&second_list, m);

    SinglyLinkedList<int> merged_list =
        SinglyLinkedList<int>::mergeLists(&first_list, &second_list);
    merged_list.print();
    return 0;
}
