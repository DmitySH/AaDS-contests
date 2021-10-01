class MyVector {

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
    ~MyVector() {
        delete[] array;
        array = nullptr;
    }

    MyVector() {
        capacity = 8;
        array = new int[capacity];
        size = 0;
    }

    MyVector &Append(int value) {
        if (size < capacity) {
            array[size] = value;
            ++size;
            return *this;
        }

        Resize();
        array[size] = value;
        ++size;

        return *this;
    }

    void Delete(int index) {
        if (index > size || index < 0) {
            throw std::out_of_range("Out of range!");
        }

        for (int i = index + 1; i < size; i++) {
            array[i - 1] = array[i];
        }
        --size;
    }

    int &operator[](int index) {
        return array[index];
    }
};
