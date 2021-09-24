#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    int **a = new int *[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[m];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
        }
    }

    std::cout << m << ' ' << n << std::endl;

    for (int i = 0; i < m; ++i) {
        for (int j = n - 1; j >= 0; --j) {
            std::cout << a[j][i] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
