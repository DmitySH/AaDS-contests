#include <iostream>
#include <string>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string word;
    std::cin >> word;

    std::string first_half, second_half;
    for (int i = 0; i < word.length() - 1; i += 2) {
        first_half += word[i];
    }

    for (int i = 1; i < word.length() - 1; i += 2) {
        second_half = word[i] + second_half;
    }

    std::cout << first_half + second_half;
    return 0;
}
