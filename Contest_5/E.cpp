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
    int pos_front = next_string->find('[');
    int pos_rear = next_string->find_last_of(']');

    if (pos_front == -1) {
        return MultiplyString(*next_string, repeats);
    }

    std::string current_string_front = next_string->substr(0, pos_front - 1);

    std::string current_string_rear = next_string->substr(pos_rear + 1);

    int number = static_cast<int> (((*next_string)[pos_front - 1]) - '0');

    *next_string = next_string->substr(pos_front + 1,
                                     pos_rear - pos_front - 1);

    std::string new_string = current_string_front +
            UnZip(number, next_string) + current_string_rear;

    return MultiplyString(new_string, repeats);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string zipped_string;
    std::cin >> zipped_string;

    int pos_front = zipped_string.find('[');
    int pos_rear = zipped_string.find_last_of(']');

    int number = static_cast<int> (zipped_string[pos_front - 1] - '0');

    zipped_string = zipped_string.substr(pos_front + 1,
                                         pos_rear - pos_front - 1);

    std::cout << UnZip(number, &zipped_string);
    return 0;
}
