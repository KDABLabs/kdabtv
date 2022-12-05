#pragma once
#include <type_traits>

namespace kdalgorithms {
namespace traits {

    namespace detail {
        template <typename T>
        struct class_with_call_operator;

        // For const operator()
        template <typename ClassType, typename ResultType, typename... Args>
        struct class_with_call_operator<ResultType (ClassType::*)(Args...) const>
        {
            using result_type = ResultType;
        };

        // For non-const operator()
        template <typename ClassType, typename ResultType, typename... Args>
        struct class_with_call_operator<ResultType (ClassType::*)(Args...)>
        {
            using result_type = ResultType;
        };
    }

    template <typename T>
    struct return_type_of;

    template <typename ClassType, typename ResultType, typename... Args>
    struct return_type_of<ResultType (ClassType::*)(Args...) const>
    {
        using result_type = ResultType;
    };

    template <typename ResultType, typename... Args>
    struct return_type_of<ResultType(Args...)>
    {
        using result_type = ResultType;
    };

    template <typename T>
    struct return_type_of : detail::class_with_call_operator<decltype(&T::operator())>
    {
    };

    template <typename T>
    using return_type_of_t = typename return_type_of<
        typename std::remove_const<typename std::remove_reference<T>::type>::type>::result_type;
} // namespace traits
} // namespace kdalgorithms
