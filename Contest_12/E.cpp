#include <iostream>
#include <set>

class SetWrapper {
public:
    SetWrapper() {
        set_ = new std::set<int>;
    }

    ~SetWrapper() {
        delete set_;
    }

    void add(int elem) {
        set_->insert(elem);
    }

    int next(int elem) {
        std::_Rb_tree_const_iterator<int> next_elem = set_->lower_bound(elem);
        if (next_elem == set_->end()) {
            return -1;
        }
        return *next_elem;
    }

private:
    std::set<int> *set_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number;
    std::cin >> number;

    SetWrapper my_set;

    char prev_operation = '+';
    int prev_result = 0;
    for (int index = 0; index < number; ++index) {
        char operation;
        int value;

        std::cin >> operation;
        std::cin >> value;

        if (operation == '+') {
            if (prev_operation == '+') {
                my_set.add(value);
            } else {
                my_set.add((value + prev_result) % 1000000000);
            }
            prev_operation = '+';
        } else {
            int res = my_set.next(value);
            std::cout << res << '\n';
            prev_operation = '?';
            prev_result = res;
        }

        prev_operation = operation;
    }

    return 0;
}
