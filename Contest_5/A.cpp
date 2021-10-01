#include <iostream>
#include <string>


class MyStack {

private:
    int size;
    int *head;
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
        delete head;
        head = nullptr;
        array = nullptr;
    }

    MyStack() {
        head = nullptr;
        size = 0;
        capacity = 8;
        array = new int[capacity];
    }

    bool IsEmpty() {
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
        if (size <= 0) {

        }
        int value = array[size];
        --size;
        return value;
    }

    void Clear() {
        for (int i = 0; i < size; ++i) {
            array[i] = 0;
        }

        size = 0;
        std::cout << "ok";
    }

    int Back() {
        if (IsEmpty()) {

        }

        return array[size];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    

    return 0;
}
