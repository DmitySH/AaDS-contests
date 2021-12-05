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

int kraskal(int edges_count, Edge *edges, int *sizes, int *parents, bool *banned) {
    int total = 0;
    for (int index = 0; index < edges_count; ++index) {
        if (find(edges[index].first_vertex, parents, sizes) !=
            find(edges[index].second_vertex, parents, sizes)) {
            unite(edges[index].first_vertex, edges[index].second_vertex, parents, sizes);
            total += edges[index].weight;
            banned[index] = true;
        }
    }

    return total;
}

int kraskalBanned(int vertex_count, int edges_count, Edge *edges, int *sizes, int *parents,
                  int banned_index) {
    int total = 0;
    for (int index = 0; index < edges_count; ++index) {
        if (index == banned_index) {
            continue;
        }

        if (find(edges[index].first_vertex, parents, sizes) !=
            find(edges[index].second_vertex, parents, sizes)) {
            unite(edges[index].first_vertex, edges[index].second_vertex, parents, sizes);
            total += edges[index].weight;
        }
    }

    if (sizes[find(0, parents, sizes)] != vertex_count) {
        return INT32_MAX;
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
    int vertex_count, edges_count;
    std::cin >> vertex_count >> edges_count;

    Edge *edges = new Edge[edges_count];
    inputEdges(edges_count, edges);
    mergeSort(edges, 0, edges_count - 1);

    int *sizes = new int[vertex_count];
    int *parents = new int[vertex_count];

    for (int i = 0; i < vertex_count; ++i) {
        sizes[i] = 1;
        parents[i] = i;
    }

    bool *banned = new bool[edges_count];
    for (int i = 0; i < edges_count; ++i) {
        banned[i] = false;
    }

    int first_min = kraskal(edges_count, edges, sizes, parents, banned);
    int second_min = INT32_MAX;

    for (int j = 0; j < vertex_count; ++j) {
        sizes[j] = 1;
        parents[j] = j;
    }

    for (int index = 0; index < edges_count; ++index) {
        if (banned[index]) {
            int weight = kraskalBanned(vertex_count, edges_count, edges, sizes, parents, index);
            if (weight < second_min) {
                second_min = weight;
            }

            for (int j = 0; j < vertex_count; ++j) {
                sizes[j] = 1;
                parents[j] = j;
            }
        }
    }

    std::cout << first_min << " " << second_min;

    delete[] banned;
    delete[] edges;
    delete[] sizes;
    delete[] parents;
    return 0;
}
