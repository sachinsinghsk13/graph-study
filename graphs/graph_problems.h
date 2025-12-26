#ifndef __GRAPH_PROBLEMS__
#define __GRAPH_PROBLEMS__
#include "graph_core.h"

bool is_bipartite_graph(const graph& g) {
    int n = g.size();
    vector<bool> visited(n, false);
    vector<char> node_color(n, '\0');
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (!is_bipartite_graph_util(g, i, visited, node_color)) return false;
        }
    }
   return true;
}

bool is_bipartite_graph_util(const graph& g, int x, vector<bool>& visited, vector<char>& node_color) {
    queue<pair<int, char>> q;
    q.push({x, 'W'});
    visited[x] = true;
    node_color[x] = 'W';

    while (!q.empty()) {
        int u = q.front().first;
        char color = q.front().second;
        q.pop();

        for (auto neighbor: g[u]) {
            int v = neighbor.first;
            if (!visited[v]) {
                visited[v] = true;
                char c = color == 'W' ? 'B' : 'W';
                q.push({v, c});
                node_color[v] = c;
            } else if (color == node_color[v]) {
                return false;
            } 
        }

    }
    return true;
}
#endif