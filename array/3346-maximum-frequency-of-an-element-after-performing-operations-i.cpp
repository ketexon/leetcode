#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int ops) {
        size_t n = nums.size();
        if (n <= 1) return n;
        sort(nums.begin(), nums.end());
        int min_num = nums.front();
        int max_num = nums.back();

        vector<int> frequencies(max_num - min_num + 1, 0);

        for (int num : nums) {
            ++frequencies[num - min_num];
        }

        vector<int>::iterator l = nums.begin();
        vector<int>::iterator r = nums.begin();

        int max_freq = 0;

        for (int target = min_num; target <= max_num; ++target) {
            // set l to first position such that *l >= target - k
            l = lower_bound(l, nums.end(), target - k);
            // set r to first pos such that *r > target + k
            r = lower_bound(r, nums.end(), target + k + 1);

            int window_size = r - l;
            int target_freq = frequencies[target - min_num];
            int ops_used = clamp(
                window_size - target_freq,
                0,
                ops
            );

            max_freq = max(
                max_freq,
                target_freq + ops_used
            );
        }
        return max_freq;
    }
};

#include <iostream>
#include <tuple>

vector<tuple<vector<int>, int, int, int>> test_cases = {
    {{1,2,4}, 5, 2, 3},
    {{5, 11, 20, 20}, 5, 1, 2},
    {{94, 10, 92}, 0, 3, 1},
};

int main() {
    Solution sol;
    int case_num = 1;
    for (const auto& [nums, k, ops, expected] : test_cases) {
        int result = sol.maxFrequency(const_cast<vector<int>&>(nums), k, ops);
        cout << "Test case " << case_num++ << ": ";
        if (result == expected) {
            cout << "Passed" << endl;
        } else {
            cout << "Failed (Expected " << expected << ", got " << result << ")" << endl;
        }
    }
    return 0;
}