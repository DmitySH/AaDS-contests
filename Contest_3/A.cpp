#include <iostream>
#include <vector>
#include <utility>
#include <map>

void shift(int *vec, int n) {
    int last = vec[n - 1];
    for (int i = n - 1; i > 0; --i) {
        vec[i] = vec[i - 1];
    }
    vec[0] = last;
}

int find_hamming(const int *first_array, std::vector<int> other_vector, int n) {
    int delta = 0;
    for (int i = 0; i < n; ++i) {
        if (first_array[i] != other_vector[i]) {
            ++delta;
        }
    }

    return delta;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    int *a = new int[n];
    std::map<std::vector<int>, std::pair<int, int>> unique_vectors;
    std::vector<int> vec(n);

    for (int i = 0; i < n; ++i) {
        int elem;
        std::cin >> elem;
        a[i] = elem;
        vec[i] = elem;
    }

    unique_vectors.insert(std::make_pair(vec, std::make_pair(0, 0)));

    int max_delta = 0;
    shift(&vec[0], n);

    for (int i = 1; i < n; ++i) {
        int delta = find_hamming(a, vec, n);
        if (delta > max_delta) {
            max_delta = delta;
        }
        if (unique_vectors.count(vec) != 1) {
            unique_vectors.insert(std::make_pair(vec, std::make_pair(delta, i)));
        }
        shift(&vec[0], n);
    }
    std::cout << max_delta << std::endl;
    for (const auto &v : unique_vectors) {
        if (v.second.first == max_delta) {
            for (int i = 0; i < n; ++i) {
                std::cout << v.first[i];
                if (i != n - 1) {
                    std::cout << ' ';
                } else {
                    std::cout << "; " << v.second.second;
                }
            }
            std::cout << '\n';
        }
    }
    return 0;
}
