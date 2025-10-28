// https://leetcode.com/problems/make-array-elements-equal-to-zero

#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

// note that for every zero, we can remove all other zeroes
// and combine adjacent positive numbers
// thus, in the end, we can combine
//      a b c 0 d e f
// to
//      (a+b+c) 0 (d+e+f)
// thus, we only care about the sum of previous and remaining elements
// which we can compute using a pre/suffix sum
// note that if the prefix and suffix are equal, right and left both work
// if they are one off, we can only start in the direction that is larger
// otherwise (eg)
//      right:  2 0 1 -> 2 0 0 -> 1 0 0 -> fail
//      left:   2 0 1 -> 1 0 1 -> 1 0 0 -> 0 0 0 -> success
//
// since we only use the prefix/suffix sum one element at a time
// we can just keep 2 accumulators and update them per iteration

class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int prefix_sum = 0;
        int suffix_sum = reduce(nums.begin(), nums.end());

        int acc = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int num = nums[i];
            prefix_sum += num;
            suffix_sum -= num;
            if (num != 0) {
                continue;
            }
            int abs_diff = abs(prefix_sum - suffix_sum);
            if (abs_diff == 0) {
                acc += 2;
            } else if (abs_diff == 1) {
                acc += 1;
            }
        }
        return acc;
    }
};

#include <tuple>
#include <iostream>

vector<tuple<vector<int>, int>> test_cases = {
	{{2, 0, 1}, 1},
	{{0, 0, 0}, 6},
	{{1, 1, 0, 1, 1}, 2},
    {{1,0,2,0,3}, 2},
    {{2,3,4,0,4,1,0}, 0},
};

int main() {
	Solution sol;
	int test_num = 1;
	for (auto& [nums, expected] : test_cases) {
		int result = sol.countValidSelections(nums);
		if (result == expected) {
			cout << "Test case " << test_num << " passed." << endl;
		} else {
			cout << "Test case " << test_num << " failed: expected " << expected << ", got " << result << "." << endl;
		}
		test_num++;
	}
	return 0;
}