// https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/submissions/1796789182/
#include <vector>
#include <tuple>
#include <iostream>
#include <numeric>

using namespace std;

class Solution {
public:
    long long minTime(vector<int>& skills, vector<int>& manas) {
        long long total_skill = accumulate(skills.begin(), skills.end(), 0);
        long long start = 0;

        for (int i = 0; i < manas.size() - 1; ++i) {
            int mana = manas[i];
            int next_mana = manas[i + 1];
            long long total_next_mana = total_skill * next_mana;

            long long skill_remaining = total_skill;
            long long next_start = 0;
            for (int skill : skills) {
                start += skill * mana;
                // the hypothetical next potion complete time
                // if this wizard is the bottleneck
                next_start = max(
                    next_start,
                    start + skill_remaining * next_mana - total_next_mana
                );
                skill_remaining -= skill;
            }

            start = next_start;
        }
        return start + total_skill * manas.back();
    }
};

vector<tuple<vector<int>, vector<int>, long long>> testcases = {
	{{1,5,2,4}, {5,1,4,2}, 110},
    {{1,1,1}, {1,1,1}, 5},
    {{1,2,3,4}, {1,2}, 21},
    {
        {307,1425,2493,3942,2896,3262,3849,4903,493,3995,2483,4649,2351,4971,2333,3592,4065,163,2276,2811,722,1560,1402,3838,1049,956,602,861,4627,4873,2972,2552,1230,2486,2972,2499,3195,1943,142,3722,1510,3801,103,3817,1419,384,3803,3074,283,1984,2215,1091,1220,4588,2917,2557,822,1378,3635,1508,2889,2773,1617,4335,4189,3794,2825,4150,994,1049,4981,3643,4729,1252,1319,1208,3440,4115,4085,1515,2702,3097,1532,1651,2048,4954,914,3242,3818,139,1959,4589,384,4119,2406,690,3675,2402,4078,3324,1147,881,1728,472,2703,2677,1881,4964,3267,651,3919,2983,2633,3994,3048,4185,3881,2931,4360,4661,4933,2877,4392,3792,830,3619,2022,3467,3301,2045,1062,4394,1093,4174,4489,3156,2415,1816,3208,1859,116,2778,3132,4761,3178,1767,2972,4009,2733,2519,1532,75,4247,4514,1324,295,1402,4496,3880,4655,1258,3018,3031,1140,3468,3109,2235,548,2628,4192,1889,2727,3484,871,4029,1852,2256},
        {2678,388,145,4674,4092,2678,3659,822,4183,4140,2449,2302,3438,1931,3264,2364,3795,3808,4175,4440,2014,334,4736,1997,3973,1442,29,2476,2680,135,1178,3682,4853,2065,1003,56,3851,175,1898,2169,4041,1437,1673,4967,4853,399,987,4516,4818,1707,4743,4871,2548,3517,2705,419,4968,905,583,497,1019,1429,4236,1737,4893,4790,3526,1962,3290,1676,2024,1736,1159,455,4516,2066,3538,2011,3883,1071,4526,2043,2698,4890,3662,4753,1387,99,4237,1350,800,3256,1902,3429,3243,135,546,1076,689,4466,3296,4347,3680,2127,4453,4008,4952,3106,1400,3588,581,4456,11,3065,3300,2532,1338,3320,3436,197,3710,4699,3297,2259,3640,1599,4790,3808,4737,681,1717,1708,3236,861},
        55932899049
    },
};

int main() {
	Solution s;
	int idx = 0;
	for (auto& [skills, manas, expect] : testcases) {
		auto result = s.minTime(skills, manas);
		cout << "Case " << idx++ << ": ";
		if (result == expect) {
			cout << "PASS\n";
		} else {
			cout << "FAIL: " << result << " != " << expect << "\n";
		}
	}
}