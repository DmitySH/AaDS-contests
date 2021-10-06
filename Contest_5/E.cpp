#include <iostream>
#include <string>

class MyStack {
 private:
  int size;
  int capacity;
  std::string *array;

  void Resize() {
    capacity *= 2;
    std::string *newArray = new std::string[capacity];
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
    array = new std::string[capacity];
  }

  bool IsEmpty() const {
    return size == 0;
  }

  void Push(std::string value) {
    if (size < capacity) {
      array[size] = value;
    } else {
      Resize();
      array[size] = value;
    }
    ++size;
  }

  std::string Pop() {
    if (IsEmpty()) {
      throw std::out_of_range("error");
    }

    --size;
    std::string value = array[size];
    return value;
  }

  void Clear() {
    size = 0;
    capacity = 8;

    delete[] array;
    array = new std::string[capacity];
  }

  std::string Back() {
    if (IsEmpty()) {
      throw std::out_of_range("error");
    }

    return array[size - 1];
  }

  int GetSize() const {
    return size;
  }
};

std::string MultiplyString(const std::string &str, int repeats) {
  std::string multiplied_string;

  for (int i = 0; i < repeats; ++i) {
    multiplied_string += str;
  }

  return multiplied_string;
}

std::string UnZip(const std::string &str) {
  std::string result;
  MyStack s;

  for (int i = 0; i < str.length(); ++i) {
    if (str[i] != ']') {
      s.Push(std::string(1, str[i]));
    } else {
      std::string elem = s.Pop();
      std::string res;
      while (elem != "[") {
        res += elem;
        elem = s.Pop();
      }
      s.Push(MultiplyString(res, std::stoi(s.Pop())));
    }
  }
  while (!s.IsEmpty()) {
    result += s.Pop();
  }

  std::string new_result;
  for (int i = result.length() - 1; i >= 0; --i) {
    new_result += result[i];
  }
  return new_result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string input;
  std::cin >> input;

  std::cout << UnZip(input);
  return 0;
}
