#pragma once
#include <iterator>
#include <tuple>
#include <type_traits>

namespace kdalgorithms {

namespace detail {
    template <typename Iterator>
    struct IteratorPair
    {
        Iterator begin;
        Iterator end;
    };

    template <typename Iterator>
    auto make_iteratorPair(Iterator begin, Iterator end)
    {
        return IteratorPair<Iterator>{begin, end};
    }

    // used for l-value containers
    template <typename Container>
    auto copy_or_move_iterators_helper(const Container &container, std::true_type)
    {
        return make_iteratorPair(container.cbegin(), container.cend());
    }

    // used for r-value containers
    template <typename Container>
    auto copy_or_move_iterators_helper(Container &&container, std::false_type)
    {
        return make_iteratorPair(std::make_move_iterator(container.begin()),
                                 std::make_move_iterator(container.end()));
    }
}

// Depending on the value type of container - either l-value or r-value
// return iterators that either copy elements out or that move elements out.
template <typename Container>
auto copy_or_move_iterators(Container &&container)
{
    return detail::copy_or_move_iterators_helper(
        std::forward<Container>(container), typename std::is_lvalue_reference<Container>::type());
}

} // namespace kdalgorithms
