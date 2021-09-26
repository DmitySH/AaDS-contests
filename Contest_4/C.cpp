#include <iostream>
#include <string>

int CountWords(const std::string &str) {
    int words_count = 0;
    int pos = str.find(' ');
    int prev_pos = 0;
    while (pos != -1) {
        ++words_count;
        prev_pos = pos + 1;
        pos = str.find(' ', prev_pos);
    }

    return ++words_count;
}

std::string SplitString(const std::string &str, int number) {
    int pos = str.find(' ');
    int prev_pos = 0;
    for (int j = 0; j < number; ++j) {
        prev_pos = pos + 1;
        pos = str.find(' ', prev_pos);
    }

    return str.substr(prev_pos, pos - prev_pos);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string rhyme, kids;
    std::getline(std::cin, rhyme);
    std::getline(std::cin, kids);

    int number_of_word = (CountWords(rhyme) - 1) % CountWords(kids);
    std::cout << SplitString(kids, number_of_word);

    return 0;
}
