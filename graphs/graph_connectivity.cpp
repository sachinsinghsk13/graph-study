#include "graph_connectivity.h"

static void dfs_component_count(graph &graph, int u, vector<bool> &visited);
static void dfs_component_mark(graph &graph, int u, vector<bool> &visited, int& count, vector<int>& marking);
static void dfs_cut_vertex(graph& graph, int u, vector<bool>& visited);
static bool dfs_check_reachability(graph& graph, int src, int dest, vector<bool>& visited);
static bool has_path(graph& graph, int src, int dest);

int count_component(graph &graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            dfs_component_count(graph, i, visited);
        }
    }
    return count;
}

static void dfs_component_count(graph &graph, int u, vector<bool> &visited) {
    visited[u] = true;
    for (auto neighbour : graph.at(u)) {
        int v = neighbour.first;
        if (!visited[v]) {
            dfs_component_count(graph, v, visited);
        }
    }   
}

vector<int> mark_component_no(graph &graph) {
    int n = graph.size();
    vector<bool> visited(n , false);
    vector<int> component_marking(n, -1);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            dfs_component_mark(graph, i, visited, count, component_marking);
        }
    }
    return component_marking;
}

static void dfs_component_mark(graph &graph, int u, vector<bool> &visited, int& count, vector<int>& marking) {
    visited[u] = true;
    marking[u] = count;
    for (auto neighbour : graph.at(u)) {
        int v = neighbour.first;
        if (!visited[v]) {
            dfs_component_mark(graph, v, visited, count, marking);
        }
    }
}



vector<int> find_articulation_points(graph& graph) {
    int n = graph.size();
    vector<int> result;
    for (int i = 0; i < n; i++) { // test each vertex i for articulation point
        vector<bool> visited(n , false);
        visited[i] = true; // mark the current vertex as visited.
        int components = 0;
        for (auto neighbour : graph.at(i)) {
            int v = neighbour.first;
            if (!visited[v]) {
                components++;
                if (components > 1) break;
                dfs_cut_vertex(graph, v, visited);
            }        
        }
        if (components > 1) {
            result.push_back(i);
        }
    }
    return result;
}

static void dfs_cut_vertex(graph& graph, int u, vector<bool>& visited) {
    visited[u] = true;
    for (auto neighbour: graph.at(u)) {
        int v = neighbour.first;
        if (!visited[v]) {
            dfs_cut_vertex(graph, v, visited);
        }
    }
}

vector<vector<int>> find_scc_brute_force(graph& graph) {
    int n = graph.size();
    vector<vector<int>> result;
    vector<bool> is_in_scc(n, false);

    // iterate all the vertices
    for (int i = 0; i < n; i++) {
        if (!is_in_scc[i]) {
            vector<int> scc;
            scc.push_back(i);
            is_in_scc[i] = true;
            for (int j = i + 1; j < n; j++) {
                if (!is_in_scc[j] && has_path(graph, i, j) && has_path(graph, j, i)) {
                    scc.push_back(j);
                    is_in_scc[j] = true;
                }
            }
            result.push_back(scc);
        }
    }
    return result;
}

static bool dfs_check_reachability(graph& graph, int src, int dest, vector<bool>& visited) {
    if (src == dest) return true;
    visited[src] = true;
    for (auto neighbour : graph.at(src)) {
        int v = neighbour.first;
        if (!visited[v]) {
            if (dfs_check_reachability(graph, v, dest, visited)) return true;
        }
    }
    return false;
}

static bool has_path(graph& graph, int src, int dest) {
    vector<bool> visited(graph.size(), false);
    return dfs_check_reachability(graph, src, dest, visited);
}