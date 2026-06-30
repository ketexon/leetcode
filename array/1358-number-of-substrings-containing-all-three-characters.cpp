// https://leetcode.com/problems/number-of-substrings-containing-all-three-characters

#include "../inc.hpp"

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        array<int, 3> freqs;
        int num_positive = 0;
        int l = 0;
        int r = 0;
        int count = 0;
        while(l < n && r < n) {
            while (r < n && num_positive < 3) {
                if (++freqs[s[r] - 'a'] == 1) {
                    ++num_positive;
                }
                ++r;
            }
            while(l < s.size() && num_positive == 3) {
                if (--freqs[s[l] - 'a'] == 0) {
                    --num_positive;
                }
                ++l;

                count += (n - r) + 1;
            }
        }
        return count;
    }
};