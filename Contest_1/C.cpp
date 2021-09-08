#include <iostream>

using namespace std;

int reverse(int num) {
    int reversed_num = 0;
    while (num != 0) {
        reversed_num = reversed_num * 10 + num % 10;
        num /= 10;
    }
    return reversed_num;
}

int main() {
    int k;
    cin >> k;
    int count = 0;
    for (int i = 1; i <= k; ++i) {
        if (i == reverse(i)) {
            count++;
        }
    }
    cout << count;
    return 0;
}
