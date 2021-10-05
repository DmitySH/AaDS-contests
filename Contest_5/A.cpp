#include <iostream>
#include <string>

class MyStack {
 private:
    int size;
    int capacity;
    int *array;

    void Resize() {
        capacity *= 2;
        int *newArray = new int[capacity];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
    }

 public:
    ~MyStack() {
        delete[] array;
        array = nullptr;
    }

    MyStack() {
        size = 0;
        capacity = 8;
        array = new int[capacity];
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void Push(int value) {
        if (size < capacity) {
            array[size] = value;
        } else {
            Resize();
            array[size] = value;
        }
        ++size;
    }

    int Pop() {
        if (IsEmpty()) {
            throw std::out_of_range("error");
        }
        
        --size;
        int value = array[size];
        return value;
    }

    void Clear() {
        size = 0;
        capacity = 8;

        delete[] array;
        array = new int[capacity];
    }

    int Back() {
        if (IsEmpty()) {
            throw std::out_of_range("error");
        }

        return array[size - 1];
    }

    int GetSize() const {
        return size;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    MyStack stack;
    std::cin >> input;
    while (input != "exit") {
        if (input == "push") {
            int elem;
            std::cin >> elem;
            stack.Push(elem);
            std::cout << "ok" << std::endl;
        } else if (input == "pop") {
            if (!stack.IsEmpty()) {
                std::cout << stack.Pop() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (input == "back") {
            if (!stack.IsEmpty()) {
                std::cout << stack.Back() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (input == "size") {
            std::cout << stack.GetSize() << std::endl;
        } else if (input == "clear") {
            stack.Clear();
            std::cout << "ok" << std::endl;
        }

        std::cin >> input;
    }
    std::cout << "bye";

    return 0;
}
