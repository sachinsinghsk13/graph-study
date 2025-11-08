#include "disjointset.h"

// Constructor definition
disjoint_set::disjoint_set(int size) : parent(size), rank(size), n(size)  {
    for (int i = 0; i < size; i++) {
        parent[i] = i;
        rank[i] = 0; // initial rank will be one
    }
}

int disjoint_set::find(int member) {
    if (member < 0 || member >= n) {
        cout << "Invalid disjoint set member" << endl;
        return -1;
    }
    if (parent[member] == member) return member;
    int root = find(parent[member]);
    parent[member] = root; // Path Compression
    return root;
}


void disjoint_set::make_union(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= n) {
        cout << "Invalid disjoint set member" << endl;
    }

    int i = find(x);
    int j = find(y);
    if (i == j) return;
    if (rank[i] == rank[j]) {
        parent[i] = j; // j is the new root for i
        rank[j]++; // increment the rank of j
    } else if (rank[i] < rank[j]) {
        parent[i] = j;
    } else {
        parent[j] = i;
    }
}

bool disjoint_set::in_same_set(int x, int y) {
    return find(x) == find(y);
}
