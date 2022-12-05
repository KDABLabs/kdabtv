#pragma once

#include "has_reserve_trait.h"
#include "shared.h"
#include <algorithm>
#include <functional>
#include <iterator>

namespace kdalgorithms {
namespace detail {
    template <typename ResultContainer, typename InputContainer, typename UnaryPredicate>
    ResultContainer filtered(InputContainer &&input, UnaryPredicate &&predicate)
    {
        ResultContainer result;
#if __cplusplus >= 201703L
        if constexpr (traits::has_reserve_method_v<ResultContainer>) {
            result.reserve(input.size());
        }
#endif
        auto range = copy_or_move_iterators(std::forward<InputContainer>(input));
        std::copy_if(range.begin, range.end, std::back_inserter(result),
                     std::forward<UnaryPredicate>(predicate));
        return result;
    }
}

template <typename Container, typename UnaryPredicate>
auto filtered(Container &&input, UnaryPredicate &&predicate)
#if __cplusplus >= 202002L
    requires UnaryPredicateOnContainerValues<UnaryPredicate, Container>
#endif
{
    return detail::filtered<remove_cvref_t<Container>>(std::forward<Container>(input),
                                                       std::forward<UnaryPredicate>(predicate));
}

template <template <typename...> class ResultContainer, typename InputContainer,
          typename UnaryPredicate>
ResultContainer<ValueType<InputContainer>> filtered(InputContainer &&input,
                                                    UnaryPredicate &&predicate)
#if __cplusplus >= 202002L
    requires UnaryPredicateOnContainerValues<UnaryPredicate, InputContainer>
#endif
{
    return detail::filtered<ResultContainer<ValueType<InputContainer>>>(
        std::forward<InputContainer>(input), std::forward<UnaryPredicate>(predicate));
}

// -------------------- filter --------------------
template <typename Container, typename UnaryPredicate>
void filter(Container &input, UnaryPredicate &&predicate)
#if __cplusplus >= 202002L
    requires UnaryPredicateOnContainerValues<UnaryPredicate, Container>
#endif
{
#if __cplusplus < 201703L
    auto it = std::remove_if(begin(input), end(input),
                             [&predicate](const ValueType<Container> &v) { return !predicate(v); });
#else
    auto it = std::remove_if(begin(input), end(input),
                             std::not_fn(std::forward<UnaryPredicate>(predicate)));
#endif
    input.erase(it, end(input));
}

} // namespace kdalgorithms
