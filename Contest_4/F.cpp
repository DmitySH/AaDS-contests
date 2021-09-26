#include <iostream>
#include <string>

void CheckSymbols(bool *a, const std::string &str) {
    for (const auto sym : str) {
        if (sym != ' ') {
            a[sym - 'a'] = true;
        }
    }
}

void FindDifference(const std::string &first, const std::string &second) {
    const int kAlphabetSize = 26;

    bool first_symbols[kAlphabetSize];
    bool second_symbols[kAlphabetSize];

    for (int i = 0; i < kAlphabetSize; ++i) {
        first_symbols[i] = false;
        second_symbols[i] = false;
    }

    CheckSymbols(first_symbols, first);
    CheckSymbols(second_symbols, second);

    bool equals = true;
    for (int i = 0; i < kAlphabetSize; ++i) {
        if (first_symbols[i] && !second_symbols[i] || !first_symbols[i] && second_symbols[i]) {
            equals = false;
            std::cout << static_cast<char> (i + 'a') << ' ';
        }
    }

    if (equals) {
        std::cout << "NONE";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_first, input_second;
    std::getline(std::cin, input_first);
    std::getline(std::cin, input_second);

    FindDifference(input_first, input_second);

    return 0;
}
