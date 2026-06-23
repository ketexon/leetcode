// https://leetcode.com/problems/number-of-zigzag-arrays-i/description/?envType=daily-question&envId=2026-06-23

#include <vector>

using namespace std;

constexpr int mod = 1000000007;

class Solution {
public:
    // to simplify: we will consider all zigZags starting up and multiply by 2
    int zigZagArrays(int n, int l, int r) {
        int m = (r - l) + 1;
        // M[len - 1][last_num] = number of zigzags of length n
        vector<vector<int>> M(n, vector<int>(m, 0));

        // 1 way for zig zag of 1 element
        for (int i = 0; i < m; ++i) {
            M[0][i] = 1;
        }

        for (int i = 1; i < n; ++i) {
            bool up = i % 2 == 0;
            int sum = 0;
            for (int last_num = up ? 0 : m - 1; last_num < m && last_num >= 0; last_num += (up ? 1 : -1)) {
                M[i][last_num] = sum;
                sum = (sum + M[i-1][last_num]) % mod;
            }
        }

        int result = 0;
        for (int last_num = 0; last_num < m; ++last_num) {
            result = (result + M[n-1][last_num]) % mod;
        }
        
        return (result * 2) % mod;
    }
};

#include "../test.hpp"
KET_TEST_MAIN(
    &Solution::zigZagArrays,
    (std::vector<std::tuple<std::tuple<int, int, int>, int>> {
        { { 3, 4, 5 }, 2 },
        { { 3, 1, 3 }, 10 },
        { { 8, 34, 67 }, 2633967 },
        { { 8, 4, 33 }, 417511445 },
        { { 9, 38, 86 }, 138519916 },
    })
);