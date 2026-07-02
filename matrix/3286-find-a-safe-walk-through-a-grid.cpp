// https://leetcode.com/problems/find-a-safe-walk-through-a-grid

#include "../inc.hpp"

class Solution {
public:
    constexpr static array<pair<int, int>, 4> dirs {{
        { -1, 0 },
        { 1, 0 },
        { 0, -1 },
        { 0, 1 },
    }};

    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        size_t n = grid.size();
        size_t m = grid.front().size();

        vector<tuple<int, int, int>> pq;
        pq.reserve(n * m);
        vector<bool> visited(n * m, false);
        
        pq.emplace_back(health - grid[0][0], 0, 0);
        visited[0] = true;

        auto in_bounds = [n, m](int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; };
        
        while(!pq.empty()) {
            auto [health, i, j] = pq.front();
            pop_heap(pq.begin(), pq.end());
            pq.pop_back();

            for (auto [di, dj] : dirs) {
                int new_i = i + di;
                int new_j = j + dj;
                if (!in_bounds(new_i, new_j)) continue;
                if (visited[new_i * m + new_j]) continue;
                int new_health = health - grid[new_i][new_j];

                if (new_i == n - 1 && new_j == m - 1) {
                    return new_health > 0;
                }
                visited[new_i * m + new_j] = true;
                pq.emplace_back(new_health, new_i, new_j);
                push_heap(pq.begin(), pq.end());
            }
        }
        return false;
    }
};

#include "../test.hpp"

KET_TEST_MAIN(
    &Solution::findSafeWalk,
    (vector<tuple<tuple<vector<vector<int>>, int>, bool>> {
        {
            { 
                {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}},
                1
            },
            true
        },
        {
            { 
                {{0,1,1,0,0,0},{1,0,1,0,0,0},{0,1,1,1,0,1},{0,0,1,0,1,0}},
                3
            },
            false
        },
        {
            { 
                {{1,1,1},{1,0,1},{1,1,1}},
                5
            },
            true
        },
        {
            { 
                {{0,0,0,1,0,1,0,0,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1},{0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1},{0,1,1,1,0,0,0,0,1,1,0,1,1,0,1,0,1,1,0,0,0,1,0,1,1,1,0,1,1},{1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0,1,1,0,0,1,0},{0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,1,0,1,1,0,0,1,0,1,0,0},{1,0,1,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0},{0,0,1,0,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1},{1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,1,1,0},{1,0,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,0,0,1,1,1,0,0,0,1,1,0,1},{1,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0},{0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,1,0,0,1,1},{0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1},{0,0,1,1,1,1,0,1,1,1,0,1,1,1,0,0,1,0,1,0,0,1,1,1,1,0,1,0,0},{0,0,0,1,0,0,1,0,0,1,0,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0},{1,1,1,1,0,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,1,0,1,1,1},{0,0,1,0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1},{1,1,0,0,0,0,1,0,1,1,1,0,0,1,0,1,0,1,1,0,1,0,1,1,1,1,0,0,0},{0,1,0,0,1,1,0,0,0,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,0,0,1},{1,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,0,0}},
                4
            },
            false
        },
    })
)