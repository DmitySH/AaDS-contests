#include <iostream>
#include <string>

std::string MergeStrings(const std::string &cur_str, const std::string &prev_str) {
    int max_str_length = cur_str.length() > prev_str.length() ?
                         cur_str.length() : prev_str.length();

    std::string new_str;
    for (int i = 0; i < max_str_length; ++i) {
        if (i < cur_str.length() && cur_str[i] == '|'
            || i < prev_str.length() && prev_str[i] == '|') {
            new_str += '+';
        } else {
            new_str += '-';
        }
    }

    return new_str;
}

std::string CreateRow(std::string *prev_line2, int current_row, int total_rows) {
    int m;
    std::cin >> m;
    std::string line1, line2;
    int length_of_row = 0;

    for (int i = 0; i < m; ++i) {
        int a;
        std::cin >> a;

        line1 += '+';
        line2 += '|';

        line1 += std::string(a, '-');
        line2 += std::string(a, ' ');
        length_of_row += a;
    }

    line1 += '+';
    line2 += '|';
    ++length_of_row;

    std::string saved_line;
    if (current_row == total_rows - 1) {
        saved_line = line1;
    }

    line1 = MergeStrings(line2, *prev_line2);
    *prev_line2 = line2;

    return line1 + '\n' + line2 + '\n' + saved_line;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::string prev_line2;
    for (int i = 0; i < n; ++i) {
        std::cout << CreateRow(&prev_line2, i, n);
    }

    return 0;
}
