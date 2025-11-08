#include "spanning_tree.h"
#include "disjointset.h"


int kruskals_mst(graph &graph) {
    int n = graph.size();
    vector<edge> edges = get_edge_list(graph, false); // Convert adjacency list to edge list
    sort(edges.begin(), edges.end(), compare_edge); // sort the edges
    disjoint_set ds(n);
    int edge_count = 0;
    int total_weight = 0;
    for (size_t i = 0; i < edges.size() && edge_count < (n - 1); i++) {
        edge e = edges[i];
        if (!ds.in_same_set(e.source, e.destination)) {
            edge_count++;
            total_weight += e.weight;
            ds.make_union(e.source, e.destination);
            cout << "Including Edge (" << e.source << ", " << e.destination << ") of weight " << e.weight << endl;
        }
    }
    return total_weight;
}

int prims_mst(graph& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    priority_queue<edge, vector<edge>, CompareEdge> pq;
    pq.push({0, -1, 0});
    int sum = 0;
    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();

        if (visited[it.source]) continue;
        visited[it.source] = true;
        sum += it.weight;

        for (auto neighbour : graph.at(it.source)) {
            int dest = neighbour.first;
            int weight = neighbour.second;

            if (!visited[dest]) {
                pq.push({dest, -2, weight});
            }
        }
    }
    return sum;
}