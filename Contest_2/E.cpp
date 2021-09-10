#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str1, str2, res, temp;
    std::cin >> str1 >> str2;
    int m, n;
    int cur = 2;
    std::cin >> n >> m;

    while (cur != n && str2.length() <= m) {
        temp = str2;
        str2 = str1 + str2;
        str1 = temp;
        cur++;
    }

    std::cout << str2[m - 1];
    return 0;
}