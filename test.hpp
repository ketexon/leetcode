#ifndef KET_TEST_HPP
#define KET_TEST_HPP

#define KET_TEST_MAIN(f, test_cases) int main() { run_tests((f), (test_cases)); return 0; }

#include <vector>
#include <tuple>
#include <iostream>

template<
    typename Solution,
    typename Result,
    typename... Args
>
using SolutionFunction = Result(Solution::*)(Args...);

template<
    typename Solution,
    typename Result,
    typename... Args
>
void run_tests(SolutionFunction<Solution, Result, Args...> f, std::vector<std::tuple<std::tuple<Args...>, Result>> test_cases) {
    Solution s;
	int idx = 0;
	for (auto& [test_case, expected] : test_cases) {
		auto result = std::apply(
            f,
            std::tuple_cat(
                std::tuple<Solution&>(s),
                test_case
            )
        );
		cout << "Case " << idx++ << ": ";
		if (result == expected) {
			cout << "PASS\n";
		} else {
			cout << "FAIL: " << result << " != " << expected << "\n";
		}
	}
};

#endif