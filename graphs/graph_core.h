#ifndef __GRAPH_CORE__
#define __GRAPH_CORE__

#include <bits/stdc++.h>
using namespace std;
/**
 * An weighted graph edge.
 */
typedef struct edge {
    int source;
    int destination;
    int weight;
} edge;

/**
 * Comparator to compare the edges by their weight.
 */
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

/**
 * Convert a adjacency list to lit of edge structs
 */
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

#endif