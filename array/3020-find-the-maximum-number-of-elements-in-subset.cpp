// https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/

#include <unordered_map>
#include <functional>

using namespace std;

constexpr int max_root = 31623;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<int, int> frequencies;
        for (int num : nums) {
            ++frequencies[num];
        }

        int longest = max(
            1,
            (frequencies[1] + 1) / 2
        );
        for (int num : nums) {
            if (num == 1) continue;
            reference_wrapper<int> freq = frequencies[num];
            if (freq <= 0) {
                continue;
            }
            int length = 0;
            int cur = num;
            while(freq != 0) {
                if (freq < 0) {
                    length += -freq;
                    break;
                }
                ++length;
                if (freq == 1 || cur > max_root) {
                    break;
                }
                cur *= cur;
                freq.get() = 0;
                freq = frequencies[cur];
            }
            longest = max(longest, length);

            // mark as visited
            frequencies[num] = -length;
        }
        return (longest - 1) * 2 + 1;
    }
};


#include "../test.hpp"

struct Wrapper {
    Solution solution;
    int maximumLength(vector<int> nums) {
        return solution.maximumLength(nums);
    }
};

KET_TEST_MAIN(
    &Wrapper::maximumLength,
    (vector<tuple<tuple<vector<int>>, int>> {
        { { { 5,4,1,2,2 } }, 3 },
        { { { 1,3,2,4 } }, 1 },
        { { { 1,1,1,1,1,1,1,1,1,1,2,4,8,16,32,64,128,256,512,1024 } }, 9 },
        { { { 1,1 } }, 1 },
        { { { 1,1,1 } }, 3 },
        { { { 15,15,225,225,50625,50625 } }, 5 },
    })
);