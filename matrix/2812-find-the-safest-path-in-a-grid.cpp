// https://leetcode.com/problems/find-the-safest-path-in-a-grid

#include "../inc.hpp"

class Solution {
public:
    constexpr static array<pair<int, int>, 4> dirs {{
        { 0, -1 },
        { 0, 1 },
        { -1, 0 },
        { 1, 0 },
    }};

    int maximumSafenessFactor(vector<vector<int>>& grid) {    
        size_t n = grid.size();
        vector<bool> visited(n * n, false);
        deque<pair<int, int>> queue;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    visited[i * n + j] = true;
                    queue.push_back(make_pair(i, j));
                }
            }
        }

        auto in_bounds = [n](int i, int j) {
            return i >= 0 && j >= 0 && i < n && j < n;
        };

        while (!queue.empty()) {
            auto [i, j] = queue.front();
            queue.pop_front();
            int distance = grid[i][j];

            for (auto [di, dj] : dirs) {
                int new_i = i + di;
                int new_j = j + dj;
                if (!in_bounds(new_i, new_j)) continue;
                if (visited[new_i * n + new_j]) continue;

                grid[new_i][new_j] = distance + 1;
                queue.push_back(make_pair(new_i, new_j));
                visited[new_i * n + new_j] = true;
            }
        }

        vector<tuple<int, int, int>> pq;
        pq.reserve(n * n);
        pq.push_back(make_tuple(grid[0][0], 0, 0));
        fill(visited.begin(), visited.end(), false);

        while(!pq.empty()) {
            auto [safeness, i, j] = pq.front();
            pop_heap(pq.begin(), pq.end());
            pq.pop_back();

            for (auto [di, dj] : dirs) {
                int new_i = i + di;
                int new_j = j + dj;
                if (!in_bounds(new_i, new_j)) continue;
                if (visited[new_i * n + new_j]) continue;

                grid[new_i][new_j] = min(grid[new_i][new_j], safeness);
                pq.push_back(make_tuple(grid[new_i][new_j], new_i, new_j));
                push_heap(pq.begin(), pq.end());
                visited[new_i * n + new_j] = true;
            }
        }

        return grid.back().back();
    }
};


#include "../test.hpp"

KET_TEST_MAIN(
    &Solution::maximumSafenessFactor,
    (vector<tuple<vector<vector<int>>, int>> {
        { {{1,0,0},{0,0,0},{0,0,1}}, 0 },
        { {{0,0,1},{0,0,0},{0,0,0}}, 2 },
        { {{0,0,0,1},{0,0,0,0},{0,0,0,0},{1,0,0,0}}, 2 },
    })
)