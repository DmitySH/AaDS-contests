#include <iostream>

void filler(int **a, int n, int a1, int d) {
    int i = 0, j = 0;
    int inc_i = 0, inc_j = 0, ij_eqn = 0, ij_sign = 1;
    bool not_turned = true;
    a[0][0] = a1;
    for (int k = 2; k != n * n + 1; ++k) {
        if (j == ij_eqn && not_turned) {
            ++i;
            inc_i = -1 * ij_sign;
            inc_j = 1 * ij_sign;
            not_turned = false;
        } else if (i == ij_eqn && not_turned) {
            ++j;
            inc_i = 1 * ij_sign;
            inc_j = -1 * ij_sign;
            not_turned = false;
        } else {
            i += inc_i;
            j += inc_j;
            not_turned = true;
        }
        a[i][j] = a1 + d * (k - 1);

        // Условие, что мы заполнили половину и диагональ.
        if (!(((i != 0 || j != n - 1) && n % 2 == 0)
              || ((i != n - 1 || j != 0) && n % 2 == 1))) {
            not_turned = true;
            ij_eqn = n - 1;
            ij_sign = -ij_sign;
        }
    }
}

void print_array(int **a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, a1, d;
    std::cin >> n >> a1 >> d;

    int **a = new int *[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[n];
    }
    filler(a, n, a1, d);

    int sum = 0;
    int i = 0;
    int diag = 0;
    for (int j = 0; i < n / 2; ++j) {
        if (j > diag && j < n - diag - 1) {
            sum += a[i][j];
        }
        if (j == n - 1) {
            ++i;
            ++diag;
            j = 0;
        }
    }
    diag = 0;
    i = n - 1;
    for (int j = n - 1; i >= n / 2; --j) {
        if (j < n - diag - 1 && j > diag) {
            sum += a[i][j];
        }
        if (j == 0) {
            --i;
            ++diag;
            j = n - 1;
        }
    }
    std::cout << sum << std::endl;

    if (n <= 20) {
        print_array(a, n);
    }

    return 0;
}
