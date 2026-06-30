// https://leetcode.com/problems/search-in-rotated-sorted-array-ii

#include "../inc.hpp"

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        size_t n = nums.size();
        int l = 0;
        int r = n-1;
        while(l < r) {
            int m = (l + r) / 2;
            int n_l = nums[l];
            int n_r = nums[r];
            int n_m = nums[m];
            if (n_l < n_r) {
                break;
            }
            if (n_l == n_m) {
                ++l;
            } else if (n_l < n_m) {
                l = m;
            } else {
                r = m;
            }
        }
        int k = (l - 1 >= 0) && nums[l-1] > nums[l] ? l : r + 1;
        k = k % n;
        return ranges::binary_search(
            views::iota(0uz, n),
            target,
            std::less<>{},
            [k,n,&nums](size_t i) {
                return nums[(i + k) % n];
            }
        );
        return false;
    }
};