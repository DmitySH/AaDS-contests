#include <iostream>
#include <string>
#include <deque>
class MyDeque {
 private:
    int size;
    int capacity;
    int *array;
    int front_index;
    int back_index;

    void Resize() {
        int *newArray = new int[capacity * 2];
        for (int i = capacity / 2; i < capacity * 2 - capacity / 2; ++i) {
            newArray[i] = array[i - capacity / 2];
        }
        capacity *= 2;

        delete[] array;
        array = newArray;

        back_index = capacity / 4 + back_index;
        front_index = capacity - capacity / 4 - (capacity / 2 - front_index);
    }

 public:
    ~MyDeque() {
        delete[] array;
        array = nullptr;
    }

    MyDeque() {
        size = 0;
        capacity = 8;
        array = new int[capacity];
        front_index = capacity / 2;
        back_index = front_index - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    int GetSize() const {
        return size;
    }

    void Clear() {
        size = 0;
        capacity = 8;
        front_index = capacity / 2;
        back_index = front_index - 1;

        delete[] array;
        array = new int[capacity];
    }

    void PushFront(int value) {
        if (front_index >= capacity) {
            Resize();
        }
        array[front_index] = value;
        ++front_index;
        ++size;
    }

    void PushBack(int value) {
        if (back_index < 0) {
            Resize();
        }
        array[back_index] = value;
        --back_index;
        ++size;
    }

    int Front() {
        if (IsEmpty()) {
            throw std::out_of_range("error");
        }

        return array[front_index - 1];
    }

    int Back() {
        if (IsEmpty()) {
            throw std::out_of_range("error");
        }

        return array[back_index + 1];
    }

    int PopFront() {
        if (IsEmpty()) {
            throw std::out_of_range("error");
        }

        --size;
        --front_index;
        int value = array[front_index];
        return value;
    }

    int PopBack() {
        if (IsEmpty()) {
            throw std::out_of_range("error");
        }

        --size;
        ++back_index;
        int value = array[back_index];
        return value;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string input;
    std::cin >> input;
    MyDeque deck;

    while (input != "exit") {
        if (input == "push_front") {
            int elem;
            std::cin >> elem;
            deck.PushFront(elem);
            std::cout << "ok" << std::endl;
        } else if (input == "push_back") {
            int elem;
            std::cin >> elem;
            deck.PushBack(elem);
            std::cout << "ok" << std::endl;
        } else if (input == "pop_front") {
            if (!deck.IsEmpty()) {
                std::cout << deck.PopFront() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (input == "pop_back") {
            if (!deck.IsEmpty()) {
                std::cout << deck.PopBack() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (input == "back") {
            if (!deck.IsEmpty()) {
                std::cout << deck.Back() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (input == "front") {
            if (!deck.IsEmpty()) {
                std::cout << deck.Front() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (input == "size") {
            std::cout << deck.GetSize() << std::endl;
        } else if (input == "clear") {
            deck.Clear();
            std::cout << "ok" << std::endl;
        }

        std::cin >> input;
    }
    std::cout << "bye";
    return 0;
}
