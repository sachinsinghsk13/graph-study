#ifndef __DISJOINT_SET__
#define __DISJOINT_SET__

#include <bits/stdc++.h>
using namespace std;

class disjoint_set {
    private:
        vector<int> parent;
        vector<int> rank;
        const int n;
    public:
        disjoint_set(int size);
        int find(int member);
        void make_union(int x, int y);
        bool in_same_set(int x, int y);
};

#endif