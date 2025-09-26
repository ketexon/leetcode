// https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses

#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <tuple>
#include <iostream>

using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<reference_wrapper<char>> unmatched;
        for (auto& ch : s) {
            if (ch == '(') {
                unmatched.push_back(ch);
            }
            if (ch == ')') {
                if (unmatched.size() > 0) {
                    unmatched.pop_back();
                } else {
                    ch = '0';
                }
            }
        }
        for (auto ch_ref : unmatched) {
            ch_ref.get() = '0';
        }

        stringstream ss;
        for (auto ch : s) {
            if (ch != '0') {
                ss << ch;
            }
        }

        return ss.str();
    }
};

bool is_valid_parens(string s) {
	int balance = 0;
	for (auto ch : s) {
		if (ch == '(') {
			balance++;
		} else if (ch == ')') {
			balance--;
			if (balance < 0) {
				return false;
			}
		}
	}
	return balance == 0;
}

bool is_removed(string original, string modified) {
	int i = 0, j = 0;
	while (i < original.size() && j < modified.size()) {
		if (original[i] == modified[j]) {
			i++;
			j++;
		} else if (original[i] == '(' || original[i] == ')') {
			i++;
		} else {
			return false;
		}
	}
	return j == modified.size();
}

vector<tuple<string, int>> test_cases = {
	{ "lee(t(c)o)de)", 1 },
	{ "a)b(c)d", 1 },
	{ "))((", 4 },
	{ "(a(b(c)d)", 1 },
	{ "abc", 0 },
};

int main() {
	Solution sol;
	int test_num = 1;
	for (auto& [input, num_removed] : test_cases) {
		auto result = sol.minRemoveToMakeValid(input);
		bool is_sol = true;
		is_sol = is_sol && is_valid_parens(result);
		is_sol = is_sol && is_removed(input, result);
		is_sol = is_sol && (input.size() - result.size() == num_removed);
		cout << "Test Case "
			<< test_num << ": "
			<< (is_sol ? "Passed" : "Failed")
			<< endl;
		test_num += 1;
	}
	return 0;
}