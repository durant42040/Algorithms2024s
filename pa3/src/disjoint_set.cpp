#include "disjoint_set.hpp"

DisjointSet::DisjointSet(int x) {
    parent = vector<int>(x);
    rank = vector<int>(x);
    for (int i = 0; i < x; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int DisjointSet::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void DisjointSet::union_set(int x, int y) {
    int x_root = find(x);
    int y_root = find(y);

    if (x_root != y_root) {
        if (rank[x_root] < rank[y_root]) {
            parent[x_root] = y_root;
        } else if (rank[x_root] > rank[y_root]) {
            parent[y_root] = x_root;
        } else {
            parent[y_root] = x_root;
            rank[x_root]++;
        }
    }
}
