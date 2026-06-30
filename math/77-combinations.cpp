// https://leetcode.com/problems/combinations

#include "../inc.hpp"

class Solution {
public:
    void impl(vector<vector<int>>& out, vector<int>& cur, int i, int l, int r) {
        for (int n = l; n <= r; ++n) {
            cur[i] = n;
            if (i == cur.size() - 1) {
                out.push_back(cur);
            }
            else {
                impl(out, cur, i+1, n+1, r);
            }
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> out;
        vector<int> cur(k, 0);
        impl(out, cur, 0, 1, n);
        return out;
    }
};