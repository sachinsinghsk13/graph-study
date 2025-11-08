#ifndef __GRAPH_TRAVERSAL__
#define __GRAPH_TRAVERSAL__
#include "graph_core.h"

vector<int> dijkstra_sssp(graph &graph, int source_node);
vector<int> bellman_ford_sssp(graph &graph, int source);
vector<vector<int>> floyd_warshall_apsp(graph &graph);

#endif