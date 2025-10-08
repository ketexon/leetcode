// https://leetcode.com/problems/successful-pairs-of-spells-and-potions/description/?envType=daily-question&envId=2025-10-08
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>

using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        vector<int> out;
        for (int spell : spells) {
            long long target = (success + spell - 1) / spell;
            if (target > numeric_limits<int>::max()) {
                out.push_back(0);
                continue;
            }

            auto res = lower_bound(
                potions.begin(),
                potions.end(),
                target
            );
            out.push_back(
                potions.end() - res
            );
        }
        return out;
    }
};

vector<tuple<vector<int>, vector<int>, long long, vector<int>>> testcases = {
    {{5,1,3}, {1,2,3,4,5}, 7, {4,0,3}},
    {{3,1,2}, {8,5,8}, 16, {2,0,2}},
    // max int as success
    {{1}, {1}, 2147483648ll, {0}},
};

int main() {
    Solution s;
    int test_num = 1;
    for (auto &[spells, potions, success, expected] : testcases) {
        vector<int> result = s.successfulPairs(spells, potions, success);
        cout << "Test case " << test_num++ << ": ";
        if (result == expected) {
            cout << "Passed" << endl;
        } else {
            cout << "Failed (Expected [";
            for (int i = 0; i < expected.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << expected[i];
            }
            cout << "], got [";
            for (int i = 0; i < result.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << result[i];
            }
            cout << "])" << endl;
        }
    }
    return 0;
}