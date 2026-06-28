// https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int max = 0;
        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i] > max) {
                arr[i] = max;
                ++max;
            }
        }
        return max;
    }
};

#include "../test.hpp"

KET_TEST_MAIN(
    &Solution::maximumElementAfterDecrementingAndRearranging,
    (vector<tuple<
        vector<int>,
        int
    >> {
        { { 2,2,1,2,1 }, 2 },
        { { 100,1,1000 }, 3 },
        { { 1,2,3,4,5 }, 5 },
    })
)