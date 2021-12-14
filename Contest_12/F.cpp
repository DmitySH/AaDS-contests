#include <iostream>
#include <map>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number, attempts;
    std::cin >> number >> attempts;

    std::map<std::string, int> solved_words;

    for (int i = 0; i < attempts; ++i) {
        int team_number;
        std::string word;
        std::cin >> team_number >> word;
        solved_words[word] = team_number;
    }

    int *team_solved = new int[number]{};
    for (auto &team : solved_words) {
        ++team_solved[team.second - 1];
    }

    for (int i = 0; i < number; ++i) {
        std::cout << team_solved[i] << ' ';
    }

    delete[] team_solved;
    return 0;
}
