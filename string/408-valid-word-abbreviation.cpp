// https://leetcode.com/problems/valid-word-abbreviation/

#include <string>
#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
		int word_idx = 0;
		int i = 0;
		while (i < abbr.size() && word_idx < word.size()) {
			auto abbr_ch = abbr[i];
			// number cannot start with '0'
			if (abbr_ch == '0') {
				return false;
			}

			if(isdigit(abbr_ch)) {
				int skip = 0;
				while(isdigit(abbr_ch)) {
					skip *= 10;
					skip += (abbr_ch - '0');

					i += 1;
					abbr_ch = abbr[i];
				}
				word_idx += skip;
				// note: no i += 1 because
				// we did not process the last character
				// (since it is not a digit)
			} else {
				if (word[word_idx] != abbr_ch) {
					return false;
				}
				word_idx += 1;
				i += 1;
			}
		}
		return word_idx == word.size() && i == abbr.size();
	}
};

vector<tuple<string, string, bool>> test_cases {
	{"substitution", "s10n", true},
	{"substitution", "sub4u4", true},
	{"substitution", "12", true},
	{"substitution", "su3i1u2on", true},
	{"substitution", "substitution", true},

	{"substitution", "s55n", false},
	{"substitution", "s010n", false},
	{"substitution", "su0bstitution", false},

	{"internationalization", "i12iz4n", true},
	{"apple", "a2e", false},
};

int main() {
	Solution solution;
	int test_num = 1;
	for (auto& [word, abbr, expected] : test_cases) {
		auto result = solution.validWordAbbreviation(word, abbr);
		cout << "Test Case " << test_num++ << ": ";
		if (result == expected) {
			cout << "Passed";
		} else {
			cout << "Failed";
		}
		cout << endl;
	}
	return 0;
}