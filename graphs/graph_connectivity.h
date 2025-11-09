#ifndef __GRAPH_CONNECTIVITY__
#define __GRAPH_CONNECTIVITY__
#include "graph_core.h"

vector<vector<int>> find_scc_brute_force(graph& graph);
vector<vector<int>> find_scc_kosaraju(graph& graph);
vector<vector<int>> find_scc_tarjans(graph& graph);
vector<int> find_articulation_points(graph& graph);
vector<int> find_articulation_points_tarjans(graph& graph);
vector<edge> find_bridges_brute_force(graph& graph);
vector<edge> find_bridges_tarjans(graph& graph);
int count_component(graph &graph);
vector<int> mark_component_no(graph &graph);

#endif