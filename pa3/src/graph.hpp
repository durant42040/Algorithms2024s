#pragma once

#include <vector>
#include <map>

using namespace std;

struct Edge {
    int u, v;
    int weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class Graph {
public:
    map<int, map<int, int> > adj;
    char type;
    int V, E;
    vector<int> visited;
    vector<Edge> edges;
    vector<Edge> removed_edges;
    vector<Edge> MST_edges;

    void add_edge(int u, int v, int w);

    void sort_edges();

    bool dfs_visit(int v, int u);

    void insert_positive_edges();

    void Kruskal();

    bool cycle_detection();
};
