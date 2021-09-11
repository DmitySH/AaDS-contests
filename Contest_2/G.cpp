#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

long long gcd(long long a, long long b) {
    if (!b) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    long long cur_lcm = -1;
    std::string inp;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> inp;
        if (std::strchr(inp.c_str(), '.')) {
            cout << "Sequence has float values!";
            return 0;
        } else {
            int num = std::stoi(inp);
            if (cur_lcm == -1) {
                cur_lcm = num;
            } else {
                cur_lcm = lcm(num, cur_lcm);
            }
        }
    }

    cout << std::abs(cur_lcm);

    return 0;
}