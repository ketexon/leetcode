// https://leetcode.com/problems/kth-largest-element-in-an-array/

#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        make_heap(nums.begin(), nums.end());
        for(int i = 0; i < k; ++i) {
            pop_heap(nums.begin(), nums.end() - i);
        }
        return nums[nums.size() - k];
    }
};

vector<tuple<vector<int>, int, int>> testcases = {
	{{3,2,1,5,6,4}, 2, 5},
	{{3,2,3,1,2,4,5,5,6}, 4, 4},
};

int main() {
	Solution s;
	int test_num = 1;
	for (auto &[nums, k, expected] : testcases) {
		int result = s.findKthLargest(nums, k);
		cout << "Test case " << test_num++ << ": ";
		if (result == expected) {
			cout << "Passed" << endl;
		} else {
			cout << "Failed (Expected "
				<< expected << ", got " << result << ")"
				<< endl;
		}
	}
	return 0;
}