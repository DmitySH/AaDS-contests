#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    int total = 0;
    std::cin >> n >> m;
    int parties[n];
    for (int i = 0; i < n; ++i) {
        parties[i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int plus_count = 0;
        int party;
        for (int j = 0; j < n; ++j) {
            char res;
            std::cin >> res;
            if (res == '+') {
                plus_count++;
                party = j;
            }
        }
        if (plus_count == 1) {
            total++;
            parties[party] += 1;
        }
    }
    for(int i = 0; i < n; ++i) {
        if (parties[i]*1.0 / total >= 0.07 ) {
            std::cout << i + 1 << ' ';
        }
    }

    return 0;
}