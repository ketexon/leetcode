#ifndef KET_TEST_HPP
#define KET_TEST_HPP

#define KET_TEST_MAIN(f, test_cases) int main() { run_tests((f), (test_cases)); return 0; }

#include <vector>
#include <tuple>
#include <iostream>

template<
    typename TSolution,
    typename TResult,
    typename... TArgs
>
using SolutionFunction = TResult(TSolution::*)(TArgs...);


template<typename... TArgs>
using FirstArg = std::tuple_element_t<0, std::tuple<TArgs...>>;

template<typename... TArgs>
using TestCaseArgs = std::conditional_t<
    (sizeof...(TArgs) > 1),
    std::tuple<std::remove_cvref_t<TArgs>...>,
    std::remove_cvref_t<FirstArg<TArgs...>>
>;


template<typename TResult, typename... TArgs>
using TestCase = std::tuple<TestCaseArgs<TArgs...>, TResult>;


template<
    typename TSolution,
    typename TResult,
    typename... TArgs
>
TResult run_test_case(
    SolutionFunction<TSolution, TResult, TArgs...> f,
    TestCaseArgs<TArgs...>& args
) {
    TSolution s;
    if constexpr (sizeof...(TArgs) > 1) {
        return std::apply(
            f,
            std::tuple_cat(
                std::tuple<Solution&>(s),
                args
            )
        );
    } else {
        return (s.*f)(args);
    }
}


template<
    typename TSolution,
    typename TResult,
    typename... TArgs
>
void run_tests(
    SolutionFunction<TSolution, TResult, TArgs...> f,
    std::vector<TestCase<TResult, TArgs...>> test_cases
) {
	int idx = 0;
	for (auto& [args, expected] : test_cases) {
        auto result = run_test_case(f, args);
		cout << "Case " << idx++ << ": ";
		if (result == expected) {
			cout << "PASS\n";
		} else {
			cout << "FAIL: " << result << " != " << expected << "\n";
		}
	}
};

#endif