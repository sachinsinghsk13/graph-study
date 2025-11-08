#include "shortest_paths.h"


vector<int> dijkstra_sssp(graph &graph, int source_node) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source_node}); // distance to source node is zero
    dist[source_node] = 0;

    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        if (p.first > dist[p.second]) continue;
        for (pair<int, int> neighbour : graph.at(p.second)) {
            int len = p.first + neighbour.second;
            if (len < dist[neighbour.first]) {
                dist[neighbour.first] = len;
                pq.push({len, neighbour.first});
            }
        }
    }
    return dist;
}

vector<int> bellman_ford_sssp(graph &graph, int source) {
    int n = graph.size(); // total vertices
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    dist[source] = 0;
    int relaxations = 0;
    while (!pq.empty()) {
        int vertex = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        for (pair<int, int> neighbour : graph.at(vertex)) {
            int d = distance + neighbour.second;
            if (d < dist[neighbour.first]) {
                pq.push({d, neighbour.first});
                dist[neighbour.first] = d;
                relaxations++;

                if (relaxations == n) {
                    // graph has negative edge cycle
                    cout << "Graph has negative edge cycle. aborting process" << endl;
                    return dist;
                }
            }
        }
    }
    return dist;
}

vector<vector<int>> floyd_warshall_apsp(graph &graph) {
    int v = graph.size();
    vector<vector<int>> dist(v, vector<int>(v, INT_MAX));

    // Distance from a node to itself is zero
    for (int i = 0; i < v; i++) dist[i][i] = 0;

    // Initialize with direct edges
    for (int i = 0; i < v; i++) {
        for (auto &n : graph[i]) {
            dist[i][n.first] = n.second;
        }
    }

    // Floyd-Warshall main logic
    for (int k = 0; k < v; k++) {
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return dist;
}