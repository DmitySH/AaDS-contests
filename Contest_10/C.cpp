#include <iostream>

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

    void appendList(SinglyLinkedList *list) {
        if (head_ == nullptr) {
            head_ = list->head_;
            tail_ = list->head_;
        } else {
            tail_->next = list->head_;
            tail_ = list->tail_;
        }
        size_ += list->size_;
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

    void deleter() {
        Node *cur = head_;
        while (cur != nullptr) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
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

class SetList {
public:
    SetList *parent;
    SinglyLinkedList<int> *list;
    int size;

    explicit SetList(int element) {
        list = new SinglyLinkedList<int>();
        list->append(element);
        parent = this;
        size = 1;
    }

    ~SetList() {
        delete list;
    }

    static void unite(SetList *first_set, SetList *second_set, int number) {
        SetList *first_leader = find(first_set);
        SetList *second_leader = find(second_set);

        if (first_leader->size > second_leader->size) {
            second_leader->parent = first_leader->parent;
            first_leader->parent->list->appendList(second_leader->list);
            first_leader->size += second_leader->size;
            if (first_leader->size == number) {
                first_leader->list->print();
                first_leader->list->deleter();
            }
        } else {
            first_leader->parent = second_leader->parent;
            second_leader->parent->list->appendList(first_leader->list);
            second_leader->size += first_leader->size;
            if (second_leader->size == number) {
                second_leader->list->print();
                second_leader->list->deleter();
            }
        }
    }

private:
    static SetList *find(SetList *vertex) {
        if (vertex->parent == vertex) {
            return vertex;
        }

        vertex->parent = find(vertex->parent);
        return vertex->parent;
    }
};

int main() {
    int number;
    std::cin >> number;
    SetList **sets = new SetList *[number];

    for (int i = 0; i < number; ++i) {
        sets[i] = new SetList(i + 1);
    }

    for (int i = 0; i < number - 1; ++i) {
        int first_element, second_element;
        std::cin >> first_element >> second_element;

        SetList::unite(sets[second_element - 1], sets[first_element - 1], number);
    }

    for (int i = 0; i < number; ++i) {
        delete sets[i];
    }

    delete[] sets;

    return 0;
}
