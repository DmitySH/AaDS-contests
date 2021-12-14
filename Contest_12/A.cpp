#include <iostream>
#include <stack>
#include <string>

int getPriority(std::string str) {
    if (str == "+" || str == "-") {
        return 1;
    } else if (str == "*" || str == "/") {
        return 2;
    } else {
        return 0;
    }
}

bool morePriority(std::string first, std::string second) {
    return getPriority(first) >= getPriority(second);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string next;

    std::stack<std::string> stack;
    while (std::cin >> next) {
        if (next == "(") {
            stack.push("(");
        } else if (next == ")") {
            while (stack.top() != "(") {
                std::cout << stack.top() << ' ';
                stack.pop();
            }
            stack.pop();
        } else if (next == "+" || next == "-" || next == "*" || next == "/") {
            while (!stack.empty() && morePriority(stack.top(), next)) {
                std::cout << stack.top() << ' ';
                stack.pop();
            }
            stack.push(next);
        } else {
            std::cout << next << ' ';
        }
    }

    while (!stack.empty()) {
        std::cout << stack.top() << ' ';
        stack.pop();
    }

    return 0;
}
