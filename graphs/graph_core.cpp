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

graph transpose(graph& original_graph) {
    int n = original_graph.size();
    auto transpose_graph = build_graph(n);
    for (int i = 0; i < n; i++) {
        for (auto neighbour : original_graph.at(i)) {
            int v = neighbour.first;
            int w = neighbour.second;
            add_edge(transpose_graph, v, i,w, true);
        }
    }
    return transpose_graph;
}


void remove_edge(graph& graph, int src, int dest) {
    remove_edge(graph, src, dest, false);
}

void remove_edge(graph& graph, int src, int dest, bool directed) {
    vector<pair<int, int>>& src_list = graph.at(src);
    auto it = find_if(src_list.begin(), src_list.end(), [dest](const pair<int, int>& p) {
        return p.first == dest;
    });
    if (it != src_list.end()) {
        src_list.erase(it);
    }

    if (!directed) {
        vector<pair<int, int>>& dest_list = graph.at(dest);
        auto it = find_if(dest_list.begin(), dest_list.end(), [src](const pair<int, int>& p) {
            return p.first == src;
        });
        if (it != dest_list.end()) {
            dest_list.erase(it);
        }
    }
}