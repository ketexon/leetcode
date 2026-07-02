#ifndef KET_TEST_HPP
#define KET_TEST_HPP

#define KET_TEST_MAIN(f, test_cases) int main() { run_tests((f), (test_cases)); return 0; }
#define KET_TEST_MAIN_EQ(f, test_cases, eq) int main() { run_tests((f), (test_cases), (eq)); return 0; }

#include <vector>
#include <tuple>
#include <iostream>
#include <print>

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
        auto all_args = std::tuple_cat(
            std::tuple<Solution&>(s),
            args
        );
        return std::apply(f, all_args);
    } else {
        return (s.*f)(args);
    }
}


template<
    typename TElem = void,
    typename TComp = std::equal_to<TElem>
>
struct CompVectorUnsorted {
    TComp comp;
    CompVectorUnsorted() : comp{} {}
    CompVectorUnsorted(auto&& comp) : comp{comp} {}

    bool operator()(auto& a, auto& b) {
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        auto it_a = a.begin();
        auto it_b = b.begin();
        while(true) {
            bool a_ended = it_a == a.end();
            bool b_ended = it_b == b.end();
            if (a_ended || b_ended) {
                return a_ended && b_ended;
            }

            if (!comp(*it_a, *it_b)) {
                return false;
            }
            ++it_a;
            ++it_b;
        }
        return true;
    }
};


template<
    typename TSolution,
    typename TResult,
    typename... TArgs
>
void run_tests(
    SolutionFunction<TSolution, TResult, TArgs...> f,
    std::vector<TestCase<TResult, TArgs...>> test_cases
) {
	run_tests(
        f,
        test_cases,
        std::equal_to<>{}
    );
};

template<
    typename TSolution,
    typename TResult,
    typename... TArgs
>
void run_tests(
    SolutionFunction<TSolution, TResult, TArgs...> f,
    std::vector<TestCase<TResult, TArgs...>> test_cases,
    auto comp
) {
	int idx = 0;
	for (auto& [args, expected] : test_cases) {
        auto result = run_test_case(f, args);
        std::print("Case {}: ", idx++);
		if (comp(result, expected)) {
			std::println("PASS");
		} else {
			std::println("FAIL: {} {}", result, expected);
		}
	}
};

#endif