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

bool IsRightSequence(std::string str) {
    MyStack stack;
    for (const char sym : str) {
        if (sym == '(' || sym == '[' || sym == '{') {
            stack.Push(sym);
        } else {
            if (stack.IsEmpty()) {
                return false;
            }

            if (sym == ')' && stack.Back() != '(' || sym == '}' && stack.Back() != '{'
                || sym == ']' && stack.Back() != '[') {
                return false;
            } else {
                stack.Pop();
            }
        }
    }

    return stack.IsEmpty();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_line;
    std::cin >> input_line;

    if (IsRightSequence(input_line)) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }

    return 0;
}
