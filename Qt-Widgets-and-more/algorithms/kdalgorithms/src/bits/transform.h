#pragma once

#include "shared.h"
#include <algorithm>

namespace kdalgorithms {
namespace detail {
    // Utility function used for meta type programming.
    // See TransformedType for details.
    template <typename ResultItemType, template <typename...> class Container, typename ItemType>
    Container<ResultItemType> replace_item_value_type(const Container<ItemType> &)
    {
    }

    // ResultItemType = resulting type when applying Transform on an item in Container.
#if __cplusplus < 201703L
    template <typename Container, typename Transform>
    using ResultItemType = typename std::result_of<Transform(ValueType<Container>)>::type;
#else
    template <typename Container, typename Transform>
    using ResultItemType = std::invoke_result_t<Transform, ValueType<Container>>;
#endif

    // Given a Container<Input> and a Transform which converts from Input to Output.
    // TransformedType = Container<Output>
    template <typename Container, typename Transform>
    using TransformedType =
        remove_cvref_t<decltype(replace_item_value_type<ResultItemType<Container, Transform>>(
            std::declval<Container>()))>;

    // Version used for l-values or where the container type changes
    template <typename ResultContainer, typename InputContainer, typename Transform>
    ResultContainer transformed(InputContainer &&input, Transform &&transform, std::true_type)
    {
        ResultContainer result;
        result.reserve(input.size());
        std::transform(input.cbegin(), input.cend(), std::back_inserter(result),
                       std::forward<Transform>(transform));
        return result;
    }

    // optimized version to use for r-values where container type is the same
    // in-place editing is possible in that case.
    template <typename ResultContainer, typename InputContainer, typename Transform>
    ResultContainer transformed(InputContainer &&input, Transform &&transform,
                                std::false_type /* r-value and same containers */)
    {
        std::transform(input.begin(), input.end(), input.begin(),
                       std::forward<Transform>(transform));
        return input;
    }

    template <typename ResultContainer, typename InputContainer, typename Transform>
    ResultContainer transformed(InputContainer &&input, Transform &&transform)
    {
        return transformed<ResultContainer>(
            std::forward<InputContainer>(input), std::forward<Transform>(transform),
            std::integral_constant < bool,
            std::is_lvalue_reference<InputContainer>::value
                || !std::is_same<ResultContainer, InputContainer>::value > ());
    }
}

template <typename InputContainer, typename Transform>
auto transformed(InputContainer &&input, Transform &&transform)

{
    using ResultType = detail::TransformedType<InputContainer, Transform>;
    return detail::transformed<ResultType>(std::forward<InputContainer>(input),
                                           std::forward<Transform>(transform));
}

template <template <typename...> class ResultContainer, typename InputContainer, typename Transform>
#if __cplusplus < 201703L
using ResultTypeForTransformed =
    ResultContainer<typename std::result_of<Transform(ValueType<InputContainer>)>::type>;

#else
using ResultTypeForTransformed =
    ResultContainer<std::invoke_result_t<Transform, ValueType<InputContainer>>>;
#endif

template <template <typename...> class ResultContainer, typename InputContainer, typename Transform>
auto transformed(InputContainer &&input, Transform &&transform)
{
    return detail::transformed<
        ResultTypeForTransformed<ResultContainer, InputContainer, Transform>>(
        std::forward<InputContainer>(input), std::forward<Transform>(transform));
}

// -------------------- transform --------------------
template <typename Container, typename UnaryPredicate>
void transform(Container &input, UnaryPredicate &&predicate)
{
    std::transform(std::begin(input), std::end(input), std::begin(input),
                   std::forward<UnaryPredicate>(predicate));
}

} // namespace kdalgorithms
