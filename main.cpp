#include <bits/stdc++.h>
#include <iostream>
#include "graphs/graph.h"
#include "graphs/disjointset.h"
#include <cmath>
using namespace std;

int main() {
	graph g(10);
	add_edge(g, 1, 2, true);
	add_edge(g, 1, 4, true);
	add_edge(g, 2, 3, true);
	add_edge(g, 3, 1, true);
	add_edge(g, 4, 5, true);
	add_edge(g, 4, 7, true);
	add_edge(g, 5, 6, true);
	add_edge(g, 6, 4, true);
	add_edge(g, 7, 8, true);
	add_edge(g, 8, 9, true);
	add_edge(g, 9, 7, true);
	
	auto r = dfs_with_time(g);
	
	cout << "Discovery Time : ";
	for (int time : r.first) 
	{
		cout << time << " ";
	}
	cout << endl;
	cout << "Finish Time : ";
	for (int time : r.second) 
	{
		cout << time << " ";
	}
	return 0;
}

