#include <iostream>
#include <fstream>
#include <vector>
#include "graph.hpp"

using namespace std;

string in_path;
string ou_path;


int main(int argc, const char *argv[]) {
    // input handling
    ifstream ifs;

    if (argc > 1) in_path = argv[1];
    if (argc > 2) ou_path = argv[2];

    ifs.open(in_path);

    // read graph
    Graph G;
    ifs >> G.type >> G.V >> G.E;
    G.edges = vector<Edge>();

    int u, v, w;
    for (int i = 0; i < G.E; i++) {
        ifs >> u >> v >> w;
        G.add_edge(u, v, w);
    }
    G.sort_edges();

    // find MST
    if (G.type == 'd') {
        G.Kruskal();
        G.insert_positive_edges();
//        G.cycle_detection();
    } else {
        G.Kruskal();
    }


    ofstream ofs;
    ofs.open(ou_path);

    int weight = 0;
    for (auto & removed_edge : G.removed_edges) {
        weight += removed_edge.weight;
    }
    ofs << weight << endl;

    for (auto & removed_edge : G.removed_edges) {
        ofs << removed_edge.u << " " << removed_edge.v << " " << removed_edge.weight << endl;
    }
}
