#include <iostream>
#include <string>

template <typename T>
class DoubleLinkedList {
    struct Node {
    public:
        T value;
        Node *next, *prev;
    };

private:
    int size_;
    Node *head_, *tail_;

public:
    DoubleLinkedList() {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    ~DoubleLinkedList() {
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

    void pushFront(T value) {
        Node *new_node = new Node{value, nullptr};
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            new_node->next = head_;
            head_->prev = new_node;
            head_ = new_node;
        }
        ++size_;
    }

    void pushBack(T value) {
        Node *new_node = new Node{value, nullptr};
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
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

    void remove(int index) {
        if (index >= size_ - 1 || index < 0) {
            throw std::out_of_range("Index error");
        }

        Node *cur = head_;
        for (int i = 0; i <= index; ++i) {
            cur = cur->next;
        }

        if (index == size_ - 2) {
            tail_ = cur->prev;
            delete cur->prev->next;
            tail_->next = nullptr;
            --size_;
            return;
        }

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        --size_;
        delete cur;
    }

    void insert(int index, T value) {
        if (index > size_ || index < 0) {
            throw std::out_of_range("Index error");
        }

        Node *new_node = new Node{value, nullptr};

        Node *cur = head_;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }

        if (index == size_ - 1) {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
            ++size_;
            return;
        }

        new_node->next = cur->next;
        cur->next = new_node;

        new_node->next->prev = new_node;
        new_node->prev = cur;
        ++size_;
    }

    void printToRight() {
        Node *cur = head_;
        while (cur != nullptr) {
            std::cout << cur->value << ' ';
            cur = cur->next;
        }
        std::cout << '\n';
    }

    void printToLeft() {
        Node *cur = tail_;
        while (cur != nullptr) {
            std::cout << cur->value << ' ';
            cur = cur->prev;
        }
        std::cout << '\n';
    }

    int &operator[](const int index) {
        return getElement(index);
    }
};

void enterList(DoubleLinkedList<int> *list, int n) {
    for (int i = 0; i < n; ++i) {
        int elem;
        std::cin >> elem;
        list->pushBack(elem);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DoubleLinkedList<int> list;

    enterList(&list, n);

    for (int i = 0; i < m; ++i) {
        std::string input;
        std::cin >> input;
        if (input == "push_front") {
            int elem;
            std::cin >> elem;
            list.pushFront(elem);
        } else if (input == "push_back") {
            int elem;
            std::cin >> elem;
            list.pushBack(elem);
        } else if (input == "insert") {
            int elem, pos;
            std::cin >> elem >> pos;
            list.insert(pos, elem);
        } else if (input == "remove") {
            int pos;
            std::cin >> pos;
            list.remove(pos);
        }
    }

    list.printToRight();
    list.printToLeft();

    return 0;
}
