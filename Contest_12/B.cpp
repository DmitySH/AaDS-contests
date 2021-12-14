#include <iostream>
#include <set>
#include <iomanip>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number;
    std::cin >> number;

    std::multiset<int> values;

    for (int i = 0; i < number; ++i) {
        int value;
        std::cin >> value;
        values.insert(value);
    }

    double total = 0;

    while (values.size() > 1) {
        std::_Rb_tree_const_iterator<int> min = (values.begin());
        std::_Rb_tree_const_iterator<int> second_min = (++values.begin());
        int sum = (*min + *second_min);
        total += sum * 0.05;
        values.erase(min, ++second_min);
        values.insert(sum);
    }
    std::cout << std::fixed << std::setprecision(2) << total;

    return 0;
}
