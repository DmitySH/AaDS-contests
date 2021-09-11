#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

int calls = 0;

int gcd(int a, int b) {
    calls++;
    if (!b) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int cur_gcd = -1;
    std::string inp;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> inp;
        if (std::strchr(inp.c_str(), '.')) {
            cout << "Sequence has float values!";
            return 0;
        }
        else {
            int num = std::stoi(inp);
            if(cur_gcd == -1) {
                cur_gcd = num;
            }
            else {
                cur_gcd = gcd(num, cur_gcd);
            }
        }
    }

    cout << cur_gcd << " " << calls;

    return 0;
}