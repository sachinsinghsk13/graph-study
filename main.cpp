#include <bits/stdc++.h>
#include <iostream>
#include "graphs/graph_problems.h"
using namespace std;



int main() {
	string start = "abcv";
	string target = "ebad";
	vector<string> words = {
		"abcd", "ebad", "ebcd", "xyza"
	};
	
	int result = word_ladder(start, target, words);
	cout << "Result = " << result << endl;
	return 0;
}