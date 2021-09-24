#include <iostream>
#include <string>

int CountSpaces(std::string &str) {
    int count = 0;
    for (const char sym : str) {
        if (sym == ' ') {
            ++count;
        }
    }

    return count;
}

void Split(std::string &str) {
    int spaces_count = 0;
    int pos = str.find(' ');
    int prev_pos = 0;
    while (pos != -1) {
        std::string word = str.substr(prev_pos, pos - prev_pos);
        std::cout << word << std::endl;
        prev_pos = pos + 1;
        pos = str.find(' ', prev_pos);
    }
    std::cout << str.substr(prev_pos, str.length() - prev_pos);
}

//std::string WhoDrives(std::string &rhyme, std::string &kids) {
//    int words_in_rhyme = CountSpaces(rhyme);
//    int kids_count = CountSpaces(kids);
//    int space_count = 0;
//    int res = words_in_rhyme % kids_count;
//    int i = 0;
//    while (space_count < res) {
//        if (kids[i] == ' ') {
//            ++space_count;
//        }
//    }
//    return ;
//}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string rhyme, kids;
    std::getline(std::cin, rhyme);
    std::getline(std::cin, kids);
    Split(rhyme);

    return 0;
}
