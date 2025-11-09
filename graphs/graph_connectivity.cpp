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

static void _dfs_finish_time(graph& g, int u, stack<pair<int, int>>& fin, vector<bool>& visited, int& time) {
    visited[u] = true;
    time = time + 1;
    // can be used to store discovery time here.
    for (auto neighbour : g.at(u)) {
        int v = neighbour.first;
        if (!visited[v]) {
            _dfs_finish_time(g, v, fin, visited, time);
        }
    }
    time = time + 1;
    fin.push({u, time});
}

static stack<pair<int, int>> dfs_finish_time(graph& g, int u) {
    stack<pair<int, int>> finish_time;
    vector<bool> visited(g.size(), false);
    int time = 0;
    for (int u = 0; u < g.size(); u++) {
        if (!visited[u]) {
            _dfs_finish_time(g, u, finish_time, visited, time);
        }
    }
    return finish_time;
}

static void dfs_collect_scc(graph& g, int u, vector<bool>& visited, vector<int>& scc) {
    visited[u] = true;
    scc.push_back(u);
    for (auto neighbour: g.at(u)) {
        int v = neighbour.first;
        if (!visited[v]) {
            dfs_collect_scc(g, v, visited, scc);
        }
    }
}

vector<vector<int>> find_scc_kosaraju(graph& graph) {
    int n = graph.size();
    vector<vector<int>> result;
    stack<pair<int, int>> fin = dfs_finish_time(graph, 0);
    vector<bool> visited(n, false);
    auto trn_graph = transpose(graph);
    while (!fin.empty()) {
        pair<int, int> top = fin.top();
        fin.pop();
        int u = top.first;
        int time = top.second;
        if (!visited[u]) {
            vector<int> scc;
            dfs_collect_scc(trn_graph, u, visited, scc);
            result.push_back(scc);
        }
    }   
    return result;
}

static void dfs_tarjans(graph& g, int u, vector<int>& disc, vector<int>& low, vector<bool>& visited, stack<int>& stack, vector<bool>& onStack, int& time) {
    visited[u] = true;
    disc[u] = ++time;
    low[u] = time;
    onStack[u] = true;
    stack.push(u);
    for (auto it: g.at(u)) {
        int v = it.first;
        if (!visited[v]) {
            dfs_tarjans(g, v, disc, low, visited, stack, onStack, time);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }
    onStack[u] = false;
    if (disc[u] == low[u]) {
        // only print the ssc for now.
        cout << "{ ";
        while (!stack.empty()) {
            int top = stack.top();
            cout << top << " ";
            stack.pop();
            if (top == u) {
                break;
            }
        }
        cout << " }" << endl;
    }
}

vector<vector<int>> find_scc_tarjans(graph& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> disc(n, -1), low(n, -1);
    vector<bool> onStack(n, false);
    stack<int> stack;
    vector<vector<int>> result;
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_tarjans(graph, i, disc, low, visited, stack, onStack, time);
        }
    }
    return result;
}

vector<edge> find_bridges_brute_force(graph& graph) {
    // convert adjacency list to edge list.
    vector<edge> edge_list = get_edge_list(graph, false);
    vector<edge> result;
    for (int i = 0; i < edge_list.size(); i++) {
        edge &e = edge_list.at(i);
        remove_edge(graph, e.source, e.destination);
        int count = count_component(graph);
        if (count > 1) {
            result.push_back(e);
        }
        add_edge(graph, e.source, e.destination);
    }
    return result;
}

static void dfs_find_bridges(graph& g,int u, vector<int>& parent, vector<int>& disc, vector<int>& low, vector<bool>& visited,vector<bool> inStack, int& time, vector<edge>& bridges) {
    visited[u] = true;
    disc[u] = ++time;
    low[u] = time;
    inStack[u] = true;
    for (pair<int, int>& it : g.at(u)) {
        int v = it.first;
        if (!visited[v]) {
            parent[v] = u;
            dfs_find_bridges(g, v, parent, disc, low, visited, inStack, time, bridges);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v] && parent[u] != v) {
            low[u] = min(low[u], disc[v]);
        }
        // check that if this edge u -> v is a bridge
        if (low[v] > disc[u]) {
            edge bridge = {u, v, it.second};
            bridges.push_back(bridge);
        }
    }
    inStack[u] = false;
}

vector<edge> find_bridges_tarjans(graph& graph) {
    int n = graph.size();
    vector<edge> result;
    vector<int> parent(n, -1), disc(n, 0), low(n, 0);
    vector<bool> visited(n, false);
    vector<bool> inStack(n, false);
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_find_bridges(graph, i, parent, disc, low, visited, inStack, time, result);
        }
    }
    return result;
}