#include <iostream>

using namespace std;

void cycle(int n, int cur_n){
    int num;
    cin >> num;
    if (cur_n != n){
        cycle(n, cur_n + 1);
    }
    cout << num << " ";
}

int main() {
    int n;
    cin >> n;
    cycle(n, 1);
    return 0;
}
