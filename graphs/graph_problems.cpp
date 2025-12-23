#include "graph_problems.h"

void test(){
    cout << "" << endl;
}

bool is_safe(int x, int y, int m, int n)
{
    return x >= 0 && y >= 0 && x < m && y < n;
}

int rotten_oranges(vector<vector<int>> &mat)
{
    int m = mat.size();
    int n = mat[0].size();

    queue<pair<int, int>> q;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // if it's a rotten orange
            if (mat[i][j] == 2)
            {
                q.push({i, j});
            }
        }
    }

    int count = 0;
    vector<vector<int>> dirs = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    while (!q.empty())
    {
        int size = q.size();
        bool rottened = false;

        for (int i = 0; i < size; i++)
        {
            pair<int, int> coor = q.front();
            q.pop();
            for (auto &dir : dirs)
            {
                int x = coor.first + dir[0];
                int y = coor.second + dir[1];

                if (is_safe(x, y, m, n) && mat[x][y] == 1)
                {
                    mat[x][y] = 2;
                    q.push({x, y});
                    rottened = true;
                }
            }
        }

        if (rottened) {
            count++;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 1)
            {
                return -1;
            }
        }
    }

    return count;
}


int snakes_and_ladders(int n, vector<int> array) {
    unordered_map<int, int> dest_map;

    for (int i = 0; i < n; i++) {
        int source = array[2 * i];
        int dest = array[2 * i + 1];
        dest_map[source] = dest;
    }

    queue<pair<int, int>> q;

    q.push({1, 0});
    int min = INT_MAX;
    while (!q.empty()) {
        int curr = q.front().first;
        int steps = q.front().second;
        q.pop();

        if (curr >= 30) {
            min =  steps;
            break;
        }

        // throw the dice
        for (int i = 1; i <= 6; i++) {
            int next = curr + i;
            // check if there's any shortcut
            if (dest_map.find(next) != dest_map.end() && dest_map[next] > curr) {
                next = dest_map[next];
            }
            q.push({next, steps + 1});
        }
    }
    return min;
}