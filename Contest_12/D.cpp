#include <iostream>
#include <stack>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::stack<int> stack;
    int number;
    std::cin >> number;

    int *given = new int[number];
    int *res = new int[number];

    for (int i = 0; i < number; ++i) {
        int elem;
        std::cin >> elem;
        given[i] = elem;
        res[i] = -1;
    }
    stack.push(0);

    for (int i = 1; i < number; ++i) {
        while (!stack.empty() && given[i] < given[stack.top()]) {
            res[stack.top()] = i;
            stack.pop();
        }
        stack.push(i);
    }

    for (int i = 0; i < number; ++i) {
        std::cout << res[i] << ' ';
    }

    delete[] given;
    delete[] res;
    return 0;
}
