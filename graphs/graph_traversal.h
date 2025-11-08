#ifndef __GRAPH_TRAVERSAL__
#define __GRAPH_TRAVERSAL__

#include "graph_core.h"

vector<int> graph_dfs(graph &graph, int start_vertex);
vector<int> graph_bfs(graph &graph, int start_vertex);


bool is_bipartite_graph(graph &graph);

#endif