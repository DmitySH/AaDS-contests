#include <iostream>
#include <string>
#include <ctime>

struct Node {
    int value;
    Node *next;
};

class MyQueue {
 private:
    Node *middle;
    Node *head;
    Node *tail;
    int size;

    void InitHead(int elem) {
        head = new Node{elem, nullptr};
        tail = head;
        middle = head;
    }

 public:
    MyQueue() {
        middle = nullptr;
        tail = nullptr;
        head = nullptr;
        size = 0;
    }

    ~MyQueue() {
        while (head != nullptr) {
            Node *current_node = head;
            head = current_node->next;
            delete current_node;
        }
        head = nullptr;
        tail = nullptr;
        middle = nullptr;
    }

    void Enqueue(int elem) {
        if (head == nullptr) {
            InitHead(elem);
        } else {
            tail->next = new Node{elem, nullptr};
            tail = tail->next;
        }
        ++size;
        if (size % 2 == 1 && size != 1) {
            middle = middle->next;
        }
    }

    void Print() {
        Node *cur = head;
        while (cur != nullptr) {
            std::cout << cur->value << ' ';
            cur = cur->next;
        }
        if (middle != nullptr) {
            std::cout << " mid = " << middle->value << '\n';
        }
    }

    void SuperEnqueue(int elem) {
        if (head == nullptr) {
            InitHead(elem);
        } else {
            middle->next = new Node{elem, middle->next};
        }
        ++size;
        if (size % 2 == 1 && size != 1) {
            middle = middle->next;
        }
        if (head == tail && middle->next != nullptr) {
            tail = middle->next;
        }
    }

    int Dequeue() {
        if (size == 0) {
            throw std::out_of_range("error");
        }

        --size;
        if (size % 2 == 1) {
            middle = middle->next;
        }

        int current_value = head->value;
        if (head == tail) {
            delete tail;
            middle = nullptr;
            head = nullptr;
            tail = nullptr;
        } else {
            Node *current_node = head;
            head = current_node->next;
            delete current_node;
        }

        return current_value;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    MyQueue queue;
    clock_t start = clock();
    for (int i = 0; i < n; ++i) {
        std::string command;
        std::cin >> command;

        if (command == "+") {
            int person;
            std::cin >> person;
            queue.Enqueue(person);
        } else if (command == "*") {
            int person;
            std::cin >> person;
            queue.SuperEnqueue(person);
        } else if (command == "-") {
            std::cout << queue.Dequeue() << '\n';
        }
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << seconds;
    return 0;
}
