#include <bits/stdc++.h>
#include <iostream>
#include "graphs/graph.h"
#include "graphs/disjointset.h"
#include <cmath>
using namespace std;

int main() {
	graph g(7);
	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 2, 3);
	add_edge(g, 3, 4);
	add_edge(g, 3, 5);
	add_edge(g, 3, 6);

	vector<int> x = find_articulation_points_tarjans(g);
	for (int& i: x) {
		cout << i << " " << endl;
	}
	return 0;
}