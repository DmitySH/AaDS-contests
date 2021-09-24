#include <utility>
#include <iostream>
#include <stack>
#include <algorithm>

class MyQueue {
 private:
    std::stack<std::pair<int, int>> s1, s2;

 public:
    void enqueue(int new_element) {
        int min = s1.empty() ? new_element : std::min(new_element, s1.top().second);
        s1.push(std::make_pair(new_element, min));
    }

    void dequeue() {
        if (s2.empty()) {
            while (!s1.empty()) {
                int element = s1.top().first;
                s1.pop();
                int min = s2.empty() ? element : std::min(element, s2.top().second);
                s2.push(std::make_pair(element, min));
            }
        }
        s2.pop();
    }

    int min() {
        int current_min;
        if (s1.empty() || s2.empty()) {
            current_min = s1.empty() ? s2.top().second : s1.top().second;
        } else {
            current_min = std::min(s1.top().second, s2.top().second);
        }

        return current_min;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    MyQueue queue;

    for (int i = 0; i < k; ++i) {
        int elem;
        std::cin >> elem;
        queue.enqueue(elem);
    }
    std::cout << queue.min() << ' ';

    for (int i = k; i < n; ++i) {
        int elem;
        std::cin >> elem;
        queue.enqueue(elem);
        queue.dequeue();
        std::cout << queue.min() << ' ';
    }

    return 0;
}
