#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    int *a = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int total_operations = 0, count_zeros = 0;

    while (count_zeros != n) {
        count_zeros = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2 != 0) {
                ++total_operations;
                if (a[i] < 0) {
                    ++a[i];
                } else {
                    --a[i];
                }
            }
            if (a[i] == 0) {
                ++count_zeros;
            }
        }
        if (count_zeros != n) {
            count_zeros = 0;
            for (int i = 0; i < n; ++i) {
                a[i] /= 2;
                if (a[i] == 0) {
                    ++count_zeros;
                }
            }
            ++total_operations;
        }
    }

    std::cout << total_operations;

    return 0;
}
