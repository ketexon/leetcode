// https://leetcode.com/problems/valid-palindrome-ii

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

class Solution {
public:
    bool validPalindrome(string s) {
        auto impl = [](auto& self, string& s, int l, int r, bool can_change) {
            while(l < r){
                char ch_l = s[l];
                char ch_r = s[r];
                if (ch_l != ch_r) {
                    if (!can_change) return false;
                    return self(
                        self, s,
                        l + 1, r,
                        false
                    ) || self(
                        self, s,
                        l, r - 1,
                        false
                    );
                }
                l += 1;
                r -= 1;
            }
            return true;
        };
        return impl(impl, s, 0, s.size() - 1, true);
    }
};

vector<tuple<string, bool>> test_cases = {
	{"aba", true},
	{"abca", true},
	{"abc", false},
	{"deeee", true},
	{"eeeed", true},
	{"eeceee", true},
};

int main() {
	Solution solution;
	int case_num = 1;
	for (auto [s, expected] : test_cases) {
		auto result = solution.validPalindrome(s);
		cout << "Case " << case_num << ": "
			 << (result == expected ? "PASS" : "FAIL")
			 << endl;
		case_num += 1;
	}
	return 0;
}