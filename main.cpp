#include <bits/stdc++.h>
#include <iostream>
#include "graphs/graph.h"
#include "graphs/disjointset.h"
#include <cmath>
using namespace std;

int main() {
	graph g(6);
    add_edge(g, 0, 1, true);
    add_edge(g, 0, 3, true);	
    add_edge(g, 1, 2, true);
    add_edge(g, 2, 0, true);
    add_edge(g, 3, 4, true);
    add_edge(g, 4, 5, true);
    add_edge(g, 5, 3, true);


	vector<vector<int>> sccs = find_scc_tarjans(g);
    cout << "Strongly Connected Components:" << endl;
    for (const auto& scc : sccs) {
        cout << "{ ";
        for (int node : scc) {
            cout << node << " ";
        }
        cout << "}" << endl;
    }
	return 0;
}

