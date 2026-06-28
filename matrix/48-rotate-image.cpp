// https://leetcode.com/problems/rotate-image/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // same as transpose then flip horizontally
        int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        for (auto& row : matrix) {
            reverse(row.begin(), row.end());
        }
    }
};