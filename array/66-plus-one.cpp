// https://leetcode.com/problems/plus-one/

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        int i;
        for (i = n - 1; i >= 0; --i) {
            int digit = digits[i];
            if (digit < 9) {
                ++digits[i];
                break;
            }
            digits[i] = 0;
        }
        if (i < 0) {
            digits.insert(digits.cbegin(), 1);
        }
        return digits;
    }
};