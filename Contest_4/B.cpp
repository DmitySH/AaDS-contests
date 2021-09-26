#include <iostream>
#include <string>

std::string MergeStrings(const std::string &str1, const std::string &str2) {
    std::string max_str = str1.length() > str2.length() ? str1 : str2;
    std::string min_str = str1 == max_str ? str2 : str1;

    for (int i = 0; i < min_str.length(); ++i) {
        if (min_str[i] == '+') {
            max_str[i] = '+';
        }
    }

    return max_str;
}

void CreateRow(std::string *prev_line2, int current_row, int total_rows) {
    int m;
    std::cin >> m;
    std::string line1, line2;
    int length_of_row = 0;

    for (int i = 0; i < m; ++i) {
        int a;
        std::cin >> a;

        line1 += '+';
        line2 += '|';
        ++length_of_row;
        for (int j = 0; j < a; ++j) {
            line1 += '-';
            line2 += ' ';
            ++length_of_row;
        }
    }
    line1 += '+';
    line2 += '|';
    ++length_of_row;

    std::string saved_line;
    if (current_row == total_rows - 1) {
        saved_line = line1;
    }

    for (char &sym : *prev_line2) {
        sym = sym == '|' ? '+' : '-';
    }
    line1 = MergeStrings(line1, *prev_line2);
    *prev_line2 = line2;

    std::cout << line1 << std::endl << line2 << std::endl;
    std::cout << saved_line;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string prev_line1;
    for (int i = 0; i < n; ++i) {
        CreateRow(&prev_line1, i, n);
    }

    return 0;
}
