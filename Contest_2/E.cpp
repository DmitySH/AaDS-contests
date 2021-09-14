#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str1, str2, order, prev_order, temp_str;
    std::cin >> str1 >> str2;
    int m, n, temp_len;
    int cur = 2;
    order = "2";
    prev_order = "1";
    std::cin >> n >> m;
    m--;
    int len1 = str1.length(), len2 = str2.length();
    int cur_len = len1, prev_len = len2;

    // Вообще, так как ордер всегда один и тот же получается,
    // можно добиться O(1) по памяти, если изначально хранить строку из порядка строк в памяти.

    while (cur != n && cur_len <= m + 1) {
        temp_str = order;
        temp_len = cur_len;
        cur_len += prev_len;
        prev_len = temp_len;
        order = prev_order.append(order);
        prev_order = temp_str;
        cur++;
    }

    int i = 0;
    while (m >= 0) {
        if (order[i] == '1') {
            m -= len1;
        }
        else {
            m -= len2;
        }
        i++;
    }
    if (order[--i] == '1') {
        std::cout << str1[len1 + m] << std::endl;
    }
    else {
        std::cout << str2[len2 + m] << std::endl;
    }

    return 0;
}