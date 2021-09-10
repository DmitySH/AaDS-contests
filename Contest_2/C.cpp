#include <iostream>

const int LeftBigLetter = (int)'A';
const int RightBigLetter = (int)'Z';
const int LeftLetter = (int)'a';
const int RightLetter = (int)'z';
const int LeftNum = (int)'0';
const int RightNum = (int)'9';

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string password;
    std::cin >> password;

    bool flags[3] = {false, false, false};

    if (password.length() < 8) {
        std::cout << "NO";
        return 0;
    }

    for (char sym : password) {
        if (!flags[0] && sym >= LeftBigLetter && sym <= RightBigLetter) {
            flags[0] = true;
        }
        if (!flags[1] && sym >= LeftLetter && sym <= RightLetter) {
            flags[1] = true;
        }
        if (!flags[2] && sym >= LeftNum && sym <= RightNum) {
            flags[2] = true;
        }
    }

    std::cout << ((flags[0] && flags[1] && flags[2])? "YES" : "NO");

    return 0;
}