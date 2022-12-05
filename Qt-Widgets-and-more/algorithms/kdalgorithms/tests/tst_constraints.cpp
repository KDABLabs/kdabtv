#if __cplusplus >= 202002L

#include "../src/kdalgorithms.h"
#include <list>
#include <string>
#include <vector>

using namespace std;

// clang-format off
#define FAIL_2_ARG(name, function, arg1, arg2) \
template <typename T, typename S>\
    void err_##name() { \
        static_assert(!requires(T t, S s){kdalgorithms::function(t, s);});\
}\
\
void test_##name() \
{\
        err_##name<arg1, arg2>();\
}

#define FAIL_3_ARG(name, function, arg1, arg2, arg3) \
template <typename T, typename S, typename U>\
    void err_##name() { \
        static_assert(!requires(T t, S s, U u){kdalgorithms::function(t, s, u);});\
}\
\
void test_##name() \
{\
        err_##name<arg1, arg2, arg3>();\
}
// clang-format on

FAIL_2_ARG(copy, copy, vector<int>, vector<string>)
FAIL_2_ARG(filtered, filtered, vector<int>, function<string(string)>)
FAIL_2_ARG(filtered2, filtered<list>, vector<int>, function<string(string)>)
FAIL_2_ARG(filter, filter, vector<int>, function<string(string)>)
FAIL_2_ARG(contains, contains, vector<int>, string)
FAIL_2_ARG(count, count, vector<int>, string)
FAIL_2_ARG(get_first_match, get_first_match, vector<int>, function<bool(string)>)
FAIL_2_ARG(get_first_match_or_default, get_first_match_or_default, vector<int>,
           function<bool(string)>)
FAIL_2_ARG(count_if_wong_type, count_if, vector<int>, std::function<bool(string)>)
FAIL_2_ARG(count_if_no_return, count_if, vector<int>, std::function<void(int)>)
FAIL_2_ARG(max_element_wrong_predicate, max_element, vector<int>, function<bool(string, string)>)
FAIL_2_ARG(max_element_no_return_value, max_element, vector<int>, function<void(int, int)>)
FAIL_2_ARG(max_element_only_one_arg, max_element, vector<int>, function<bool(int)>)
FAIL_2_ARG(max_value_less_than_wrong_needle, max_value_less_than, vector<int>, string)
FAIL_3_ARG(max_value_less_than_wrong_predicate, max_value_less_than, vector<int>, int,
           function<bool(string, string)>)
FAIL_3_ARG(max_value_less_than_returns_nothing, max_value_less_than, vector<int>, int,
           function<void(int, int)>)
FAIL_3_ARG(max_value_less_than_one_arg, max_value_less_than, vector<int>, int, function<bool(int)>)
FAIL_2_ARG(is_permutation, is_permutation, vector<int>, vector<string>)
FAIL_2_ARG(accumulate_wrong_arg_count, accumulate, vector<int>, function<int(int)>)
FAIL_2_ARG(accumulate_wrong_return_type, accumulate, vector<int>, function<string(int, int)>)

#endif // C++ 20
