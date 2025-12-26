#include <bits/stdc++.h>
#include <iostream>
#include "graphs/graph_problems.h"
using namespace std;

int main() {
	graph g = build_graph(5);
	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 0, 3);
	add_edge(g, 1, 2);
	add_edge(g, 3, 4);
	auto cg = complement(g);
	print_graph(cg);
	return 0;
}