#include "graph.hpp"
#include "disjoint_set.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

void Graph::add_edge(int u, int v, int w) {
    adj[u][v] = w;
    edges.emplace_back(u, v, w);
}

void Graph::sort_edges() {
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    });
}

bool Graph::dfs_visit(int v, int u) {
    visited[v] = 1;
    for (const auto &i: adj[v]) {
        if (i.first == u) {
            return true;
        }
        if (visited[i.first] == 0) {
            if (dfs_visit(i.first, u)) {
                return true;
            }
        }
    }
    return false;
}

void Graph::insert_positive_edges() {
    for(int i = 0; removed_edges[i].weight > 0 && i < removed_edges.size(); i++){
        visited = vector<int>(V, 0);
        int u = removed_edges[i].u;
        int v = removed_edges[i].v;
        int w = removed_edges[i].weight;

        if(!dfs_visit(v, u)) {
            adj[u][v] = w;
            edges.emplace_back(u, v, w);
            removed_edges.erase(removed_edges.begin() + i);
            i--;
        }
    }

}

void Graph::Kruskal() {
    DisjointSet MST = DisjointSet(V);
    for (int i = edges.size() - 1; i >= 0; i--) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (MST.find(u) != MST.find(v)) {	
            MST.union_set(u, v);
        } else {
            removed_edges.emplace_back(u, v, w);
            edges.erase(edges.begin() + i);
            adj[u].erase(v);
        }
    }
}

bool Graph::cycle_detection() {
    for (int i = 0; i < V; i++) {
        visited = vector<int>(V, 0);

        if (dfs_visit(i, i)) {
            return true;
        }
    }
    return false;
}



