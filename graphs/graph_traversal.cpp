#include "graph_traversal.h"


vector<int> graph_dfs(graph &graph, int start_vertex) {
	int n = graph.size(); // total nodes
	vector<int> result;
	vector<bool> visited(n, false);
	stack<int> stack;
	stack.push(start_vertex);
	visited[start_vertex] = true;

	while (!stack.empty()) {
		int x = stack.top();
		stack.pop();
		result.push_back(x);
		for (pair<int, int> neighbour : graph[x]) {
			if (!visited[neighbour.first]) {
				stack.push(neighbour.first);
				visited[neighbour.first] = true;
			}
		}
	}
	return result;
}

vector<int> graph_bfs(graph &graph, int start_vertex) {
	int n = graph.size(); // total nodes
	vector<int> result;
	vector<bool> visited(n, false);
	queue<int> queue;
	queue.push(start_vertex);
	visited[start_vertex] = true;

	while (!queue.empty()) {
		int x = queue.front();
		queue.pop();
		result.push_back(x);
		for (pair<int, int> neighbour : graph[x]) {
			if (!visited[neighbour.first]) {
				queue.push(neighbour.first);
				visited[neighbour.first] = true;
			}
		}
	}
	return result;
}

static void dfs_util(graph& graph, int u, vector<bool>& visited, vector<int>& disc, vector<int>& fin, int& time) {
	visited[u] = true;
	time++;
	disc[u] = time;
	for (pair<int, int> neighbour: graph.at(u)) {
		int v = neighbour.first;
		if (!visited[v]) {
			dfs_util(graph, v, visited, disc, fin, time);
		}
	}
	time = time + 1;
	fin[u] = time;
}

pair<vector<int>, vector<int>> dfs_with_time(graph& graph) {
	int n = graph.size();
	vector<bool> visited(n, false);
	vector<int> disc(n, 0), fin(n, 0);
	int time = 0;
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			dfs_util(graph, i, visited, disc, fin, time);
		}
	}
	return {disc, fin};
}