#include "cycle_detection.h"

static bool check_cycle(graph &graph, int u, vector<bool> &visited, int parent);

bool has_cycle_undirected_bfs(graph &graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<int> q;

    parent[0] = -1;
    visited[0] = true;
    q.push(0);

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto neighbour : graph.at(u)) {
            int v = neighbour.first;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            } else if (parent[u] != v) {
                return true;
            }
        }
    }
    return false;
}

bool has_cycle_undirected_dfs(graph &graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    return check_cycle(graph, 0, visited, -1);
}

static bool check_cycle(graph &graph, int u, vector<bool> &visited, int parent) {
    visited[u] = true;
    for (auto neighbour : graph.at(u)) {
        int v = neighbour.first;
        if (!visited[v]) {
            bool r = check_cycle(graph, v, visited, u);
            if (r) return true;
        } else if (v != parent) return true;
    }
    return false;
}
