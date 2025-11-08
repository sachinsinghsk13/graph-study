#include <bits/stdc++.h>
#include <iostream>
#include "graphs/graph.h"
#include "graphs/disjointset.h"
#include <cmath>
using namespace std;

int main() {
    graph g(5);
    add_edge(g, 0, 2, true);
    add_edge(g, 0, 3, true);
    add_edge(g, 1, 0, true);
    add_edge(g, 2, 1, true);
    add_edge(g, 3, 4, true);
    auto v = find_scc_brute_force(g);
    for (auto list : v) {
        for (int i : list) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}

