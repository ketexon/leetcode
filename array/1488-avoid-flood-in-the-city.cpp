// https://leetcode.com/problems/avoid-flood-in-the-city/description/
#include <vector>
#include <tuple>
#include <unordered_map>
#include <set>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        unordered_map<int, int> last_rain_day;
        // we need to search, insert, and delete efficiently
        set<int> dry_days;

        for(int i = 0; i < rains.size(); ++i) {
            int lake_idx = rains[i];
            if (lake_idx == 0){
                dry_days.insert(i);
                continue;
            }
#if __cplusplus >= 202002L
            if (last_rain_day.contains(lake_idx)) {
#else
			if (last_rain_day.find(lake_idx) != last_rain_day.end()) {
#endif
                auto it = dry_days.lower_bound(
                    last_rain_day[lake_idx]
                );
                if (it == dry_days.end()) {
                    return {};
                }
                rains[*it] = -lake_idx;
                dry_days.erase(it);
            }
            last_rain_day[lake_idx] = i;
        }

        for(int& x : rains) {
            if (x > 0) {
                x = -1;
            } else if (x < 0) {
                x = -x;
            } else {
                x = 1; // dry arbitrary lake
            }
        }

        return rains;
    }
};

vector<tuple<vector<int>, vector<int>>> testcases = {
	{{1,2,3,4}, {-1,-1,-1,-1}},
	{{1,2,0,0,2,1}, {-1,-1,2,1,-1,-1}},
	{{1,2,0,1,2}, {}},
	{{69,0,0,0,69}, {-1,69,1,1,-1}},
	{{10,20,20}, {}},
};

int main() {
	Solution s;
	int test_num = 1;
	for (auto &[rains, expected] : testcases) {
		vector<int> result = s.avoidFlood(rains);
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