// https://leetcode.com/problems/insert-interval

#include "../inc.hpp"

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& new_interval) {
        vector<vector<int>> out;
        out.reserve(intervals.size() + 1);
        int i;
        int prev_end = -99999;
        for (i = 0; i < intervals.size(); ++i) {
            const auto& interval = intervals[i];
            if (interval[0] > new_interval[0]) {
                break;
            }
            out.push_back(interval);
            prev_end = interval[1];
        }
        out.push_back(new_interval);
        while (true) {
            int back_start = out.back()[0];
            int back_end = out.back()[1];
            if (prev_end >= back_start) {
                out.pop_back();
                back_end = max(out.back()[1], back_end);
                out.back()[1] = back_end;
            }
            if (i >= intervals.size()) break;
            prev_end = back_end;
            out.push_back(intervals[i]);
            ++i;
        }
        return out;
    }
};