// https://leetcode.com/problems/split-message-based-on-limit/
// solution: https://leetcode.com/problems/split-message-based-on-limit/solutions/7312030/c-with-detailed-explanation-on-19ms-beat-hch4/

// let n be the message length
// we want to find the smallest number of parts such that characters(parts, limit) > n
// where characters(parts, limit) is the numbers of characters able to fit in parts
// characters(parts, limit) = 
//          parts * (limit - floor(log10(parts)) - 3) total number of characters excluding part index (-3 for </>) 
//          - (
//                  1 * parts                             ones place 
//                  + 1 * max(parts - 9, 0))              tens place
//                  + 1 * max(parts - 99, 0))             hundreds place
//                  + 1 * max(parts - 999, 0))            thousands place
//          )
//
// the naive solution is just check every valid number of parts
// this would be O(n), since at least one character in message should be
// able to fit in each part, so we can't have more than n parts
//
// however, we can note that characters(parts, limit) is *almost* monotonically
// increasing with parts
// it is only not monotonically increasing when we add a new digit:
//      characters(7,9) = 28
//      characters(8,9) = 32
//      characters(9,9) = 36
//      characters(10,9) = 29 <-- tens place added
//      characters(11,9) = 31
//
// thus, we can check for every number of digits in the total number of parts
// to check if n fits within parts in that range
// ie. for 1 digit, check if characters(1, limit) <= n <= characters(9, limit)
//     for 2 digits, check if characters(10, limit) <= n <= characters(99, limit)
// since we want to find the smallest number of digits, we only need to check
// n <= characters(9, limit), n <= characters(99, limit), ...
//
// then, we can do a lower bound binary search within that range to find the actual number of parts
// needed
//
// for creating the output string, we iterate the number of parts, calculate the number of 

#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>

using namespace std;

constexpr int num_digits(int n) {
    return n < 10 ? 1
        : n < 100 ? 2
        : n < 1000 ? 3
        : 4;
}

// counts the number of digits in
//      1 2 3 4 5 ... 10 11 12 13 ... num
constexpr int count_num_digits_from_1(int num) {
    return num                  // number of ones places
        + max(num - 9, 0)       // number of tens places
        + max(num - 99, 0)      // number of hundreds places
        + max(num - 999, 0);    // number of thousands places
}

constexpr int max_message_size(int parts, int limit) {
    return parts * (limit - num_digits(parts)) - count_num_digits_from_1(parts);
};

class Solution {
public:
    vector<string> splitMessage(string message_string, int limit) {
        limit -= 3; // ignore </> in <a/b>
        string_view message(message_string); // to prevent copying for substr
        const int n = message.length();
        if (limit < 2 || limit == 2 && n > 0) {
            return {};
        }

        int max_parts = 0;
        for (int i : { 9, 99, 999, 9999 }) {
            int max_characters = max_message_size(i, limit);
            if (n <= max_characters) {
                max_parts = i;
                break;
            }
        }
        if (max_parts == 0) {
            return {};
        }
        int min_parts = (max_parts + 1) / 10;
        max_parts = min(max_parts, n);

        // lower_bound implementation
        // for function
        while (max_parts - min_parts > 0)
        {
            int delta = max_parts - min_parts;
            int middle = min_parts + delta / 2;
            int characters_fit = max_message_size(middle, limit);
            if (characters_fit >= n)
            {
                max_parts = middle;
            }
            else
            {
                min_parts = middle + 1;
            }
        }
        int num_parts = min_parts;

        vector<string> out(num_parts, "");
        limit = limit - num_digits(num_parts); // ignore b in <a/b>
        int message_i = 0;
        stringstream ss;
        for(int part_num = 1; part_num <= num_parts; ++part_num) {
            int part_num_digits = num_digits(part_num);
            int remaining_length = limit - part_num_digits;
            ss << message.substr(message_i, remaining_length)
                << '<'
                << part_num
                << '/'
                << num_parts
                << '>';
            out[part_num - 1] = ss.str();
            ss.str("");
            message_i += remaining_length;
        }
        
        return out;
    }
};

#include <iostream>
#include <tuple>

vector<tuple<string, int, vector<string>>> tests = {
    {"this is really a very awesome message", 9, {"thi<1/14>","s i<2/14>","s r<3/14>","eal<4/14>","ly <5/14>","a v<6/14>","ery<7/14>"," aw<8/14>","eso<9/14>","me<10/14>"," m<11/14>","es<12/14>","sa<13/14>","ge<14/14>"}},
    {"short message", 15, {"short mess<1/2>","age<2/2>"}},
    {"boxpn", 5, {}},
    {"a", 6, {"a<1/1>"}},
    {"baaaababab aabaaba", 7, {"ba<1/9>","aa<2/9>","ab<3/9>","ab<4/9>","ab<5/9>"," a<6/9>","ab<7/9>","aa<8/9>","ba<9/9>"}},
    {"faavwbcawh", 2, {}},
    {"p", 7, {"p<1/1>"}},
};

int main() {
    Solution sol;
    int test_num = 1;
    for (auto& [message, limit, expected] : tests) {
        auto result = sol.splitMessage(message, limit);
        if (result == expected) {
            cout << "Test " << test_num << " passed." << endl;
        } else {
            cout << "Test " << test_num << " failed." << endl;
            cout << "  Message: " << message << endl;
            cout << "  Limit: " << limit << endl;
            cout << "  Expected: ";
            for (auto& part : expected) {
                cout << '"' << part << "\" ";
            }
            cout << endl;
            cout << "  Got: ";
            for (auto& part : result) {
                cout << '"' << part << "\" ";
            }
            cout << endl;
        }
        test_num++;
    }

    return 0;
}