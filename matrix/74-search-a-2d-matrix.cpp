// https://leetcode.com/problems/search-a-2d-matrix

#include "../inc.hpp"

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        auto row_it = upper_bound(
            matrix.cbegin(),
            matrix.cend(),
            target,
            [](const auto& v, const auto& row) {
                return row[0] > v;
            }
        );
        if (row_it == matrix.begin()) {
            return false;
        }
        --row_it;
        const auto& row = *row_it;
        return binary_search(row.cbegin(), row.cend(), target);
    }
};