#include <iostream>
#include <string>

std::string SequenceBuilder(int x, int n) {
    std::string current_sequence;
    current_sequence = std::to_string(x);
    if (n > 1) {
        current_sequence = "1" + std::to_string(x);
    }

    for (int i = 2; i < n; ++i) {
        std::string next_sequence;
        int row_counter = 1;

        for (int j = 1; j < current_sequence.length(); ++j) { // 3 1 1 3
            if (current_sequence[j] == current_sequence[j - 1]) {
                ++row_counter;
            } else {
                next_sequence += std::to_string(row_counter) + current_sequence[j - 1];
                row_counter = 1;
            }
        }
        next_sequence += std::to_string(row_counter) + current_sequence[current_sequence.length() - 1];
        current_sequence = next_sequence;
    }

    return current_sequence;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x, n;
    std::cin >> x >> n;
    std::cout << SequenceBuilder(x, n);

    return 0;
}
