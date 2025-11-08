#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <bits/stdc++.h>
#include "disjointset.h"
using namespace std;

typedef struct edge {
    int source;
    int destination;
    int weight;
} edge;


struct CompareEdge {
    bool operator()(const edge &a, const edge &b) const {
        return a.weight > b.weight;
    }
};

bool compare_edge(const edge &a, const edge &b);
/**
 * Defined a adjacency list for graph. pair's first element represents the destination node and second element
 * represents the weight to reach that destination.
 */
typedef vector<vector<pair<int, int>>> graph;

const int DEFAULT_WEIGHT = 1;

vector<edge> get_edge_list(graph& graph, bool directed);

// build the graph adjacency list
graph build_graph(int n);

/* functions to add different types of edges into the graph */

/**
 * Adds an unweighted undirected edge
 */
void add_edge(graph &graph, int src, int dest);

/**
 * Adds an weighted undirected edge
 */
void add_edge(graph &graph, int src, int dest, int weight);

/**
 * Adds an directed/undirected edge based on directed parameter
 */
void add_edge(graph &graph, int src, int dest, bool directed);



/**
 * Adds an weighted edge directed or undirected based on directed parameter
 */
void add_edge(graph &graph, int src, int dest, int weight, bool directed);

// Visualize the graph
void print_graph(graph &graph);

// Traverse the graph
vector<int> graph_dfs(graph &graph, int start_vertex);
vector<int> graph_bfs(graph &graph, int start_vertex);

pair<vector<int>, vector<int>> dfs_visit(graph &graph);

// shortest path algorithm
vector<int> dijkstra_sssp(graph &graph, int source_node);
vector<int> bellman_ford_sssp(graph &graph, int source);
vector<vector<int>> floyd_warshall_apsp(graph &graph);


// Cycle Detection Algorithms
bool has_cycle_undirected_bfs(graph &graph);
bool has_cycle_undirected_dfs(graph &graph);
bool has_cycle_directed(graph &graph);

// components identification in graph
int count_component(graph &graph);
vector<int> mark_component_no(graph &graph);

// Bipartite Graph Check
bool is_bipartite_graph(graph &graph);

// Minimum Spanning Tree
int kruskals_mst(graph& graph);
int prims_mst(graph& graph);

// Graph Connectivity
vector<vector<int>> find_scc_brute_force(graph& graph);
vector<int> find_articulation_points(graph& graph);

#endif // __GRAPH_H__