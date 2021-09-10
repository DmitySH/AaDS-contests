#include <iostream>

// Сам бинпоиск для остортированного массива.
int binary_search(const int arr[], int size , int elem) {
    int left = 0, right = size;
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;
        if (arr[middle] == elem) {
            return middle;
        }
        if (elem < arr[middle]) {
            right = middle - 1;
        }
        else {
            left = middle + 1;
        }
    }
}
// Видно, что сложность = log2(n)

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

//    int arr[5] = {2, 5, 6, 7, 123};
//    std::cout << binary_search(arr, 5, 7);

    int pow = 0 , num = 1;
    int n;
    std::cin >> n;


    while (num < n) {
        num *= 2;
        pow++;
    }

    std::cout << ((pow) ? pow : 1);
    return 0;
}