// Prod. by Andryuschenko Michael in 2021.

#include <iostream>
#include <string>
// Used only by sqrt.
#include <cmath>

template <typename T>
using Operation = T (*)(T first_element, T second_element);

template <typename T>
class SpecifyList {
public:
    void build(T *array, int size) {
        //        if (!isFirst) {
        //            clear();
        //        }
        //        isFirst = false;
        clear();

        size_ = size;
        block_length_ = static_cast<int>(std::sqrt(size)) + 1;
        count_block_ = (size + block_length_ - 1) / block_length_;
        array_ = new T *[count_block_];
        size_of_arrays_ = new T[count_block_];

        for (int i = 0; i < count_block_; ++i) {
            array_[i] = new T[block_length_];
            size_of_arrays_[i] = block_length_;
        }

        size_of_arrays_[count_block_ - 1] = size % block_length_;

        for (int i = 0; i < size; ++i) {
            array_[i / block_length_][i % block_length_] = array[i];
        }
    }

    void readData(int count_elements) {
        T *array = new T[count_elements];
        for (int i = 0; i < count_elements; ++i) {
            std::cin >> array[i];
        }

        build(array, count_elements);

        delete[] array;
    }

    void setOperation(char operation) {
        if (operation == '+') {
            operation_ = [](T first, T second) { return first + second; };
        }

        if (operation == '^') {
            operation_ = [](T first, T second) { return first ^ second; };
        }
    }

    SpecifyList() {
        array_ = new T *[2];
        size_of_arrays_ = new T[2];
    }

    ~SpecifyList() {
        for (int i = 0; i < count_block_; ++i) {
            delete[] array_[i];
        }

        delete[] array_;
        delete[] size_of_arrays_;
        array_ = nullptr;
        size_of_arrays_ = nullptr;
    }

private:
    bool isFirst = true;
    int size_ = 0;
    int block_length_ = 0;
    int count_block_ = 0;
    T **array_;
    int *size_of_arrays_;
    int count_operation_ = 0;
    Operation<T> operation_;

    void clear() {
        for (int i = 0; i < count_block_; ++i) {
            delete[] array_[i];
        }

        delete[] array_;
        delete[] size_of_arrays_;

        size_ = 0;
        block_length_ = 0;
        count_block_ = 0;
        count_operation_ = 0;
        array_ = new T *[count_block_];
        size_of_arrays_ = new T[block_length_];
    }

    void rebuild() {
        T *array = new T[size_];
        int current_position = 0;

        for (int i = 0; i < count_block_; ++i) {
            for (int j = 0; j < size_of_arrays_[i]; ++j) {
                array[current_position] = array_[i][j];
            }
        }

        build(array, size_);
    }
};

int main() {
    SpecifyList<int> ans;
    int *kek = new int[5];
    kek[0] = 1;
    kek[1] = 2;
    kek[2] = 3;
    kek[3] = 4;
    kek[4] = 5;

    ans.build(kek, 5);

    delete[] kek;

    std::cout << "1";
    return 0;
}