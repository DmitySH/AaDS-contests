#include <iostream>
#include <string>

std::string MultiplyString(const std::string &str, int repeats) {
    std::string multiplied_string;

    for (int i = 0; i < repeats; ++i) {
        multiplied_string += str;
    }

    return multiplied_string;
}

std::string UnZip(int repeats, std::string *next_string) {
    std::string result;
    bool opened = false;
    for (int i = 0; i < next_string->length(); ++i) {
        if ((*next_string)[i] == '[') {
            opened = true;
            std::string next = next_string->substr(i + 1);
            result.pop_back();
            result += UnZip(static_cast<int> ((*next_string)[i - 1]) - '0', &next);
        } else if ((*next_string)[i] == ']') {
            opened = false;
            return MultiplyString(result, repeats);
        } else if (!opened) {
            result += (*next_string)[i];
        }
    }

    return MultiplyString(result, repeats);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string zipped_string;
    std::cin >> zipped_string;

    bool opened = false;
    std::string result;
    for (int i = 0; i < zipped_string.length(); ++i) {
        if (zipped_string[i] == '[' && !opened) {
            opened = true;
            std::string next = zipped_string.substr(i + 1);
            result.pop_back();
            result += UnZip(static_cast<int> (zipped_string[i - 1]) - '0', &next);
        } else if (zipped_string[i] == ']') {
            opened = false;
        } else if (!opened) {
            result += zipped_string[i];
        }
    }
    std::cout << result;
    return 0;
}
