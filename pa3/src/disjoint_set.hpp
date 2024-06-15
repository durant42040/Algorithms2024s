#pragma once

#include <vector>

using namespace std;

class DisjointSet {
public:
    vector<int> parent;
    vector<int> rank;

    explicit DisjointSet(int x);

    int find(int x);

    void union_set(int x, int y);
};


