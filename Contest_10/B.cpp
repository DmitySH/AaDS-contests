#include <iostream>

void inputBridges(int mumber, int number, int *sizes, int *parents);
int find(int vertex, int *parent, int *sizes) {
    if (vertex == parent[vertex]) {
        return vertex;
    }
    parent[vertex] = find(parent[vertex], parent, sizes);
    return parent[vertex];
}

bool unite(int first_vertex, int second_vertex, int *parent, int *sizes, int number) {
    int first_leader, second_leader;

    first_leader = find(first_vertex, parent, sizes);
    second_leader = find(second_vertex, parent, sizes);

    if (first_leader == second_leader) {
        return false;
    }

    if (sizes[first_leader] > sizes[second_leader]) {
        parent[second_leader] = parent[first_leader];
        sizes[first_leader] += sizes[second_leader];
    } else {
        parent[first_leader] = parent[second_leader];
        sizes[second_leader] += sizes[first_leader];
    }

    if (sizes[first_leader] == number || sizes[second_leader] == number) {
        return true;
    }
    return false;
}

void inputBridges(int mumber, int number, int *sizes, int *parents) {
    for (int i = 0; i < mumber; ++i) {
        int xix, ygryk;
        std::cin >> xix >> ygryk;
        if (unite(xix, ygryk, parents, sizes, number)) {
            std::cout << i + 1;
            delete[] parents;
            delete[] sizes;
            break;
        }
    }
}

int main() {
    int mumber, number;
    std::cin >> number >> mumber;

    int *sizes = new int[number];
    int *parents = new int[number];

    for (int i = 0; i < number; ++i) {
        sizes[i] = 1;
        parents[i] = i;
    }

    if (number == 1) {
        std::cout << 0;
        return 0;
    }

    inputBridges(mumber, number, sizes, parents);

    return 0;
}
