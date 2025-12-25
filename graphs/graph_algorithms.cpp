#include "graph_algorithms.h"

bool has_only_one_letter_different(string a, string b);
int word_ladder_util(string current, string target, vector<string> words, vector<bool> used, int chain_len);

vector<vector<int>> transitive_closure(vector<vector<int>> graph, int V) {
	// set diagonal to 1
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (i == j)
				graph[i][j] = 1;
		}
	}

	// calculate the transitive closure
	for (int k = 0; k < V; k++)
	{
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
			}
		}
	}
	
	return graph;
}

int word_ladder(string start, string target, vector<string> words) {
	int n = words.size();
	vector<bool> used(n, false);
	return word_ladder_util(start, target, words, used, 1);
}

int word_ladder_util(string current, string target, vector<string> words, vector<bool> used, int chain_len) {
	if (current == target) return chain_len;
	int min_len = INT_MAX;
	
	for (size_t i = 0; i < words.size(); i++) 
	{
		string& next_word = words[i];
		if (has_only_one_letter_different(current, next_word) && !used[i]) 
		{	used[i] = true;
			int result = word_ladder_util(next_word, target, words, used, chain_len + 1);
			used[i] = false;
			min_len = min(min_len, result);
		}
	}
	return min_len;
}

bool has_only_one_letter_different(string a, string b) {
	size_t min = a.size() > b.size() ? b.size() : a.size();
	int count = 0;
	for (size_t i = 0; i < min; i++) 
	{
		if (a[i] != b[i])
			count++;
	}
	return count == 1;
}