#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    auto **a = new long long int *[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new long long int[m];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 || j == 0) {
                a[i][j] = 1;
            } else {
                a[i][j] = a[i - 1][j] + a[i][j - 1];
            }
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
