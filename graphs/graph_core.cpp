#include "graph_core.h"

bool compare_edge(const edge &a, const edge &b) {
    return a.weight < b.weight;
}

vector<edge> get_edge_list(graph& g, bool directed) {
    vector<edge> edges;
    
    int n = g.size();

    for(int u = 0; u < n; u++) {
        for(auto &p : g[u]) {
            int v = p.first;
            int w = p.second;

            // To avoid duplication in an undirected graph
            if(!directed && u < v) {
                edges.push_back({u, v, w});
            }
        }
    }
    return edges;
}

graph build_graph(int n) {
    return vector<vector<pair<int, int>>>(n, vector<pair<int, int>>());
}


void add_edge(graph &graph, int src, int dest) {
    add_edge(graph, src, dest, DEFAULT_WEIGHT, false);
}


void add_edge(graph &graph, int src, int dest, int weight) {
    add_edge(graph, src, dest, weight, false);
}


void add_edge(graph &graph, int src, int dest, bool directed) {
    add_edge(graph, src, dest, DEFAULT_WEIGHT, directed);
}

void add_edge(graph &graph, int src, int dest, int weight, bool directed) {
    graph.at(src).push_back({dest, weight});
    if (!directed) {
        graph.at(dest).push_back({src, weight});
    }
}

void print_graph(graph &graph) {
    for (size_t i = 0; i < graph.size(); i++) {
        cout << i << ": ";
        for (pair<int, int> neighbor : graph[i])
            cout << neighbor.first << "(" << neighbor.second << ")";
        cout << endl;
    }
}