#include <iostream>
#include <queue>

void inputCards(std::queue<int> *player) {
    for (int i = 0; i < 5; ++i) {
        int elem;
        std::cin >> elem;
        player->push(elem);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::queue<int> first;
    std::queue<int> second;

    inputCards(&first);
    inputCards(&second);

    for (int index = 0; index < 1000000; ++index) {
        int first_card = first.front();
        int second_card = second.front();
        first.pop();
        second.pop();

        if ((first_card > second_card || first_card == 0 && second_card == 9) &&
            !(first_card == 9 && second_card == 0)) {
            first.push(first_card);
            first.push(second_card);
        } else {
            second.push(first_card);
            second.push(second_card);
        }

        if (first.empty()) {
            std::cout << "second " << ++index;
            return 0;
        }
        if (second.empty()) {
            std::cout << "first " << ++index;
            return 0;
        }
    }

    std::cout << "botva";

    return 0;
}