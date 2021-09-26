#include <iostream>
#include <string>

int pow(int num, int pow) {
    if (pow == 0) {
        return 1;
    }
    for (int i = 1; i < pow; ++i) {
        num *= num;
    }

    return num;
}

std::string *SplitString(const std::string &str, char sym, int n) {
    int pos = str.find(sym);
    int prev_pos = 0;
    auto *a = new std::string[n];

    for (int i = 0; i < n - 1; ++i) {
        pos = str.find(sym, prev_pos);

        a[i] = str.substr(prev_pos, pos - prev_pos);
        prev_pos = pos + 1;
    }
    a[n - 1] = str.substr(prev_pos, pos - prev_pos);

    return a;
}

int CountSymbols(const std::string &str, char sym) {
    int syms_count = 0;
    int pos = str.find(sym);
    int prev_pos = 0;
    while (pos != -1) {
        ++syms_count;
        prev_pos = pos + 1;
        pos = str.find(sym, prev_pos);
    }

    return syms_count;
}

std::string Timer(const std::string &input_first, const std::string &input_second) {
    int total_seconds = ((input_first[0] - '0') * 10 + (input_first[1] - '0')) * 3600 +
                          ((input_first[3] - '0') * 10 + (input_first[4] - '0')) * 60 +
                        ((input_first[6] - '0') * 10 + (input_first[7] - '0'));

    int number_of_nums = CountSymbols(input_second, ':') + 1;
    std::string *a = SplitString(input_second, ':', number_of_nums);

    int pow_number = 0;
    for (int i = number_of_nums - 1; i >= 0; --i) {
        total_seconds += std::stoi(a[i]) * pow(60, pow_number);
        ++pow_number;
    }

    int new_seconds, new_minutes, new_hours, days;

    days = total_seconds / 3600 / 24;
    new_hours = total_seconds / 3600 % 24;
    new_minutes = total_seconds % 3600 / 60;
    new_seconds = total_seconds % 3600 % 60;

    std::string result = std::to_string(new_hours / 10) + std::to_string(new_hours % 10)
                         + ':' + std::to_string(new_minutes / 10)
                         + std::to_string(new_minutes % 10) + ':'
                         + std::to_string(new_seconds / 10) +
                         std::to_string(new_seconds % 10);

    if (days != 0) {
        result += '+' + std::to_string(days) + " days";
    }

    return result;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_first, input_second;
    std::cin >> input_first >> input_second;

    std::cout << Timer(input_first, input_second);

    return 0;
}
