#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int sum = 0;
    int cur;
    int n = 0;
    cin >> cur;
    while (cur != 0) {
        sum += cur;
        cin >> cur;
        n++;
    }

    if (n == 0) {
        cout << setprecision(5) << 0;
    }
    else {
        cout << setprecision(5) << sum * 1.0 / n;
    }
    return 0;
}
