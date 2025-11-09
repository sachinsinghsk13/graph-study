#include <bits/stdc++.h>
#include <iostream>
#include "graphs/graph.h"
#include "graphs/disjointset.h"
#include <cmath>
using namespace std;

int main() {
	graph g(5);
	add_edge(g, 0, 1);
	add_edge(g, 1, 2);
	add_edge(g, 2, 0);
	add_edge(g, 0, 3);
	add_edge(g, 3, 4);
	vector<edge> x = find_bridges_tarjans(g);
	for (edge& i: x) {
		cout << i.source << " -> " << i.destination << endl;
	}
	return 0;
}