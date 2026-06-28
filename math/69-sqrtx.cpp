// https://leetcode.com/problems/sqrtx

#include <algorithm>

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        int l = 1;
        int r = min(x / 2, 46340);

        while (l < r) {
            int m = (l + r) / 2;
            int square = m * m;
            if (square > x) {
                r = m - 1;
            }
            else if (square < x) {
                l = m + 1;
            }
            else {
                return m;
            }
        }
        return l * l <= x ? l : l - 1;
    }
};