#ifndef __GRAPH_CONNECTIVITY__
#define __GRAPH_CONNECTIVITY__
#include "graph_core.h"

vector<vector<int>> find_scc_brute_force(graph& graph);
vector<int> find_articulation_points(graph& graph);
int count_component(graph &graph);
vector<int> mark_component_no(graph &graph);

#endif