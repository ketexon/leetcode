// https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <tuple>

using namespace std;

// There are two cases
//      The target is a number
//      The target is not a number
//          In this case, it must be between two numbes
//          In fact, there is always one optimal solution
//          where the target is k away from a number
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int ops) {
        size_t n = nums.size();
        if (n <= 1) return n;

        int min_num = nums[0];
        int max_num = nums[0];
        unordered_map<int, int> freqs;
        for (int num : nums) {
            min_num = min(min_num, num);
            max_num = max(max_num, num);
            ++freqs[num];
        }

        vector<tuple<int, int, int>> num_freqs;
        for (int num : nums) {
            if (freqs[num] == 0) continue;
            num_freqs.emplace_back(num, freqs[num], 0);
            freqs[num] = 0;

#if __cplusplus >= 202002L
            if (num - k > min_num && !freqs.contains(num - k)) {
#else
            if (num - k > min_num && freqs.find(num - k) == freqs.end()) {
#endif
                freqs[num - k] = 0;
                num_freqs.emplace_back(num - k, 0, 0);
            }
            // same as num + k < max_num, but better
            // with integer overflow
#if __cplusplus >= 202002L
            if (num < max_num - k && !freqs.contains(num + k)) {
#else
			if (num < max_num - k && freqs.find(num + k) == freqs.end()) {
#endif
                freqs[num + k] = 0;
                num_freqs.emplace_back(num + k, 0, 0);
            }
        }

        sort(num_freqs.begin(), num_freqs.end());

        int total_freq = 0;
        for (auto& [_, freq, freq_acc] : num_freqs) {
            freq_acc = total_freq;
            total_freq += freq;
        }

        auto l = num_freqs.begin();
        auto r = num_freqs.begin();

        int max_freq = 0;

        for (auto [num, freq, prefix] : num_freqs) {
            auto l_it = lower_bound(l, num_freqs.end(), make_tuple(num - k, 0, 0));
            auto r_it = lower_bound(r, num_freqs.end(), make_tuple(num + k + 1, 0, 0));


            int l_freq_acc = l_it == num_freqs.end() ? total_freq : get<2>(*l_it);
            int r_freq_acc = r_it == num_freqs.end() ? total_freq : get<2>(*r_it);

            auto total_freq = r_freq_acc - l_freq_acc - freq;
            max_freq = max(
                max_freq,
                freq + clamp(total_freq, 0, ops)
            );
        }

        return max_freq;
    }
};

#include <iostream>

vector<tuple<vector<int>, int, int, int>> test_cases = {
	{{1,4,5}, 1, 2, 2},
	{{5, 11, 20, 20}, 5, 1, 2},
	{{999999997,999999999,999999999}, 999999999, 2, 3},
};

int main() {
	Solution sol;
	int case_num = 1;
	for (const auto& [nums, k, ops, expected] : test_cases) {
		int result = sol.maxFrequency(const_cast<vector<int>&>(nums), k, ops);
		if (result == expected) {
			cout << "Test case " << case_num << " passed." << endl;
		} else {
			cout << "Test case " << case_num << " failed: expected "
				 << expected << ", got " << result << "." << endl;
		}
		++case_num;
	}
	return 0;
}