#include <iostream>
#include <string>

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
    capacity = 16;
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

void AddUsualPerson(MyDeque *enter, MyDeque *exit, int *delta, int person) {
  if (*delta == 1) {
    exit->PushBack(enter->PopFront());
    enter->PushBack(person);
    --(*delta);
  } else {
    enter->PushBack(person);
    ++(*delta);
  }
}

void AddSuperPerson(MyDeque *enter, MyDeque *exit, int *delta, int person) {
  if (*delta == 1) {
    exit->PushBack(enter->PopFront());
    enter->PushFront(person);
    --(*delta);
  } else {
    enter->PushFront(person);
    ++(*delta);
  }
}

int ThrowPersonAway(MyDeque *enter, MyDeque *exit, int *delta) {
  if (*delta == 1) {
    exit->PushBack(enter->PopFront());
    --(*delta);
  } else {
    ++(*delta);
  }

  return exit->PopFront();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  MyDeque enter, exit;
  int delta = 0;

  for (int i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;

    if (command == "+") {
      int person;
      std::cin >> person;
      AddUsualPerson(&enter, &exit, &delta, person);
    } else if (command == "*") {
      int person;
      std::cin >> person;
      AddSuperPerson(&enter, &exit, &delta, person);
    } else if (command == "-") {
      std::cout << ThrowPersonAway(&enter, &exit, &delta) << '\n';
    }
  }

  return 0;
}
