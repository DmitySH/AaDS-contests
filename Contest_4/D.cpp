#include <iostream>
#include <string>

struct Timer {
 private:
    int64_t days, hours, minutes, seconds;

 public :

    explicit Timer(int64_t seconds) {
        days = seconds / 3600 / 24;
        hours = seconds / 3600 % 24;
        minutes = seconds % 3600 / 60;
        this->seconds = seconds % 3600 % 60;
    }

    void AddHours(int64_t additional_hours) {
        days += (additional_hours + hours) / 24;
        hours = (hours + additional_hours) % 24;
    }

    void AddMinutes(int64_t additional_minutes) {
        AddHours((additional_minutes + minutes) / 60);
        minutes = (minutes + additional_minutes) % 60;
    }

    void AddSeconds(int64_t additional_seconds) {
        AddMinutes((additional_seconds + seconds) / 60);
        seconds = (seconds + additional_seconds) % 60;
    }

    std::string ToStringTime() const {
        std::string result = std::to_string(hours / 10) + std::to_string(hours % 10)
                             + ':' + std::to_string(minutes / 10)
                             + std::to_string(minutes % 10) + ':'
                             + std::to_string(seconds / 10) +
                             std::to_string(seconds % 10);

        if (days != 0) {
            result += '+' + std::to_string(days) + " days";
        }

        return result;
    }
};

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
    int prev_pos;
    while (pos != -1) {
        ++syms_count;
        prev_pos = pos + 1;
        pos = str.find(sym, prev_pos);
    }

    return syms_count;
}

std::string CountTimer(const std::string &input_first, const std::string &input_second) {
    int64_t total_seconds = ((input_first[0] - '0') * 10 + (input_first[1] - '0')) * 3600 +
                            ((input_first[3] - '0') * 10 + (input_first[4] - '0')) * 60 +
                            ((input_first[6] - '0') * 10 + (input_first[7] - '0'));

    Timer timer(total_seconds);

    int number_of_nums = CountSymbols(input_second, ':') + 1;
    std::string *a = SplitString(input_second, ':', number_of_nums);

    switch (number_of_nums) {
        case 1:
            timer.AddSeconds(std::stoll(a[0]));
            break;
        case 2:
            timer.AddSeconds(std::stoll(a[1]));
            timer.AddMinutes(std::stoll(a[0]));
            break;
        case 3:
            timer.AddSeconds(std::stoll(a[2]));
            timer.AddMinutes(std::stoll(a[1]));
            timer.AddHours(std::stoll(a[0]));
            break;
        default:
            return "";
    }

    return timer.ToStringTime();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_first, input_second;
    std::cin >> input_first >> input_second;

    std::cout << CountTimer(input_first, input_second);

    return 0;
}
