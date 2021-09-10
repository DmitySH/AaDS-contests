#include <iostream>
#include <unordered_set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::unordered_set<char> letters = {'b', 'c', 'd', 'f', 'g',
                                              'h', 'j', 'k', 'l', 'm', 'n',
                                              'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};
    std::string str;
    std::cin >> str;

    bool is_to_right = true, is_poly = true;

    int left_index = 0, right_index = str.length() - 1;
    while (left_index < right_index) {
        if (is_to_right) {
            if (letters.find(str[left_index]) != letters.end()) {
                is_to_right = false;
            }
            left_index++;
        }
        else {
            if (letters.find(str[right_index]) != letters.end()) {
                is_to_right = true;
                if (str[right_index] != str[left_index - 1]) {
                    is_poly = false;
                    break;
                }
            }
            right_index--;
        }
    }


    if (is_poly) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}