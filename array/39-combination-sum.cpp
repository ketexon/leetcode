// https://leetcode.com/problems/combination-sum/description/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void impl(
        vector<int>& candidates,
        int cur_candidate_index,
        vector<int>& cur_solution,
        int remaining,
        vector<vector<int>>& solutions
    ) {
        if (remaining == 0) {
            solutions.push_back(cur_solution);
            return;
        }

        if (cur_candidate_index >= candidates.size()) {
            return;
        }

        int cur_candidate = candidates[cur_candidate_index];
        if (cur_candidate <= remaining) {
            cur_solution.push_back(cur_candidate);
            remaining -= cur_candidate;
            impl(candidates, cur_candidate_index, cur_solution, remaining, solutions);
            remaining += cur_candidate;
            cur_solution.pop_back();
        }
        return impl(
            candidates,
            cur_candidate_index + 1,
            cur_solution,
            remaining,
            solutions
        );
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end(), greater<>());
        
        vector<int> cur_solution;
        vector<vector<int>> solutions;
        impl(
            candidates,
            0,
            cur_solution,
            target,
            solutions
        );
        return solutions;
    }
};