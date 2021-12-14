#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number;
    std::cin >> number;

    std::vector<int> sorted_nums;

    for (int i = 0; i < number; ++i) {
        int elem;
        std::cin >> elem;
        sorted_nums.push_back(elem);
    }
    int max_len = 1;
    int cur_len = 1;

    std::sort(sorted_nums.begin(), sorted_nums.end());

    for (auto iterator = ++sorted_nums.begin(); iterator != sorted_nums.end(); ++iterator) {
        auto cur_iterator = iterator;
        int current = *cur_iterator;
        int prev = *(--cur_iterator);

        if (current == prev) {
            continue;
        }

        if (current == prev + 1) {
            cur_len += 1;
        } else {
            if (cur_len > max_len) {
                max_len = cur_len;
            }
            cur_len = 1;
        }
    }

    if (cur_len > max_len) {
        max_len = cur_len;
    }

    std::cout << max_len;

    return 0;
}