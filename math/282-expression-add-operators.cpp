// https://leetcode.com/problems/expression-add-operators

#include "../inc.hpp"

class Solution {
public:
    void impl(
        vector<string>& out,
        string& num,
        string& cur_expr,
        int target,
        int cur_index = 0,
        bool op_add = true,
        int64_t term = 1
    ) {
        size_t end = num[cur_index] == '0' ? cur_index + 1 : num.size();
        int64_t factor = 0;
        for (int i = cur_index; i < end; ++i) {
            char ch = num[i];
            factor = factor * 10 + (ch - '0');

            int64_t new_term = term * factor;

            cur_expr.push_back(ch);
            if (i == num.size() - 1) {
                if (new_term == target) {
                    out.push_back(cur_expr);
                }
                continue;
            }
            // add
            cur_expr.push_back('+');
            impl(
                out, num, cur_expr, 
                target - new_term,
                i + 1,
                true,
                1
            );
            cur_expr.pop_back();

            // sub
            cur_expr.push_back('-');
            impl(
                out, num, cur_expr, 
                target - new_term,
                i + 1,
                true,
                -1
            );
            cur_expr.pop_back();

            // mult
            cur_expr.push_back('*');
            impl(
                out, num, cur_expr, 
                target,
                i + 1,
                false,
                new_term
            );
            cur_expr.pop_back();
        }

        for (int i = cur_index; i < end; ++i) {
            cur_expr.pop_back();
        }
    }

    vector<string> addOperators(string num, int target) {
        vector<string> out;
        string cur_expr;
        cur_expr.reserve(num.size() * 2 - 1);
        impl(out, num, cur_expr, target);
        return out;
    }
};

#include "../test.hpp"

KET_TEST_MAIN_EQ(
    &Solution::addOperators,
    (vector<tuple<tuple<string, int>, vector<string>>> {
        { { "123", 6 }, { "1*2*3", "1+2+3" } },
        { { "232", 8 }, { "2+3*2", "2*3+2" } },
        { { "3456237490", 9191 }, {} },
        { { "105", 5 }, { "1*0+5","10-5" } },
    }),
    CompVectorUnsorted{}
)