#include <iostream>

struct Edge {
    int first_vertex;
    int second_vertex;
    int weight;

    bool operator<=(Edge const &other) const {
        return weight <= other.weight;
    }
};

void merge(Edge *ar, int left, int mid, int right) {
    Edge *left_ar = new Edge[mid - left + 1];
    Edge *right_ar = new Edge[right - mid];

    int left_number = mid - left + 1;
    int right_number = right - mid;

    for (int i = 0; i < left_number; ++i) {
        left_ar[i] = ar[left + i];
    }

    for (int i = 0; i < right_number; ++i) {
        right_ar[i] = ar[mid + 1 + i];
    }

    int first_index = 0;
    int second_index = 0;
    int merged_index = left;

    while (first_index < left_number && second_index < right_number) {
        if (left_ar[first_index] <= right_ar[second_index]) {
            ar[merged_index] = left_ar[first_index];
            ++first_index;
        } else {
            ar[merged_index] = right_ar[second_index];
            ++second_index;
        }
        ++merged_index;
    }

    while (first_index < left_number) {
        ar[merged_index] = left_ar[first_index];
        ++first_index;
        ++merged_index;
    }

    while (second_index < right_number) {
        ar[merged_index] = right_ar[second_index];
        ++second_index;
        ++merged_index;
    }

    delete[] left_ar;
    delete[] right_ar;
}

void mergeSort(Edge *ar, int begin, int end) {
    if (begin >= end) {
        return;
    }

    int mid = begin + (end - begin) / 2;
    mergeSort(ar, begin, mid);
    mergeSort(ar, mid + 1, end);
    merge(ar, begin, mid, end);
}

int find(int vertex, int *parent, int *sizes) {
    if (vertex == parent[vertex]) {
        return vertex;
    }
    parent[vertex] = find(parent[vertex], parent, sizes);
    return parent[vertex];
}

void unite(int first_vertex, int second_vertex, int *parent, int *sizes) {
    int first_leader, second_leader;

    first_leader = find(first_vertex, parent, sizes);
    second_leader = find(second_vertex, parent, sizes);

    if (sizes[first_leader] > sizes[second_leader]) {
        parent[second_leader] = parent[first_leader];
        sizes[first_leader] += sizes[second_leader];
    } else {
        parent[first_leader] = parent[second_leader];
        sizes[second_leader] += sizes[first_leader];
    }
}

int kraskal(int number, int mumber, const Edge *edges, int *sizes, int *parents, int total) {
    for (int i = 0; i < mumber; ++i) {
        if (find(edges[i].first_vertex, parents, sizes) !=
            find(edges[i].second_vertex, parents, sizes)) {
            unite(edges[i].first_vertex, edges[i].second_vertex, parents, sizes);
            total += edges[i].weight;
        }
        if (sizes[edges[i].first_vertex] == number || sizes[edges[i].second_vertex] == number) {
            break;
        }
    }
    return total;
}

void inputEdges(int mumber, Edge *edges) {
    for (int i = 0; i < mumber; ++i) {
        int first_vertex;
        int second_vertex;
        int weight;
        std::cin >> first_vertex >> second_vertex >> weight;
        edges[i] = Edge{first_vertex - 1, second_vertex - 1, weight};
    }
}

int main() {
    int number, mumber;
    std::cin >> number >> mumber;

    Edge *edges = new Edge[mumber];
    inputEdges(mumber, edges);
    mergeSort(edges, 0, mumber - 1);

    int *sizes = new int[number];
    int *parents = new int[number];

    for (int i = 0; i < number; ++i) {
        sizes[i] = 1;
        parents[i] = i;
    }

    int total = 0;
    total = kraskal(number, mumber, edges, sizes, parents, total);
    std::cout << total;

    delete[] edges;
    delete[] sizes;
    delete[] parents;
    return 0;
}
