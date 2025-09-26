#include <array>
#include <deque>
#include <limits>
#include <tuple>
#include <vector>
#include <cstdint>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        auto m = grid.size();
        auto n = grid[0].size();

        for (auto& row : grid) {
            for (auto& cell : row) {
                cell = (numeric_limits<int16_t>::max() << 16) | cell;
            }
        }
        grid[0][0] &= 0xFFFF;

        static array<tuple<int,int>,4> dirs {
            make_tuple(0,1),
            make_tuple(0,-1),
            make_tuple(1,0),
            make_tuple(-1,0),
        };

        vector<vector<int>> min_costs(
            m,
            vector<int>(n, numeric_limits<int>::max())
        );

        // start
        min_costs[0][0] = 0;

        auto in_bounds = [m,n](int i, int j) {
            return i >= 0 && j >= 0 && i < m && j < n;
        };

        deque<tuple<int,int>> q;
        q.emplace_front(0,0);
        while(!q.empty()){
            auto [i,j] = q.front();
            q.pop_front();

            int cell = grid[i][j];

            int dir = cell & 0xFFFF;
            int cost = cell >> 16;

            if (i == m - 1 && j == n - 1) {
                return cost;
            }

            // already visited
            if (dir == 0) continue;
            grid[i][j] = cost << 16;

            auto [dir_i, dir_j] = dirs[dir - 1];

            // add neighboring cells
            for (auto [di, dj] : dirs) {
                int ni = i + di;
                int nj = j + dj;
                if (!in_bounds(ni, nj)) continue;

                int n_cell = grid[ni][nj];
                int n_dir = n_cell & 0xFFFF;
                int n_cost = n_cell >> 16;

                // already visited
                if (n_dir == 0) continue;

                // zero weight, push_front
                int new_cost = cost;
                if (dir_i == di && dir_j == dj) {
                    q.emplace_front(ni, nj);
                } else {
                    new_cost += 1;
                    q.emplace_back(ni, nj);
                }
                n_cost = min(n_cost, new_cost);
                grid[ni][nj] = (n_cost << 16) | n_dir;
            }
        }
        return -1;
    }
};

// tests
vector<tuple<vector<vector<int>>,int>> tests = {
	{
		{
			{1,1,1,1},
			{2,2,2,2},
			{1,1,1,1},
			{2,2,2,2}
		},
		3
	},
	{
		{
			{1,1,3},
			{3,2,2},
			{1,1,4}
		},
		0
	},
	{
		{
			{1,2},
			{4,3}
		},
		1
	},
};

int main() {
	Solution s;
	int test_num = 1;
	for (auto [grid, expected] : tests) {
		auto result = s.minCost(grid);
		cout << "Test " << test_num << ": ";
		if (result == expected) {
			cout << "Passed" << endl;
		} else {
			cout << "Failed (expected " << expected << ", got " << result << ")" << endl;
		}
		test_num++;
	}
	return 0;
}