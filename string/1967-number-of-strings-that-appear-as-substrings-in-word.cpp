// https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int count = 0;
        for (auto& s : patterns) {
            if (word.contains(s)) {
                ++count;
            }
        }
        return count;
    }
};