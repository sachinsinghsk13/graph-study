#include "graph.h"
#include <cmath>
using namespace std;

// private function declations
static void dfs(graph &graph, int u, int &time,vector<int> &d, vector<int> &f, vector<int> &p, vector<bool> &visited);
static bool check_cycle(graph &graph, int u, vector<bool> &visited, int parent);
static void dfs_component_count(graph &graph, int u, vector<bool> &visited);
static void dfs_component_mark(graph &graph, int u, vector<bool> &visited, int& count, vector<int>& marking);
static void dfs_cut_vertex(graph& graph, int u, vector<bool>& visited);
static bool dfs_check_reachability(graph& graph, int src, int dest, vector<bool>& visited);
static bool has_path(graph& graph, int src, int dest);

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

vector<int> graph_dfs(graph &graph, int start_vertex) {
    int n = graph.size(); // total nodes
    vector<int> result;
    vector<bool> visited(n, false);
    stack<int> stack;
    stack.push(start_vertex);
    visited[start_vertex] = true;

    while (!stack.empty()) {
        int x = stack.top();
        stack.pop();
        result.push_back(x);
        for (pair<int, int> neighbour : graph[x]) {
            if (!visited[neighbour.first]) {
                stack.push(neighbour.first);
                visited[neighbour.first] = true;
            }
        }
    }
    return result;
}

vector<int> graph_bfs(graph &graph, int start_vertex) {
    int n = graph.size(); // total nodes
    vector<int> result;
    vector<bool> visited(n, false);
    queue<int> queue;
    queue.push(start_vertex);
    visited[start_vertex] = true;

    while (!queue.empty()) {
        int x = queue.front();
        queue.pop();
        result.push_back(x);
        for (pair<int, int> neighbour : graph[x]) {
            if (!visited[neighbour.first]) {
                queue.push(neighbour.first);
                visited[neighbour.first] = true;
            }
        }
    }
    return result;
}

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


pair<vector<int>, vector<int>> dfs_visit(graph &graph) {
    int n = graph.size();
    vector<int> d(n, 0), f(n, 0), parent(n, 0);
    int time = 0;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(graph, i, time, d, f, parent, visited);
        }
    }

    return {d, f};
}

static void dfs(graph &graph, int u, int &time,vector<int> &d, vector<int> &f, vector<int> &p, vector<bool> &visited) {
    visited[u] = true;
    d[u] = time;
    for (pair<int, int> neighbour : graph.at(u)) {
        int v = neighbour.first;
        if (!visited[v]) {
            p[v] = u;
            dfs(graph, v, time, d, f, p, visited);
        }
    }
    time = time + 1;
    f[u] = time;
}


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

bool has_cycle_directed(graph &graph) {
    return true;
}

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

bool is_bipartite_graph(graph &graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    /*
        W => not colored, B = colored black, R = colored Red.
    */
    vector<char> color(n, 'W');
    stack<int> stack;

    // start with zero
    stack.push(0);
    visited[0] = true;
    color[0] = 'B'; // start with black color.

    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        for (auto neighbour : graph.at(u)) {
            int v = neighbour.first;
            if (!visited[v]) {
                visited[v] = true;
                stack.push(v);
                color[v] = color[u] == 'R' ? 'B' : 'R';
            } else if (color[u] == color[v]) return false; // Adjacent nodes are having same color. So for sure this is not a bipartite graph.
        }
    }
    return true;
}


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