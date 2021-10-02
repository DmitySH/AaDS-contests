#include <iostream>
#include <string>

class MyDeck {
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
    ~MyDeck() {
        delete[] array;
        array = nullptr;
    }

    MyDeck() {
        size = 0;
        capacity = 8;
        array = new int[capacity];
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

        delete[] array;
        array = new int[capacity];
    }

    void PushFront(int value) {

    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    return 0;
}
