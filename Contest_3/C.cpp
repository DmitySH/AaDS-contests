#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    int *arr = new int[n];

    std::cin >> arr[0];
    arr[0] = (arr[0] == 0) ? 1 : 0;

    for (int i = 1; i < n; ++i) {
        std::cin >> arr[i];
        if (!arr[i]) {
            arr[i] = arr[i - 1] + 1;
        } else {
            arr[i] = arr[i - 1];
        }
    }

    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r;
        std::cin >> l >> r;
        --l;
        --r;
        std::cout << arr[r] - arr[l - 1] << ' ';
    }
    return 0;
}
