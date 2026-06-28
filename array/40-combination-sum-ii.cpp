// https://leetcode.com/problems/combination-sum-ii/

#include <vector>
#include <span>
#include <algorithm>

using namespace std;

class Solution {
public:
    void impl(
        span<int> candidates,
        vector<int>& cur_solution,
        int remaining,
        vector<vector<int>>& solutions
    ) {
        if (remaining == 0) {
            solutions.push_back(cur_solution);
            return;
        }

        if (remaining < 0) {
            return;
        }

        int prev_candidate = 0;
        while(!candidates.empty()) {
            int candidate = candidates[0];
            candidates = candidates.subspan(1);
            if (candidate == prev_candidate) continue;

            cur_solution.push_back(candidate);
            impl(candidates, cur_solution, remaining-candidate, solutions);
            cur_solution.pop_back();

            prev_candidate = candidate;
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<int> cur_solution;
        vector<vector<int>> solutions;
        impl(
            candidates,
            cur_solution,
            target,
            solutions
        );
        return solutions;
    }
};